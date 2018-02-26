#include<iostream>
using namespace std;

int a[100001], b[100001], w[100001], parent[100001];
void Union(int r1, int r2)
{
	if (r1 == r2)
		return;
	if (parent[r1]<parent[r2])
	{
		parent[r1] += parent[r2];
		parent[r2] = r1;
	}
	else {
		parent[r2] += parent[r1];
		parent[r1] = r2;
	}
}

int Find(int x)
{
	if (parent[x]<0)
		return  x;
	else
		return Find(parent[x]);
}

void swap(int&x, int &y)
{
	int t = x;x = y;y = t;
}

void qsort(int l, int r, int w[], int a[], int b[])
{
	if (l >= r) return;
	int i = l;int j = r;
	int mid = w[(i + j) / 2];
	while (i <= j)
	{
		while (w[i]<mid) ++i;
		while (w[j]>mid) --j;
		if (i <= j)
		{
			swap(w[i], w[j]);swap(a[i], a[j]);swap(b[i], b[j]);
			++i;--j;
		}

	}
	qsort(l, j, w, a, b);
	qsort(i, r, w, a, b);
}

int main()
{
	int n, m;cin >> n >> m;
	for (int i = 1;i <= m;++i)
	{
		cin >> a[i] >> b[i] >> w[i];
	}
	qsort(1, m, w, a, b);
	for (int i = 1;i <= n;++i) parent[i] = -1;
	int cnt = 0;
	int u, v;
	int i = 1;
	int vers = 0;
	while (vers != n - 1)
	{
		u = Find(a[i]);
		v = Find(b[i]);
		if (u != v)
		{
			Union(u, v);
			vers++;
			cnt += w[i];
		}
		++i;
	}
	cout << cnt << endl;

	return 0;
}
