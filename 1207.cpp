#include<iostream>
#include<iomanip>
#include<queue>
using namespace std;

int main()
{
	queue<int> truck,car;
	int totalNum,truckNum = 0,carNum = 0;
	int timer=0;
	int ship;
	int truckWaitTime=0,carWaitTime=0;
	int type,arrTime,i;


	cin >> totalNum;

	for(i = totalNum;i > 0;--i) 
	{
		cin >> type;
		cin >> arrTime;
		if (type)
		{
			truck.push(arrTime);
			truckNum+=1;
		}
			
		else
		{
			car.push(arrTime);
			carNum+=1;
		}
	}

	while (!truck.empty() || !car.empty())
	{
		for (ship = 0;ship < 8 && !car.empty() && car.front() <= timer;++ship)
		{
			carWaitTime += timer - car.front();
			car.pop();
		}
		for (;ship < 10 && !truck.empty() && truck.front() <= timer;++ship)
		{
			truckWaitTime += timer - truck.front();
			truck.pop();
		}
		for (;ship < 10 && !car.empty() && car.front() <= timer;++ship)
		{
			carWaitTime += timer - car.front();
			car.pop();
		}
		timer += 10;
	}

	cout << fixed <<setprecision(3) << carWaitTime / double(carNum) << " " << truckWaitTime / double(truckNum) << endl;

	return 0;
}