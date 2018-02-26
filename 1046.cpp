#include<iostream>
#include<stdio.h>
using namespace std;

template <class elemType>
class linkStack
{
private:
	struct node
	{
		elemType data;
		node *next;
		node(const elemType &x, node *N = NULL)
		{
			data = x;
			next = N;
		}
		node() :next(NULL) {}
		~node() {}
	};

	node * elem;

public:
	linkStack() { elem = NULL; }

	~linkStack();

	bool isEmpty() const { return elem == NULL; }

	void push(const elemType &x)
	{
		node * tmp = new node(x, elem);
		elem = tmp;
	}

	elemType pop()
	{
		node *tmp = elem;
		elemType x = tmp->data;
		elem = elem->next;
		delete tmp;
		return x;
	}

	elemType top() const
	{
		return elem->data;
	}
};

template <class elemType>
linkStack<elemType>::~linkStack()
{
	node *tmp;
	while (elem != NULL)
	{
		tmp = elem;
		elem = elem->next;
		delete tmp;
	}
}

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
class BinaryTree_1046
{
private:
	struct node {
		elemType data;
		int parent, left, right, num;
	};

	node * elem;
	int length, top;
public:
	BinaryTree_1046(int N);

	~BinaryTree_1046() { delete[] elem; }

	void color(int t, int x)
	{
		linkQueue<int> que;
		int i, y = 0, tar;
		midOrder(t, que, y);
		for (i = 0;i < (x % y) + 1;++i)
			tar = que.deQueue();
		elem[tar].data = true;
	}

	void midOrder(int t, linkQueue<int> &que, int &count)
	{
		linkStack<int> s, times;
		int current, current_times;
		s.push(t);
		times.push(0);

		while (!s.isEmpty())
		{
			current = s.pop();
			current_times = times.pop();
			if (current_times == 1)
			{
				que.enQueue(current);
				count++;
				if (elem[current].right != 0)
				{
					s.push(elem[current].right);
					times.push(0);
				}
			}
			else
			{
				s.push(current);
				times.push(1);
				if (elem[current].left != 0)
				{
					s.push(elem[current].left);
					times.push(0);
				}
			}
		}

	}

	void preOrder(int t, int &cnt)
	{
		linkStack<int> s;
		int current;

		s.push(t);
		while (!s.isEmpty())
		{
			current = s.pop();
			if (elem[current].data)
				cnt++;
			if (elem[current].right != 0)  s.push(elem[current].right);
			if (elem[current].left != 0)  s.push(elem[current].left);
		}
	}

	void count(int t)
	{
		int cnt = 0;
		preOrder(t, cnt);
		printf("%d\n",cnt);
	}
};


template <class elemType>
BinaryTree_1046<elemType>::BinaryTree_1046(int N)
{
	int l, r, pos, i;
	length = N + 1;
	elem = new node[N + 1];

	for (i = 0;i < length;++i)
	{
		elem[i].parent = 0;
	}

	for (i = 0;i < N;++i)
	{
		scanf("%d%d%d", &pos, &l, &r);
		elem[pos].data = false;
		elem[pos].left = l;
		elem[pos].right = r;
		if (l)
			elem[l].parent = pos;

		if (r)
			elem[r].parent = pos;
	}

	i = 1;
	while (elem[i].parent != 0)
	{
		i = elem[i].parent;
	}
	top = i;
}

int main()
{
	int N, P, Q, i, t, x;
	scanf("%d%d%d", &N, &P, &Q);
	BinaryTree_1046<bool> tree(N);
	for (i = 0;i < P;++i)
	{
		scanf("%d%d", &t, &x);
		tree.color(t, x);
	}
	for (i = 0;i < Q;++i)
	{
		scanf("%d", &t);
		tree.count(t);
	}

	return 0;
}