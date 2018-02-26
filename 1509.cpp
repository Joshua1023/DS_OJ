#include<iostream>
using namespace std;

int main()
{
	int i, j, a, b, c, y1, y2, total_y_a = 0, day_y_a, day, total_m_a;
	cin >> a >> b >> c >> y1 >> y2;

	bool ifRun[201];
	int days1[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 }, days2[12] = { 31,29,31,30,31,30,31,31,30,31,30,31 };
	for (i = 1850;i <= 2050;++i)
	{
		if ((i % 4 == 0 && i % 100 != 0) || i % 400 == 0)
			ifRun[i - 1850] = true;
		else
			ifRun[i - 1850] = false;
	}

	for (i = 1851;i <= y1;++i)
	{
		if (ifRun[i - 1851])
			total_y_a += 366;
		else
			total_y_a += 365;
	}

	total_m_a = total_y_a;

	for (i = y1; i <= y2; ++i)
	{
		if (ifRun[i - 1850])
		{
			for (j = 0;j < a - 1;++j)
				total_m_a = total_m_a + days2[j];
		}
		else
			for (j = 0;j < a - 1;++j)
				total_m_a = total_m_a + days1[j];

		day_y_a = (total_m_a) % 7 + 2;
		if (day_y_a == 8)
			day_y_a = 1;

		if (c >= day_y_a)
			day = 1 + 7 * (b - 1) + (c - day_y_a);
		else
			day = 1 + (7 - day_y_a + c) + 7 * (b - 1);
		if (ifRun[i - 1850])
		{
			if (day > days2[a - 1])
				cout << "none\n";
			else
			{
				cout << i << '/';
				switch (a)
				{
				case 1:cout << "01/";break;
				case 2:cout << "02/";break;
				case 3:cout << "03/";break;
				case 4:cout << "04/";break;
				case 5:cout << "05/";break;
				case 6:cout << "06/";break;
				case 7:cout << "07/";break;
				case 8:cout << "08/";break;
				case 9:cout << "09/";break;
				case 10:cout << "10/";break;
				case 11:cout << "11/";break;
				case 12:cout << "12/";break;
				}
				switch (day)
				{
				case 1:cout << "01";break;
				case 2:cout << "02";break;
				case 3:cout << "03";break;
				case 4:cout << "04";break;
				case 5:cout << "05";break;
				case 6:cout << "06";break;
				case 7:cout << "07";break;
				case 8:cout << "08";break;
				case 9:cout << "09";break;
				default:cout << day;
				}
				cout << endl;
			}

		}
		else
		{
			if (day > days1[a - 1])
				cout << "none\n";
			else
			{
				cout << i << '/';
				switch (a)
				{
				case 1:cout << "01/";break;
				case 2:cout << "02/";break;
				case 3:cout << "03/";break;
				case 4:cout << "04/";break;
				case 5:cout << "05/";break;
				case 6:cout << "06/";break;
				case 7:cout << "07/";break;
				case 8:cout << "08/";break;
				case 9:cout << "09/";break;
				case 10:cout << "10/";break;
				case 11:cout << "11/";break;
				case 12:cout << "12/";break;
				}
				switch (day)
				{
				case 1:cout << "01";break;
				case 2:cout << "02";break;
				case 3:cout << "03";break;
				case 4:cout << "04";break;
				case 5:cout << "05";break;
				case 6:cout << "06";break;
				case 7:cout << "07";break;
				case 8:cout << "08";break;
				case 9:cout << "09";break;
				default:cout << day;
				}
				cout << endl;
			}
		}
		if (ifRun[i - 1850])
			total_y_a += 366;
		else
			total_y_a += 365;
		total_m_a = total_y_a;

	}

	return 0;
}
