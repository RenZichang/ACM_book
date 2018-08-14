#include<iostream>
#include<algorithm>
using namespace std;
struct treasure
{
    int volume;
    int price;
    int number;
}enu{ 0, 0, 0 }, oth{ 0, 0, 0 };
int main()
{
    cout << "箱子体积N:";
    int N;
    cin >> N;
    int V[2], S[2];
    cout << "宝藏1的体积V1和价值S1:";
    cin >> V[0] >> S[0];
    cout << "宝藏2的体积V2和价值S2:";
    cin >> V[1] >> S[1];
    int n = (V[1]*S[0] > V[0]*S[1]) ? 1 : 0;		//谁价值密度小，就穷举谁
    int maxNum = min(N / V[n], V[int(!n)] - 1);		//最小穷举数
    enu.volume = V[n], enu.price = S[n];
    oth.volume = V[int(!n)], oth.price = S[int(!n)];
    int price = enu.number * enu.price + oth.number * oth.price;
    for (int i = 0; i < maxNum; i++)
    {
	int priceNow = i*enu.price + (N-enu.volume*i) / oth.volume * oth.price;
	if (price < priceNow)		//更优解
	{
	    enu.number = i;
	    oth.number = (N-enu.volume*i)/oth.volume;
	    price = priceNow;
	}
    }
    if (n == 1)
	goto __1__;
__2__:
    cout << "宝藏" << n + 1 << "拿" << enu.number << "个" << endl;
    if (n == 1)
	goto __3__;
__1__:
    cout << "宝藏" << int(!n) + 1 << "拿" << oth.number << "个" << endl;
    if (n == 1)
	goto __2__;
__3__:
    cout << "总价值为:" << price << endl;
    return 0;
}
