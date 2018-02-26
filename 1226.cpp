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
	int i,j;
	cin >> i;
	int *elem = new int[i];

	for (j = 0;j < i;++j)
	{
		cin >> elem[j];
	}

	quickSort(elem,0,i - 1);
	for (j = 0;j < i;++j)
		cout << elem[j] << ' ';
	cout << endl;

	return 0;
}
