#include<iostream>
#include<stdio.h>
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
	int M,N,i,layer = 1, cnt = 0;
	long long WPL = 0;
	cin >> N >> M;
	int *F = new int[N], *b = new int[N];



	for(i = 0;i < N;++i)
		scanf("%d",&F[i]);

	quickSort(F,0,N - 1);

	int fi = 0,bi = 0,blen = 0,num,sum;
	bool first = true;
	while (N - fi + blen - bi > 1)
	{
		num = 0;
		if (first)
		{
			if((N - M) % (M - 1) == 0)
				num = M;
			else
				num = (N - M) % (M - 1) + 1;
			first  = false;
		}
		else
			num = M;
		sum = 0;
		while (num--)
		{
			if (fi == N)
			{
				sum += b[bi];
				bi++;
			}
			else if (bi == blen)
			{
				sum += F[fi];
				fi++;
			}
			else if (F[fi] < b[bi])
			{
				sum += F[fi];
				fi++;
			}
			else
			{
				sum += b[bi];
				bi++;
			}
		}
		WPL += sum;
		b[blen++] = sum;
	}
	cout << WPL << endl;
	delete [] F;
	delete [] b;

	return 0;
}
