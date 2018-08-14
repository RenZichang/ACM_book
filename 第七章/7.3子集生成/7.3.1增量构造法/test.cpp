#include<iostream>
using namespace std;
void print_subset(int size, const int *array, int curpos=0);


int main()
{
    cout << "输入数组大小:" << endl;
    int size;
    cin >> size;
    int *const b = new int[size];
    for (int i = 0; i < size; i++)
	b[i] = i;
    print_subset(size, b);
    delete[]b;
    return 0;
}
void print_subset(int size, const int *array, int curpos)
{
    static int *hold = new int[size];
    /*curpos指示的是hold末尾的位置
     * 而尝试添加在hold末尾的元素应该从在array里位于以hold末尾元素为下标的元素的后面中选
     * 故而i的初始值为blabla*/
    for (int i = curpos > 0 ? hold[curpos-1] + 1 : 0; i < size; i++)
    {
	hold[curpos] = i;
	for (int j = 0; j < curpos; j++)
	    cout << array[hold[j]] << ' ';
	cout << array[hold[curpos]] << endl;
	print_subset(size, array, curpos+1);
    }
    if (curpos == 0)
	delete[]hold;
}
