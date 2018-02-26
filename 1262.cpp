#include <iostream>
#include <stdlib.h>
using namespace std;

struct car
{
	int start;
	int end;
};
car cars[5001];
car newcars[5001];

void quickSort(car s[], int l, int r)
{
	if (l< r)
	{
		int i = l, j = r;
		car x = s[l];
		while (i < j)
		{
			while (i < j && s[j].start >= x.start)
				j--;
			if (i < j)
				s[i++] = s[j];
			while (i < j && s[i].start < x.start)
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

	int N,i;
	cin >> N;
	for (i = 0; i < N; ++i)
		cin >> cars[i].start >> cars[i].end;
	int maxIN = 0, maxOUT = 0;
	quickSort(cars,0,N - 1);
	int newN = 0;
	newcars[newN].start = cars[0].start;
	newcars[newN].end = cars[0].end;


	for (i = 1; i < N; ++i)
	{
		if (cars[i].start <= newcars[newN].end && cars[i].end >= newcars[newN].end) {
			newcars[newN].end = cars[i].end;
		}
		else if (cars[i].start >= newcars[newN].start && cars[i].end <= newcars[newN].end)
			continue;
		else {
			newN++;
			newcars[newN].start = cars[i].start;
			newcars[newN].end = cars[i].end;
		}
	}
	for (i = 0; i <= newN; ++i)
	{
		int period = (newcars[i].end - newcars[i].start);
		if (period > maxIN)
			maxIN = period;
	}
	//maxOUT
	for (int i = 1; i <= newN; ++i)
	{
		int interval = newcars[i].start - newcars[i - 1].end;
		if (interval > maxOUT)
			maxOUT = interval;
	}
	cout << maxIN << " " << maxOUT << endl;

	return 0;
}
