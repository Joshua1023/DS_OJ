#include<iostream>
#include<map>
using namespace std;

struct node {
	long long tag;
	int num;
	node() {};
	node(long long t, int n)
	{
		tag = t;
		num = n;
	}
};

node *cows;
int len_cows = 0, len_tag = 0, Max = 0;



int main()
{
	int N, K, i, num = 0;
	cin >> N >> K;

	long long lastTag = -1, tmp;
	cows = new node[N];
	map<int, int> cnt;

	for (i = 0;i < N;++i)
	{
		cin >> tmp;
		if (tmp == lastTag)
			num++;
		else
		{
			cows[len_cows++] = node(lastTag, num);
			num = 1;
			lastTag = tmp;
		}
	}

	int l = 0, counter = 0;
	for (i = 0;i < len_cows;++i)
	{
		if (cnt.find(cows[i].tag) != cnt.end())
			cnt[cows[i].tag] += cows[i].num;

		else
		{
			if (counter == K + 1)
			{
				for (int j = l;j <= len_cows;++j)
				{
					cnt[cows[j].tag] -= cows[j].num;
					if (cnt[cows[j].tag] == 0)
					{
						cnt.erase(cows[j].tag);
						counter--;
						l = j + 1;
						break;
					}
				}
			}
			cnt[cows[i].tag] = cows[i].num;
			counter++;
		}
		if (cnt[cows[i].tag] > Max)
			Max = cnt[cows[i].tag];
	}

	cout << Max << endl;


	return 0;
}
