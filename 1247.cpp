#include<iostream>
using namespace std;

struct range {
	int begin; //开始位置
	int end;   //结束位置
};

void quickSort(range s[], int l, int r) //以开始位置从小到大的快速排序
{
	if (l< r)
	{
		int i = l, j = r;
		range x = s[l];
		while (i < j)
		{
			while (i < j && s[j].begin >= x.begin)
				j--;
			if (i < j)
				s[i++] = s[j];
			while (i < j && s[i].begin < x.begin)
				i++;
			if (i < j)
				s[j--] = s[i];
		}
		s[i] = x;
		quickSort(s, l, i - 1);
		quickSort(s, i + 1, r);
	}
}

int main()
{
	int i,L,m,res,b,e;
	cin >> L >> m;
	res = L + 1; //剩余树数
	range *skill = new range[m];

	for (i = 0;i < m;++i)
	{
		cin >> skill[i].begin >> skill[i].end;
	}

	quickSort(skill,0,m - 1);
	b = skill[0].begin;
	e = skill[0].end;

	for (i = 1;i < m;++i)
	{
		if(skill[i].begin <= e)//有重叠部分，更新结束位置
			e = e > skill[i].end? e:skill[i].end;
		else//无重叠部分，更新树数、开始位置、结束位置
		{
			res -= e - b + 1;
			b = skill[i].begin;
			e = skill[i].end;
		}
	}
	res -= e - b + 1;

	cout << res << endl;

	return 0;
}