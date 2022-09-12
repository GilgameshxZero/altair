/*
ID: yangchess1
PROG: gift1
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int mod (int x, int y)
{
	if (y == 0)
		return x;

	return x - ((int)(x / y) * y);
}

int main ()
{
	ofstream output;
	ifstream input;
	int people, x, a, b, money[10], y, z, initial[10];
	string names[10], now, other;

	input.open ("gift1.in");
	input >> people;

	for (x = 0;x < people;x++)
	{
		input >> names[x];
		money[x] = 0;
	}

	for (x = 0;x < people;x++)
	{
		input >> now >> a >> b;
		
		for (y = 0;y < people;y++)
		{
			if (names[y] == now)
				break;
		}

		money[y] += mod (a,b);
		initial[y] = a;

		for (y = 0;y < b;y++)
		{
			input >> other;

			for (z = 0;z < people;z++)
			{
				if (names[z] == other)
					break;
			}

			money[z] += (int)(a / b);
		}
	}

	input.close ();
	output.open ("gift1.out");

	for (x = 0;x < people;x++)
		output << names[x] << " " << (money[x] - initial[x]) << "\n" ;

	output.close ();

	return 0;
}