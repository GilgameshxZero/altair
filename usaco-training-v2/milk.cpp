/*
ID: yangchess1
PROG: milk
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int main ()
{
	ifstream input;
	ofstream output;
	int x, y, z, need, people, price[5000], amount[5000], cost = 0;

	input.open ("milk.in");
	input >> need >> people;
	
	for (x = 0;x < people;x++)
		input >> price[x] >> amount[x];

	input.close ();

	for (z = 0;z < people;z++)
	{

		for (x = 0;x < people - 1;x++)
		{
			if (price[x] > price[x + 1])
			{
				y = price[x];
				price[x] = price[x + 1];
				price[x + 1] = y;

				y = amount[x];
				amount[x] = amount[x + 1];
				amount[x + 1] = y;
			}
		}

	}

	x = 0;

	while (need != 0)
	{
		if (amount[x] <= need)
		{
			need -= amount[x];
			cost += amount[x] * price[x];
			x++;
		}
		else
		{
			cost += need * price[x];
			break;
		}
	}

	output.open ("milk.out");
	output << cost << "\n";
	output.close ();

	return 0;
}