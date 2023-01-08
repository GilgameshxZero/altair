#include <iostream>

#include <algorithm>
#include <climits>
#include <cmath>
#include <vector>

using namespace std;

const double PI = 3.141592653589793238462,
	EPS = 1e-9;

bool CloseTo (double a, double b)
{
	return (abs (a - b) < EPS);
}

int Round (double x)
{
	if (x >= 0)
		return (int)(x + 0.5);
	return (int)(x - 0.5);
}

class Point
{
	public:
		double x, y;

		Point ()
		{
			x = y = 0;
		}

		Point (double x, double y)
		{
			this->x = x;
			this->y = y;
		}

		bool operator == (const Point& a) const
		{
			return (CloseTo (x, a.x) && CloseTo (y, a.y));
		}
};

//cross product of b - a and c - a
double CrossProd (Point& a, Point& b, Point& c)
{
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

double PPDist (Point &a, Point &b)
{
	return sqrt ((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

//Above is from "Computational Geometry"

bool CompGS (pair<double, Point> a, pair<double, Point> b)
{
	return (a.first < b.first);
}

//Stores convex hull in `hull`, based on Graham's Scan. Requires >= 3 distinct points
//O(NlogN)
void ConvexHullGS (vector<Point>& hull, vector<Point>& pts)
{
	//find lowest (then leftmost) point
	Point s = pts[0];
	for (int a = 0;a < pts.size ();a++)
	{
		if (pts[a].y < s.y)
			s = pts[a];
		else if (pts[a].y == s.y && pts[a].x < s.x)
			s = pts[a];
	}

	//sort all points by the angle they make with point s
	vector< pair<double, Point> > ptang;
	for (int a = 0;a < pts.size ();a++)
		if (!(pts[a] == s))
			ptang.push_back (make_pair (atan2 (pts[a].y - s.y, pts[a].x - s.x), pts[a]));
	sort (ptang.begin (), ptang.end (), CompGS);

	//loop through points and maintain convexity
	hull.clear ();
	hull.push_back (s);
	for (int a = 0;a < ptang.size ();a++)
	{
		//if adding this point will make the last point obsolete, delete the last point, until this doesn't happen anymore
		while (hull.size () >= 2 && CrossProd (hull[hull.size () - 2], hull.back (), ptang[a].second) <= 0) //discards collinear points
			hull.pop_back ();

		hull.push_back (ptang[a].second);
	}
}