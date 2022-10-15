/*
ID: yangchess1
PROG: barn1
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
	int x, y, z, max, stalls, cows, used[200], gap[199], unused;

	input.open ("barn1.in");
	input >> max >> stalls >> cows;

	for (x = 0;x < 199;x++)
		gap[x] = 1;

	for (x = 0;x < cows;x++)
		input >> used[x];

	for (x = 0;x < cows;x++)
	{
		for (y = 0;y < cows - 1;y++)
		{
			if (used[y] > used[y + 1])
			{
				z = used[y];
				used[y] = used[y + 1];
				used[y + 1] = z;
			}
		}
	}

	for (x = 0;x < cows - 1;x++)
		gap[x] = used[x + 1] - used[x];

	for (x = 0;x < cows;x++)
	{
		for (y = 0;y < cows - 1;y++)
		{
			if (gap[y] < gap[y + 1])
			{
				z = gap[y];
				gap[y] = gap[y + 1];
				gap[y + 1] = z;
			}
		}
	}

	unused = used[0] + stalls - used[cows - 1] - 1;

	for (x = 0;x < max - 1;x++)
		unused = unused + gap[x] - 1;

	output.open ("barn1.out");
	output << stalls - unused << "\n";
	output.close ();

	return 0;
}