#include <iostream>
using namespace std;

int  cnt = 0, res = 0, de;

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

class graph
{
private:
	int vSize, eSize;
	struct edgeNode {
		int weight;
		int end;
		edgeNode*next;
		edgeNode(int e, int w, edgeNode *n = NULL)
		{
			weight = w;
			end = e;
			next = n;
		}
	};
	struct verNode {
		int ver;
		edgeNode*head;
		verNode(edgeNode*h = NULL)
		{
			head = h;
		}
	};
	verNode*verList;
public:
	graph(int size)
	{
		vSize = size;
		eSize = 0;
		verList = new verNode[vSize + 1];
		for (int i = 1;i <= vSize;++i)
		{
			verList[i].ver = i;
		}
	}
	void insert(int u, int v, int weight = 1)
	{
		verList[u].head = new edgeNode(v, weight, verList[u].head);
		eSize++;
	}
	int topSort()
	{
		int tmp = 0;
		linkQueue<int> q,q2;
		int *inDegrees = new int[vSize + 1];
		for (int i = 1;i <= vSize;++i)
			inDegrees[i] = 0;
		for (int i = 1;i <= vSize;++i)
		{
			edgeNode*p = verList[i].head;
			while (p != NULL)
			{
				++inDegrees[p->end];
				p = p->next;
			}
		}
		bool *marked = new bool[vSize + 1];for (int j = 1;j <= vSize;++j) marked[j] = false;
		for (int i = 1;i <= vSize;++i)
		{
			if (inDegrees[i] == 0)
			{
				q.enQueue(i);
			}
		}

		while (!q.isEmpty())
		{
			++tmp;
			while (!q.isEmpty())
			{
				de = q.deQueue();
				marked[de] = true;
				edgeNode*p = verList[de].head;
				while (p != NULL) {
					if (marked[p->end] == false)
					{
						if (--inDegrees[p->end] == 0) q2.enQueue(p->end);
					}
					p = p->next;
				}
			}
			if (!q2.isEmpty()) tmp++;
			while (!q2.isEmpty())
			{
				de = q2.deQueue();
				marked[de] = true;
				edgeNode*p = verList[de].head;
				while (p != NULL) {
					if (marked[p->end] == false)
					{
						if (--inDegrees[p->end] == 0) q.enQueue(p->end);
						//  marked[p->end]=true;
					}
					p = p->next;
				}
			}
		}
		return tmp;
	}
};
int main()
{
	int n, m, u, v;
	cin >> n >> m;
	graph g(n);
	for (int i = 0;i<m;++i)
	{
		cin >> u >> v;
		g.insert(u, v);
	}
	int res = g.topSort();
	cout << res << endl;

	return 0;
}
