#include<iostream>
using namespace std;

template <class elemType>
class linkStack
{
private:
	struct node
	{
		elemType data;
		node *next;
		node(const elemType &x, node *N = NULL)
		{
			data = x;
			next = N;
		}
		node() :next(NULL) {}
		~node() {}
	};

	node * elem;

public:
	linkStack() { elem = NULL; }

	~linkStack();

	bool isEmpty() const { return elem == NULL; }

	void push(const elemType &x)
	{
		node * tmp = new node(x, elem);
		elem = tmp;
	}

	elemType pop()
	{
		node *tmp = elem;
		elemType x = tmp->data;
		elem = elem->next;
		delete tmp;
		return x;
	}

	elemType top() const
	{
		return elem->data;
	}
};

template <class elemType>
linkStack<elemType>::~linkStack()
{
	node *tmp;
	while (elem != NULL)
	{
		tmp = elem;
		elem = elem->next;
		delete tmp;
	}
}

int main()
{
	int V,P,N,P_last=-1,V_last;
	linkStack<int> s;
	cin >> N;
	for (int i = 0;i < N;++i)
	{
		cin >> P >> V;
		

		if (!s.isEmpty())
		{
			if (P == P_last)
			{
				V_last = s.pop();
				V > V_last ? s.push(V_last):s.push(V);
			}
			while (!s.isEmpty() && s.top() > V)
			{
				s.pop();
			}
			s.push(V);

		}
		else
			s.push(V);
	}

	int count = 0;
	while (!s.isEmpty())
	{
		count++;
		s.pop();
	}
	cout << count << endl;


	return 0;
}