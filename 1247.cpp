#include<iostream>
using namespace std;

struct range {
	int begin; //��ʼλ��
	int end;   //����λ��
};

void quickSort(range s[], int l, int r) //�Կ�ʼλ�ô�С����Ŀ�������
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
	res = L + 1; //ʣ������
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
		if(skill[i].begin <= e)//���ص����֣����½���λ��
			e = e > skill[i].end? e:skill[i].end;
		else//���ص����֣�������������ʼλ�á�����λ��
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