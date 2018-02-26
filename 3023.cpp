#include <iostream>
using namespace std;

int main()
{
	int n,i,j;
	int a[101];
	int f1[101];
	int f2[101];
	cin >> n;
	for (i = 1;i <= n;i++)
		cin >> a[i];
	for (i = 1;i <= n;i++)
	{
		f1[i] = 1;
		for (j = 1;j<i;j++)
		{
			if (a[i]>a[j] && f1[i]<f1[j] + 1)
				f1[i] = f1[j] + 1;
		}
	}
	for (int i = n;i >= 1;i--)
	{
		f2[i] = 1;
		for (int j = i + 1;j <= n;j++)
		{
			if (a[i]>a[j] && f2[i]<f2[j] + 1)
				f2[i] = f2[j] + 1;
		}
	}

	int ans = 0;
	for (int i = 1;i <= n;i++)
		if (ans<f1[i] + f2[i] - 1)
			ans = f1[i] + f2[i] - 1;
	cout << n - ans << endl;

	return 0;
}
