#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
bool bdfs(int depth, int from, int a, int b);
int getFirst(int a, int b);
bool better(int depth);

const int MaxSize = 100;
int ans[MaxSize], v[MaxSize];			//ans为解集,v为当前解
int maxd;				//设为全局变量,方便

int main()
{
    printf("输入希望拆解的分数:\n");
    int a, b;
    scanf("%d/%d", &a, &b);
    int start = getFirst(a, b);
    for (maxd = 1;; maxd++)
    {
	if (bdfs(0, start, a, b))
	{
	    printf("%d/%d = ", a, b);
	    for (int i = 0; i < maxd; i++)
		printf("1/%d + ", ans[i]);
	    printf("1/%d\n", ans[maxd]);
	    break;
	}
    }
    return 0;
}
int getFirst(int a, int b)
{
    return b / a + 1;
}
bool better(int depth)
{
    for (int i = depth; i >= 0; i--)		//从后往前比较,更加快速
    {
	if (ans[i] != v[i])
	    return (ans[i] == 0) || (v[i] < ans[i]);	//前面的条件是说ans尚为空
    }
}
bool bdfs(int depth, int from, int a, int b)
{
    bool if_ok = false;
    if (depth == maxd)				//若到达最大的搜索深度
    {
        if (b % a)				//不是埃及分数
	    return false;
	v[depth] = b / a;
	if (better(depth))			//如果更优,则更新ans
	    memcpy(ans, v, sizeof(int) * (depth + 1));
	return true;				//已经找到了这一分枝的最优解
    }
    from = max(from, getFirst(a, b));    	//确定迭代的起点
    for (int i = from;; i++)		//尝试所有可以迭代的起点
    {
	if ((maxd+1-depth) * b <= a * i)
	    break;
	v[depth] = i;
	int a_ = a * i - b;
	int b_ = b * i;
	int g_ = __gcd(a_, b_);
	if (bdfs(depth+1, i+1, a_/g_, b_/g_))
	    if_ok = true;
    }
    return if_ok;
}
