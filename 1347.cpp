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
	int red=0,yellow=0,blue=0,len;
	linkStack<char> context,judge;
	char para[1001];

	cin.getline(para,1001);
	len = strlen(para);

	for(int i=0;i < len;++i)
	{
		if (para[i] == '<')
		{
			if (para[i + 1] == '/' && para[i + 2] == 'b' && para[i + 3] == 'l'&& para[i + 4] == 'u' && para[i + 5] == 'e' && para[i + 6] == '>')
			{
				i += 6;
				while (!context.isEmpty() && context.top() != '<')
				{
					blue++;
					context.pop();
				}
				context.pop();
			}
			else
				if (para[i + 1] == '/' && para[i + 2] == 'y' && para[i + 3] == 'e'&& para[i + 4] == 'l' && para[i + 5] == 'l' && para[i + 6] == 'o' && para[i + 7] == 'w' && para[i + 8] == '>')
				{
					i += 8;
					while (!context.isEmpty() && context.top() != '<')
					{
						yellow++;
						context.pop();
					}
					context.pop();
				}
				else
					if (para[i + 1] == '/' && para[i + 2] == 'r' && para[i + 3] == 'e'&& para[i + 4] == 'd' && para[i + 5] == '>')
					{
						i += 5;
						while (!context.isEmpty() && context.top() != '<')
						{
							red++;
							context.pop();
						}
						context.pop();
					}
					else
						if (para[i + 1] == 'b' && para[i + 2] == 'l'&& para[i + 3] == 'u' && para[i + 4] == 'e' && para[i + 5] == '>')
						{
							i+=5;
							context.push('<');
						}
						else
							if (para[i + 1] == 'y' && para[i + 2] == 'e'&& para[i + 3] == 'l' && para[i + 4] == 'l' && para[i + 5] == 'o' && para[i + 6] == 'w' && para[i + 7] == '>')
							{
								i += 7;
								context.push('<');
							}
							else
								if (para[i + 1] == 'r' && para[i + 2] == 'e'&& para[i + 3] == 'd' && para[i + 4] == '>')
								{
									i+=4;
									context.push('<');
								}
		}
		else
			if((para[i] <= 'z' && para[i] >= 'a') || (para[i] <= 'Z' && para[i] >= 'A'))
				context.push(para[i]);



	}

	cout << red << ' ' << yellow << ' ' << blue << endl;

	return 0;
}
