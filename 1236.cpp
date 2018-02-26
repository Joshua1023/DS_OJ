#include<iostream>
#include<stdio.h>
#include<cstring>
using namespace std;

const int maxN = 200010;
struct Edge
{
	int    to, next, w;
} e[maxN];

int    n, m, cnt, p[maxN], Dis[maxN];
int    In[maxN];
bool    visited[maxN];

void    Add_Edge(const int x, const int y, const int z)
{
	e[++cnt].to = y;
	e[cnt].next = p[x];
	e[cnt].w = z;
	p[x] = cnt;
	return;
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

bool    Spfa(const int S)
{
	int i, t, temp;
	linkQueue<int> Q;
	memset(visited, 0, sizeof(visited));
	memset(Dis, 0x3f, sizeof(Dis));
	memset(In, 0, sizeof(In));

	Q.enQueue(S);
	visited[S] = true;
	Dis[S] = 0;

	while (!Q.isEmpty())
	{
		t = Q.deQueue();
		visited[t] = false;
		for (i = p[t]; i; i = e[i].next)
		{
			temp = e[i].to;
			if (Dis[temp] > Dis[t] + e[i].w)
			{
				Dis[temp] = Dis[t] + e[i].w;
				if (!visited[temp])
				{
					Q.enQueue(temp);
					visited[temp] = true;
					if (++In[temp]>n)return false;
				}
			}
		}
	}
	return true;
}

int main()
{
	int    S, T,x,y,w;

	scanf("%d%d%d%d", &n, &m, &S, &T);
	for (int i = 1; i <= m; ++i)
	{
		scanf("%d%d%d", &x, &y, &w);
		Add_Edge(x, y, w);
	}

	if (!Spfa(S)) printf("FAIL!\n");
	else
		printf("%d\n", Dis[T]);

	return 0;
}
