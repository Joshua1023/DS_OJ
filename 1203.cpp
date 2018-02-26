#include<iostream>
#include<list>

using namespace std;

int main()
{
	char type[7];
	int len1,len2,i;
	cin >> type;
	cin >> len1;
	cin >> len2;
	if (!strcmp(type, "int"))
	{
		int itmp;
		list<int> merge_list;
		list<int>::iterator itr,itr_end;
		for (i = 0; i < len1;++i)
		{
			cin >> itmp;
			merge_list.push_back(itmp);
		}
		for (i = 0; i < len2;++i)
		{
			cin >> itmp;
			merge_list.push_back(itmp);
		}
		itr_end = merge_list.end();
		for(itr = merge_list.begin();itr!=itr_end;++itr)
			cout << *itr << ' ';
		cout << endl;
	}
	if (!strcmp(type, "char"))
	{
		char ctmp;
		list<char> merge_list;
		list<char>::iterator itr,itr_end;
		for (i = 0; i < len1;++i)
		{
			cin >> ctmp;
			merge_list.push_back(ctmp);
		}
		for (i = 0; i < len2;++i)
		{
			cin >> ctmp;
			merge_list.push_back(ctmp);
		}
		itr_end = merge_list.end();
		for (itr = merge_list.begin();itr != itr_end;++itr)
			cout << *itr << ' ';
		cout << endl;
	}
	if (!strcmp(type, "double"))
	{
		double dtmp;
		list<double> merge_list;
		list<double>::iterator itr,itr_end;
		for (i = 0; i < len1;++i)
		{
			cin >> dtmp;
			merge_list.push_back(dtmp);
		}
		for (i = 0; i < len2;++i)
		{
			cin >> dtmp;
			merge_list.push_back(dtmp);
		}
		itr_end = merge_list.end();
		for (itr = merge_list.begin();itr != itr_end;++itr)
			cout << *itr << ' ';
		cout << endl;
	}

	return 0;
}