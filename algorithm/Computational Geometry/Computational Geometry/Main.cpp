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

double CrossProd (Point& a, Point& b, Point& c)
{
	return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
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
	//test that the angle s1 makes with a is equal to the angle a makes with s2
	double ang1 = atan2 (s1.y - a.y, s1.x - a.x),
		ang2 = atan2 (a.y - s2.y, a.x - s2.x);
	return CloseTo (ang1, ang2);
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

//tests if point is inside a polygon using random points. returns true if point is on polygon
bool PtInsidePolyIncRand (Point &x, vector<Point>& poly)
{
	//shoot rays in random directions out of x and count intersections. take majority of (inside, outside)
	const int TESTS = 3;
	const double DIST = 1e50;
	int dir = min (TESTS, (const int)poly.size ());

	//for ease
	poly.push_back (poly[0]);

	//check if point is on the polygon
	for (int a = 0;a < poly.size () - 1;a++)
	{
		if (x == poly[a] || PointOnSegExc (x, poly[a], poly[a + 1])) 
		{
			poly.pop_back ();
			return true;
		}
	}

	//choose angles to be between points themselves
	vector<double> ang (dir);
	for (int a = 0;a < dir;a++)
		ang[a] = (atan2 (poly[a].y - x.y, poly[a].x - x.x) + atan2 (poly[a + 1].y - x.y, poly[a + 1].x - x.x)) / 2;

	vector<Point> mp (dir);
	vector<Line> ray (dir);
	for (int a = 0;a < dir;a++)
		mp[a] = Point (x.x + DIST * sin (ang[a]), x.y + DIST * cos (ang[a]));

	vector<int> i (dir); //number of intersections
	for (int a = 0;a < poly.size () - 1;a++) //check intersection with Line (poly[a], poly[a + 1])
		for (int b = 0;b < dir;b++)
			if (SegIntersecExc (x, mp[b], poly[a], poly[a + 1]))
				i[b]++;

	poly.pop_back ();

	//take majority
	int cnt = 0;
	for (int a = 0;a < dir;a++)
		cnt += (i[a] & 1); //if intersections is odd, then pass

	return (cnt > dir / 2);
}

//deterministic algorithm that might break but probably won't
bool PtInsidePolyIncDet (Point &x, vector<Point>& poly)
{
	//shoot horozontal ray out of x and if it intersects polygon at an odd number of points then return true
	Point mp (1e50, x.y); //this constant merely has to be bigger than the largest x coordinate in the polygon
	Line l (x, mp);

	//temporarily add the first point to poly's end to facilitate calculations
	poly.push_back (poly[0]);
	
	//check if point is on the polygon
	for (int a = 0;a < poly.size () - 1;a++)
	{
		if (x == poly[a] || PointOnSegExc (x, poly[a], poly[a + 1]))
		{
			poly.pop_back ();
			return true;
		}
	}

	//keep track of whether the last point (not on ray) was above or below the ray
	bool below;
	for (int a = 0;a < poly.size () - 1;a++)
	{
		if (!CloseTo (poly[a].y, x.y))
		{
			below = (poly[a].y < x.y);
			break;
		}
	}

	int i = 0; //number of intersections on the right
	Line tl;
	for (int a = 1;a < poly.size ();a++)
	{
		if (!CloseTo (poly[a].y, x.y))
		{
			if (below != (poly[a].y < x.y)) //below is changing, check intersection
			{
				below = !below;
				tl = Line (poly[a], poly[a - 1]);
				if (LLIntersec (l, tl).x > x.x)
					i++;
			}
		}
	}

	poly.pop_back ();

	return (i & 1); //if intersections is odd
}

int main ()
{
	Point l1 (0, 0), l2 (10, 0);
	Line l (l1, l2);

	Point p1 (1, 1), p2 (2, 2);
	cout << PtSameSide (p1, p2, l) << "\n"; //1
	
	p1 = Point (1, 1);
	p2 = Point (-100, -1);
	cout << PtSameSide (p1, p2, l) << "\n"; //0

	cout << SegIntersecExc (l1, l2, p1, p2) << "\n"; //0

	p1 = Point (2, 2);
	p2 = Point (1, -1);
	cout << SegIntersecExc (l1, l2, p1, p2) << "\n"; //1

	p1 = Point (10, 0);
	p2 = Point (20, 0);
	cout << SegIntersecExc (l1, l2, p1, p2) << "\n"; //0

	p1 = Point (9, 0);
	p2 = Point (20, 0);
	cout << SegIntersecExc (l1, l2, p1, p2) << "\n"; //1

	vector<Point> poly;
	poly.push_back (Point (0, 0));
	poly.push_back (Point (1, 2));
	poly.push_back (Point (2, 0));
	p1 = Point (1, 1);
	cout << PtInsidePolyIncDet (p1, poly) << "\n"; //1

	p1 = Point (1, 2);
	cout << PtInsidePolyIncDet (p1, poly) << "\n"; //1

	p1 = Point (0, 2);
	cout << PtInsidePolyIncDet (p1, poly) << "\n"; //0

	poly.clear ();
	poly.push_back (Point (0, 0));
	poly.push_back (Point (10, 10));
	poly.push_back (Point (20, 5));
	poly.push_back (Point (30, 15));
	poly.push_back (Point (40, 0));
	p1 = Point (10, 5);
	cout << PtInsidePolyIncDet (p1, poly) << "\n"; //1

	p1 = Point (0, 5);
	cout << PtInsidePolyIncDet (p1, poly) << "\n"; //0

	p1 = Point (0, 0);
	cout << PtInsidePolyIncDet (p1, poly) << "\n"; //1

	p1 = Point (-1, 0);
	cout << PtInsidePolyIncDet (p1, poly) << "\n"; //0

	p1 = Point (41, 0);
	cout << PtInsidePolyIncDet (p1, poly) << "\n"; //0

	p1 = Point (39, 0);
	cout << PtInsidePolyIncDet (p1, poly) << "\n"; //1

	p1 = Point (0, 10);
	cout << PtInsidePolyIncDet (p1, poly) << "\n"; //0

	poly.clear ();
	poly.push_back (Point (0, 0));
	poly.push_back (Point (0, 10));
	poly.push_back (Point (10, 5));
	poly.push_back (Point (20, 5));
	poly.push_back (Point (30, 5));
	poly.push_back (Point (30, 0));
	p1 = Point (5, 5);
	cout << PtInsidePolyIncDet (p1, poly) << "\n"; //1
	
	p1 = Point (15, 5);
	cout << PtInsidePolyIncDet (p1, poly) << "\n"; //1
	
	p1 = Point (-15, 5);
	cout << PtInsidePolyIncDet (p1, poly) << "\n"; //0
	
	p1 = Point (31, 5);
	cout << PtInsidePolyIncDet (p1, poly) << "\n"; //0
	
	p1 = Point (-1, 10);
	cout << PtInsidePolyIncDet (p1, poly) << "\n"; //0

	//100101110101001011000
	cin.get ();

	return 0;
}