#include<iostream>
#include<set>
#include<cstring>
using namespace std;

//State是一个含有9个int元素的数组
typedef int State[9];
//st是状态数组，goal是目标状态，father是每个状态节点的父节点的下标，用于打印
const int size = 1000000;
State st[size], goal;
int father[size];
//dist是距离数组
int dist[size];
//移动x和y坐标用于提供方便的数组
int mv_x[4] = { 0, 0, -1, 1 };
int mv_y[4] = { -1, 1, 0, 0 };
//STL集合，用于判重
set<int> vis;
//注意上面的节点、路径、距离等等都是针对解答树而言的

int bfs();
void init_lookup_table();
bool try_to_insert(int);


int main()
{
    cout << "请输入魔板初始状态:" << endl;
    for (int i = 0; i < 9; i++)
	cin >> st[1][i];
    cout << "请输入魔板最终状态:" << endl;
    for (int i = 0; i < 9; i++)
	cin >> goal[i];
    int answer = bfs();
    if (answer == -1)
	cout << "没有找到变换方法!" << endl;
    else
    {
	cout << "需要" << dist[answer] << "步." <<endl;
	cout << "是否打印路径?(y/n)" << endl;
	char judge;
	cin >> judge;
	if (judge == 'y' || judge == 'Y')
	{
	    int len = dist[answer];
	    int *temp = new int[len];
	    for (int i = len - 1; i >= 0; i--)
	    {
		temp[i] = answer;
		answer = father[answer];
	    }
	    for (int i = 0; i < len; i++)
	    {
		for (int j = 0; j < 3; j++)
		{
		    for (int k = 0; k < 3; k++)
			cout << st[temp[i]][j * 3 + k] << ' ';
		    cout << endl;
	        }
		cout << "--.--\n";
	    }
	    delete []temp;
	}
    }
    return 0;
}
int bfs()
{
    init_lookup_table();
    int front = 1, rear = 2;		//头尾指针
    while (front < rear)
    {
	if (memcmp(goal, st[front], sizeof(goal)) == 0)
	    return front;
	int zero_pos = 0;
	for (int i = 0; i < 9; i++)	//先找到front指针 所指向的 状态 中 0所在的位置
	    if (st[front][i] == 0)
	    {
		zero_pos = i;
		break;
	    }
	int x = zero_pos / 3;
	int y = zero_pos % 3;		//确定0所在处的横纵坐标
	for (int i = 0; i < 4; i++)
	{
	    int new_x = x + mv_x[i];			//移动
	    int new_y = y + mv_y[i];
	    int new_zero_pos = new_x * 3 + new_y;
	    if (new_x >= 0 && new_x <= 2 && new_y >= 0 && new_y <= 2)		//移动合法
	        {
		    memcpy(&(st[rear]), &(st[front]), sizeof(st[front]));	//扩展节点
		    father[rear] = front;					//记录父节点
	            st[rear][new_zero_pos] = st[front][zero_pos];
		    st[rear][zero_pos] = st[front][new_zero_pos];
		    dist[rear] = dist[front] + 1;				//更新距离数组(解答树)
		    if (try_to_insert(rear))			//rear指向的状态 没有重复，则尾指针自增
			rear++;
		}
	}
	front++;			//扩展完毕，继续以下一个状态为出发点，搜索解答树
    }
    return -1;				//1000000种状态全部找过了，没有发现答案，查找失败
}
void init_lookup_table()
{
    vis.clear();
}
bool try_to_insert(int rear)
{
    int v = 0;
    for (int i = 0; i < 9; i++)
	v = v * 10 + st[rear][i];
    if (vis.count(v))
	return false;
    vis.insert(v);
    return true;
}
