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
#include <set>
#include <string>
#include <vector>
#include <map>

using namespace std;

//Segment finding w/ Exclusive line intersection w/ exceptions.

//#define DEBUG 0
#define DEBUG 1

struct Segment
{
	bool color; //false = black, true = red.
	bool vert; //false = horo, true = vert;
	bool add; //for horo only.
	int pos, c1, c2; //differs on vert.

	Segment (bool c, bool v, int p, int a, int b)
	{
		color = c;
		vert = v;
		pos = p;
		c1 = a;
		c2 = b;
	}
	
	Segment (bool c, bool v, bool ad, int p, int a, int b)
	{
		color = c;
		vert = v;
		add = ad;
		pos = p;
		c1 = a;
		c2 = b;
	}
};

struct Mirror
{
	int x, y, dir; // 0 = \, 1 = /. -1 is sepcial
};

vector<Segment> seg, ev;
map< int, vector < Mirror > > xset, yset;
Mirror tmm;
int n, bx, by;
char tc;

const int MAX = 1000000000;
const int MIN = -1000000000;

bool CX (Mirror a, Mirror b)
{
	return (a.x < b.x);
}
bool CY (Mirror a, Mirror b)
{
	return (a.y < b.y);
}
bool CEV (Segment a, Segment b) //Put delete events before add events.
{
	return (a.pos < b.pos);
}

void FillSeg (int cdir, int cx, int cy, bool color) //Current; 0 = up, 1 = right, 2 = down, 3 = left.
{
	int a;

	while (true)
	{
		if (cdir == 0) //xset
		{
			if (xset.find (cx) == xset.end ()) //Goes to infinity.
			{
				seg.push_back (Segment (color, true, cx, cy, MAX));
				break;
			}
			else
			{
				for (a = 0;a < xset[cx].size ();a++)
				{
					if (xset[cx][a].y > cy)
						break;
				}

				if (a == xset[cx].size ()) //infinity
				{
					seg.push_back (Segment (color, true, cx, cy, MAX));
					break;
				}
				else //Hits a mirror.
				{
					seg.push_back (Segment (color, true, cx, cy, xset[cx][a].y));
					cy = xset[cx][a].y;

					if (xset[cx][a].dir == 0) //left
						cdir = 3;
					else if (xset[cx][a].dir == 1) //right
						cdir = 1;
					else //dir == -1.
						break;
				}
			}
		}
		else if (cdir == 1) //yset
		{
			if (yset.find (cy) == yset.end ()) //Goes to infinity.
			{
				seg.push_back (Segment (color, false, cy, cx, MAX));
				break;
			}
			else
			{
				for (a = 0;a < yset[cy].size ();a++)
				{
					if (yset[cy][a].x > cx)
						break;
				}

				if (a == yset[cy].size ()) //infinity
				{
					seg.push_back (Segment (color, false, cy, cx, MAX));
					break;
				}
				else //Hits a mirror.
				{
					seg.push_back (Segment (color, false, cy, cx, yset[cy][a].x));
					cx = yset[cy][a].x;

					if (yset[cy][a].dir == 0) //down
						cdir = 2;
					else if (yset[cy][a].dir == 1) //up
						cdir = 0;
					else //dir == -1.
						break;
				}
			}
		}
		else if (cdir == 2) //xset
		{
			if (xset.find (cx) == xset.end ()) //Goes to infinity.
			{
				seg.push_back (Segment (color, true, cx, cy, MIN));
				break;
			}
			else
			{
				for (a = xset[cx].size () - 1;a >= 0;a--)
				{
					if (xset[cx][a].y < cy)
						break;
				}

				if (a == -1) //infinity
				{
					seg.push_back (Segment (color, true, cx, cy, MIN));
					break;
				}
				else //Hits a mirror.
				{
					seg.push_back (Segment (color, true, cx, cy, xset[cx][a].y));
					cy = xset[cx][a].y;

					if (xset[cx][a].dir == 0) //right
						cdir = 1;
					else if (xset[cx][a].dir == 1) //left
						cdir = 3;
					else //dir == -1.
						break;
				}
			}
		}
		else if (cdir == 3) //yset
		{
			if (yset.find (cy) == yset.end ()) //Goes to infinity.
			{
				seg.push_back (Segment (color, false, cy, cx, MIN));
				break;
			}
			else
			{
				for (a = yset[cy].size () - 1;a >= 0;a--)
				{
					if (yset[cy][a].x < cx)
						break;
				}

				if (a == -1) //infinity
				{
					seg.push_back (Segment (color, false, cy, cx, MIN));
					break;
				}
				else //Hits a mirror.
				{
					seg.push_back (Segment (color, false, cy, cx, yset[cy][a].x));
					cx = yset[cy][a].x;

					if (yset[cy][a].dir == 0) //up
						cdir = 0;
					else if (yset[cy][a].dir == 1) //down
						cdir = 2;
					else //dir == -1.
						break;
				}
			}
		}
	}
}

