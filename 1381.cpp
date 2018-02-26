#include <iostream>
using namespace std;
//从0到9耗费的牙签数
int cost[10] = { 6,2,5,5,4,5,6,3,7,6 };
struct num
{
	int n;//用于计算的数
	int c;//耗费的牙签
};

num v[100000];
int main()
{

	int v_size = 0;
	//一位数
	for (int i = 0; i <= 9; ++i)
	{
		num t;
		t.n = i;
		t.c = cost[i];
		v[t.n] = t;
	}
	//两位数
	for (int i = 1; i <= 9; ++i)
	{
		for (int j = 0; j <= 9; ++j)
		{
			num t;
			t.n = i * 10 + j;
			t.c = v[i].c + v[j].c;
			v[t.n] = t;
		}
	}
	//三位数
	for (int i = 1; i <= 9; ++i)
	{
		for (int j = 0; j <= 9; ++j)
		{
			for (int k = 0; k <= 9; ++k) {
				num t;
				t.n = i * 100 + j * 10 + k;
				t.c = v[i].c + v[j].c + v[k].c;
				v[t.n] = t;
			}
		}
	}

	int total = 0; //一共的答案数
	cin >> total;
	int ans = 0;
	//枚举A - B 计算C 和 cost
	for (int i = 999; i >= 0; --i)
	{
		for (int j = 0; j <= i; ++j)
		{
			int k = v[i].n - v[j].n;
			int cost = 3 + v[i].c + v[j].c + v[k].c;
			if (cost == total) 
			{
				ans++;
			}
		}
	}
	cout << ans << endl;

	return 0;
}