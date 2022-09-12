/*
ID: yangchess1
LANG: C++
PROB: fence3
*/

/*
Excuse the bad practices (massive headers, using namespace). They are for a faster coding.

Backup this program every so often in the Backup files in case something goes wrong later.

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
#include <iomanip>

using namespace std;

struct Fence
{
	double x1, y1, x2, y2;
};

int cfence;
Fence fence[150];

//Calculates the total length of wire needed from a certain coordinate.
double Length (double x, double y)
{
	double r = 0;

	for (int a = 0;a < cfence;a++)
	{
		//Vertical.
		if (fence[a].x1 == fence[a].x2)
		{
			if (y > max (fence[a].y1, fence[a].y2))
				r += hypot (y - max (fence[a].y1, fence[a].y2), x - fence[a].x1);
			else if (y < min (fence[a].y1, fence[a].y2))
				r += hypot (y - min (fence[a].y1, fence[a].y2), x - fence[a].x1);
			else
				r += abs (x - fence[a].x1); 
		}

		//Horozontal.
		else if (fence[a].y1 == fence[a].y2)
		{
			if (x > max (fence[a].x1, fence[a].x2))
				r += hypot (x - max (fence[a].x1, fence[a].x2), y - fence[a].y1);
			else if (x < min (fence[a].x1, fence[a].x2))
				r += hypot (x - min (fence[a].x1, fence[a].x2), y - fence[a].y1);
			else
				r += abs (y - fence[a].y1); 
		}
	}

	return r;
}

int main ()
{
	std::ifstream in ("fence3.in");
	std::ofstream out ("fence3.out");
	double a, b, c, d;

	in >> cfence;

	for (int a = 0;a < cfence;a++)
		in >> fence[a].x1 >> fence[a].y1 >> fence[a].x2 >> fence[a].y2;

	in.close ();

	//Close in with approximations.
	//Interval	Square		# of calls to Length
	//--------------------------
	//10		100x100		81
	//2			20x20		81
	//0.4		4x4			81
	//0.1		0.8x0.8		81
	//Complete	0.1x0.1		0

	double t1, t2, i[4], sq[4];

	t1 = t2 = 50;
	i[0] = 10;
	i[1] = 2;
	i[2] = 0.4;
	i[3] = 0.1;
	sq[0] = 40;
	sq[1] = 8;
	sq[2] = 1.6;
	sq[3] = 0.4;
	c = 100000000;

	for (int e = 0;e < 4;e++)
	{
		for (a = t1 - sq[e];a <= t1 + sq[e];a += i[e])
		{
			for (b = t2 - sq[e];b < t2 + sq[e];b += i[e])
			{
				d = Length (a, b);

				if (d < c)
				{
					c = d;
					t1 = a;
					t2 = b;
				}
			}
		}
	}

	out << setprecision (1) << std::fixed << t1 << " " << t2 << " " << c << "\n";
	out.close ();

	return 0;
}