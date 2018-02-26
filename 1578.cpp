#include<iostream>
using namespace std;

int min(int a, int b)
{
	return a < b ? a:b;
}

int max(int a, int b)
{
	return a > b ? a:b;
}

char by[1000][1000];
int Count[4][3];
int duijiao[4][3];
int n,m;

void renew(int i_H,int j_H)
{
	int c_C, c_D, c_M,i, begin_j, end_j, c_C2, c_D2, c_M2;

	c_C = 0;
	c_D = 0;
	c_M = 0;
	c_C2 = 0;
	c_D2 = 0;
	c_M2 = 0;
	for (i = i_H - 1;i >= 0;--i)
	{
		begin_j = max(-1, j_H - (i_H - i));
		end_j = min(m, j_H + (i_H - i));
		if (begin_j == -1 && end_j == m)
			break;

		if (begin_j > -1)
		{
			if (by[i][begin_j] == 'C')
				c_C += 1;
			else if (by[i][begin_j] == 'D')
				c_D += 1;
			else if (by[i][begin_j] == 'M')
				c_M += 1;
		}

		if (end_j < m)
		{
			if (by[i][end_j] == 'C')
				c_C2 += 1;
			else if (by[i][end_j] == 'D')
				c_D2 += 1;
			else if (by[i][end_j] == 'M')
				c_M2 += 1;
		}

	}
	duijiao[0][0] = c_C;
	duijiao[0][1] = c_D;
	duijiao[0][2] = c_M;
	duijiao[1][0] = c_C2;
	duijiao[1][1] = c_D2;
	duijiao[1][2] = c_M2;

	c_C = 0;
	c_D = 0;
	c_M = 0;
	c_C2 = 0;
	c_D2 = 0;
	c_M2 = 0;
	for (i = i_H + 1;i < n;++i)
	{
		begin_j = max(-1, j_H - (i - i_H));
		end_j = min(m, j_H + (i - i_H));
		if(begin_j == -1 && end_j == m)
			break;

		if (begin_j > -1)
		{
			if (by[i][begin_j] == 'C')
				c_C += 1;
			else if (by[i][begin_j] == 'D')
				c_D += 1;
			else if (by[i][begin_j] == 'M')
				c_M += 1;
		}

		if (end_j < m)
		{
			if (by[i][end_j] == 'C')
				c_C2 += 1;
			else if (by[i][end_j] == 'D')
				c_D2 += 1;
			else if (by[i][end_j] == 'M')
				c_M2 += 1;
		}

	}
	duijiao[2][0] = c_C;
	duijiao[2][1] = c_D;
	duijiao[2][2] = c_M;
	duijiao[3][0] = c_C2;
	duijiao[3][1] = c_D2;
	duijiao[3][2] = c_M2;

}

void add(int c, int d)
{
	Count[c][0] = Count[c][0] + duijiao[d][0];
	Count[c][1] = Count[c][1] + duijiao[d][1];
	Count[c][2] = Count[c][2] + duijiao[d][2];
}

void sub(int c, int d)
{

	Count[c][0] = Count[c][0] - duijiao[d][0];
	Count[c][1] = Count[c][1] - duijiao[d][1];
	Count[c][2] = Count[c][2] - duijiao[d][2];
}

void fix_add(int i_H, int j_H,int area)
{
	if (by[i_H][j_H] == 'C')
		Count[area][0]++;
	else if (by[i_H][j_H] == 'D')
		Count[area][1]++;
	else if (by[i_H][j_H] == 'M')
		Count[area][2]++;
}
void fix_sub(int i_H, int j_H,int area)
{
	if (by[i_H][j_H] == 'C')
		Count[area][0]--;
	else if (by[i_H][j_H] == 'D')
		Count[area][1]--;
	else if (by[i_H][j_H] == 'M')
		Count[area][2]--;
}

