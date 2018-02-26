#include<iostream>
#include<string.h>
using namespace std;

template<class elemType>
class priorityQueue
{
private:
	int currentSize;
	elemType * array;
	int maxSize;
	void doubleSpace();
	void buildHeap();
	void percolateDown(int hole);

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
	int findMin(elemType x)
	{
		elemType Min;
		int ID = -1;

		for(int i = 1;i <= currentSize;++i)
			if (array[i] > x && (ID == -1 || array[i] < Min))
			{
				Min = array[i];
				ID = i;
			}

		return ID;
	}

	void decreaseKey(int i, elemType value)
	{
		elemType x;
		int hole;

		array[hole = i] -= value;
		for(x = array[i];hole > 1 && x < array[hole / 2];hole /= 2)
			array[hole] = array[hole / 2];
		array[hole] = x;
	}

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
priorityQueue<elemType>::priorityQueue(const elemType *items, int size):maxSize(size + 10), currentSize(size)
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

int main()
{
	int ops, num,num2;
	char op_name[9];
	cin >> ops;

	priorityQueue<int> heap(ops);

	for (int i = 0; i < ops; ++i)
	{
		cin >> op_name;

		if (!strcmp(op_name, "find"))
		{
			cin >> num;
			cout << heap.findMin(num) << endl;
		}			
		else if (!strcmp(op_name, "insert"))
		{
			cin >> num;
			heap.enQueue(num);
		}
		else if (!strcmp(op_name, "decrease"))
		{
			cin >> num >> num2;
			heap.decreaseKey(num,num2);
		}

	}

	return 0;
}