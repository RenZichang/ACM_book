#include<iostream>
#include<cstring>
#include<set>
using namespace std;
const int MaxSize = 1000000;

void rotate(int tar, int direct);			//操作函数
void bfs(int number);					//宽度优先遍历解答树
bool found(int tar, int number);			//不谈
bool tryToInsert(int tar, int number);			//判重后再添加 函数


struct node						//状态节点，state是四条带子，pos是四条带子上的位置
{
    int state[4][7];
    int pos[4];
};
node ans[MaxSize];					//解答树
int dist[MaxSize];					//距离数组
set<int>diffSet;						//判重表


const int greatMoving[8][5] = 				//移动方式表，不仔细想肯定看不懂(#滑稽)
{
    {0, 2, 3, 2, 1},
    {1, 2, 3, 4, 1},
    {2, 0, 1, 2, 0},
    {3, 0, 1, 4, 0},
    {1, 2, 3, 4, 0},
    {0, 2, 3, 2, 0},
    {3, 0, 1, 4, 1},
    {2, 0, 1, 2, 1}
};

int main()
{
    cout << "请按从上到下从左到右顺序输入四条带子上的数字:" << endl;
    node &start = ans[0];				//ans[0]用来存储初始状态
    for (int i = 0; i < 4; i++)
    {
	for (int j = 0; j < 7; j++)
	    cin >> start.state[i][j];
	start.pos[i] = 2;
    }
    for (int i = 1; i <= 3; i++)
	bfs(i);						//搜索不同的数字目标
}
void rotate(int tar, int direct)
{
    int *pos = ans[tar].pos;
    int (*state)[7] = ans[tar].state;
    const int *m = greatMoving[direct];
    if (m[4])
        pos[m[0]] = (pos[m[0]] + 1) % 7;
    else
        pos[m[0]] = (pos[m[0]] - 1) % 7;
    state[m[1]][m[3]] = state[m[0]][pos[m[0]]];
    state[m[2]][m[3]] = state[m[0]][pos[m[0]] + 2];
}
bool tryToInsert(int tar, int number)
{
    int sta = 0;
    int pos = 0;
    node temp;
    memcpy(&temp, &(ans[tar]), sizeof(node));
    for (int i = 0; i < 4; i++)
    {
	for (int j = 0; j < 7; j++)
	{
	    temp.state[i][j] = bool(temp.state[i][j]-number);		//数字number的位置上都变成了0,其它地方均为1
	    if (temp.state[i][j])					//然后再构造二进制数
		sta = sta * 2 + 1;
	    else
		sta *= 2;
	}
    pos = pos * 10 + temp.pos[i];		//构造另一个判断标准
    }
    int t = sta * 10000 + pos;
    if (diffSet.count(t))
	return false;
    else
    {
	diffSet.insert(t);
	return true;
    }
}
bool found(int tar, int number)
{
    for(int i = 0; i < 4; i++)
    {
	int beg = ans[tar].pos[i];
	for (int j = 0; j < 3; j++)
	{
	    int pos = (beg+j) % 7;
	    if (ans[tar].state[i][pos] != number)
		return false;
	}
    } 
    return true;
}
void bfs(int number)
{
    diffSet.clear();
    memset(ans + 1, 0, sizeof(ans));			//清空答案数组
    int front = 0, rear = 1;
    while (front < rear && rear < MaxSize)
    {
	for (int i = 0; i < 8; i++)			//尝试向八个方向旋转
	{
	    memcpy(&(ans[rear]), &(ans[front]), sizeof(node));			//扩展新结点
	    rotate(rear, i);				//旋转!
            if (tryToInsert(rear, number))		//按照数字number判重
	    {
		dist[rear] = dist[front] + 1;		//更新距离数组
                if (found(rear, number))		//已找到
                {
                    cout << "按照" << number << "寻找,需要" << dist[rear] << "次旋转" << endl;
		    return;
		}
		rear++;
	    }
	}
	front++;
    }
    cout << "没有找到!" << endl;
}