int main()
{
	char tmp;
	int i,j,N,z,i_H,j_H,c_C,c_D,c_M,begin_j,end_j,begin_i,end_i;

	cin >> n >> m;
	cin.get();
	for (i = 0;i < n;++i)
	{
		for (j = 0;j < m;++j)
		{
			cin.get(tmp);
			if (tmp != '\n')
				by[i][j] = tmp;
			if (tmp == 'H')
			{
				i_H = i;
				j_H = j;
			}
		}
		cin.get();
		continue;
	}


	c_C = 0;
	c_D = 0;
	c_M = 0;
	for (i = i_H - 1;i >= 0;--i)
	{
		begin_j = max(0, j_H - (i_H - i));
		end_j = min(m - 1, j_H + (i_H - i));
		for (j = begin_j;j <= end_j;++j)
		{
			if (by[i][j] == 'C')
				c_C += 1;
			else if (by[i][j] == 'D')
				c_D += 1;
			else if (by[i][j] == 'M')
				c_M += 1;
		}

	}
	Count[0][0] = c_C;
	Count[0][1] = c_D;
	Count[0][2] = c_M;

	c_C = 0;
	c_D = 0;
	c_M = 0;
	for (i = i_H + 1;i < m;++i)
	{
		begin_j = max(0, j_H - (i - i_H));
		end_j = min(m - 1, j_H + (i - i_H));
		for (j = begin_j;j <= end_j;++j)
		{
			if (by[i][j] == 'C')
				c_C += 1;
			else if (by[i][j] == 'D')
				c_D += 1;
			else if (by[i][j] == 'M')
				c_M += 1;
		}

	}
	Count[1][0] = c_C;
	Count[1][1] = c_D;
	Count[1][2] = c_M;

	c_C = 0;
	c_D = 0;
	c_M = 0;
	for (j = j_H + 1;j < n;++j)
	{
		begin_i = max(0, i_H - (j - j_H));
		end_i = min(n - 1, i_H + (j - j_H));
		for (i = begin_i;i <= end_i;++i)
		{
			if (by[i][j] == 'C')
				c_C += 1;
			else if (by[i][j] == 'D')
				c_D += 1;
			else if (by[i][j] == 'M')
				c_M += 1;
		}

	}
	Count[2][0] = c_C;
	Count[2][1] = c_D;
	Count[2][2] = c_M;

	c_C = 0;
	c_D = 0;
	c_M = 0;
	for (j = j_H - 1;j >= 0;--j)
	{
		begin_i = max(0, i_H - (j_H - j));
		end_i = min(n - 1, i_H + (j_H - j));
		for (i = begin_i;i <= end_i;++i)
		{
			if (by[i][j] == 'C')
				c_C += 1;
			else if (by[i][j] == 'D')
				c_D += 1;
			else if (by[i][j] == 'M')
				c_M += 1;
		}
	}
	Count[3][0] = c_C;
	Count[3][1] = c_D;
	Count[3][2] = c_M;

	renew(i_H,j_H);
	cin >> N;
	for (z = 0;z < N;++z)
	{
		cin >> tmp;
		if (tmp == 'N')
		{
			if (i_H != 0)
			{
				sub(0,0);
				sub(0,1);
				sub(3,2);
				sub(2,3);


				i_H -= 1;
				renew(i_H,j_H);
				add(1,2);
				add(1,3);
				fix_add(i_H+1, j_H, 1);
				add(2,1);
				add(3,0);
				cout << Count[0][0] << ' ' << Count[0][1] << ' ' << Count[0][2] << endl;
				fix_sub(i_H, j_H, 0);
			}
		}
		else if (tmp == 'S')
		{
			if (i_H != n - 1)
			{

				sub(1, 2);
				sub(1, 3);
				sub(3, 0);
				sub(2, 1);

				i_H += 1;
				renew(i_H, j_H);
				add(0, 0);
				add(0, 1);
				add(2, 3);
				add(3, 2);
				fix_add(i_H-1, j_H, 0);
				cout << Count[1][0] << ' ' << Count[1][1] << ' ' << Count[1][2] << endl;
				fix_sub(i_H, j_H, 1);
			}
		}

		else if (tmp == 'E')
		{
			if (j_H != m - 1)
			{

				sub(2, 1);
				sub(2, 3);
				sub(0, 0);
				sub(1, 2);

				j_H += 1;
				renew(i_H, j_H);;
				add(0, 1);
				add(1, 3);
				add(3, 0);
				add(3, 2);
				fix_add(i_H, j_H-1, 3);
				cout << Count[2][0] << ' ' << Count[2][1] << ' ' << Count[2][2] << endl;
				fix_sub(i_H, j_H, 2);
			}
		}
		if (tmp == 'W')
		{
			if (j_H != 0)
			{
				sub(3, 0);
				sub(3, 2);
				sub(0, 1);
				sub(1, 3);

				j_H -= 1;
				renew(i_H, j_H);
				add(0, 0);
				add(1, 2);
				add(2, 1);
				add(2, 3);
				fix_add(i_H, j_H+1, 2);
				cout << Count[3][0] << ' ' << Count[3][1] << ' ' << Count[3][2] << endl;
				fix_sub(i_H, j_H, 3);
			}
		}
	}

	return 0;
}
