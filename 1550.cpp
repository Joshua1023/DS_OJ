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

int min(int a, int b)
{
	if(a > b)
		return b;
	else
		return a;
}

int main()
{
	char tmp;
	int N,value=0,i=0,total=0,pos1,pos2,mini;
	cin >> N;
	int *height = new int [N];
	linkQueue<int>	q;

	while (cin.get(tmp))
	{
		if(tmp <= '9' && tmp >= '0')
			value = 10 * value + tmp - '0';
		if (tmp == ',' || tmp == ']')
		{
			height[i] = value;
			value = 0;
			i++;
		}
	}

	if(height[0] > height[1])
		q.enQueue(0);


	for(i=1;i<N-1;++i)
		if(height[i] >= height[i-1] && height[i] >= height[i + 1] &&(height[i] != height[i - 1] || height[i] != height[i + 1]))
			q.enQueue(i);

	if (height[N-1] > height[N-2])
		q.enQueue(N-1);


	if(!q.isEmpty())
		pos1 = q.deQueue();
	while (!q.isEmpty())
	{
		pos2 = q.deQueue();
		mini = min(height[pos1], height[pos2]);

		for (i = pos1 + 1;i<pos2;++i)
			if (mini - height[i] > 0)
			{
				total += mini - height[i];
				height[i] = mini;
			}
		pos1 = (height[pos1] >= height[pos2]) ? pos1 : pos2;

	}

	cout << total << endl;

	delete [] height;
	return 0;
}
