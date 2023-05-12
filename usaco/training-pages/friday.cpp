/*
ID: yangchess1
PROG: friday
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int mod (int x, int y)
{
	return x - ((int)(x / y)) * y;
}

int main ()
{
	ifstream input;
	ofstream output;
	int years, month[12] = {31,28,31,30,31,30,31,31,30,31,30,31}, x, last, days[7], y, left = 0;

	for (x = 0;x < 7;x++)
		days[x] = 0;

	input.open ("friday.in");
	input >> years;
	input.close ();

	last = 1900 + years;

	for (x = 1900;x < last;x++)
	{
		if (mod (x,4) == 0 && mod (x,100) != 0 || mod (x,400) == 0)
			month[1] = 29;

		for (y = 0;y < 12;y++)
		{
			days[mod (left + 13,7)]++;
			left = month[y] - 13 + mod (left + 13,7);
		}

		month[1] = 28;
	}

	output.open ("friday.out");
	output << days[6] << " " << days[0] << " " << days[1] << " " << days[2] << " " << days[3] << " " << days[4] << " " << days[5] << "\n";
	output.close ();

	return 0;
}