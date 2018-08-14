#include<iostream>
using namespace std;
void print_subset(int, int*);


int main()
{
    cout << "请输入数组大小:";
    int size;
    cin >>size;
    int *buffer = new int[size];
    for (int i = 0; i < size; i++)
	buffer[i] = i;
    print_subset(size, buffer);
    delete []buffer;
    return 0;
}
//接受一个比较随意的数组，生成下标的所有子集
void print_subset(int size, int *buffer)
{
    int count = 0;
    //i就是所有的二进制表示法子集
    for (int i = 0; i < (1 << size); i++)
    {
	//遍历下标序列，找到所有i所表示的子集中的元素
	for (int j = 0; j < size; j++)
	{
	    if (i & (1 << j))
		cout << buffer[j] << ' ';
	}
	count++;
	cout << endl;
    }
    cout << "子集个数为:" << count << endl;
}
