#include<iostream>
#include<string.h>

using namespace std;

template <class elemType>
class stack
{
public:
	virtual bool isEmpty() const = 0;
	virtual void push(const elemType &x) = 0;
	virtual elemType pop() = 0;
	virtual elemType top() const = 0;
	virtual ~stack() {}
};

template <class elemType>
class linkStack :public stack<elemType>
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
	int flag = 1, begin = 0;
	char txt[80];
	linkStack<char> stack;


	while (cin >> txt)
	{
		if (!strcmp(txt, "begin"))
		{
			if (!stack.isEmpty())
			{
				if (stack.top() == 'i')
				{
					flag = 0;
					break;
				}
				else
				{
					stack.push('b');
					continue;
				}
			}
			else
			{
				stack.push('b');
				continue;
			}

		}

		if (!strcmp(txt, "if"))
		{
			if (!stack.isEmpty())
			{
				if (stack.top() == 'i')
				{
					flag = 0;
					break;
				}
				else
				{
					stack.push('i');
					continue;
				}
			}
			else
			{
				stack.push('i');
				continue;
			}

		}

		if (!strcmp(txt, "end"))
		{
			if (!stack.isEmpty())
			{
				while (stack.top() == 't')
				{
					stack.pop();
				}
				if (stack.top() != 'b')
				{
					flag = 0;
					break;
				}
				else
				{
					stack.pop();
					continue;
				}
			}
			else
			{
				flag = 0;
				break;
			}

		}

		if (!strcmp(txt, "then"))
		{
			if (!stack.isEmpty())
			{
				if (stack.top() != 'i')
				{
					flag = 0;
					break;
				}
				else
				{
					stack.pop();
					stack.push('t');
					continue;
				}

			}
			else
			{
				flag = 0;
				break;
			}
		}
		if (!strcmp(txt, "else"))
		{
			if (!stack.isEmpty())
			{
				if (stack.top() != 't')
				{
					flag = 0;
					break;
				}
				else
				{
					stack.pop();
					continue;
				}
			}
			else
			{
				flag = 0;
				break;
			}
		}
	}

	while (!stack.isEmpty())
	{
		if (stack.top() == 't')
			stack.pop();
		else
		{
			flag = 0;
			break;
		}

	}

	if (flag && stack.isEmpty())
		cout << "Match!\n";
	else
		cout << "Error!\n";

	return 0;
}
