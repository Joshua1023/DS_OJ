#include<iostream>
using namespace std;

template <class elemType>
class linkQueue
{
private:
	struct node {
		elemType data;
		node * next;
		node(const elemType &x, node *N = NULL)
		{
			data = x;
			next = N;
		}
		node() :next(NULL) {}
		~node() {}
	};

	node *front, *rear;

public:
	linkQueue() { front = rear = NULL; }

	~linkQueue();

	bool isEmpty() { return front == NULL; }

	void enQueue(const elemType &x);

	elemType deQueue();

	elemType getHead() { return front->data; }
};

template<class elemType>
linkQueue<elemType>::~linkQueue()
{
	node * tmp;
	while (front != NULL)
	{
		tmp = front;
		front = front->next;
		delete tmp;
	}
}

template<class elemType>
void linkQueue<elemType>::enQueue(const elemType &x)
{
	if (rear == NULL)
		front = rear = new node(x);
	else
	{
		rear->next = new node(x);
		rear = rear->next;
	}
}

template<class elemType>
elemType linkQueue<elemType>::deQueue()
{
	node *tmp = front;
	elemType value = front->data;
	front = front->next;
	if (front == NULL)
		rear = NULL;
	delete tmp;
	return value;
}

template <class elemType>
class BinaryTree_1212
{
private:
	struct node {
		elemType data;
		int parent, left, right;
	};

	node * elem;
	int length, top;
public:
	BinaryTree_1212();

	~BinaryTree_1212() { delete[] elem; }

	void levelOrder()
	{
		linkQueue<int> que;
		int cur;

		que.enQueue(top);
		while (!que.isEmpty())
		{
			cur = que.deQueue();
			if (elem[cur].left != -1) que.enQueue(elem[cur].left);
			if (elem[cur].right != -1) que.enQueue(elem[cur].right);
			cout << elem[cur].data << ' ';
		}
		cout << endl;
	}
};


template <class elemType>
BinaryTree_1212<elemType>::BinaryTree_1212()
{
	int l, r, w, i;
	cin >> length;

	elem = new node[length];

	for (i = 0;i < length;++i)
	{
		elem[i].parent = 0;
	}

	for (i = 0;i < length;++i)
	{
		cin >> l >> r >> w;
		elem[i].data = w;
		elem[i].left = l - 1;
		elem[i].right = r - 1;
		if (l)
			elem[l - 1].parent = i;

		if (r)
			elem[r - 1].parent = i;
	}

	i = 0;
	while (elem[i].parent != 0)
	{
		i = elem[i].parent;
	}
	top = i;
}

int main()
{
	BinaryTree_1212<int> tree;
	tree.levelOrder();

	return 0;
}
