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

int stall[3000000];

int main ()
{
	std::ifstream in ("empty.in");
	std::ofstream out ("empty.out");
	int n, k;

	in >> n >> k;
	for (int a = 0, b, c, d, e;a < k;a++)
	{
		in >> b >> c >> d >> e;
		for (int f = 1, g = (d + e) % n;f <= c;f++)
		{
			stall[g] += b;
			g = (g + d) % n;
		}
	}

	in.close ();

	//Sweep.
	int curr = 0;
	for (int a = 0;a < 2;a++)
	{
		for (int b = 0;b < n;b++)
		{
			if (curr > 0 && stall[b] == 0)
			{
				curr--;
				stall[b] = 1;
			}
			else if (stall[b] > 1)
			{
				curr += stall[b] - 1;
				stall[b] = 1;
			}
		}
	}

	for (int a = 0;a < n;a++)
	{
		if (stall[a] == 0)
		{
			out << a << "\n";
			out.close ();
			return 0;
		}
	}

	return 0;
}