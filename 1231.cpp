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

struct node {

	int parent, left, right, num;
};

node * elem;
int top;

int main()
{
	int X,Y,i;

	sb[0] = 1;
	for (int i = 1;i <= 15;i++)
	{
		sb[i] = sb[i - 1] << 1;
	}
	scanf("%d%d%d", &n,&X,&Y);
	elem = new node[n + 1];

	for (i = 1;i <= n;++i)
	{
		elem[i].parent = 0;
	}

	for (i = 1;i <= n;i++)
	{
		scanf("%d %d", &a, &b);
		elem[i].left = a;
		elem[i].right = b;
		if (a)
		{
			elem[a].parent = i;
			add(a,i);
			add(i,a);
		}


		if (b)
		{
			elem[b].parent = i;
			add(b,i);
			add(i,b);
		}

	}
	i = 1;
	while (elem[i].parent != 0)
	{
		i = elem[i].parent;
	}
	root = i;

	memset(visit, 0, sizeof(visit));

	bfs();

	int t = lca(X, Y);
	printf("%d\n",t);

	return 0;
}
