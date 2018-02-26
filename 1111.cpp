#include<iostream>
#include<string.h>
using namespace std;

char pre[27];
char mid[27];
int len_p = 0, len_m = 0;

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

typedef struct _node {
	char v;
	_node *l,*r;
	_node(){l = NULL;r = NULL;}

}Node, *PNode;


int locate(char c)
{
	return strchr(mid, c) - mid;
}

void createTree(PNode &p, int i, int j, int len)
{
	if(len <= 0)
		return;

	p = new Node;
	p->v = pre[i];
	int m = locate(pre[i]);
	createTree(p->l,i+1,j,m-j);
	createTree(p->r, i + (m - j) + 1, m + 1, len - 1 - (m - j));
}


int main()
{
	char tmp;
	while(cin.get(tmp))
		if(tmp != '\n')
			pre[len_p++] = tmp;
		else
			break;

	while(cin.get(tmp))
		if (tmp != '\n')
			mid[len_m++] = tmp;
		else
			break;


	PNode root = NULL;
	int len = len_m;

	createTree(root,0,0, len);


	linkQueue<PNode> que;
	PNode pos;
	que.enQueue(root);
	while (!que.isEmpty() && len)
	{
		pos = que.deQueue();
		if (pos != NULL)
		{
			cout << pos->v << ' ';
			len--;
			que.enQueue(pos->l);
			que.enQueue(pos->r);
		}
		else
		{
			cout << "NULL" << ' ';
			que.enQueue(NULL);
			que.enQueue(NULL);
		}


	}

	return 0;
}
