#include<iostream>
using namespace std;

int min(int a, int b)
{
	if(a<b)
		return a;
	else
		return b;
}

int main()
{
	int N, ans,tmp;
	int i, j, num[100], eq;
	bool flag[101] = { false };

	cin >> N;
	for (i = 0;i < N;++i)
	{
		cin >> num[i];
		flag[num[i]] = true;
	}

	ans = N;
	for (i = 0;i < N - 1;++i)
		for (j = i + 1;j < N;++j)
		{
			if (i != j)
			{
				if (num[i] > num[j])
					eq = num[i] / num[j];
				else
					eq = num[j] / num[i];
				if (!flag[eq])
				{
					flag[eq] = true;
					num[ans++] = eq;
				}
			}				
		}

	while (ans != N)
	{
		tmp = N;
		N = ans;
		for (i = 0;i < N - 1;++i)
			for (j= (i+1)>tmp?i+1:tmp;j < N;++j)
			{
				if (i != j)
				{
					if (num[i] > num[j])
						eq = num[i] / num[j];
					else
						eq = num[j] / num[i];
					if (!flag[eq])
					{
						flag[eq] = true;
						num[ans++] = eq;
					}
				}
					
			}
	}

	cout << ans << endl;
	return 0;
}