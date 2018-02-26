#include<iostream>
#include<list>
using namespace std;

int main()
{
	char ctmp;
	int end,carry;
	list<int> num1,num2,sum;
	list<int>::iterator itr1,itr2,itr_end1,itr_end2;

	while (true)
	{
		cin.get(ctmp);
		if(ctmp!='\n')
			num1.push_front(ctmp - '0');
		else
			break;
	}
	while (true)
	{
		cin.get(ctmp);
		if (ctmp != '\n')
			num2.push_front(ctmp - '0');
		else
			break;
	}

	itr1 = num1.begin();
	itr2 = num2.begin();
	itr_end1 = num1.end();
	itr_end2 = num2.end();
	carry = 0;
	while (itr1 != itr_end1 && itr2 != itr_end2)
	{
		end = *itr1 + *itr2 + carry;
		if (end > 9)
		{
			end -= 10;
			carry = 1;
		}
		else
			carry = 0;
		sum.push_front(end);
		++itr1;
		++itr2;
	}
	if (itr1 == itr_end1)
	{
		while (itr2 != itr_end2)
		{
			end = *itr2 + carry;
			if (end > 9)
			{
				end -= 10;
				carry = 1;
			}
			else
				carry = 0;
			sum.push_front(end);
			++itr2;
		}		
	}
	else
	{
		while (itr1 != itr_end1)
		{
			end = *itr1 + carry;
			if (end > 9)
			{
				end -= 10;
				carry = 1;
			}
			else
				carry = 0;
			sum.push_front(end);
			++itr1;
		}
	}
	if(carry!=0)
		sum.push_front(carry);

	
	itr_end1 = sum.end();
	for(itr1 = sum.begin();itr1!=itr_end1;++itr1)
		cout << *itr1;
	cout << endl;

	return 0;
}