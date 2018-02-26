#include<iostream>
#include<stdio.h>
#include<string.h>
using namespace std;

struct Word
{
	char word[100];
	int word_len;
	int ori_id;
};

Word dic[1000000];

struct node
{
	bool isEnd;
	int sonNum;
	node* son[26];
	int id;
	node()
	{
		isEnd = false;
		sonNum = 0;
		id = -1;
		for(int i = 0;i < 26; ++i)
			son[i] = NULL;
	}
};

node *stack[1000000] = {0};

node *root;

void insert(char *word, int len, int id)
{
	node * pos = root;
	for (int i = 0;i < len; ++i)
	{
		int index = word[i] - 'a';
		if (pos->son[index] == NULL)
		{
			pos->son[index] = new node();
			pos->sonNum++;
		}

		if (i == len - 1)
		{
			pos->son[index]->isEnd = true;
			pos->son[index]->id = id;
		}

		pos = pos->son[index];
	}
}

bool cmp_word(const Word &a, const Word &b)
{
	int longer = a.word_len < b.word_len ? a.word_len:b.word_len;
	for (int i = 0;i < longer;++i)
	{
		if(a.word[i] == b.word[i])
			continue;
		return a.word[i] < b.word[i];
	}
	return a.word_len < b.word_len;
}

void quickSort_word(Word s[], int l, int r)
{
	if (l< r)
	{
		int i = l, j = r;
		Word x = s[l];
		while (i < j)
		{
			while (i < j && !cmp_word(s[j],x))
				j--;
			if (i < j)
				s[i++] = s[j];
			while (i < j && cmp_word(s[i], x))
				i++;
			if (i < j)
				s[j--] = s[i];
		}
		s[i] = x;
		quickSort_word(s, l, i - 1);
		quickSort_word(s, i + 1, r);
	}
}

int find(int cnt, char *pre, int len)
{
	node *pos = root;
	int cur_id;

	for (int i = 0;i < len;++i)
	{
		cur_id = pre[i] - 'a';
		if(pos->son[cur_id] != NULL)
			pos = pos->son[cur_id];
	}

	int top = 0;
	stack[top++] = pos;
	while (top > 0)
	{
		node *next = stack[--top];
		if(next->isEnd)
			return next->id;
		else
		{
			int haveAdded = 0;
			for (int i = 25;i >= 0;--i)
			{
				if (next->son[i] != NULL)
				{
					haveAdded++;
					stack[top++] = next->son[i];
					if(haveAdded == next->sonNum)
						break;
				}
			}
		}
	}
	return -1;
}

bool isIn(Word &word, char *pre, int len)
{
	if(word.word_len < len)
		return false;
	for(int i = 0;i < len;++i)
		if(word.word[i] != pre[i])
			return false;
	return true;
}

int main()
{
	int N,M,i,j;
	cin >> N >> M;
	root = new node();

	for (i = 1;i <= N;++i)
	{
		scanf("%s",dic[i].word);
		dic[i].word_len = strlen(dic[i].word);
		dic[i].ori_id = i;
	}

	quickSort_word(dic,1,N);

	for(i = 1; i <= N;++i)
		insert(dic[i].word,dic[i].word_len,i);

	char pre[1010];
	for (i = 0; i < M;++i)
	{
		j = 0; 
		scanf("%d %s",&j,pre);
		int first = find(j,pre,strlen(pre));

		if(first + j - 1 <= N && isIn(dic[first + j - 1],pre,strlen(pre)))
			cout << dic[first + j - 1].ori_id << endl;
		else
			cout << -1 << endl;
	}

	return 0;
}