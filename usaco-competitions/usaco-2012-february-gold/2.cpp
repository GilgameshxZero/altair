#include <algorithm>
#include <bitset>
#include <limits>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <map>
#include <queue>
#include <utility>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

typedef long long ll;

bool CloseTo (double a, double b)
{
	const double EPS = 1e-9;
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

		bool IsNull ()
		{
			return (A == 0 && B == 0 && C == 0);
		}

		//makes line into either AX + BY + 1 = 0 or X + BY = 0 depending on if C is 0 or just X = 0 or Y = 0
		void Standardize ()
		{
			if (IsNull ())
				return;

			if (C != 0)
			{
				A /= C;
				B /= C;
				C = 1;
			}
			else if (A != 0) //C = 0
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

bool Parallel (Line &a, Line &b)
{
	return CloseTo (a.B * b.A - a.A * b.B, 0);
}

Line LineThru (Point &a, Point &b)
{
	return Line (b.y - a.y, a.x - b.x, b.x * a.y - a.x * b.y);
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

//assumes nonparallel
Point LLIntersec (Line &a, Line &b)
{
	return Point ((b.B * a.C - a.B * b.C) / (a.B * b.A - a.A * b.B), (a.A * b.C - a.C * b.A) / (a.B * b.A - a.A * b.B));
}

//reflect point a across line l
Point Reflect (Point &a, Line &l)
{
	Line m = PerpLine (a, l);
	Point b = LLIntersec (l, m);
	return Point (2 * b.x - a.x, 2 * b.y - a.y);
}

int main ()
{
	ios_base::sync_with_stdio (false);

	std::freopen ("symmetry.in", "r", stdin);
	std::freopen ("symmetry.out", "w", stdout);

	int n;
	cin >> n;

	vector< pair<int, int> > pt (n);
	for (int a = 0;a < n;a++)
		cin >> pt[a].first >> pt[a].second;

	//insert all into set for easy check existence
	set< pair<int, int> > spt;
	for (int a = 0;a < n;a++)
		spt.insert (pt[a]);

	vector<Line> ans;
	Point t1, t2;
	//check every line around point a
	for (int a = 0;a < 2;a++)
	{
		for (int b = 1;b < n;b++)
		{
			if (b == a)
				continue;

			t1 = Point (pt[a].first, pt[a].second);
			t2 = Point (pt[b].first, pt[b].second);
			Line l = PerpBisec (t1, t2);
			bool flag = true;

			for (int c = 0;c < n;c++)
			{
				t1 = Point (pt[c].first, pt[c].second);
				Point p = Reflect (t1, l);

				if (!(CloseTo (p.x, Round (p.x)) && CloseTo (p.y, Round (p.y))
					&& spt.find (make_pair (Round (p.x), Round (p.y))) != spt.end ()))
				{
					flag = false;
					break;
				}
			}

			if (flag)
			{
				//check that line is not duplicate
				flag = true;
				for (int c = 0;c < ans.size ();c++)
				{
					if (ans[c] == l)
					{
						flag = false;
						break;
					}
				}
				if (flag)
					ans.push_back (l);
			}
		}
	}
	
	//check the line through pt[0] and pt[1]
	int a = 0, b = 1;
	t1 = Point (pt[a].first, pt[a].second);
	t2 = Point (pt[b].first, pt[b].second);
	Line l = LineThru (t1, t2);
	bool flag = true;

	for (int c = 0;c < n;c++)
	{
		t1 = Point (pt[c].first, pt[c].second);
		Point p = Reflect (t1, l);

		if (!(CloseTo (p.x, Round (p.x)) && CloseTo (p.y, Round (p.y))
			&& spt.find (make_pair (Round (p.x), Round (p.y))) != spt.end ()))
		{
			flag = false;
			break;
		}
	}

	if (flag)
	{
		//check that line is not duplicate
		flag = true;
		for (int c = 0;c < ans.size ();c++)
		{
			if (ans[c] == l)
			{
				flag = false;
				break;
			}
		}
		if (flag)
			ans.push_back (l);
	}

	cout << ans.size () << "\n";

	return 0;
}