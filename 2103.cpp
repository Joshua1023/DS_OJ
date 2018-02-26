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
	int i, j, k, M,move,N,num,start;
	node *head, *tail, *tmp, *pos,*eat_next;
	int last;
	cin >> M;
	bool flag;

	node *tmp2;

	for (j = 0;j < M;++j)
	{
		cin >> N;
		num = 8 * N;
		head = new node;
		head->next = tail = new node;
		tail->prev = head;

		for (i = num;i > 0;--i)
		{
			pos = head->next;
			tmp = new node(i, pos, head);
			head->next = tmp;
			pos->prev = tmp;
		}
		pos = head->next;
		head->next->prev = tail->prev;
		tail->prev->next = pos;

		eat_next = pos;
		last = 0;
		for (i = 0;i < 7;++i)
		{

			flag = true;
			cin >> move;

			pos = eat_next;
			start = pos->data;

			while (num > 0)
			{

				for (k = 0;k < move - 1;++k)
				{
					pos = pos->next;
					if (pos->data == start)
					{
						flag = false;
						break;

					}
				}
				if (!flag)
					break;

				for (k = 0;k < move;++k)
				{
					pos = pos->next;
					last = pos->prev->data;
					tmp2 = pos->prev;
					tmp2->prev->next = tmp2->next;
					tmp2->next->prev = tmp2->prev;
					delete tmp2;
					eat_next = pos;
					num--;

					if (pos->data == start)
					{
						flag = false;
						break;
					}
				}
				if (!flag)
					break;
			}
		}

		cout << last << endl;

		while (num)
		{
			node *tmp = pos;
			pos = pos->next;
			delete tmp;
			num--;
		}

	}

	return 0;
}
