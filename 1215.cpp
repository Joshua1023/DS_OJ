#include<iostream>
#include<math.h>
#include<string.h>
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

template<class elemType>
class tree {
public:
	struct node {
		elemType data;
		node *son,*brother;

		node(elemType d, node *s = NULL, node *b = NULL)
		{
			data = d;
			son  = s;
			brother = b;
		}
		node(){}
	};

private:
	node *root;

public:
	tree(node *t = NULL){root = t;}
	void createTree(elemType flag);
	void preOrder(){ preOrder(root); }
	void postOrder() { postOrder(root); }
	void levelOrder();

private:
	void preOrder(node *t);
	void postOrder(node *t);
};

template<class elemType>
void tree<elemType>::createTree(elemType flag)
{
	linkQueue<node *> que;
	node * tmp;
	elemType x,son;

	cin >> x;
	root = new node(x);
	que.enQueue(root);

	while (!que.isEmpty())
	{
		tmp = que.deQueue();
		cin >> son;
		if(son == flag)
			continue;
		tmp->son = new node(son);
		tmp = tmp->son;
		que.enQueue(tmp);
		while (true)
		{
			cin >> son;
			if(son == flag)
				break;
			tmp->brother = new node(son);
			tmp = tmp->brother;
			que.enQueue(tmp);
		}
	}
}

template<class elemType>
void tree<elemType>::preOrder(node *t)
{
	if(t == NULL) return;
	cout << t->data << ' ';

	node *p = t -> son;
	while (p != NULL)
	{
		preOrder(p);
		p = p->brother;
	}
}

template<class elemType>
void tree<elemType>::postOrder(node *t)
{
	if(t == NULL) return;

	node *p = t->son;
	while (p != NULL)
	{
		postOrder(p);
		p = p->brother;
	}

	cout << t->data << ' ';
}

template<class elemType>
void tree<elemType>::levelOrder()
{
	linkQueue<node *> que;
	node *tmp;

	if(root == NULL) return;
	que.enQueue(root);
	while (!que.isEmpty())
	{
		tmp = que.deQueue();
		cout << tmp->data << ' ';
		tmp = tmp->son;
		while (tmp != NULL)
		{
			que.enQueue(tmp);
			tmp = tmp->brother;
		}
	}
}

template<class elemType>
class Binomial {
	typename tree<elemType>::node **forest;
	int noOfTree;

	typename tree<elemType>::node *merge(typename tree<elemType>::node *t1, typename tree<elemType>::node *t2);
	int findmin();
	void deleteTree(typename tree<elemType>::node *rt)
	{
		typename tree<elemType>::node *son = rt->son,*t;
		while (son != NULL)
		{
			t = son;
			son = son->brother;
			deleteTree(t);
		}
		delete rt;
	}

public:
	Binomial(int n = 100)
	{
		noOfTree = int(log(n) / log(2)) + 1;
		forest = new typename tree<elemType>::node * [noOfTree];
		for(int i = 0;i < noOfTree;++i)  forest[i] = NULL;
	}

	~Binomial()
	{
		for(int i = 0;i < noOfTree; ++i)
			if(forest[i] != NULL) deleteTree(forest[i]);
		delete [] forest;
	}

	void enQueue(elemType x);
	elemType deQueue();
	bool isEmpty();
	elemType getHead();
	void merge(Binomial &other);

};

