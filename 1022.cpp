#include<iostream>
using namespace std;

int Array[2040] = { 1,1 };

int main()
{
	long long N;
	cin >> N;

	for (int i = 2; i < 2040; ++i) 
	{
		Array[i] = (Array[i - 2] + Array[i - 1]) % 2010;
	}
	cout << Array[N % 2040 - 1] << endl;
	return 0;
}