#include<iostream>
#include<string.h>
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
	char expression[101];
	linkStack<char> s;
	linkStack<int> pos;
	int length,i;

	cin.getline(expression,101);
	length = strlen(expression);
	char *error = new char[length+1];
	for(i=0;i<length;++i)
		error[i] = ' ';
	error[i] = '\0';


	for (i = 0;i < length;++i)
	{
		if (expression[i] == '(')
		{
			s.push('(');
			pos.push(i);
		}
		else
		if (expression[i] == ')')
		{
			if (!s.isEmpty())
			{
				if (s.top() == '(')
				{
					s.pop();
					pos.pop();
				}
				else
					error[i] = '?';
			}
			else
				error[i] = '?';
		}
	}
	while (!s.isEmpty())
	{
		s.pop();
		error[pos.pop()] = '$';
	}

	cout << expression << endl << error << endl;
	delete[] error;

	return 0;
}
