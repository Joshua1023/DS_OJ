#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;

const int maxn = 400005;
struct edge
{
	int to;
	int next;
}e[maxn];
int n;
int m;
int x, y, a, b;
int k = 0;
int head[maxn];
int root;
int sb[16];
int deep[maxn];
int queue[maxn];
int father[maxn][16];
bool visit[maxn];

void add(int u, int v)
{
	k++;
	e[k].to = v;
	e[k].next = head[u];
	head[u] = k;
}

void bfs()
{
	int qhead = 0;
	int tail = 1;
	queue[qhead] = root;
	visit[root] = 1;
	while (qhead<tail)
	{
		int now = queue[qhead++];
		for (int i = 1;i <= 15;i++)
		{
			if (sb[i] <= deep[now])
			{
				father[now][i] = father[father[now][i - 1]][i - 1];
			}
			else break;
		}
		int p = head[now];
		while (p != 0) {
			if (!visit[e[p].to])
			{
				deep[e[p].to] = deep[now] + 1;
				father[e[p].to][0] = now;
				visit[e[p].to] = 1;
				queue[tail++] = e[p].to;

			}
			p = e[p].next;
		}
	}
}
int lca(int a, int b)
{
	if (deep[a]<deep[b])
	{
		int temp = a;
		a = b;
		b = temp;
	}

	int t = deep[a] - deep[b];

	for (int i = 0;i <= 15;i++)
	{
		if (t&sb[i])//
		{
			a = father[a][i];
		}
	}
	for (int i = 15;i >= 0;i--)
	{
		if (father[a][i] != father[b][i])
		{
			a = father[a][i];
			b = father[b][i];
		}
	}

	if (a == b) return b;
	return father[a][0];
}
int main()
{
	sb[0] = 1;
	for (int i = 1;i <= 15;i++)
	{
		sb[i] = sb[i - 1] << 1;
	}
	scanf("%d", &n);
	for (int i = 1;i <= n;i++)
	{
		scanf("%d %d", &a, &b);
		if (b == -1) root = a;
		else
		{
			add(a, b);
			add(b, a);
		}
	}
	memset(visit, 0, sizeof(visit));

	bfs();
	scanf("%d", &m);
	for (int i = 1;i <= m;i++)
	{
		scanf("%d %d", &x, &y);
		int t = lca(x, y);
		if (x == t&&t != y) printf("1\n");
		else if (y == t&&x != t) printf("2\n");
		else printf("0\n");
	}

	return 0;
}
