#include<iostream>
using namespace std;

//seqQueue
template<class elemType>
class seqQueue
{
private:
	elemType *elem;
	int maxSize;
	int front, rear;

	void doubleSpace();

public:
	seqQueue(int size = 10)
	{
		elem = new elemType[size];
		maxSize = size;
		front = rear = 0;
	}

	~seqQueue() { delete[] elem; }

	bool isEmpty() { return front == rear; }

	void enQueue(const elemType &x);

	void deQueue(const elemType &x);

	elemType getHead() { return elem[front]; }

};

template <class elemType>
void seqQueue<elemType>::doubleSpace()
{
	elemType *tmp = elem;

	elem = new elemType[2 * maxSize];

	for (int i = 1;i < maxSize;++i)
		elem[i] = tmp[(front + i) % maxSize];

	front = 0;
	rear = maxSize - 1;
	maxSize *= 2;

	delete tmp;
}

template<class elemType>
void seqQueue<elemType>::enQueue(const elemType &x)
{
	if ((rear + 1) % maxSize == front)  doubleSpace();
	while (rear != front&&elem[(rear - 1) % maxSize] < x)
	{
		rear = (rear - 1) % maxSize;
	}
	elem[rear] = x;
	rear = (rear + 1) % maxSize;
}

template<class elemType>
void seqQueue<elemType>::deQueue(const elemType &x)
{
	if (elem[front] == x)
	{
		front = (front + 1) % maxSize;
	}
}


int main()
{
	int tmp,len,quest,i,min_max;
	int *chain;

	cin >> len;
	cin >> quest;
	chain = new int[len];
	for (i = 0;i < len;++i)
	{
		cin >> tmp;
		chain[i] = tmp;
	}
	seqQueue<int> que(len);

	for (i = 0;i < quest;++i)
	{
		que.enQueue(chain[i]);
	}
	min_max = que.getHead();
	if (quest == len)
	{
		cout << min_max << endl;
		return 0;
	}

	i = quest;
	while (i != quest - 1)
	{
		que.deQueue((i - quest < 0) ? (chain[i - quest + len]) : (chain[i - quest]));
		que.enQueue(chain[i]);
		if(min_max > que.getHead())
			min_max = que.getHead();
		i = ((i + 1)==len)?(0):(i+1);
	}

	cout << min_max << endl;

	delete [] chain;
	return 0;
}