int main ()
{
	std::ifstream in ("optics.in");
	std::ofstream out ("optics.out");

	in >> n >> bx >> by;

	for (int a = 0;a < n;a++)
	{
		in >> tmm.x >> tmm.y >> tc;

		if (tc == '\\')
			tmm.dir = 0;
		else
			tmm.dir = 1;

		xset[tmm.x].push_back (tmm);
		yset[tmm.y].push_back (tmm);
	}

	in.close ();

	//Insert barn and laser into sets, and set .dir = -1.
	tmm.x = tmm.y = 0;
	tmm.dir = -1;
	xset[0].push_back (tmm);
	yset[0].push_back (tmm);

	tmm.x = bx;
	tmm.y = by;
	xset[bx].push_back (tmm);
	yset[by].push_back (tmm);
	
	//Sort all x vectors by y, and all y vectors by x.
	for (map<int, vector< Mirror > >::iterator it = xset.begin ();it != xset.end ();++it)
		sort (it->second.begin (), it->second.end (), CY);

	for (map<int, vector< Mirror > >::iterator it = yset.begin ();it != yset.end ();++it)
		sort (it->second.begin (), it->second.end (), CX);

	//Find all segments (red and black). Current; 0 = up, 1 = right, 2 = down, 3 = left.
	FillSeg (0, 0, 0, false);

	for (int a = 0;a < 4;a++)
		FillSeg (a, bx, by, true);

	//Transform segments into events. Vertical: 1 event. Horozontal: 2 events.
	for (int a = 0;a < seg.size ();a++)
	{
		if (seg[a].vert == true)
		{
			ev.push_back (Segment (seg[a].color, true, false, seg[a].pos, min (seg[a].c1, seg[a].c2), max (seg[a].c1, seg[a].c2)));
		}
		else
		{
			ev.push_back (Segment (seg[a].color, false, false, max (seg[a].c1, seg[a].c2), seg[a].pos, 0));
			ev.push_back (Segment (seg[a].color, false, true, min (seg[a].c1, seg[a].c2), seg[a].pos, 0));
		}
	}

	sort (ev.begin (), ev.end (), CEV);

	//Line sweep events and find only black/red intersections.
	map<int, bool> points; //ypos, color
	int ans = 0;

	for (int a = 0;a < ev.size ();a++)
	{
		//No duplicates.
		if (a != 0 && ev[a].color == true && ev[a].color == ev[a - 1].color && ev[a].pos == ev[a - 1].pos && ev[a].c1 == ev[a - 1].c1 && ev[a].c2 == ev[a - 1].c2 && ev[a].add == ev[a - 1].add)
			continue;

		if (ev[a].vert == false)
		{
			if (ev[a].add == true)
				points[ev[a].c1] = ev[a].color;
			else
				points.erase (ev[a].c1);
		}
		else //Vertical line; iterate through all points, and if they are opposite color and exclusively in range, add to ans.
		{
			for (map<int, bool>::iterator it = points.begin ();it != points.end ();++it)
			{
				if (it->first > ev[a].c1 && it->first < ev[a].c2 && it->second != ev[a].color)
					ans++;
			}
		}
	}

	out << ans << "\n";
	out.close ();

	return 0;
}