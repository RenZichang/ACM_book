#include<iostream>
using namespace std;
void print_smallband(int size, int **array, int curpos=0);
int ban(const int *hold, int hold_size, int**array, int array_size);


int main()
{
    cout << "请输入节点个数:";
    int size;
    cin >> size;
    cout << "请按行列顺序输入邻接矩阵" << endl;
    int **array = new int*[size];
    for (int i = 0; i < size; i++)
	array[i] = new int[size];
    for (int i = 0; i < size; i++)
	for (int j = 0; j < size; j++)
	    cin >> array[i][j];
    print_smallband(size, array);
}
void print_smallband(int size, int **array, int curpos)
{
    //静态变量mini_len的值为当前最短带宽
    static int mini_len = size;
    //静态变量hold用来保存递归创建的序列
    static int *const hold = new int[size];
    //递归边界，到达这里说明带宽一直是目前情况下最小的
    if (curpos == size)
    {

	mini_len = ban(hold, curpos, array, size);
	for (int i = 0; i < size; i++)
	    cout << hold[i] << ' ';
	cout << "len: " << mini_len;
    }
    //尝试向hold末尾添加元素
    for (int i = 0; i < size; i++)
    {
	bool used = false;
	for (int j = 0; j < curpos; j++)
	    if (hold[j] == i)
	    {
		used = true;
		break;
	    }
	if (used)
	    continue;
	hold[curpos] = i;
	//获取当前的带宽
	int len = ban(hold, curpos+1, array, size);
	//若更长，则停止递归，继续循环，尝试添加下一个元素
	if (len >= mini_len)
	    continue;
	else
	    print_smallband(size, array, curpos+1);
    }
}
int ban(const int *hold, int hold_size, int**array, int array_size)
{
    //外层循环，从第一个开始到hold结束统计当前位置的节点到其后面的与之相连通的节点之间的带宽
    int len = hold_size;
    for (int i = 0; i < hold_size; i++)
    {
	for (int j = i; j < hold_size; j++)
	{
	    //连通取最长
	    if (array[hold[i]][hold[j]])
		len = len > (j-i) ? len : (j-i);
	}
    }
    return len;
}