template<class elemType>
void Binomial<elemType>::merge(Binomial &other)
{
	typename tree<elemType>::node **tmp = forest,*carry;
	int tmpSize = noOfTree,i;
	int min = noOfTree < other.noOfTree ? noOfTree : other.noOfTree;

	if (noOfTree < other.noOfTree)
	{
		noOfTree = other.noOfTree;
		if(other.forest[noOfTree] != NULL) ++noOfTree;
	}
	else if(forest[noOfTree] != NULL) ++noOfTree;

	forest = new typename tree<elemType>::node * [noOfTree];
	for(i = 0;i < noOfTree;++i) forest[i] = NULL;

	carry = NULL;
	for (i = 0;i < min;++i)
	{
		if (carry == NULL)
		{
			if(tmp[i] == NULL)
				forest[i] = other.forest[i];
			else
			{
				if(other.forest[i] == NULL)
					forest[i] = tmp[i];
				else
					carry = merge(other.forest[i],tmp[i]);
			}
		}
		else
		{
			if (tmp[i] != NULL && other.forest[i] != NULL)
			{
				forest[i] = carry;
				carry = merge(other.forest[i],tmp[i]);
			}
			else
				if (tmp[i] == NULL && other.forest[i] == NULL)
				{
					forest[i] = carry;
					carry = NULL;
				}
				else if(tmp[i] == NULL)
					carry = merge(other.forest[i],carry);
				else
					carry = merge(tmp[i],carry);
		}
	}

	if (other.noOfTree == min)
	{
		for(;i < tmpSize;++i)
			if(carry == NULL) forest[i] = tmp[i];
			else if (tmp[i] == NULL)
			{
				forest[i] = carry;
				carry = NULL;
			}
			else
				carry = merge(tmp[i],carry);
	}
	else
	{
		for(;i < other.noOfTree;++i)
			if(carry == NULL) forest[i] = other.forest[i];
			else if (other.forest[i] == NULL)
			{
				forest[i] = carry;
				carry = NULL;
			}
			else
				carry = merge(other.forest[i],carry);
	}
	if(carry != NULL)
		forest[i] = carry;

	for(i = 0;i < other.noOfTree;++i)
		other.forest[i] = NULL;
	delete [] tmp;
}

template<class elemType>
typename tree<elemType>::node *Binomial<elemType>::merge(typename tree<elemType>::node *t1, typename tree<elemType>::node *t2)
{
	typename tree<elemType>::node *min,*max;

	if (t1->data < t2->data)
	{
		min = t1;
		max = t2;
	}
	else
	{
		min = t2;
		max = t1;
	}

	if(min->son == NULL) min->son = max;
	else
	{
		typename tree<elemType>::node *t = min->son;
		while(t->brother != NULL) t = t->brother;
		t->brother = max;
	}
	return min;
}

template<class elemType>
void Binomial<elemType>::enQueue(elemType x)
{
	Binomial tmp(1);
	tmp.forest[0] = new typename tree<elemType>::node(x);
	merge(tmp);
}

template<class elemType>
elemType Binomial<elemType>::deQueue()
{
	elemType value;
	int min = findmin();

	if (min == 0)
	{
		value = forest[0] -> data;
		delete forest[0];
		forest[0] = NULL;
		return value;
	}

	typename tree<elemType>::node *t = forest[min],*son,*brother;
	int sizeOfQueue = int(pow(2,min) - 1);
	Binomial tmp(sizeOfQueue);
	value = t->data;
	forest[min] = NULL;

	son = t->son;
	delete t;
	int i = 0 ;
	do {
		tmp.forest[i++] = son;
		brother = son -> brother;
		son -> brother = NULL;
	}while((son = brother)!=NULL);

	merge(tmp);

	return value;
}

template<class elemType>
int Binomial<elemType>::findmin()
{
	int i,min;

	for(i = 0; i < noOfTree && forest[i] == NULL; ++i);
	min = i;
	for(;i < noOfTree;++i)
		if(forest[i] != NULL && forest[i]->data < forest[min]->data)
			min = i;

	return min;
}

template<class elemType>
bool Binomial<elemType>::isEmpty()
{
	for(int i = 0;i < noOfTree;++i)
		if(forest[i] != NULL)
			return false;
	return true;
}

template<class elemType>
elemType Binomial<elemType>::getHead()
{
	int pos = findmin();
	return forest[pos]->data;
}

int main()
{

	int ops,num;
	char op_name[7];
	cin >> ops;
	Binomial<int> BQ(ops);
	for (int i = 0; i < ops; ++i)
	{
		cin >> op_name;

		if(!strcmp(op_name,"min"))
			cout << BQ.getHead() << endl;
		else if (!strcmp(op_name, "insert"))
		{
			cin >> num;
			BQ.enQueue(num);
		}
		else if (!strcmp(op_name, "delete"))
			BQ.deQueue();
	}

	return 0;
}
