#include<iostream>
#include <stdio.h>

using namespace std;

int n;
void Farey(int a, int b, int c, int d)
{
	if (b + d>n)
		return;
	Farey(a, b, c + a, d + b);
	printf("%d/%d\n", a + c, b + d);
	Farey(c + a, d + b, c, d);
}

int main()
{
	cin >> n;
	cout << 0 << '/' << 1 << endl;
	Farey(0, 1, 1, 1);
	cout << 1 << '/' << 1 << endl;

	return 0;
}