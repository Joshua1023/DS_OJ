#include <iostream>
using namespace std;

struct node
{
	int data;
	node *next, *prev;

	node(const int &x, node * n = NULL, node *p = NULL)
	{
		data = x;
		next = n;
		prev = p;
	}
	node() :next(NULL), prev(NULL) {}
	~node() {}
};

int main()
{
	int i, j, M, K, move,N,op,w,z;
	node *head, *tail, *tmp, *pos;
	cin >> M;

	head = new node;
	head->next = tail = new node;
	tail->prev = head;

	for (i = M;i > 0;--i)
	{
		pos = head->next;
		tmp = new node(i, pos, head);
		head->next = tmp;
		pos->prev = tmp;
	}
	pos = head->next;

	head->next->prev = tail->prev;
	tail->prev->next = pos;

	cin >> N;
	i = M;
	for (z = 0; z < N; ++z)
	{
		cin >> op;
		if (op == 0)
		{
			cin >> K;
			move = K % i;
			if (move == 0)
				pos = pos->prev;
			else
				for (j = 0;j<move - 1;++j)
					pos = pos->next;

			node *tmp2;
			tmp2 = pos;

			tmp2->prev->next = tmp2->next;
			tmp2->next->prev = tmp2->prev;

			pos = tmp2->next;
			delete tmp2;
			i--;
		}
		else
		{
			cin >> K >> w;
			move = K % i;
			if (move == 0)
				pos = pos->prev;
			else
				for (j = 0;j<move - 1;++j)
					pos = pos->next;

			tmp = new node(w, pos->next, pos);

			pos->next->prev = tmp;
			pos->next = tmp;
			pos = tmp;
			i++;
		}
	}
	int count = 0;
	for (z = 0;z < i;++z)
	{
		count += pos -> data;
		pos = pos->next;
		
	}

	cout << count << endl;

	return 0;
}