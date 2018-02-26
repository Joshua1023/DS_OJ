#include<iostream>
#include<math.h>
using namespace std;

struct node {
	long long pos;
	long long height;
	node(){}
	node(long long p, long long h)
	{
		pos = p;
		height = h;
	}
	node(const node &x)
	{
		pos = x.pos;
		height = x.height;
	}
};

void quickSort(node * s , int l, int r)
{
	if (l< r)
	{
		int i = l, j = r;
		node x = s[l];
		while (i < j)
		{
			while (i < j && s[j].pos >= x.pos)
				j--;
			if (i < j)
				s[i++] = s[j];
			while (i < j && s[i].pos < x.pos)
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
	long long x, h,maxH=0;
	long long D;
	int N, i, j, cnt = 0;
	int flag;

	cin >> N >> D;
	node *cows = new node[N];
	for (i = 0;i < N;++i)
	{
		cin >> x >> h;
		cows[i] = node(x,h);
		if(h > maxH)
			maxH = h;
	}

	quickSort(cows,0,N - 1);

	for (i = 0;i < N;++i)
	{
		if(cows[i].height > maxH / 2)
			continue;
		flag = 0;
		for (j = i - 1;j >= 0 && cows[i].pos - cows[j].pos <= D;--j)
		{
			if (cows[j].height >= 2 * cows[i].height)
			{
				flag++;
				break;
			}
		}
		if(flag == 1)
			for (j = i + 1;j < N && cows[j].pos - cows[i].pos <= D;++j)
			{
				if (cows[j].height >= 2 * cows[i].height)
				{
					flag++;
					break;
				}
			}
		if (flag == 2)
			cnt++;
	}

	cout << cnt << endl;

	return 0;
}
