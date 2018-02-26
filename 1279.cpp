#include<iostream>
#include<string.h>
using namespace std;
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

//ц╟ещ
int* BubbleSort(int* ary, int length)
{
	int i, j, tmp;
	for (i = 0; i<length - 1; i++)
	{
		tmp = ary[i];

		for (j = length - 1; j>i; j--)
		{

			if (tmp > ary[j])
			{
				ary[i] = ary[j];
				ary[j] = tmp;
				tmp = ary[i];
			}
		}
	}

	return ary;
}



void Print(int x)
{
	int i;
	char tmp[7] = {'0'};
	for (i = 0;i < 7;++i)
	{
		tmp[6-i] = '0' + x % 10;
		x /= 10;
	}
	for(i=0;i<=2;++i)
		cout << tmp[i];
	cout << '-';
	for(i=3;i<7;++i)
		cout << tmp[i];
}

int main()
{
	int N,i,j,digit,z,*tel,last,count,flag=0;
	char *tmp;
	cin >> N;
	tel = new int [N];

	cin.get();
	for (i = 0;i < N;++i)
	{
		tmp = new char[50];
		cin >> tmp;
		cin.get();
		z=0;
		for (j = 0;j < strlen(tmp);++j)
		{
			if (tmp[j] <= '9'&&tmp[j] >= '0')
			{
				digit = tmp[j] - '0';	
				z = 10 * z + digit;
			}
				
			else
				if (tmp[j] <= 'O' && tmp[j] >= 'A')
				{
					digit = (tmp[j] - 'A') / 3 + 2;
					z = 10 * z + digit;
				}
				else
					if (tmp[j] <= 'S' && tmp[j] >= 'P')
					{
						digit = 7;
						z = 10 * z + digit;
					}
					else
						if (tmp[j] <= 'Y' && tmp[j] >= 'T')
						{
							digit = (tmp[j] - 'T') / 3 + 8;
							z = 10 * z + digit;
						}
			
		}

		tel[i] = z;
		delete [] tmp;
	}

	quickSort(tel,0,N-1);

	last = tel[0];
	count = 1;

	for (i = 1;i < N;++i)
	{
		if (tel[i] != last)
		{
			if (count > 1)
			{
				Print(last);
				cout << ' ' << count << endl;
				count = 1;
				flag = 1;
			}
			last = tel[i];
		}
		
		else
			count++;
	}
		
	if (count > 1)
	{
		Print(last);
		cout << ' ' << count << endl;
		count = 1;
		flag = 1;
	}

	if(!flag)
		cout << "No duplicates.\n";

	delete [] tel;

	return 0;
}