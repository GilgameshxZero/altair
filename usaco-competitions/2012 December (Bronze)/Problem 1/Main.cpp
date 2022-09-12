/*
Excuse the bad practices (massive headers, using namespace). They are for a faster coding.

When submitting the program, define DEBUG 0. When debugging, define DEBUG 1. In the program, for debugging information, use if (DEBUG){...} such that when it is submitted we don't have that code there.

Use this code to immediately terminate if the time is too much to handle: if (clock() > 0.95 * CLOCKS_PER_SEC) break;

Use the contest logger we made to log the contest.

Backup this program every so often in the Backup.txt files in case something goes wrong later.
*/

#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstring>
#include <ctime>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

//#define DEBUG 0
#define DEBUG 1

using namespace std;

#define INFINITY 200000000;
#define MAX_XY 1000000;

//Finds distance between two points
double PointPointDistance (double p1[2], double p2[2])
{
	return sqrt ((p1[0] - p2[0]) * (p1[0] - p2[0]) + (p1[1] - p2[2]) * (p1[1] - p2[2]));
}

//Finds intersection of two lines and if they intersect or not.
bool LineIntersection (double intersection[2], double p1[2], double p2[2], double p3[2], double p4[2])
{
	double a = (p4[0] - p3[0]) * (p1[1] - p3[1]) - (p4[1] - p3[1]) * (p1[0] - p3[0]), 
		b = (p4[1] - p3[1]) * (p2[0] - p1[0]) - (p4[0] - p3[0]) * (p2[1] - p1[1]);

	if (b == 0)
		return false;

	intersection[0] = p1[0] + (p2[0] - p1[0]) * a / b;
	intersection[1] = p1[1] + (p2[1] - p1[1]) * a / b;

	return true;
}

//Determines if two points are on the same side of a line.
bool PointsOnSameSideOfLine (double p1[2], double p2[2], double l1[2], double l2[2])
{
	double intersection[2], a, b;

	if (LineIntersection (intersection, p1, p2, l1, l2) == false) //If these lines are parallel:
		return true; //Then they are on the same side of line l.

	a = PointPointDistance (p1, intersection);
	b = PointPointDistance (p2, intersection);

	if (a > b)
	{
		if (PointPointDistance (p1, p2) < a)
			return true;

		return false;
	}
	else
	{
		if (PointPointDistance (p1, p2) < b)
			return true;

		return false;
	}
}
//void FloodFill (int sx, int sy, 

int main ()
{
	std::ifstream in ("crazy.in");
	std::ofstream out ("crazy.out");
	vector<int> shapes[333];
	bool fence_done[1000];
	int cfence, ccow, cshapes = 0, start[2], next[2], fence[1000][2][2], cow[1000][2];
	int a, b, c;

	in >> cfence >> ccow;

	for (a = 0;a < cfence;a++)
		in >> fence[a][0][0] >> fence[a][0][1] >> fence[a][1][0] >> fence[a][1][1];

	for (a = 0;a < ccow;a++)
		in >> cow[a][0] >> cow[a][1];

	in.close ();

	//Separate the fences into shapes.
	for (a = 0;a < 1000;a++)
		fence_done[a] = false;

	for (a = 0;a < cfence;a++)
	{
		if (fence_done[a] == false)
		{
			shapes[cshapes].push_back (a);
			fence_done[a] = true;
			start[0] = fence[a][0][0];
			start[1] = fence[a][0][1];
			next[0] = fence[a][1][0];
			next[1] = fence[a][1][1];

			while (!(next[0] == start[0] && next[1] == start[1]))
			{
				for (b = a + 1;b < cfence;b++)
				{
					if (fence_done[b] == false && fence[b][0][0] == next[0] && fence[b][0][1] == next[1])
					{
						shapes[cshapes].push_back (b);
						fence_done[b] = true;
						next[0] = fence[b][1][0];
						next[1] = fence[b][1][1];
						break;
					}
					else if (fence_done[b] == false && fence[b][1][0] == next[0] && fence[b][1][1] == next[1])
					{
						shapes[cshapes].push_back (b);
						fence_done[b] = true;
						next[0] = fence[b][0][0];
						next[1] = fence[b][0][1];
						break;
					}
				}
			}

			cshapes++;
		}
	}

	//

	return 0;
}