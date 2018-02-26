#include<iostream>
using namespace std;

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

template<class elemType>
class set {
	friend set<elemType> operator* (const set<elemType> &a,const set<elemType> &b)
	{
		set<elemType> c;
		for (int i = 0;i < a.size;++i)
			if (b.exist(a.elem[i])) c.insert(a.elem[i]);
		return c;
	}

	friend set<elemType> operator+ (const set<elemType> &a, const set<elemType> &b)
	{
		set<elemType> c = a;
		for (int i = 0;i < b.size;++i)
			c.insert(b.elem[i]);
		return c;
	}
	friend set<elemType> operator- (const set<elemType> &a, const set<elemType> &b)
	{
		set<elemType> c;
		for (int i = 0;i < a.size;++i)
			if (!b.exist(a.elem[i])) c.insert(a.elem[i]);
		return c;
	}

private:
	elemType *elem;
	int size,maxSize;
	void doubleSpace();


public:
	set(int m = 20);
	set(const set<elemType> &a);
	~set(){delete [] elem; }

	set &operator = (const set<elemType> &a);
	int Get_Size() {return size;}
	bool exist(elemType x) const;
	bool insert(elemType x);
	bool erase(elemType x);
	void display();
	void clear(){size = 0;}
};

template<class elemType>
set<elemType>::set(int m)
{
	size = 0;
	maxSize = m;
	elem = new elemType[maxSize];
}

template<class elemType>
set<elemType>::set(const set<elemType> &a)
{
	size = a.size;
	maxSize = a.maxSize;
	elem = new elemType[maxSize];
	for(int i = 0;i < size; ++i) elem[i] = a.elem[i];
}

template<class elemType>
void set<elemType>::doubleSpace()
{
	maxSize *= 2;
	elemType *tmp = new elemType[maxSize];
	for(int i = 0;i < size;++i) tmp[i] = elem[i];
	delete [] elem;
	elem = tmp;
}

template<class elemType>
bool set<elemType>::exist(elemType x) const
{
	for(int i = 0;i < size;++i)
		if(elem[i] == x) return true;
	return false;
}

template<class elemType>
bool set<elemType>::insert(elemType x)
{
	if(exist(x)) return false;
	if(size == maxSize) doubleSpace();
	elem[size++] = x;
	return true;
}

template<class elemType>
bool set<elemType>::erase(elemType x)
{
	bool flag = false;
	int i;
	for(i = 0;i < size;++i)
		if (elem[i] == x)
		{
			flag = true;
			break;
		}
	if (flag)
	{
		for (;i < size - 1;++i)
			elem[i] = elem[i + 1];
		size--;
	}
	return flag;
}

template<class elemType>
set<elemType> &set<elemType>::operator=(const set<elemType> &a)
{
	size = a.size;
	maxSize = a.maxSize;
	delete [] elem;
	elem = new elemType[maxSize];
	for(int i = 0;i < size;++i) elem[i] = a.elem[i];
	return *this;
}

template<class elemType>
void set<elemType>::display()
{
	quickSort(elem,0,size - 1);
	for(int i = 0;i < size;++i)
		cout << elem[i] << " ";
	cout << endl;
}

int main()
{
	set<int> a(100),b(100);
	int i,j,op_num,numbers,tmp;
	char op;

	cin >> op_num;
	for (i = 0;i < op_num;++i)
	{
		cin >> op;
		if (op == '+')
		{
			cin >> numbers;
			for (j = 0;j < numbers;++j)
			{
				cin >> tmp;
				a.insert(tmp);
			}
			a.display();
		}

		else if (op == '*')
		{
			cin >> numbers;
			for (j = 0;j < numbers;++j)
			{
				cin >> tmp;
				if(a.exist(tmp)) b.insert(tmp);
			}
			a = b;
			b.clear();
			a.display();
		}
		else if (op == '-')
		{
			cin >> numbers;
			for (j = 0;j < numbers;++j)
			{
				cin >> tmp;
				b.insert(tmp);
			}
			a = a - b;
			b.clear();
			a.display();
		}
	}

	return 0;
}
