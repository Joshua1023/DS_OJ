#include<iostream>
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

void quickSort(int s[], int l, int r)
{
	if (l< r)
	{
		int i = l, j = r, x = s[l];
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

int main()
{
	int M,S,C,i,result,cur_num = 1;
	priorityQueue<int> q;
	cin >> M >> S >>C;

	int *cow = new int[C];
	for(i = 0;i < C;++i)
		cin >> cow[i];
	quickSort(cow,0,C - 1);

	for(i = 1;i < C;++i)
		if (cow[i] - cow[i - 1]>1)
		{
			cur_num += 1;
			q.enQueue(cow[i] - cow[i-1] - 1);
		}
	result = C;

	for(i = 0;i < cur_num - M;++i)
		if(!q.isEmpty())
			result += q.deQueue();

	cout << result << endl;

	return 0;
}
