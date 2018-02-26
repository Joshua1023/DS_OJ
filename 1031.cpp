#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

struct Point
{
	int x;
	int y;
	Point(int a, int b)
	{
		x = a;
		y = b;
	}
	Point(){}
};

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

const int MaxN = 101;
int MAP[MaxN][MaxN];
int n;
int Max = -1, Min = 120;
bool vis[MaxN][MaxN];



int to_x[4] = { -1,+1,0,0 };
int to_y[4] = { 0,0,-1,+1 };

linkQueue<Point> q;

bool bfs(int low_bd, int up_bd) {
	if (MAP[1][1]>up_bd || MAP[1][1]<low_bd || MAP[n][n]>up_bd || MAP[n][n]<low_bd)
		return false;
	memset(vis, false, sizeof(vis));

	Point start(1, 1);
	while (!q.isEmpty())
		q.deQueue();
	q.enQueue(start);

	while (!q.isEmpty()) 
	{
		Point cur = q.getHead();
		q.deQueue();
		vis[cur.x][cur.y] = true; 

		for (int i = 0; i < 4; ++i)
		{
			int x = cur.x + to_x[i];
			int y = cur.y + to_y[i];
			if (x<1 || x>n || y<1 || y>n)
				continue;
			if (vis[x][y])
				continue;
			if (MAP[x][y]<low_bd || MAP[x][y]>up_bd)
				continue;
			Point nxt(x, y);
			q.enQueue(nxt);
			vis[x][y] = true;
			if (vis[n][n])
				return true;
		}

	}
	return false;
}


void init() {
	cin >> n;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j) 
		{
			cin >> MAP[i][j];

			Max = max(Max, MAP[i][j]);
			Min = min(Min, MAP[i][j]);
		}
}

int BinaryFind() {

	int L = 0, R = Max - Min;
	int mid;

	while (L<R) 
	{
		mid = (L + R) / 2;

		bool isOK = false;
		for (int i = Min; i <= Max - mid; ++i)
		{ 

			if (bfs(i, i + mid)) 
			{
				isOK = true;
				break;
			}
		}

		if (isOK)    R = mid;
		else        L = mid + 1;

	}

	return L;
}

int main()
{
	init();
	cout << BinaryFind() << endl;


	return 0;
}