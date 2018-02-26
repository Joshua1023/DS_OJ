#include<iostream>
#include<stdio.h>
using namespace std;

int N,R;

struct AI {
	int NO;
	int score;
	int power;
	AI(){}
	~AI() {}
};

bool cmp(AI p1, AI p2)
{
	if(p1.score !=  p2.score)
		return p1.score < p2.score;
	else
		return p1.NO > p2.NO;
}

void quickSort(AI array[], int left, int right)
{
	AI tmp;
	if (left < right)
	{
		int i = left - 1, j = right + 1;
		AI mid = array[(left + right) / 2];
		while (true)
		{
			while (cmp(mid,array[++i]));
			while (cmp(array[--j],mid));
			if (i >= j) break;
			tmp = array[i];
			array[i] = array[j];
			array[j] = tmp;
		}
		quickSort(array, left, i - 1);
		quickSort(array, j + 1, right);
	}
}

int main()
{
	int i,j;
	cin >> N >>R;
	AI *l = new AI[2 * N];

	for (i = 0;i < 2 * N;++i)
	{
		scanf("%d",&l[i].score);
		l[i].NO = i + 1;
	}


	for (i = 0;i < 2 * N;++i)
		scanf("%d", &l[i].power);


	for (i = 0;i < R;++i)
	{
		quickSort(l, 0, 2 * N - 1);
		for (j = 0;j < N;++j)
		{
			if(l[2 * j].power > l[2 * j + 1].power)
				l[2 * j].score++;
			else
				l[2 * j + 1].score++;
		}

	}

	quickSort(l, 0, 2 * N - 1);

	for(i = 0;i <= 2 * N - 1;++i)
		printf("%d ",l[i].NO);
	cout << endl;

	delete [] l;

	return 0;
}
