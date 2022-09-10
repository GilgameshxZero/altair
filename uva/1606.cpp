#include <algorithm>
#include <bitset>
#include <cassert>
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
#include <limits>
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
	int x, y, type;
};

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	const int PI = 3.14159265358979;
	int N, ans;
	double dtemp;
	vector<Point> pts;
	vector< pair<double, int> > angle; //0: add type 0, 1: add type 1, 2: rem type 0, 3: rem type 1
	pair<int, int> cnt[2];

	while (cin >> N, N != 0)
	{
		pts.resize (N);
		for (int a = 0;a < N;a++)
			cin >> pts[a].x >> pts[a].y >> pts[a].type;

		if (N == 1)
		{
			cout << "2\n";
			continue;
		}

		//use sweepline approach centering the line at every point
		ans = 0;
		for (int a = 0;a < N;a++)
		{
			cnt[0].first = cnt[0].second = 0;
			cnt[1] = cnt[0];
			//sort all points by angle (0 <= alpha < 180) with respect to point a and get counts
			angle.clear ();
			for (int b = 0;b < N;b++)
			{
				if (a == b)
					continue;

				dtemp = atan2 ((double)(pts[b].y - pts[a].y), (double)(pts[b].x - pts[a].x));
				if (pts[b].y == pts[a].y && pts[b].x < pts[a].x)
					dtemp = -PI;
				if (pts[b].type == 0 && dtemp >= 0)
					angle.push_back (make_pair (dtemp, 0)),
					cnt[0].first++;
				else if (pts[b].type == 1 && dtemp >= 0)
					angle.push_back (make_pair (dtemp, 1)),
					cnt[0].second++;
				else if (pts[b].type == 0)
					angle.push_back (make_pair (dtemp + PI, 2)),
					cnt[1].first++;
				else
					angle.push_back (make_pair (dtemp + PI, 3)),
					cnt[1].second++;
			}
			sort (angle.begin (), angle.end ());

			//loop through points, testing both cases with each point, and use sweepline, and update ans on the way
			for (int b = 0;b < angle.size ();b++)
			{
				//sweepline
				if (angle[b].second == 0)
					cnt[0].first--;
				else if (angle[b].second == 1)
					cnt[0].second--;
				else if (angle[b].second == 2)
					cnt[1].first--;
				else
					cnt[1].second--;

				//update ans (+2 because there are 2 points on line)
				ans = max (ans, 2 + max (cnt[0].first + cnt[1].second, cnt[0].second + cnt[1].first));

				//sweepline
				if (angle[b].second == 0)
					cnt[1].first++;
				else if (angle[b].second == 1)
					cnt[1].second++;
				else if (angle[b].second == 2)
					cnt[0].first++;
				else
					cnt[0].second++;
			}
		}

		cout << ans << "\n";
	}

	return 0;
}