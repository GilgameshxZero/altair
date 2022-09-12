/*
Excuse the bad practices (massive headers, using namespace). They are for a faster coding.

When submitting the program, define DEBUG 0. When debugging, define DEBUG 1. In the program, for debugging information, use if (DEBUG){...} such that when it is submitted we don't have that code there.

Use this code to immediately terminate if the time is too much to handle: if (clock() > 0.95 * CLOCKS_PER_SEC) break;

Backup this program every so often in the Backup.txt files in case something goes wrong later.

Useful constants: INT_MAX, INT_MIN, UINT_MAX, LLONG_MIN, LLONG_MAX, ULLONG_MAX, _I64_MIN, _I64_MAX, _UI64_MAX.
*/

#include <algorithm>
#include <bitset>
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

const int	MAX_SQUARES	= 50000;

struct Point
{
	int x;
	int y;
};

int main ()
{
	std::ifstream in ("squares.in");
	std::ofstream out ("squares.out");
	Point center[MAX_SQUARES];
	int csquares, side_len, coverlap = 0, area;
	int a, b, c, d;

	in >> csquares >> side_len;

	for (a = 0;a < csquares;a++)
	{
		in >> center[a].x >> center[a].y;

		//Check if this square is in the range of any other.
		for (b = 0;b < a;b++)
		{
			c = abs (center[a].x - center[b].x);
			d = abs (center[a].y - center[b].y);

			if (c < side_len && d < side_len)
			{
				coverlap++;

				if (coverlap > 1)
				{
					out << "-1\n";
					out.close ();

					return 0;
				}

				//Find the area of overlap.
				area = (side_len - c) * (side_len - d);
			}
		}
	}

	if (coverlap == 0)
	{
		out << "0\n";
		out.close ();

		return 0;
	}
	
	out << area << "\n";
	out.close ();

	return 0;
}