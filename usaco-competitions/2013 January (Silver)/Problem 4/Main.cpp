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

const int	LG_RANGE	= INT_MAX;
const int	SM_RANGE	= INT_MIN;
const int	LG_SEGMENT	= 1000000;

struct FSegment
{
	int start;
	int end;
	int layers;
};

FSegment Intersection (FSegment *seg1, FSegment *seg2)
{
	FSegment x = FSegment ();

	if (seg1->start >= seg2->end)
		return x;
	else if (seg1->start < seg2->end && seg1->start > seg2->start)
	{
		x.start = seg1->start;

		if (seg1->end < seg2->end)
		{
			x.end = seg1->end;

			return x;
		}
		else
		{
			x.end = seg2->end;

			return x;
		}
	}
	else
	{
		if (seg1->end <= seg2->start)
			return x;
		else if (seg1->end > seg2->start && seg1->end < seg2->end)
		{
			x.start = seg2->start;
			x.end = seg1->end;

			return x;
		}
		else
		{
			x.start = seg2->start;
			x.end = seg2->end;

			return x;
		}
	}
}

FSegment segments[LG_SEGMENT];

int main ()
{
	std::ifstream in ("paint.in");
	std::ofstream out ("paint.out");
	FSegment x, y, z, j;
	char dir;
	int cmoves, sm_layer, pos = 0, csegments;
	int a, b, c, d;

	in >> cmoves >> sm_layer;

	segments[0].start = SM_RANGE;
	segments[0].end = LG_RANGE;
	segments[0].layers = 0;
	csegments = 1;

	//Read in the moves and compute sections of paint.
	for (a = 0;a < cmoves;a++)
	{
		in >> b >> dir;
		
		if (dir == 'L')
		{
			x.end = pos;
			pos -= b;
			x.start = pos;
		}
		else
		{
			x.start = pos;
			pos += b;
			x.end = pos;
		}

		d = csegments;
		for (c = 0;c < d;c++)
		{
			j = segments[c];

			if (j.start != j.end)
			{
				y = Intersection (&x, &j);

				//If there is an intersection...
				if (y.start != y.end)
				{
					y.layers = j.layers + 1;
					segments[csegments++] = y;
				
					//Split up segments.at (c) into 2 segments by using segment y.
					if (j.start != y.start)
					{
						z.start = j.start;
						z.end = y.start;
						z.layers = j.layers;
						segments[csegments++] = z;
					}

					if (y.end != j.end)
					{
						z.start = y.end;
						z.end = j.end;
						z.layers = j.layers;
						segments[csegments++] = z;
					}

					//Delete the larger partitioned segment by changing its properties.
					segments[c].end = segments[c].start;
					d--;
				}
			}
		}
	}

	//Find the segments with the required layers of paint, and remember those.
	c = 0;
	for (a = 0;a < csegments;a++)
	{
		if (segments[a].layers >= sm_layer)
			c += (segments[a].end - segments[a].start);
	}

	out << c << "\n";
	out.close ();

	return 0;
}