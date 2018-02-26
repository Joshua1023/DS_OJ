#include<iostream>
#include<stdio.h>
using namespace std;

template<class elemType>
class priorityQueue
{
public:
	priorityQueue(int capacity = 100)
	{
		array = new elemType[capacity];
		maxSize = capacity;
		currentSize = 0;
	}
	priorityQueue(const elemType *data, int size);
	~priorityQueue() { delete[] array; }

	bool isEmpty() const { return currentSize == 0; }
	void enQueue(const elemType &x);
	elemType deQueue();
	elemType getHead() const { return array[1]; }

private:
	int currentSize;
	elemType * array;
	int maxSize;

	void doubleSpace();
	void buildHeap();
	void percolateDown(int hole);
};

template<class elemType>
void priorityQueue<elemType>::enQueue(const elemType &x)
{
	if (currentSize == maxSize - 1)
		doubleSpace();

	int hole = ++currentSize;
	for (;hole > 1 && x < array[hole / 2]; hole /= 2)
		array[hole] = array[hole / 2];
	array[hole] = x;

}

template<class elemType>
elemType priorityQueue<elemType>::deQueue()
{
	elemType minItem;
	minItem = array[1];
	array[1] = array[currentSize--];
	percolateDown(1);
	return minItem;
}

template<class elemType>
void priorityQueue<elemType>::percolateDown(int hole)
{
	int child;
	elemType tmp = array[hole];

	for (;hole * 2 <= currentSize;hole = child)
	{
		child = hole * 2;
		if (child != currentSize && array[child + 1] < array[child])
			child++;
		if (array[child] < tmp)
			array[hole] = array[child];
		else
			break;
	}
	array[hole] = tmp;
}

template<class elemType>
void priorityQueue<elemType>::buildHeap()
{
	for (int i = currentSize / 2;i > 0;--i)
		percolateDown(i);
}

template<class elemType>
priorityQueue<elemType>::priorityQueue(const elemType *items, int size) :maxSize(size + 10), currentSize(size)
{
	array = new elemType[maxSize];
	for (int i = 0;i < size; ++i)
		array[i + 1] = items[i];
	buildHeap();
}

template<class elemType>
void priorityQueue<elemType>::doubleSpace()
{
	elemType *tmp = array;

	maxSize *= 2;
	array = new elemType[maxSize];

	for (int i = 0; i <= currentSize; ++i)
		array[i] = tmp[i];

	delete[] tmp;
}

template<class TypeOfVer, class TypeOfEdge>
class adjListGraph {
public:
	adjListGraph(int vSize, const TypeOfVer d[]);
	bool insert(int u, int v, TypeOfEdge w);
	bool remove(int u, int v);
	bool exist(int u, int v) const;
	int numOfVer() const { return Vers; }
	int numOfEdge() const { return Edges; }
	~adjListGraph();
	void dijkstra(TypeOfVer start,TypeOfEdge noEdge, TypeOfVer END) const;
	void printPath(int start, int end, int prev[])const
	{
		if (start == end)
		{
			cout << verList[start].ver;
			return;
		}
		printPath(start,prev[end],prev);
		cout << ' ' << verList[end].ver;
	}

private:
	struct edgeNode {
		int end;
		TypeOfEdge weight;
		edgeNode *next;

		edgeNode(int e, TypeOfEdge w, edgeNode *n = NULL)
		{
			end = e;
			weight = w;
			next = n;
		}
	};

	struct verNode {
		TypeOfVer ver;
		edgeNode *head;
		verNode(edgeNode *h = NULL)
		{
			head = h;
		}
	};

	struct queueNode {
		TypeOfEdge dist;
		int node;

		bool operator < (const queueNode &rp) const {return dist < rp.dist;}
	};
	verNode *verList;
	int Vers, Edges;
};

