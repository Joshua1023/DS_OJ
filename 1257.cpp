#include<iostream>
#include<string.h>
#include<stdio.h>
using namespace std;

bool flag[100001] = {false};


template <class elemType>
class BinaryTree_1039
{
private:
	struct node {
		int bro, left, right,parent;
		node(){bro = 0;left = 0;right = 0;parent = 0;}
	};

	node * elem;
	int top;
	void preOrder(int t)
	{
		if (t != 0)
		{
			printf("%d ",t);
			preOrder(elem[t].left);
			preOrder(elem[t].right);
		}
	}
public:
	BinaryTree_1039();

	~BinaryTree_1039() { delete[] elem; }


	void preOrder()
	{
		preOrder(top);
		cout << endl;
	}
	void insert(int a,int b,int c);
	void check(int a)
	{
		if (!flag[a])
		{
			printf("Error!\n");
			return;
		}
		printf("%d %d %d\n",elem[a].parent,elem[a].left,elem[a].right);
	}
	void swi(int a)
	{
		if (a == 1 || !flag[a])
		{
			printf("Error!\n");
			return;
		}
		int p = elem[a].parent;
		if (elem[p].left == a)
		{
			elem[p].left = elem[a].bro;
			elem[p].right = a;
		}
		else
		{
			elem[p].right = elem[a].bro;
			elem[p].left = a;
		}
		printf("%d\n",elem[a].bro);
	}
};

template <class elemType>
BinaryTree_1039<elemType>::BinaryTree_1039()
{
	elem = new node[100001];
	top = 1;
}


template <class elemType>
void BinaryTree_1039<elemType>::insert(int a,int b,int c)
{
	if (!flag[a] || flag[b] || flag[c] || b == c)
	{
		printf("Error!\n");
		return;
	}
	if (elem[a].left != 0 || elem[a].right != 0)
	{
		printf("Error!\n");
		return;
	}

	elem[a].left = b;
	elem[a].right = c;
	elem[b].parent = a;
	elem[c].parent = a;
	elem[b].bro = c;
	elem[c].bro = b;

	flag[b] = true;
	flag[c] = true;
	printf("Ok!\n");
}

int main()
{
	long long op;
	int type,a,b,c;
	BinaryTree_1039<int> tree;
	flag[1] = true;

	cin >> op;
	for (long long i = 0;i < op;++i)
	{
		scanf("%d",&type);
		if (type == 1)
		{
			scanf("%d%d%d",&a,&b,&c);
			tree.insert(a,b,c);
		}
		else if (type == 2)
		{
			scanf("%d",&a);
			tree.check(a);
		}
		else if (type == 3)
		{
			scanf("%d",&a);
			tree.swi(a);
		}
	}
	tree.preOrder();

	return 0;
}
