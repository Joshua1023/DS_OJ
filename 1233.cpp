#include <iostream>

using namespace std;
int M, cnt = 0;
class graph
{
private:
	struct edgeNode {
		int end;
		edgeNode*next;
		int weight;
		edgeNode(int e, int w, edgeNode*n)
		{
			end = e;weight = w;next = n;
		}
	};
	struct verNode {
		int ver;
		edgeNode *head;
		verNode(edgeNode*h = NULL)
		{
			head = h;
		}
	};
	verNode*verList;
	int vSize, eSize;
public:
	graph(int size) {
		vSize = size;
		eSize = 0;
		verList = new verNode[size + 1];
		for (int i = 1;i <= size;++i)
			verList[i].ver = i;
	}
	void insert(int u, int v, int weight)
	{
		verList[u].head = new edgeNode(v, weight, verList[u].head);
		eSize++;
	}
	void dfs(int depth, int start, bool visit[])
	{
		visit[start] = true;
		if (depth == M) { cnt++;return; }
		edgeNode* p = verList[start].head;
		while (p != NULL)
		{
			if (visit[p->end] == false)
			{
				visit[p->end] = true;
				dfs(depth + 1, p->end, visit);
				visit[p->end] = false;
			}
			p = p->next;
		}
		visit[start] = false;
	}
	void dfs(int depth, int start)
	{
		bool *visit = new bool[vSize + 1];
		for (int i = 1;i <= vSize;++i) visit[i] = false;

		dfs(depth, start, visit);
	}
};
int main()
{
	int n, m, start, u, v;
	cin >> n >> m >> start >> M;

	graph g(n);
	for (int i = 0;i<m;++i)
	{
		cin >> u >> v;
		g.insert(u, v, 1);
	}
	g.dfs(0, start);
	cout << cnt << endl;

	return 0;
}
