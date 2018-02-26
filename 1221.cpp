#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
using namespace std;

const int minInt = 1 << 31;
const int maxInt = minInt - 1;

struct dot
{
	int c, num, size;
	dot *son[2], *up; // son[false]是左孩子，son[true]是右孩子，up是父亲

	dot(int value = 0) { c = value; num = size = 1; son[false] = son[true] = up = 0; }
	bool get(dot *lr) { return son[true] == lr; }
	void add_up(int n) { for (dot *u = this;u;u = u->up) u->size += n; }
	dot* born(bool k, dot* lr)
	{
		son[k] = lr;
		if (lr) { lr->up = this; add_up(lr->size); }
		return this;
	}
	dot* kill(bool k)
	{
		dot *lr = son[k]; son[k] = 0;
		if (lr) { lr->up = 0; add_up(-lr->size); }
		return lr;
	}
};

int vv(dot *u) { return u ? u->c : 0; }
int nn(dot *u) { return u ? u->num : 0; }
int ss(dot *u) { return u ? u->size : 0; }

class Splay
{
public:
	dot *Root, *Min, *Max;
private:
	void zg(dot *x)
	{
		dot *y = x->up, *z = y->up;
		bool i = (z ? z->get(y) : 0), k = y->get(x); // 此处i==0时，i无意义

		if (z) z->kill(i);
		x->born(!k, y->born(k, y->kill(k)->kill(!k)));
		if (z) z->born(i, x);

		if (y == Root) Root = x; // 维护Root，可能也是保险?no!This is useful!
	}
	void splay(dot *x, dot *up = 0) // 将x旋转到其父亲为up的位置
	{
		dot *y, *z;
		while (x->up != up) // x还没到指定位置
		{
			y = x->up; if (y->up == up) { zg(x); break; } // 如果y是指定位置，则将x旋转到y
			z = y->up; zg((z->get(y) == y->get(x)) ? y : x); zg(x); // 将x旋转到z即可
		}
	}
	void recycle(dot *p)
	{
		if (!p) return;
		recycle(p->son[false]); recycle(p->son[true]);
		delete p;
	}
	dot* next(dot *p, bool k)
	{
		splay(p);

		dot *u = p->son[k];
		while (u->son[!k]) u = u->son[!k];
		return u;
	}
public:
	Splay()
	{
		Min = Root = new dot(minInt); Max = new dot(maxInt);
		Min->born(true, Max);
	}
	int size() { return Root->size - 2; }
	dot* Find(int c)
	{
		dot *u = Root;
		while (u&&u->c != c) u = u->son[c>u->c];
		return u;
	}

	void Insert(int c)
	{
		bool k;
		dot *u = 0, *v = Root;

		while (v&&v->c != c)
		{
			u = v;
			k = (c>v->c);
			v = v->son[k];
		}
		if (v) { ++v->num; v->add_up(1); }
		else splay(u->born(k, new dot(c))->son[k]);
	}
	void Delete(int c)
	{
		dot *p = Find(c), *l, *r;

		--p->num; p->add_up(-1);
		if (p->num == 0)
		{
			l = next(p, false); r = next(p, true);
			splay(l); splay(r, Root);
			recycle(r->kill(false));
		}
	}
	void Delete(int cl, int cr)
	{
		dot *L, *R, *l, *r;

		Insert(cl); Insert(cr);
		L = Find(cl); R = Find(cr);

		l = next(L, false); r = next(R, true);
		splay(l); splay(r, Root);
		recycle(r->kill(false));
	}
	int Find_ith(int i, dot *u) // 这里的三种情况，用到了其先后顺序，故顺序不能轻易改变
	{
		int size = ss(u->son[false]), mid = u->num;
		if (i <= size) return Find_ith(i, u->son[false]);
		if (i <= size + mid) return u->c;
		return Find_ith(i - size - mid, u->son[true]);
	}
};

Splay A; // 创建一棵Splay树，名叫A

int main()
{

	int n, x, y; cin >> n;
	string order;
	for (int i = 1;i <= n;++i)
	{
		cin >> order;
		if (order == "insert") { cin >> x; A.Insert(x); }
		if (order == "delete") { cin >> x; A.Delete(x); }
		if (order == "delete_less_than") { cin >> y; A.Delete(minInt + 1, y - 1); }
		if (order == "delete_greater_than") { cin >> x; A.Delete(x + 1, maxInt - 1); }
		if (order == "delete_interval") { cin >> x >> y; A.Delete(x + 1, y - 1); }
		if (order == "find") { cin >> x; cout << (A.Find(x) ? "Y" : "N") << endl; }
		if (order == "find_ith")
		{
			cin >> x;
			if (A.size()<x) { cout << "N" << endl; continue; }
			cout << A.Find_ith(x + 1, A.Root) << endl; // 有一个Min，所以得找第x+1个
		}
	}

	return 0;
}
