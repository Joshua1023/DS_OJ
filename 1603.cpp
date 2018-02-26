#include<iostream>
using namespace std;

int *res;

struct Node {
	int val, smaller;
	Node *left, *right;
	Node(int v, int s) : val(v), smaller(s), left(NULL), right(NULL) {}
};
int insert(Node *&root, int v) {
	if (!root) return (root = new Node(v, 0)), 0;
	if (root->val > v) return root->smaller++, insert(root->left, v);
	else return insert(root->right, v) + root->smaller + (root->val < v ? 1 : 0);
}

int main()
{
	int len,i,tmp;
	cin >> len;
	res = new int[len];
	int *arr = new int[len];
	Node *root = NULL;

	for (i = 0;i < len;++i)
	{
		cin >> arr[i];
	}
	for (i = len - 1; i >= 0; --i) {
		res[i] = insert(root, arr[i]);
	}
	for(i = 0;i < len;++i)
		cout << res[i] << ' ';
	cout << endl;

	return 0;
}
