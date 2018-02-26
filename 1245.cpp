#include<iostream>
#include<math.h>
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

int opers(char op)
{
	switch (op)
	{
	case '(':return 100;
	case ')':return 900;
	case '+':return 100;
	case '-':return 100;
	case '*':return 200;
	case '/':return 200;
	}
}

int main()
{
	int i=0,j,z=0,val,num1,num2,type,last_type;
	char ch,tmp,change[1000],expression[1000];
	linkStack<char> s,prefix;
	linkStack<int> cal;

	cin.getline(expression,1000);

	z = 0;
	j = strlen(expression) - 1;

	while (j>=0)
	{

		tmp = expression[j];
		if (tmp == ' ')
		{
			j--;
			continue;
		}
		if (tmp <= '9' && tmp >= '0')
		{
			if (j > 0)
			{
				if (expression[j - 1] <= '9' && expression[j - 1] >= '0')
				{
					prefix.push(tmp);
				}
				else
				{
					prefix.push(tmp);
					prefix.push(' ');
				}
			}
			else
			{
				prefix.push(tmp);
				prefix.push(' ');
			}
		}

		else
		{
			if(tmp == ')')
				s.push(tmp);

			else
				if (tmp == '(')
			{
				while (!s.isEmpty())
				{
					if (s.top() == ')')
					{
						s.pop();
						break;
					}
					else
					{
						prefix.push(s.top());
						prefix.push(' ');
						s.pop();
					}
				}
			}
				else
			{
				while (!s.isEmpty() && s.top() != ')' && (opers(s.top()) > opers(tmp)))
				{
					prefix.push(s.top());
					prefix.push(' ');
					s.pop();
				}
				s.push(tmp);

			}
		}
		j--;
	}


	while (!s.isEmpty())
	{
		prefix.push(s.top());
		prefix.push(' ');
		s.pop();
	}

	i = 0;
	prefix.pop();

	while (!prefix.isEmpty())
	{
			change[i++] = prefix.top();
			prefix.pop();
	}
	change[i] = '\0';

	cout << change << endl;

	for (j = i - 1;j >= 0;--j)
	{
		tmp = change[j];
		if (tmp <= '9' && tmp >= '0')
		{
			val = 0;
			z = 0;
			while (tmp <= '9' && tmp >= '0')
			{
				val += int(pow(10,z++)) * (tmp - '0');
				--j;
				tmp = change[j];
			}
			cal.push(val);
		}

		if(tmp == '+' || tmp == '-' || tmp == '*' || tmp == '/')
		{
			num2 = cal.pop();
			num1 = cal.pop();
			switch (tmp)
			{
			case '+':cal.push(num2 + num1);break;
			case '-':cal.push(num2 - num1);break;

			case '*':cal.push(num2 * num1);break;
			case '/':cal.push(num2 / num1);break;
			case ' ':break;
			}

		}

	}
	cout << cal.top() << endl;

	return 0;
}
