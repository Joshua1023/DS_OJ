#include<iostream>
#include<stdio.h>
#include<string.h>
using namespace std;

class OutOfBound {};
class IllegalSize {};

template<class elemType>
class linkList
{
private:
	struct node
	{
		elemType data;
		node *prev, *next;

		node(const elemType &x, node *p = NULL, node * n = NULL)
		{
			data = x;
			next = n;
			prev = p;
		}
		node() :next(NULL), prev(NULL) {}
		~node() {}
	};

	node *head, *tail;
	int currentLength;

	node * move(int i) const;

public:
	linkList();
	~linkList() { clear();delete head; delete tail; }

	void clear();
	int length() const { return currentLength; }
	void insert(int i, const elemType &x);
	void remove(int i);
	int search(const elemType &x) const;
	elemType visit(int i) const;
	void pushback(const elemType &x)
	{
		node *pos, *tmp;

		pos = tail;
		tmp = new node(x, pos->prev, pos);
		pos->prev->next = tmp;
		pos->prev = tmp;

		++currentLength;
	}
	void traverse() const;
};

template <class elemType>
typename linkList<elemType>::node *linkList<elemType>::move(int i) const
{
	node *p = head->next;
	if (i < 0 || i > currentLength) throw OutOfBound();
	while (i--) p = p->next;

	return p;
}

template <class elemType>
linkList<elemType>::linkList()
{
	head = new node;
	head->next = tail = new node;
	tail->prev = head;
	currentLength = 0;
}

template <class elemType>
void linkList<elemType>::clear()
{
	node * p = head->next, *q;
	head->next = tail;
	tail->prev = head;
	while (p != tail)
	{
		q = p->next;
		delete p;
		p = q;
	}
	currentLength = 0;
}

template <class elemType>
void linkList<elemType>::insert(int i, const elemType &x)
{
	node *pos, *tmp;

	pos = move(i);
	tmp = new node(x, pos->prev, pos);
	pos->prev->next = tmp;
	pos->prev = tmp;

	++currentLength;
}

template<class elemType>
void linkList<elemType>::remove(int i)
{
	node *pos;

	pos = move(i);
	pos->prev->next = pos->next;
	pos->next->prev = pos->prev;

	delete pos;
	--currentLength;
}

template <class elemType>
int linkList<elemType>::search(const elemType &x) const
{
	node *p = head->next;
	int i = 0;

	while (p != tail && p->data != x)
	{
		p = p->next;
		++i;
	}

	if (p == tail) return -1;
	else return i;
}

template <class elemType>
elemType linkList<elemType>::visit(int i) const
{
	node *p = move(i);

	return p->data;
}

template <class elemType>
void linkList<elemType>::traverse() const
{
	node *p = head->next;
	while (p != tail)
	{
		printf("%c", p->data);
		p = p->next;
	}
	printf("\n");
}
linkList<char> l;

template<class elemType>
class BinarySearchTree
{
private:
	struct BinaryNode
	{
		elemType data;
		BinaryNode *left;
		BinaryNode *right;
		BinaryNode(const elemType & d, BinaryNode * l, BinaryNode *r)
		{
			data = d;left = l;right = r;
		}
	};
	BinaryNode *root;
	void change(BinaryNode* &t)
	{

		if (t->right != NULL)
			t = t->right;
	}


	void insert(const elemType &x, BinaryNode* &t);
	void remove(const elemType &x, BinaryNode* &t);
	bool find(const elemType &x, BinaryNode *t) const;
	void delLess(const elemType &x, BinaryNode* &t);
	void delGreat(const elemType &x, BinaryNode* &t);
	void delRange(const elemType &x, const elemType &y, BinaryNode* &t);
	bool findKmax(int i, elemType &x, BinaryNode* &t);
	int size(BinaryNode *t) const
	{
		if (t == NULL) return 0;
		return 1 + size(t->left) + size(t->right);
	}
	void makeEmpty(BinaryNode* &t)
	{
		if (t != NULL)
		{
			if (t->left != NULL)
				makeEmpty(t->left);

			if (t->right != NULL)
				makeEmpty(t->right);
			delete t;
		}

	}

public:
	BinarySearchTree(BinaryNode *t = NULL) { root = t; }
	bool find(const elemType &x) const;
	void insert(const elemType &x);
	void remove(const elemType &x);
	void delLess(const elemType &x);
	void delGreat(const elemType &x);
	void delRange(const elemType &x, const elemType &y);
	bool findKmax(int i, elemType &x);
};

template<class elemType>
bool BinarySearchTree<elemType>::find(const elemType &x) const
{
	l.pushback('*');
	return find(x, root);
}

