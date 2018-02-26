#include <iostream>
#include<stdio.h>
using namespace std;

struct Period
{
	int start;
	int end;
};

void quickSort(Period array[], int left, int right)
{
	Period tmp;
	if (left < right)
	{
		int i = left - 1, j = right + 1;
		Period mid = array[(left + right) / 2];
		while (true)
		{
			while (mid.end > array[++i].end);
			while (array[--j].end > mid.end);
			if (i >= j) break;
			tmp = array[i];
			array[i] = array[j];
			array[j] = tmp;
		}
		quickSort(array, left, i - 1);
		quickSort(array, j + 1, right);
	}
}

Period ps[100001];

int main()
{

	int n;
	cin >> n;
	for (int i = 0; i < n; ++i)
	{
		scanf("%d%d",&ps[i].start, &ps[i].end);
	}

	quickSort(ps,0,n - 1);

	int ans = 1;
	int cur = ps[0].end;
	for (int i = 1; i < n; ++i)
	{
		if (ps[i].start >= cur)
		{
			cur = ps[i].end;
			ans++;
		}
	}

	cout << ans << endl;

	return 0;
}
