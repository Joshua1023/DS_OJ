#include<iostream>
using namespace std;
int matrix[6][6] = {0};
int path[7] = {0};
int dx[4] = {0,0,-1,1};
int dy[4] = { 1,-1,0,0 };
bool flag[32] = {false};

struct point
{
	int x;
	int y;
	int No;
	point()
	{
		x = 0;
		y = 0;
		No = 0;
	}
	point(int a, int b)
	{
		x = a;
		y = b;
		No = y + (x - 1) * 5;
	}
	point(int no)
	{
		No = no;
		y = no % 5;
		if(y == 0 && no > 0)
			y = 5;
		x = (no - 1) / 5 + 1;
	}

	bool checkPath()
	{
		for(int i = 0;i < 7;++i)
			if(path[i] == No)
				return true;
			else if(path[i] > No)
				return false;
		return false;
	}
};

point que[50];
void initial()
{
	int i,j;
	char tmp;

	for(i = 1;i < 6;++i)
		for (j = 1;j < 6;++j)
		{
			cin >> tmp;
			if(tmp == 'J')
				matrix[i][j] = 1;
		}

}

bool check()
{
	int i,front = 0, tail = 0;
	for(i = 0;i < 32;++i)
		flag[i] = false;

	point start(path[0]);
	que[tail++] = start;

	int sum = matrix[start.x][start.y];
	int cur = 1;
	while (front < tail)
	{
		point &pos = que[front];
		front++;
		flag[pos.No] = true;
		for (i = 0;i < 4;++i)
		{
			point next(pos.x + dx[i], pos.y + dy[i]);
			if(next.x > 5 || next.x < 1 || next.y > 5 || next.y < 1)
				continue;
			if (!flag[next.No] && next.checkPath())
			{
				flag[next.No] = true;
				cur++;
				sum += matrix[next.x][next.y];
				if(7 - cur + sum < 4)
					return false;
				que[tail++] = next;
			}
		}
	}
	return (cur == 7 && sum >= 4);
}

int main()
{
	initial();
	int cnt = 0;
	for(path[0] = 1;path[0] <= 19; path[0]++)
		for (path[1] = path[0] + 1;path[1] <= 20; path[1]++)
			for (path[2] = path[1] + 1; path[2] <= 21; path[2]++)
				for (path[3] = path[2] + 1; path[3] <= 22; path[3]++)
					for (path[4] = path[3] + 1; path[4] <= 23; path[4]++)
						for (path[5] = path[4] + 1; path[5] <= 24; path[5]++)
							for (path[6] = path[5] + 1; path[6] <= 25; path[6]++)
								cnt += check();

	cout << cnt <<endl;

	return 0;
}
