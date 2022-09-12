//incremental convex hull to maintian queries
//binary search for slope of line on convex hull to get range of y-ints, then check if line intersects hull
//NlogN
//edit:no time

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

typedef long long ll;

struct Point
{
	ll x, y;
};

bool Close (double a, double b)
{
	return (abs (a - b) < 1e-8);
}

int main ()
{
	ios_base::sync_with_stdio (false);

	std::freopen ("fencing.in", "r", stdin);
	std::freopen ("fencing.out", "w", stdout);

	int n, q;
	cin >> n >> q;

	vector<Point> pt;
	for (int a = 0;a < n;a++)
		pt.push_back (Point ()),
		cin >> pt.back ().x >> pt.back ().y;

	double k, l;

	for (int a = 0;a < q;a++)
	{
		ll x;
		cin >> x;

		if (x == 1)
		{
			pt.push_back (Point ()),
			cin >> pt.back ().x >> pt.back ().y;
		}
		else
		{
			ll y, z;
			cin >> x >> y >> z;
			
			l = (double)z;
			bool big = ((double)x * pt[0].x + (double)y * pt[0].y > (double)z), flag = true;
			for (int b = 0;b < pt.size ();b++)
			{
				k = (double)x * pt[b].x + (double)y * pt[b].y;
				if (Close (k, l))
				{
					flag = false;
					break;
				}
				if ((big && (k < l)) || (!big && (k > l)))
				{
					flag = false;
					break;
				}
			}

			if (flag)
				cout << "YES\n";
			else
				cout << "NO\n";
		}
	}

	return 0;
}