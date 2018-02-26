#include<stdio.h>
#include<string.h>
#include<iostream>
using namespace std;

int map[101][101];
int x[101];

int main()
{
	int n, m, t, i, j, a, b,flag,flag1,xx,yy;
	scanf("%d", &t);

	for(int k = 0;k < t ;++k)
	{
		scanf("%d%d", &n, &m);
		if (m == 0)
		{
			printf("NO ODD SUBGRAPH\n");
			continue;
		}
		memset(x, 0, sizeof(x));
		memset(map, 0, sizeof(map));
		for (i = 0;i<m;i++)
		{
			scanf("%d%d", &a, &b);
			x[a]++;
			x[b]++;
			map[a][b]++;
			map[b][a]++;
		}
		flag = 0;
		for (i = 1;i <= n;i++)
		{
			if (x[i] % 2 == 0)
			{
				flag = 1;
				break;
			}
		}
		flag1 = 0;
		if (flag == 1)
		{
			flag1 = 0;
			for (i = 1;i <= n;i++)
			{
				for (j = i + 1;j <= n;j++)
				{
					if (map[i][j] % 2 == 1)
					{
						flag1 = 1;
						xx = i;
						yy = j;
						break;
					}
				}
				if (flag1 == 1)
					break;
			}
		}
		else
		{
			printf("ODD GRAPH\n");
			continue;
		}

		if (flag1 == 1)
		{
			printf("2 %d %d\n", xx, yy);
		}
		if (flag == 0 && flag1 == 0)
			printf("NO ODD SUBGRAPH\n");
	}

	return 0;
}
