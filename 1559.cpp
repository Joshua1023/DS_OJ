#include<iostream>
using namespace std;

struct point
{
	int p_x;
	int p_y;
	point() {}
	point(int x, int y)
	{
		p_x = x;
		p_y = y;
	}
	point(point &x)
	{
		p_x = x.p_x;
		p_y = x.p_y;
	}
};

point * GPoint, *HPoint;
int H_num = 0, G_num = 0, maxPoint = 0, minS = 1000000;

void findReg(point *Gp,point *Hp,int g_num,int h_num)
{
	int i ;

	if(h_num < maxPoint)  return;

	if (g_num)
	{
		point *Gpart1 = new point[g_num + 1], *Hpart1 = new point[h_num + 1];
		int g_num1 = 0, h_num1 = 0;
		point *Gpart2 = new point[g_num + 1], *Hpart2 = new point[h_num + 1];
		int g_num2 = 0, h_num2 = 0;
		point *Gpart3 = new point[g_num + 1], *Hpart3 = new point[h_num + 1];
		int g_num3 = 0, h_num3 = 0;
		point *Gpart4 = new point[g_num + 1], *Hpart4 = new point[h_num + 1];
		int g_num4 = 0, h_num4 = 0;

		for (i = 0;i < g_num;++i)
		{
			if (Gp[i].p_x < Gp[0].p_x)
			{
				Gpart1[g_num1++] = Gp[i];
			}
			else if (Gp[i].p_x > Gp[0].p_x)
			{
				Gpart2[g_num2++] = Gp[i];
			}

			if (Gp[i].p_y < Gp[0].p_y)
			{
				Gpart3[g_num3++] = Gp[i];
			}
			else if (Gp[i].p_y > Gp[0].p_y)
			{
				Gpart4[g_num4++] = Gp[i];
			}
		}
		for (i = 0;i < h_num;++i)
		{
			if (Hp[i].p_x < Gp[0].p_x)
			{
				Hpart1[h_num1++] = Hp[i];
			}
			else if (Hp[i].p_x > Gp[0].p_x)
			{
				Hpart2[h_num2++] = Hp[i];
			}
			if (Hp[i].p_y < Gp[0].p_y)
			{
				Hpart3[h_num3++] = Hp[i];
			}
			else if (Hp[i].p_y > Gp[0].p_y)
			{
				Hpart4[h_num4++] = Hp[i];
			}
		}

		findReg(Gpart1,Hpart1,g_num1,h_num1);
		findReg(Gpart2, Hpart2, g_num2, h_num2);
		findReg(Gpart3, Hpart3, g_num3, h_num3);
		findReg(Gpart4, Hpart4, g_num4, h_num4);

		delete [] Gpart1;
		delete [] Hpart1;
		delete[] Gpart2;
		delete[] Hpart2;
		delete[] Gpart3;
		delete[] Hpart3;
		delete[] Gpart4;
		delete[] Hpart4;

	}
	else
	{
		int cnt = 0, mUp = 0, mDown = 1000, mLeft = 1000, mRight = 0, S;
		for (i = 0;i < h_num;++i)
		{
			if (Hp[i].p_x  < mLeft)
				mLeft = Hp[i].p_x;
			if (Hp[i].p_x  > mRight)
				mRight = Hp[i].p_x;
			if (Hp[i].p_y > mUp)
				mUp = Hp[i].p_y;
			if (Hp[i].p_y < mDown)
				mDown = Hp[i].p_y;
			cnt++;
		}

		S = (mUp - mDown) * (mRight - mLeft);
		if (cnt > maxPoint)
		{
			maxPoint = cnt;
			minS = S;
		}
		else
			if (cnt == maxPoint)
				if (minS > S)
					minS = S;
	}

}



int main()
{
	int N, x, y;
	char type;

	cin >> N;
	GPoint = new point[N];
	HPoint = new point[N];
	for (int i = 0;i < N;++i)
	{
		cin >> x >> y >> type;
		if (type == 'H')
			HPoint[H_num++] = point(x, y);
		else
			GPoint[G_num++] = point(x, y);
	}

	findReg(GPoint,HPoint,G_num,H_num);

	cout << maxPoint << ' ' << minS << endl;

	return 0;
}
