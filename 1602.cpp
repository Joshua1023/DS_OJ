#include<iostream>
using namespace std;

int main()
{
	int len1,len2,len3,pos1,pos2;
	int i;

	cin >> len1 >> len2;
	int *l1 = new int[len1];
	int *l2 = new int[len2];

	for(i = 0;i < len1;++i)
		cin >> l1[i];
	for (i = 0;i < len2;++i)
		cin >> l2[i];

	len3 = len1 + len2;

	pos1 = 0;
	pos2 = 0;
	for (i = 0;i < len3;++i)
	{
		if(pos1 < len1 && pos2 < len2)
			if(l1[pos1] < l2[pos2])
				cout << l1[pos1++] << ' ';
			else
				cout << l2[pos2++] << ' ';
		else if(pos1 == len1)
			cout << l2[pos2++] << ' ';
		else if(pos2 == len2)
			cout << l1[pos1++] << ' ';
	}
	cout << endl;

	return 0;
}
