#include <iostream>
#include <algorithm>
#include<stdio.h>
using namespace std;

struct Point
{
	int x;
	int y;
	int z;
};

int n;
const int MAXN = 100000;

Point points[MAXN];
int curx[MAXN];
int cury[MAXN];

bool cmpPoint(const Point& a, const Point& b)
{
	if (a.x != b.x) {
		return a.x<b.x;
	}
	else
		return a.y<b.y;
}

void quickSort(Point s[], int l, int r)
{
	if (l< r)
	{
		int i = l, j = r;
		Point x = s[l];

		while (i < j)
		{
			while (i < j && !cmpPoint(s[j] , x))
				j--;
			if (i < j)
				s[i++] = s[j];
			while (i < j && cmpPoint(s[i], x))
				i++;
			if (i < j)
				s[j--] = s[i];
		}
		s[i] = x;
		quickSort(s, l, i - 1);
		quickSort(s, i + 1, r);
	}
}

int find(int x, int y) {
	Point tofind;
	tofind.x = x;
	tofind.y = y;
	Point* f = lower_bound(points, points + n, tofind, cmpPoint);

	if (f != points + n && f->x == x && f->y == y)
		return f->z;
	return 0;
}

void exe() {
	int m;
	cin >> m;
	quickSort(points, 0, n - 1);
	for (int i = 0; i < m; ++i)
	{
		int op, x, y;
		scanf("%d %d %d", &op, &x, &y);
		if (op == 0) {
			swap(curx[x], curx[y]);
		}
		else if (op == 1)
			swap(cury[x], cury[y]);
		else {

			printf("%d\n", find(curx[x], cury[y]));
		}
	}
}


int main()
{
	int i;
	cin >> n;
	for (i = 0; i < n; ++i) {
		scanf("%d %d %d", &points[i].x, &points[i].y, &points[i].z);
	}

	for (i = 0; i < MAXN; ++i)
		curx[i] = i;
	for (i = 0; i < MAXN; ++i)
		cury[i] = i;

	exe();

	return 0;
}
