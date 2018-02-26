#include<iostream>
#include<list>
#include<string>
#include<string.h>
using namespace std;

void error()
{
	cout << "Error!"<<endl;
}

int getNum(char * &s)
{
	int num = 0;
	while(*s==' ')++s;
	if(*s >'9' || *s < '0')
		return -1;
	while(*s<='9'&&*s>='0' )
		num = num * 10 + *(s++) - '0';
	return num;
}

void List(char* s,list<string> *text)
{
	int beg,end,i;
	list<string>::iterator itr,itr_end,itr_check;

	beg = getNum(s);

	end = getNum(s);

	if (beg == -1 || end == -1)
	{
		error();
		return;
	}

	if (end < beg || beg < 1)
	{
		error();
		return;
	}

	itr = text->begin();
	itr_end = text->end();
	i= beg;
	while (--i)
	{
		++itr;
		if (itr == itr_end)
		{
			error();
			return;
		}
	}
	end -= beg -1;
	i = end;
	itr_check = itr;
	while (i--)
	{
		if (itr_check == itr_end)
		{
			error();
			return;
		}
		++itr_check;
    }
	while (end--)
	{
        cout << *itr << endl;
		++itr;
	}
}

void del(char* s, list<string> *text)
{
	int i,row,col,num;
	list<string>::iterator itr, itr_end;

	row = getNum(s);
	col = getNum(s);
	num = getNum(s);
	if (row == -1 || col == -1 || num == -1)
	{
		error();
		return;
	}
	i = row;
	itr = text->begin();
	itr_end = text->end();
	while (--i)
	{
		++itr;
		if (itr == itr_end)
		{
			error();
			return;
		}
	}
	if (col > int((*itr).size()))
	{
		error();
		return;
	}
	if (col+num-1 > int((*itr).size()))
	{
		error();
		return;
	}
	(*itr).erase(col - 1,num);
}

void ins(char* s, list<string> *text)
{
	int i, row, col;
	list<string>::iterator itr, itr_end;
	row = getNum(s);
	col = getNum(s);
	if(*s=='\0')
	{
		error();
		return;
	}
	s++;
	if (*s == '\0')
	{
		error();
		return;
	}

	if (row == -1 || col == -1)
	{
		error();
		return;
	}
	i = row;
	itr = text->begin();
	itr_end = text->end();
	while (--i)
	{
		++itr;
		if (itr == itr_end)
		{
			error();
			return;
		}
	}
	if (col > int((*itr).size()) + 1)
	{
		error();
		return;
	}
	else
	{
		if (col == int((*itr).size()) + 1)
			*itr = *itr + s;
		else
			(*itr).insert(col - 1, s);
	}

}

int main()
{
	list<string> text;
	list<string>::iterator itr, itr_end;
	char command[120],comName[10];
	int i;
	string str;

	while (true)
	{
		getline(cin, str, '\n');
		if (!str.compare("******"))
			break;
		text.push_back(str);
	}

	while (true)
	{
		cin.getline(command,120);
		for (i = 0;!(command[i] == ' ' || command[i] == '\0');++i);
		strncpy(comName,command,i);
		comName[i] = '\0';
		if (!strcmp(comName, "quit"))
		{
			break;
		}
		if(!strcmp(comName, "list"))
			List(command+i,&text);
		if (!strcmp(comName, "del"))
			del(command + i, &text);
		if (!strcmp(comName, "ins"))
			ins(command + i, &text);
	}
	itr_end = text.end();
	for (itr = text.begin();itr != itr_end;++itr)
	{
		cout << *itr << endl;
	}
	return 0;
}
