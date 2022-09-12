/*
TASK: fc
ID: yangchess1
LANG: C++
*/
#include <iostream>
#include <algorithm>
#include <climits>
#include <cmath>
#include <cstdio>
#include <iomanip>
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

		Point operator - (const Point& a) const
		{
			return Point (x - a.x, y - a.y);
		}
};

class Line
{
	public:
		//AX + BY + C = 0
		double A, B, C;

		Line ()
		{
			A = B = C = 0;
		}

		Line (double A, double B, double C)
		{
			this->A = A;
			this->B = B;
			this->C = C;
		}

		Line (Point &a, Point &b)
		{
			A = b.y - a.y;
			B = a.x - b.x;
			C = b.x * a.y - a.x * b.y;
		}

		bool IsNull ()
		{
			return (A == 0 && B == 0 && C == 0);
		}

		//makes line into either AX + BY + 1 = 0 or X + BY = 0 depending on if C is 0 or just X = 0 or Y = 0. assumes non-null
		void Standardize ()
		{
			if (IsNull ())
				return;

			if (!CloseTo (C, 0))
			{
				A /= C;
				B /= C;
				C = 1;
			}
			else if (!CloseTo (A, 0)) //C = 0
			{
				B /= A;
				A = 1;
			}
			else //B != 0
				B = 1;
		}

		bool operator == (const Line& x) const
		{
			Line a (A, B, C), b (x.A, x.B, x.C);
			a.Standardize ();
			b.Standardize ();

			return (CloseTo (a.A, b.A) && CloseTo (a.B, b.B) && CloseTo (a.C, b.C));
		}
};

double DotProd (Point &a, Point &b)
{
	return a.x * b.x + a.y * b.y;
}

double CrossProd (Point &a, Point &b)
{
	return a.x * b.y - a.y * b.x;
}

//cross product of b - a and c - a
double CrossProd (Point& a, Point& b, Point& c)
{
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

//tests if two lines are parallel
bool Parallel (Line &a, Line &b)
{
	return CloseTo (a.B * b.A - a.A * b.B, 0);
}

double PPDist (Point &a, Point &b)
{
	return sqrt ((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

bool PointOnLine (Point &a, Line &l)
{
	return CloseTo (a.x * l.A + a.y * l.B + l.C, 0);
}

//test if point a is on the segment from s1 to s2. assumes a is not s1 or s2
bool PointOnSegExc (Point &a, Point &s1, Point &s2)
{
	return CloseTo (CrossProd (s1, a, s2), 0);
}

//assumes nonparallel
Point LLIntersec (Line &a, Line &b)
{
	return Point ((b.B * a.C - a.B * b.C) / (a.B * b.A - a.A * b.B), (a.A * b.C - a.C * b.A) / (a.B * b.A - a.A * b.B));
}

//check if segments p1 to p2 and p3 to p4 intersect, not counting endpoints. assumes endpoints distinct
bool SegIntersecExc (Point &p1, Point &p2, Point &p3, Point &p4)
{
	Line l1 (p1, p2), l2 (p3, p4);

	if (Parallel (l1, l2))
	{
		//all four points may be collinear
		if (PointOnSegExc (p1, p3, p4) || PointOnSegExc (p2, p3, p4) || PointOnSegExc (p3, p1, p2) || PointOnSegExc (p4, p1, p2))
			return true;

		return false;
	}

	Point x = LLIntersec (l1, l2);
	if (PointOnSegExc (x, p1, p2) && PointOnSegExc (x, p3, p4)) //point must be on both segments to be true
		return true;

	return false;
}

Line PerpBisec (Point &a, Point &b)
{
	return Line (2 * (a.x - b.x), 2 * (a.y - b.y), b.x * b.x + b.y * b.y - a.x * a.x - a.y * a.y);
}

//get line passing through a and perpendicular to l
Line PerpLine (Point &a, Line &l)
{
	return Line (-l.B, l.A, l.B * a.x - l.A * a.y);
}

//reflect point a across line l
Point Reflect (Point &a, Line &l)
{
	Line m = PerpLine (a, l);
	Point b = LLIntersec (l, m);
	return Point (2 * b.x - a.x, 2 * b.y - a.y);
}

//checks if points a and b are on the same side of line l. assumes a != b, and that points don't lie on line
bool PtSameSide (Point &a, Point &b, Line &l)
{
	//if parallel, then they are on the same side
	Line l2 (a, b);
	if (Parallel (l, l2))
		return true;

	Point i = LLIntersec (l, l2);
	double x = PPDist (i, a), y = PPDist (i, b);

	if (PPDist (a, b) < max (x, y))
		return true;

	return false;
}

//tests if point is inside a polygon. returns true if point is on polygon
bool PtInsidePolyInc (Point &x, vector<Point>& poly)
{
	//shoot horozontal ray out of x and if it intersects polygon at an odd number of points then return true
	Point mp (1e50, x.y); //this constant merely has to be bigger than the largest x coordinate in the polygon
	Line l (x, mp);

	//temporarily add the first point to poly's end to facilitate calculations
	poly.push_back (poly[0]);

	int i = 0; //number of intersections
	for (int a = 0;a < poly.size () - 1;a++) //check intersection with Line (poly[a], poly[a + 1])
	{
		if (x == poly[a] || PointOnSegExc (x, poly[a], poly[a + 1])) //check if point is on the polygon
			return true;

		if (SegIntersecExc (x, mp, poly[a], poly[a + 1])) //intersects in the middle of side. should work even if side is horozontal and colinear with ray.
			i++;
		else if (PointOnSegExc (poly[a], x, mp)) //if our ray passes through a vertex of the polygon
		{
			//increment i only if the vertices before and after poly[a] are on opposite sides of the ray
			if (a == 0)
				i += !PtSameSide (poly[poly.size () - 2], poly[a + 1], l);
			else
				i += !PtSameSide (poly[a - 1], poly[a + 1], l);
		}
	}

	poly.pop_back ();

	return (i & 1); //if intersections is odd
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

int main ()
{
	freopen ("fc.in", "r", stdin);
	freopen ("fc.out", "w", stdout);

	//input
	int n;
	cin >> n;

	vector<Point> x;
	x.resize (n);
	for (int a = 0;a < n;a++)
		cin >> x[a].x >> x[a].y;

	//hull
	vector<Point> hull;
	ConvexHullGS (hull, x);

	//go through hull and add dists
	double ans = 0;
	hull.push_back (hull[0]); //for ease
	for (int a = 0;a < hull.size () - 1;a++)
		ans += PPDist (hull[a], hull[a + 1]);

	cout << fixed << setprecision (2) << ans << "\n";
	return 0;
}