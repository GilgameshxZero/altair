/*
ID: yangchess1
LANG: C++
PROB: buylow
*/

/*
Excuse the bad practices (massive headers, using namespace). They are for a faster coding.

When submitting the program, define DEBUG 0. When debugging, define DEBUG 1. In the program, for debugging information, use if (DEBUG){...} such that when it is submitted we don't have that code there.

Backup this program every so often in the Backup.txt files in case something goes wrong later.

Max's and mins: numeric_limits<type_name>::min().
*/

#include <algorithm>
#include <bitset>
#include <limits>
#include <climits>
#include <cmath>
#include <cstring>
#include <ctime>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

//#define DEBUG 0
#define DEBUG 1

std::string str_sum (std::string x, std::string y)
{
	int carry = 0, max_size = max (x.size (), y.size ());
	std::string rtrn (max_size, '0');

	for (int a = 0, b = 0, c = 0; a < max_size; a++, b = 0, c = 0)
	{
		if (a < x.size ())
			b = x[x.size () - a - 1] - '0';

		if (a < y.size ())
			c = y[y.size () - a - 1] - '0';

		b += carry + c;
		rtrn[max_size - a - 1] = '0' + (b % 10);
		carry = b / 10;
	}

	if (carry == 1)
		rtrn = "1" + rtrn;

	return rtrn;
}

const int	MAXDAYS	= 5000;

int main ()
{
	std::ifstream in ("buylow.in");
	std::ofstream out ("buylow.out");
	std::string cdistinct, ways[MAXDAYS];
	int days, longest, price[MAXDAYS], best[MAXDAYS];

	in >> days;

	for (int a = 0;a < days;a++)
		in >> price[a];

	in.close ();

	//Probably a DP solution? Declare an array best with the number of optimal sequences ending on the array number.
	for (int a = 0;a < MAXDAYS;a++)
	{
		best[a] = 1;
		ways[a] = "1";
	}

	//Start the DP.
	for (int a = 0;a < days;a++)
	{
		//See if we can get a longer sequence with the things we have.
		for (int b = 0;b < a;b++)
		{
			if (price[b] > price[a])
			{
				if (best[b] + 1 > best[a])
				{
					best[a] = best[b] + 1;
					ways[a] = ways[b];
				}
				else if (best[b] + 1 == best[a])
					ways[a] = str_sum (ways[a], ways[b]);
			}

			//Search through the previous numbers, and see if we had an identical price before. If so, make that one invalid -- don't use it in the future -- set it as -1 or something. This is to ensure that our ways[] count is accurate.
			if (price[b] == price[a] && best[b] < best[a])
				best[b] = -1;
			else if (price[b] == price[a] && best[b] >= best[a])
				best[a] = -1;
		}
	}

	longest = 0;
	cdistinct = "0";

	for (int a = 0;a < days;a++)
		if (best[a] > longest)
			longest = best[a];

	for (int a = 0;a < days;a++)
		if (best[a] == longest)
			cdistinct = str_sum (cdistinct, ways[a]);

	out << longest << " " << cdistinct << "\n";
	out.close ();

	return 0;
}