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

struct Point
{
	int x, y; //Not intuitive, x = row, y = column.
};

struct ACell
{
	Point cell;
	int dist;
};

//The basic algorithm I'll be using in this problem is that for each starting point, we keep a vector of distances to accessible cells. Each time we visit the closest cell, and update our vector with either shorter distances or new accessible cells. We stop when we visit T cells, and output the longest distance we had to surmount.

int m, n, t, grid[500][500], itemp;
int in_q[500][500]; //Speed. 0 = not in q, visited. 1 = in q. 2 = not in q, not visited.

int main ()
{
	std::ifstream in ("skilevel.in");
	std::ofstream out ("skilevel.out");
	vector<Point> start;
	Point ptemp;
	ACell atemp;
	unsigned long long int ans = 0;
	vector<ACell> q; //Starts from the farthest cells, then to nearer ones.
	Point pcurr;
	int vis, lgdist;

	in >> m >> n >> t;

	for (int a = 0;a < m;a++)
		for (int b = 0;b < n;b++)
			in >> grid[a][b];

	for (int a = 0;a < m;a++)
	{
		for (int b = 0;b < n;b++)
		{
			in >> itemp;

			if (itemp == 1)
			{
				ptemp.x = a;
				ptemp.y = b;
				start.push_back (ptemp);
			}
		}
	}

	if (start.size () == 0)
	{
		out << "0\n";
		out.close ();

		return 0;
	}

	//Visit each starting point.
	for (int a = 0, b, c;a < start.size ();a++)
	{
		q.clear ();
		vis = lgdist = 0;

		for (b = 0;b < m;b++)
			for (c = 0;c < n;c++)
				in_q[b][c] = 2;

		atemp.cell = start[a];
		atemp.dist = 0;
		q.push_back (atemp);
		in_q[start[a].x][start[a].y] = 1;

		while (vis != t)
		{
			pcurr = q.back ().cell;

			if (q.back ().dist > lgdist)
				lgdist = q.back ().dist;

			q.pop_back ();
			in_q[pcurr.x][pcurr.y] = 0;
			vis++;

			//Update cells adjacent to pcurr.
			if (pcurr.x > 0)
			{
				if (in_q[pcurr.x - 1][pcurr.y] == 2) //Add cell to q.
				{
					in_q[pcurr.x - 1][pcurr.y] = 1;
					c = abs (grid[pcurr.x - 1][pcurr.y] - grid[pcurr.x][pcurr.y]); //Temp distance.

					for (b = 0;b < q.size ();b++)
					{
						if (q[b].dist <= c)
							break;
					}

					atemp.cell.x = pcurr.x - 1;
					atemp.cell.y = pcurr.y;
					atemp.dist = c;
					q.insert (q.begin () + b, atemp);
				}
				else if (in_q[pcurr.x - 1][pcurr.y] == 1)//Find value in q and update dist if appropriate.
				{
					c = abs (grid[pcurr.x - 1][pcurr.y] - grid[pcurr.x][pcurr.y]); //Temp distance.

					for (b = 0;b < q.size ();b++)
					{
						if (q[b].cell.x == pcurr.x - 1 && q[b].cell.y == pcurr.y)
						{
							if (q[b].dist > c)
								q[b].dist = c;

							break;
						}
					}
				} //No need for action if in_q = 0, which means we have already visited that square.
			}
			if (pcurr.y > 0)
			{
				if (in_q[pcurr.x][pcurr.y - 1] == 2) //Add cell to q.
				{
					in_q[pcurr.x][pcurr.y - 1] = 1;
					c = abs (grid[pcurr.x][pcurr.y - 1] - grid[pcurr.x][pcurr.y]); //Temp distance.

					for (b = 0;b < q.size ();b++)
					{
						if (q[b].dist <= c)
							break;
					}

					atemp.cell.x = pcurr.x;
					atemp.cell.y = pcurr.y - 1;
					atemp.dist = c;
					q.insert (q.begin () + b, atemp);
				}
				else if (in_q[pcurr.x][pcurr.y - 1] == 1)//Find value in q and update dist if appropriate.
				{
					c = abs (grid[pcurr.x][pcurr.y - 1] - grid[pcurr.x][pcurr.y]); //Temp distance.

					for (b = 0;b < q.size ();b++)
					{
						if (q[b].cell.x == pcurr.x && q[b].cell.y == pcurr.y - 1)
						{
							if (q[b].dist > c)
								q[b].dist = c;

							break;
						}
					}
				} //No need for action if in_q = 0, which means we have already visited that square.
			}
			if (pcurr.x < m - 1)
			{
				if (in_q[pcurr.x + 1][pcurr.y] == 2) //Add cell to q.
				{
					in_q[pcurr.x + 1][pcurr.y] = 1;
					c = abs (grid[pcurr.x + 1][pcurr.y] - grid[pcurr.x][pcurr.y]); //Temp distance.

					for (b = 0;b < q.size ();b++)
					{
						if (q[b].dist <= c)
							break;
					}

					atemp.cell.x = pcurr.x + 1;
					atemp.cell.y = pcurr.y;
					atemp.dist = c;
					q.insert (q.begin () + b, atemp);
				}
				else if (in_q[pcurr.x + 1][pcurr.y] == 1)//Find value in q and update dist if appropriate.
				{
					c = abs (grid[pcurr.x + 1][pcurr.y] - grid[pcurr.x][pcurr.y]); //Temp distance.

					for (b = 0;b < q.size ();b++)
					{
						if (q[b].cell.x == pcurr.x + 1 && q[b].cell.y == pcurr.y)
						{
							if (q[b].dist > c)
								q[b].dist = c;

							break;
						}
					}
				} //No need for action if in_q = 0, which means we have already visited that square.
			}
			if (pcurr.y < n - 1)
			{
				if (in_q[pcurr.x][pcurr.y + 1] == 2) //Add cell to q.
				{
					in_q[pcurr.x][pcurr.y + 1] = 1;
					c = abs (grid[pcurr.x][pcurr.y + 1] - grid[pcurr.x][pcurr.y]); //Temp distance.

					for (b = 0;b < q.size ();b++)
					{
						if (q[b].dist <= c)
							break;
					}

					atemp.cell.x = pcurr.x;
					atemp.cell.y = pcurr.y + 1;
					atemp.dist = c;
					q.insert (q.begin () + b, atemp);
				}
				else if (in_q[pcurr.x][pcurr.y + 1] == 1)//Find value in q and update dist if appropriate.
				{
					c = abs (grid[pcurr.x][pcurr.y + 1] - grid[pcurr.x][pcurr.y]); //Temp distance.

					for (b = 0;b < q.size ();b++)
					{
						if (q[b].cell.x == pcurr.x && q[b].cell.y == pcurr.y + 1)
						{
							if (q[b].dist > c)
								q[b].dist = c;

							break;
						}
					}
				} //No need for action if in_q = 0, which means we have already visited that square.
			}
		}

		ans += lgdist;
	}

	out << ans << "\n";
	out.close ();

	return 0;
}