template<class elemType>
bool BinarySearchTree<elemType>::find(const elemType &x, BinaryNode *t) const
{
	if (t == NULL)
		return false;
	else if (x < t->data)
	{
		l.pushback('l');
		return find(x, t->left);
	}

	else if (t->data < x)
	{
		l.pushback('r');
		return find(x, t->right);
	}

	else
		return true;
}

template<class elemType>
void BinarySearchTree<elemType> ::insert(const elemType &x)
{
	insert(x, root);
}

template<class elemType>
void BinarySearchTree<elemType> ::insert(const elemType &x, BinaryNode* &t)
{
	if (t == NULL)
		t = new BinaryNode(x, NULL, NULL);
	else if (x < t->data)
		insert(x, t->left);
	else if (x > t->data)
		insert(x, t->right);
}

template<class elemType>
void BinarySearchTree<elemType> ::remove(const elemType &x)
{
	remove(x, root);
}

template<class elemType>
void BinarySearchTree<elemType> ::remove(const elemType &x, BinaryNode* &t)
{
	if (t == NULL) return;
	if (x < t->data) remove(x, t->left);
	else if (t->data < x)	remove(x, t->right);
	else if (t->right != NULL)
	{
		BinaryNode *tmp = t->right, *tmp_p = t->right;
		if (tmp->left != NULL) tmp = tmp->left;
		while (tmp->left != NULL)
		{
			tmp_p = tmp;
			tmp = tmp->left;
		}
		t->data = tmp->data;
		if (t->right == tmp)
			t->right = tmp->right;
		else
			tmp_p->left = tmp->right;

		delete tmp;
	}
	else
	{
		BinaryNode * oldNode = t;
		t = (t->left != NULL) ? t->left : t->right;
		delete oldNode;
	}
}

template<class elemType>
void BinarySearchTree<elemType> ::delLess(const elemType &x)
{
	delLess(x, root);
}

template<class elemType>
void BinarySearchTree<elemType> ::delLess(const elemType &x, BinaryNode* &t)
{
	if (t == NULL) return;
	if (t->data < x)
	{
		BinaryNode *tmp = t;
		t = t->right;
		makeEmpty(tmp->left);
		delete tmp;
		delLess(x, t);
	}
	else delLess(x, t->left);
}

template<class elemType>
void BinarySearchTree<elemType> ::delGreat(const elemType &x)
{
	delGreat(x, root);
}

template<class elemType>
void BinarySearchTree<elemType> ::delGreat(const elemType &x, BinaryNode* &t)
{
	if (t == NULL) return;
	if (t->data > x)
	{
		BinaryNode *tmp = t;
		t = t->left;
		makeEmpty(tmp->right);
		delete tmp;
		delGreat(x, t);
	}
	else delGreat(x, t->right);
}

template<class elemType>
void BinarySearchTree<elemType> ::delRange(const elemType &x, const elemType &y)
{
	delRange(x, y, root);
}

template<class elemType>
void BinarySearchTree<elemType> ::delRange(const elemType &x, const elemType &y, BinaryNode* &t)
{
	if (t == NULL) return;
	if (t->data <= x) delRange(x, y, t->right);
	else if (t->data >= y) delRange(x, y, t->left);
	else
	{
		remove(t->data, t);
		delRange(x, y, t);
	}
}

template<class elemType>
bool BinarySearchTree<elemType> ::findKmax(int i, elemType &x)
{
	return findKmax(i, x, root);
}

template<class elemType>
bool BinarySearchTree<elemType> ::findKmax(int i, elemType &x, BinaryNode* &t)
{
	if (t == NULL) return false;
	int ls = size(t->left);
	if (ls == i - 1)
	{
		x = t->data;
		return true;
	}
	if (ls >= i) return findKmax(i, x, t->left);
	else return findKmax(i - ls - 1, x, t->right);
}



int main()
{
	long long ops, t;
	char op;
	BinarySearchTree<long long> tree;

	cin >> ops;
	for (int i = 0;i < ops;i++)
	{
		scanf("%c", &op);
		while (op == '\n')
			scanf("%c", &op);

		if (op == '+')
		{
			scanf("%lld", &t);
			tree.insert(t);
		}
		else if (op == '-')
		{
			scanf("%lld", &t);
			tree.remove(t);
		}

		else if (op == '*')
		{
			scanf("%lld", &t);
			if (tree.find(t))
			{
				l.traverse();

			}
			else
				printf("Nothing.\n");
			l.clear();
		}


	}

	return 0;
}
