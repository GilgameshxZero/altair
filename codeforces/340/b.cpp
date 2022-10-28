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
#include <functional>
#include <map>
#include <queue>
#include <utility>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

struct Point
{
	double x, y;
};

//Finds the distance between two points.
//Point p1 (in): The first point.
//Point p2 (in): The second point.
double PointPointDistance (Point p1, Point p2)
{
	return sqrt ((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

//This function calculates the conves hull of a set of points using Jarvis' March.
//Point *hull (out): Pass a Point array which a size of at least cpoint to this variable. It will contain the convex hull after the funtion completes.
//size_t *hull_size (out): Pass a pointer to a size_t variable to this parameter. It will contain the number of points in the convex hull when the function completes.
//const Point *point (in): Pass the set of points to this variable. It will not be modified.
//const size_t cpoint (in): Pass the number of points availible.
bool ConvexHullJarvis (Point *hull, size_t *hull_size, const Point *point, const size_t cpoint)
{
	const double PI = atan2 (0, -1);
	Point low_pt, high_pt, curr_pt, next_pt;
	double low_rad, b;
	unsigned int a;

	//Check if cpoint is 0 or 1, because that means that we our hull is either empty or just one point.
	if (cpoint == 0)
	{
		*hull_size = 0;

		return false;
	}
	else if (cpoint == 1)
	{
		*hull_size = 1;
		hull[0].x = point[0].x;
		hull[0].y = point[0].y;

		return false;
	}

	//Calculate the lowest-left point, and the highest-right point, because these points are guaranteed to be in our hull.
	*hull_size = 0;
	low_pt.x = low_pt.y = numeric_limits<double>::max ();
	high_pt.x = high_pt.y = numeric_limits<double>::min ();

	for (a = 0;a < cpoint;a++)
	{
		if (point[a].y < low_pt.y)
		{
			low_pt.y = point[a].y;
			low_pt.x = point[a].x;
		}
		else if (point[a].y == low_pt.y && point[a].x < low_pt.x)
			low_pt.x = point[a].x;

		if (point[a].y > high_pt.y)
		{
			high_pt.y = point[a].y;
			high_pt.x = point[a].x;
		}
		else if (point[a].y == high_pt.y && point[a].x > high_pt.x)
			high_pt.x = point[a].x;
	}

	curr_pt = low_pt;

	//Determine the right chain.
	while (!(high_pt.x == curr_pt.x && high_pt.y == curr_pt.y))
	{
		low_rad = numeric_limits<double>::max ();

		//Calculate the point with the lowest angle degree when considered in a vector with our curr_pt. Take the farthest one in case of a tie.
		for (a = 0;a < cpoint;a++)
		{
			//Make sure they aren't the same point.
			if (!(point[a].x == curr_pt.x && point[a].y == curr_pt.y))
			{
				//atan2 will take into account the quadrant, unlike atan.
				b = atan2 (point[a].y - curr_pt.y, point[a].x - curr_pt.x);

				if (b < low_rad && b >= 0 && b < PI) //Strictly above the left horozontal axis, and inclusively above the right horozontal axis.
				{
					low_rad = b;
					next_pt = point[a];
				}
				else if (b == low_rad) //In case of a tie, take the point farthest from curr_pt.
					if (PointPointDistance (curr_pt, point[a]) > PointPointDistance (curr_pt, next_pt))
						next_pt = point[a];
			}
		}

		//Add our curr_pt to the convex hull, and set curr_pt to equal next_pt.
		hull[(*hull_size)++] = curr_pt;
		curr_pt = next_pt;
	}

	//Determine the left chain. This is pretty similar to before, but instead of finding the least angle with the positive x axis, we are going to determine the smallest angle to the negative x axis.
	while (!(low_pt.x == curr_pt.x && low_pt.y == curr_pt.y))
	{
		low_rad = 0;

		for (a = 0;a < cpoint;a++)
		{
			if (!(point[a].x == curr_pt.x && point[a].y == curr_pt.y))
			{
				b = atan2 (point[a].y - curr_pt.y, point[a].x - curr_pt.x);

				//Make sure the inequalities work.
				if (b == PI)
					b = -PI;

				if (b < low_rad)
				{
					low_rad = b;
					next_pt = point[a];
				}
				else if (b == low_rad)
					if (PointPointDistance (curr_pt, point[a]) > PointPointDistance (curr_pt, next_pt))
						next_pt = point[a];
			}
		}

		hull[(*hull_size)++] = curr_pt;
		curr_pt = next_pt;
	}

	return false;
}

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	Point x[300], hull[300];
	int n;
	size_t shull;

	cin >> n;
	for (int a = 0;a < n;a++)
		cin >> x[a].x >> x[a].y;

	ConvexHullJarvis (hull, &shull, x, n);

	for (int a = 0;a < shull;a++)
	{
		for (int b = 0;b < shull;b++)
		{
			for (int c = 0;c < shull;c++)
			{
				for (int d = 0;d < shull;d++)
				{
					if (a != b && a != c && a != d && b != c && b != d && c != d)

				}
			}
		}
	}

	return 0;
}