#include<iostream>
#include<iomanip>
using namespace std;


bool judge(int, int);
int main()
{       
        int n;
        cin >> n;
	cout << setfill('0');
        for (int j = 01234; j <= 50000; ++j)
        {
                int i = j * n;
                if (judge(i, j))
                        cout << setw(5) << i << " / " << setw(5) << j << " = " << n << endl;
        }
        return 0;
}
bool judge(int a, int b)
{
	//拆分数字
	int hold[10];
	for (int i = 0; i < 5; ++i)
	{
		hold[i] = b % 10;
		b /= 10;
	}
        for (int i = 5; i < 10; ++i)
        {
                hold[i] = a % 10;
                a /= 10;
        }
	//a的位数超过5
	if (a != 0)
		return false;
	//计数数组
	int judge[10] = { 0 };
	for (int i = 0; i < 10; ++i)
		judge[hold[i]]++;
	for (int i = 0; i < 10; ++i)
		//肯定所有的数字使用过而且只使用过一次
		if(judge[i] != 1)
			return false;
	return true;
}