template<class TypeOfVer, class TypeOfEdge>
adjListGraph<TypeOfVer, TypeOfEdge>::adjListGraph(int vSize, const TypeOfVer d[])
{
	Vers = vSize;
	Edges = 0;

	verList = new verNode[vSize];

	for (int i = 0;i < Vers;++i)
		verList[i].ver = d[i];
}

template<class TypeOfVer, class TypeOfEdge>
adjListGraph<TypeOfVer, TypeOfEdge>::~adjListGraph()
{
	int i;
	edgeNode *p;

	for (i = 0;i < Vers;++i)
		while ((p = verList[i].head) != NULL)
		{
			verList[i].head = p->next;
			delete p;
		}

	delete[] verList;
}

template<class TypeOfVer, class TypeOfEdge>
bool adjListGraph<TypeOfVer, TypeOfEdge>::insert(int u, int v, TypeOfEdge w)
{
	verList[u].head = new edgeNode(v, w, verList[u].head);
	++Edges;
	return true;
}

template<class TypeOfVer, class TypeOfEdge>
bool adjListGraph<TypeOfVer, TypeOfEdge>::remove(int u, int v)
{
	edgeNode *p = verList[u].head, *q;

	if (p == NULL)
		return false;

	if (p->end == v)
	{
		verList[u].head = p->next;
		delete p;
		--Edges;
		return true;
	}

	while (p->next != NULL && p->next->end != v) p = p->next;
	if (p->next == NULL) return false;
	q = p->next;p->next = q->next;delete q;
	--Edges;
	return true;
}

template<class TypeOfVer, class TypeOfEdge>
bool adjListGraph<TypeOfVer, TypeOfEdge>::exist(int u, int v) const
{
	edgeNode *p = verList[u].head;

	while (p != NULL && p->end != v) p = p->next;
	if (p == NULL) return false;
	else
		return true;
}

template<class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::dijkstra(TypeOfVer start, TypeOfEdge noEdge,TypeOfVer END) const
{
	TypeOfEdge *distance = new TypeOfEdge[Vers];
	int *prev = new int[Vers];
	bool *known = new bool[Vers];
	int *hop = new int[Vers];
	int sNo,i;
	edgeNode *p;
	priorityQueue<queueNode> q(Vers);
	queueNode min,succ;

	for (i = 0;i < Vers;++i)
	{
		known[i] = false;
		distance[i] = noEdge;
		hop[i] = 0;
	}

	for(sNo = 0;sNo < Vers;++sNo)
		if(verList[sNo].ver == start) break;
	if (sNo == Vers) {
		cout << "起始节点不存在\n";
		return;
	}

	distance[sNo] = 0;
	prev[sNo] = sNo;
	min.dist = 0;
	min.node = sNo;
	q.enQueue(min);

	while (!q.isEmpty())
	{
		min = q.deQueue();
		if(known[min.node]) continue;
		known[min.node] = true;
		for(p = verList[min.node].head;p != NULL;p = p->next)
			if (!known[p->end] && (distance[p->end] > min.dist + p->weight || (distance[p->end] == min.dist + p->weight && hop[p->end] > hop[min.node] + 1)))
			{
				distance[p->end] = min.dist + p->weight;
				succ.dist = min.dist + p->weight;
				prev[p->end] = min.node;
				succ.node = p->end;
				hop[p->end] = hop[min.node] + 1;
				q.enQueue(succ);
			}
	}

	cout << distance[END - 1] << endl;
	printPath(sNo,END - 1,prev);
	cout << endl;
}

int main()
{
	int n,m,start,end,i,s,e,w;

	cin >> n >> m >> start >> end;

	int *v = new int[n];
	for(i = 0;i < n;++i)
		v[i] = i + 1;

	adjListGraph<int,int> g(n,v);

	for (i = 0;i < m;++i)
	{
		scanf("%d%d%d",&s,&e,&w);
		g.insert(s - 1,e - 1,w);
	}

	g.dijkstra(start, 200000000,end);

	return 0;

}
