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
class BinaryTree_1214
{
private:
	struct node {
		elemType data;
		int parent, left, right;
	};

	node * elem;
	int length, top;
public:
	BinaryTree_1214();

	~BinaryTree_1214() { delete[] elem; }

	void preOrder(){preOrder(top); cout << endl;}

	void postOrder() { postOrder(top); cout << endl; }

	void levelOrder()
	{
		linkQueue<int> que;
		int cur;

		que.enQueue(top);
		while (!que.isEmpty())
		{
			cur = que.deQueue();
			cout << elem[cur].data << ' ';
			if(elem[cur].left >= 0) que.enQueue(elem[cur].left);
			while (elem[cur].right >= 0)
			{
				cout << elem[elem[cur].right].data << ' ';
				if(elem[elem[cur].right].left >= 0) que.enQueue(elem[elem[cur].right].left);
				cur = elem[cur].right;
			}
		}
		cout << endl;
	}

private:
	void preOrder(int t)
	{
		if(t <= -1) return;
		cout << elem[t].data << ' ';

		if(elem[t].left >= 0) preOrder(elem[t].left);

		if (elem[t].right >= 0) preOrder(elem[t].right);
	}

	void postOrder(int t)
	{
		if (t <= -1) return;


		if(elem[t].left >= 0) postOrder(elem[t].left);
		cout << elem[t].data << ' ';
		if (elem[t].right >= 0) postOrder(elem[t].right);
	}
};


template <class elemType>
BinaryTree_1214<elemType>::BinaryTree_1214()
{
	int l, r, w, i;
	cin >> length;

	elem = new node[length];
	int *times = new int [length];

	for (i = 0;i < length;++i)
	{
		elem[i].parent = 0;
		elem[i].right = -1;
		elem[i].left = -1;
		times[i] = 0;
	}

	for (i = 0;i < length;++i)
	{
		cin >> l >> r >> w;
		elem[i].data = w;
		elem[i].left = l - 1;
		elem[i].right = r - 1;
		if (l)
		{
			elem[l - 1].parent = i;
			times[l - 1]++;
		}
		if (r)
		{

			times[r - 1]++;
		}



	}

	for(i=0;i < length;++i)
		if(times[i] == 0)
			break;
	top = i;
	delete [] times;
}

int main()
{
	BinaryTree_1214<int> tree;
	tree.preOrder();
	tree.postOrder();
	tree.levelOrder();

	return 0;
}
