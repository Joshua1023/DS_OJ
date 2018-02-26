#include<iostream>
using namespace std;

void quickSort(int s[], int l, int r)
{
	if (l< r)
	{
		int i = l, j = r, x = s[l];
		while (i < j)
		{
			while (i < j && s[j] >= x)
				j--;
			if (i < j)
				s[i++] = s[j];
			while (i < j && s[i]< x)
				i++;
			if (i < j)
				s[j--] = s[i];
		}
		s[i] = x;
		quickSort(s, l, i - 1);
		quickSort(s, i + 1, r);
	}
}

int main()
{
	int i,n,tmp,cnt = 0;
	cin >> n;
	int *p = new int[n];
	cin >> p[0];
	for (i = 1;i < n;++i)
	{
		cin >> tmp;
		p[i] = tmp + p[i - 1];
	}
	
	int half = p[n - 1] / 2;  //得到半圆周长

	i = n - 1;
	while (p[i] > half)   //所有位置大于半圆周长的选手位置减去半圆周长
	{
		p[i] -= half;
		i--;
	}

	quickSort(p,0,n - 1);//重新排序
	for (i = 0;i < n - 1;++i)//统计重复数字
	{
		if (p[i] == p[i + 1])
		{
			cnt++;
			++i;
		}
	}

	cout << cnt * (cnt - 1) / 2 << endl; //nC2

	return 0;
}