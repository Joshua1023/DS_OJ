#include <iostream>
#include <stack>
#include <cstdio>
#include <cstring>
using namespace std;

int k, n, m;
bool map[1000 + 5][1000 + 5];
bool vis[1000 + 5][1000 + 5];
int dx[4] = { 0,0,-1,+1 };
int dy[4] = { +1,-1,0,0 };
void init() {
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			int t;
			scanf("%d", &t);
			map[i][j] = t;
		}
	}
	memset(vis, 0, sizeof(vis));
}

struct Point
{
	int x;
	int y;
	int done;
	Point(int a, int b) {
		x = a;
		y = b;
		done = 0;
	}
};

bool build() {
	stack<Point> s;
	Point start(1, 1);
	s.push(start);
	while (!s.empty()) {
		Point cur = s.top();
		s.pop();
		vis[cur.x][cur.y] = true;
		for (int i = 0; i < 4; ++i)
		{
			int new_x = cur.x + dx[i];
			int new_y = cur.y + dy[i];
			if (new_x >= 1 && new_x <= n && new_y >= 1 && new_y <= m) {
				if (!vis[new_x][new_y]) {
					vis[new_x][new_y] = true;
					if (map[new_x][new_y] == false || cur.done == 0) {
						Point next(new_x, new_y);
						next.done = cur.done + map[new_x][new_y];
						if (next.done <= 1) {

							s.push(next);
							if (new_x == n && new_y == m)
								return true;
						}
					}
				}
			}
		}
	}
	return false;
}

int main()
{
	cin >> k;
	for (int i = 0; i < k; ++i)
	{
		init();
		cout << build() << endl;
	}
	return 0;
}
