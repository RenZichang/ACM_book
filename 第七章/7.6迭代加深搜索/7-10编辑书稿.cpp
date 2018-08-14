#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;


bool bdfs(int depth);
int nError(int depth);					//启发函数,统计ans[depth]中后缀错误的段落的个数
bool diff(int depth);					//统计当前深度之前有没有重复的情况(属于本递归分枝)
void edit(int size, int from, int to, int depth);	//剪切粘贴一次,结果放在ans[depth]中


int maxd;
int *ans[9];			//ans[0]存储初始状态,总共递归深度不超过8,所以申请9个空间.每个ans元素都指向一个待申请的动态数组
int n;				//n表示每个ans元素数组大小


int main()
{
    cout << "输入自然段个数(2~9):";
    cin >> n;
    for (int i = 0; i < 9; i++)
	ans[i] = new int[n];
    cout << "输入初始状态:" << endl;
    for (int i = 0; i < n; i++)
	cin >> ans[0][i];
    if (nError(0) == 0)
	goto sb;
    for (maxd = 1; maxd <= 8; maxd++)
    {
	if (bdfs(1))
	{
sb:	    cout << endl;
	    for (int i = 0; i <= maxd; i++)
	    {
		for (int j = 0; j < n-1; j++)
    		    cout << ans[i][j] << ' ';
	        cout << ans[i][n-1] << endl;
	    }    
	    break;
	}
    }
    for (int i = 0; i < 9; i++)
	delete[](ans[i]);
    return 0;
}
bool bdfs(int depth)
{
    if (depth == maxd+1)					//当前深度已经到达maxd+1,可以终止这里的递归了
	return false;
    for (int size = 1; size <= n/2; size++)			//在当前递归深度处尝试剪切size个
    {
	for (int from = 0; from <= n-size; from++)			//from表示从哪里剪切
	    for (int to = 0; to <= n-size; to++)			//to表示插入的位置
		if (from == to)
		    continue;
		else
		{
		    memcpy(ans[depth], ans[depth-1], sizeof(int)*n);
		    edit(size, from, to, depth);
		    int ne = nError(depth);
		    if (ne == 0)				//如果已经找到最优解,直接返回true即可
			return true;
		    if (ne > 3*(maxd-depth))			//如果剩下的几次全部是最优化情况,仍然不能理顺,则不需递归
			continue;
		    if (!diff(depth))				//判重
			continue;
		    if (bdfs(depth+1))				//递归,如果找到一解,直接返回即可
			return true;
		}
    }
    return false;
}
void edit(int size, int from, int to, int depth)
{
    int *ctrlX = new int[size];
    int *remain = new int[n-size];
    memcpy(ctrlX, &(ans[depth][from]), sizeof(int)*size);
    memset(&(ans[depth][from]), 0, sizeof(int)*size);
    for (int i = 0, j = 0; i < n; i++)
    {
	if (!ans[depth][i])		//跳过ctrlX粘贴了的地方
	    continue;
	remain[j++] = ans[depth][i];
    }
    for (int i = 0; i < to; i++)
	ans[depth][i] = remain[i];
    for (int i = 0; i < size; i++)
	ans[depth][i+to] = ctrlX[i];
    for (int i = to; i < n-size; i++)
	ans[depth][i+size] = remain[i];
    delete[]remain;
    delete[]ctrlX;
}
bool diff(int depth)
{
    for (int i = 0; i < depth; i++)
	if (memcmp(ans[depth], ans[i], sizeof(int)*n) == 0)
	    return false;
    return true;
}
int nError(int depth)
{
    int count = 0;
    for (int i = 0; i < n-1; i++)
	if (ans[depth][i+1] - ans[depth][i] != 1)
	    count++;
    return count;
}
