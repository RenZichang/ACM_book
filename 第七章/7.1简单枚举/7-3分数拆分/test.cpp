#include<iostream>
#include<cmath>
#define Error 0.0001
using namespace std;


int main()
{

	int k;
	int count = 0;
	cin >> k;
	//x>=y，所以y应该从k+1到2k
	for (int y = k + 1; y <= 2 * k; ++y)
		{
			double x = (k * y) / (y - k);
			if (abs(x - int(x + 0.5)) <= Error)
			{
				cout << "1/" << k << " = 1/" << x << " + 1/" << y << endl;
				++count;
			}
		}
	return 0;
}
