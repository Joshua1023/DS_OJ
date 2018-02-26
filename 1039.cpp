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
class BinaryTree_1039
{
private:
	struct node {
		elemType data;
		int pos, left, right;
	};

	node * elem;
	int length, top;
	void postOrder(int t)
	{
		if (t != -1)
		{
			postOrder(elem[t].left);
			postOrder(elem[t].right);
			cout << t << ' ';
		}
	}
public:
	BinaryTree_1039();

	~BinaryTree_1039() { delete[] elem; }

	void levelOrder()
	{
		linkQueue<int> que;
		int cur;
		int *pos = new int[length+1];
		int tag = 0,cnt = 0;

		que.enQueue(top);
		while (!que.isEmpty())
		{
			if(cnt == length)
				break;
			cur = que.deQueue();
			tag++;
			if (cur != -1)
			{
				que.enQueue(elem[cur].left);
				que.enQueue(elem[cur].right);
				pos[elem[cur].data] = tag;
				cnt++;
			}
			else
			{
				que.enQueue(-1);
				que.enQueue(-1);

			}

		}
		for(int i =1;i < length + 1;++i)
			cout << pos[i]<<' ';

		cout << endl;

		delete pos;
	}

	void postOrder()
	{
		postOrder(top);
		cout << endl;
	}
};


template <class elemType>
BinaryTree_1039<elemType>::BinaryTree_1039()
{
	int l, r, w, i;
	cin >> length;

	elem = new node[length + 1];


	for (i = 1;i < length + 1;++i)
	{
		cin >> w >> l >> r;
		elem[w].data = w;
		elem[w].left = l ;
		elem[w].right = r;
	}
	top = 1;
}

int main()
{
	BinaryTree_1039<int> tree;
	tree.levelOrder();
	tree.postOrder();

	return 0;
}
