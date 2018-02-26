#include<iostream>
using namespace std;

void move(char Matrix[15][15], int R_now, int C_now, int R_end, int C_end,int &count)
{


	if(R_now == R_end && C_now == C_end)
		count++;
	if(R_now < R_end && C_now < C_end)
		for(int i = R_now + 1; i <= R_end;++i)
			for (int j = C_now + 1;j <= C_end;++j)
			{
				if(Matrix[i][j] != Matrix[R_now][C_now])
					move(Matrix,i,j,R_end,C_end,count);
			}

}

int main()
{
	int R,C,i,j,count;

	cin >> R >> C;
	char Matrix[15][15];
	cin.get();
	for (i = 0;i < R;++i)
	{
		for (j = 0;j<C;++j)
			cin.get(Matrix[i][j]);
		cin.get();
	}


	count = 0;
	move(Matrix,0,0,R-1,C-1,count);

	cout << count << endl;

	return 0;
}
