#include<iostream>
#include<iomanip>
using namespace std;

void quickSort(long long s[], long long l, long long r)
{
	if (l< r)
	{
		long long i = l, j = r, x = s[l];
		while (i < j)
		{
			while (i < j && s[j] >= x)
				j--;
			if (i < j)
				s[i++] = s[j];
			while (i < j && s[i]< x)
				i++;
			if (i < j)
				s[j--] = s[i];
		}
		s[i] = x;
		quickSort(s, l, i - 1);
		quickSort(s, i + 1, r);
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

int main()
{

	long long N,i,tmp,M,timer = 0,boyW=0,girlW=0,pos_B=0,pos_G=0;
	cin >> N;
	long long *sing = new long long[100000];

	for (i = 0;i < N;++i)
	{
		cin >> tmp;
		sing[i] = tmp;
	}

	cin >> M;
	long long *boy = new long long[10000000], *girl = new long long[10000000];
	for (i = 0;i < M;++i)
	{
		cin >> tmp;
		if (tmp == 1)
		{
			cin >> tmp;
			boy[pos_B++] = tmp;
		}
		else
		{
			cin >> tmp;
			girl[pos_G++] = tmp;
		}
	}

	quickSort(boy,0,M / 2 - 1);
	quickSort(girl,0,M / 2 - 1);
	pos_B = 0;
	pos_G = 0;
	for(i = 0;i < N;++i)
	{	

		while (pos_B < M / 2 && pos_G < M / 2 && boy[pos_B] - timer <=  0 && girl[pos_G] - timer <= 0)
		{
			boyW += timer - boy[pos_B++];
			girlW += timer - girl[pos_G++];
		}
		timer+=sing[i];
	}
	timer -= sing[N - 1];
	while (pos_B < M / 2 && pos_G < M / 2)
	{
		boyW += timer - boy[pos_B++];
		girlW += timer - girl[pos_G++];
		
	}

	cout << fixed << setprecision(2) << boyW / double(M / 2) << " " << girlW / double(M / 2) << endl;

	return 0;
}