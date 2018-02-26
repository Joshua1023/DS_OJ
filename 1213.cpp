#include<iostream>
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
class BinaryTree_1213
{
private:
	struct node {
		elemType data;
		int parent, left, right, num;
	};


	int length, top;
public:
	node * elem;

	BinaryTree_1213();

	~BinaryTree_1213() { delete[] elem; }

	int getRoot(){return top;}
};


template <class elemType>
BinaryTree_1213<elemType>::BinaryTree_1213()
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

void same(BinaryTree_1213<int> &tree1, BinaryTree_1213<int> &tree2)
{

	linkStack<int> s1,s2;
	int current1,current2;
	bool flag = true;

	s1.push(tree1.getRoot());
	s2.push(tree2.getRoot());
	while (!s1.isEmpty() && !s2.isEmpty())
	{
		current1 = s1.pop();
		current2 = s2.pop();
		if (tree1.elem[current1].data != tree2.elem[current2].data)
		{
			flag = false;
			break;
		}
		if (tree1.elem[current1].right != -1)  s1.push(tree1.elem[current1].right);
		if (tree1.elem[current1].left != -1)  s1.push(tree1.elem[current1].left);
		if (tree2.elem[current2].right != -1)  s2.push(tree2.elem[current2].right);
		if (tree2.elem[current2].left != -1)  s2.push(tree2.elem[current2].left);
	}

	if(!s1.isEmpty() || !s2.isEmpty())
		flag = false;
	if(flag)
		cout << "Y\n";
	else
		cout << "N\n";
}

int main()
{
	BinaryTree_1213<int> tree1,tree2;

	same(tree1,tree2);

	return 0;
}
