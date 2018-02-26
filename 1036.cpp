#include<iostream>
using namespace std;

long long max(long long a, long long b, long long c)
{
	b = (b>c ? b : c);
	return (a>b ? a : b);
}


int main()
{
	long long num_people,i,j,k,tmp,W,T,T1=0,T2=0,T3=0;
	int *time;

	cin >> num_people;
	time = new int[num_people];

	for (i = 0;i < num_people;++i)
	{
		cin >> tmp;
		time[i] = tmp;
	}
	
	W = 0;
	T = 0;
	i = 0;
	j = 1;
	k = 2;
	while (i < num_people || j < num_people || k < num_people)
	{
		if (i < num_people)
		{
			W += T1;
			T1+= time[i];
			i += 3;
		}
			


		if (j < num_people)
		{
			W += T2;
			T2 += time[j];
			j += 3;
		}


		if (k < num_people)
		{
			W += T3;
			T3 += time[k];
			k += 3;
		}
	}

	T = max(T1,T2,T3);
	cout << W << ' ' << T << endl;

	W = 0;
	T = 0;
	
	long long sum[3] = { 0 },t;
	i = 0;
	while (i < num_people)
	{
		t = (sum[1] <= sum[2] ? 1 : 2);
		t = (sum[0] <= sum[t] ? 0 : t);
		W+=sum[t];
		sum[t] += time[i];
		++i;
	}
	T = max(sum[0], sum[1], sum[2]);
	cout << W << ' ' << T << endl;
	
	delete [] time;

	return 0;
}