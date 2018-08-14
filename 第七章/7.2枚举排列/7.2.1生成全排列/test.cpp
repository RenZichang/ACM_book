#include<iostream>
using namespace std;
template<class t>
void print_permutation(t *array, int size, int curpos=0);


int main()
{
    cout << "输入数组长度(不超过26):";
    int size;
    cin >> size;
    char *buffer = new char[size];
    for (int i = 0; i < size; i++)
	buffer[i] = i + 'A';
    print_permutation(buffer, size);
    delete []buffer;
}
template<class t>
void print_permutation(t *array, int size, int curpos)
{
    //这个数组是用来在末尾递归添加元素的
    static t *hold = new t [size];
    //循环尝试在hold末尾添加array的元素
    for (int i = 0; i < size; i++)
    {
	bool used = false;
        //检测待添加元素是否已经在hold之前的位置出现过
	for (int j = 0; j < curpos; j++)
	    if (hold[j] == array[i])
	    {
		used = true;
		break;
	    }
	if (used)
	    continue;
	hold[curpos] = array[i];
	//递归边界
	if (curpos == size - 1)
	{
	    for (int k = 0; k < size - 1; k++)
		cout << hold[k] << ' ';
	    cout << hold[size-1] << endl;
	}
	else
	    print_permutation(array, size, curpos+1);
    }
    //释放动态分配的空间hold
    if (curpos == 0)
	delete []hold;
}
