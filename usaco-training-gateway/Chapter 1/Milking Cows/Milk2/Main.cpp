/*
ID: yangchess1
PROG: milk2
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
	int number, start[5000], stop[5000], x, y, z, milking = 0, stopping = 0, begin, end;

	input.open ("milk2.in");
	input >> number;

	for (x = 0;x < number;x++)		
		input >> start[x] >> stop[x];

	for (z = 0;z < number - 1;z++)
	{
		for (x = 0;x < number - 1;x++)
		{
			if (start[x] > start[x + 1])
			{
				y = start[x];
				start[x] = start[x + 1];
				start[x + 1] = y;

				y = stop[x];
				stop[x] = stop[x + 1];
				stop[x + 1] = y;
			}
		}
	}

	begin = start[0];
	end = stop[0];
	milking = end - begin;

	for (x = 1;x < number;x++)
	{
		if (start[x] <= end && stop[x] >= end)
		{
			end = stop[x];

			if (end - begin > milking)
				milking = end - begin;
		}

		if (start[x] > end)
		{
			if (end - begin > milking)
				milking = end - begin;

			if (start[x] - end > stopping)
				stopping = start[x] - end;

			begin = start[x];
			end = stop[x];
		}
	}

	output.open ("milk2.out");
	output << milking << " " << stopping << "\n";
	output.close ();
	input.close ();

	return 0;
}