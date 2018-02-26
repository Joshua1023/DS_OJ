#include <iostream>
using namespace std;

int prenode[1002];
int num[350] = { 0 };
int len = 1;

void mul2(int power) {
	num[0] = 1;

	for (int i = 0; i < power; ++i)
	{
		int r = 0;
		int ori_len = len;
		for (int j = 0; j < ori_len; ++j)
		{
			int tmp = num[j] * 2 + r;
			r = 0;
			num[j] = (tmp) % 10;

			if (tmp >= 10) {
				r = (tmp) / 10;
			}
		}
		if (r != 0)
			num[len++] = r;
	}
}

int find(int x)
{
	int res = x;
	while (res != prenode[res]) 
	{
		res = prenode[res];
	}
	
	while (x != res) 
	{
		int pre = prenode[x];
		prenode[x] = res;
		x = pre;
	}
	return res;
}

void join(int x, int y) 
{
	int rootx = find(x), rooty = find(y);
	if (rootx != rooty)
		prenode[rootx] = rooty;
	return;
}


int main()
{

	int n, m;
	cin >> n >> m;
 
	for (int i = 1; i <= n; ++i)
		prenode[i] = i;

	for (int i = 0; i < m; ++i)
	{
		int x, y;
		cin >> x >> y;
		join(x, y);
	}

	int k = 0;
	for (int i = 1; i <= n; ++i)
		if (prenode[i] == i)
			k++;



	mul2(n - k);
	for (int i = len - 1; i >= 0; --i)
	{
		cout << num[i];
	}
	cout << endl;


	return 0;
}