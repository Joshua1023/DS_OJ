#include<iostream>
#include<cstdio>
using namespace std;
void BinaryTreeFromOrderings(int* midorder, int* preorder, int len)
{
	if (len == 0)
	{
		return;
	}
	int elem = *preorder;
	int i;
	for (i = 0; i < len; i++)
	{
		if (midorder[i] == *preorder)
			break;
	}
	BinaryTreeFromOrderings(midorder, preorder + 1, i);
	BinaryTreeFromOrderings(midorder + i + 1, preorder + i + 1, len - (i + 1));
	cout << elem << " ";
}

int main()
{
	int n;
	cin >> n;
	int * pre = new int[n];
	int * mid = new int[n];
	for (int i = 0; i < n; i++)
	{
		cin >> pre[i];
	}
	for (int i = 0; i < n; i++)
	{
		cin >> mid[i];
	}
	BinaryTreeFromOrderings(mid, pre, n);
	delete[] pre;
	delete[] mid;

	return 0;
}