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
#include <stack>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

typedef long long ll;

struct Point
{
	int x, y;
};

double FindCross (Point p1, Point p2, int x) //assumes non-vert line
{
	double m = (double)(p2.y - p1.y) / (p2.x - p1.x);
	double b = p1.y - m * p1.x;
	return m * x + b;
}

bool CompP (Point a, Point b)
{
	return (a.y < b.y);
}

int main ()
{
	ios_base::sync_with_stdio (false);

	std::freopen ("tied.in", "r", stdin);
	std::freopen ("tied.out", "w", stdout);

	int n, m;
	Point bes;

	cin >> n >> m >> bes.x >> bes.y;

	vector<Point> post (n);
	for (int a = 0;a < n;a++)
		cin >> post[a].x >> post[a].y;

	vector<Point> rope (m + 1);
	for (int a = 0;a < m + 1;a++)
		cin >> rope[a].x >> rope[a].y;

	sort (post.begin (), post.end (), CompP);

	//precompute all cuts
	vector<int> cuts;
	vector<int> loc (n + 1);
	bool right = true;
	int ind;
	double cross;
	for (int a = 0;a < n;a++)
		loc[a] = post[a].y;
	loc[n] = 1e9;
	for (int a = 0;a < m;a++)
	{
		if ((rope[a + 1].x < post[0].x && right == true) ||
			(rope[a + 1].x > post[0].x && right == false))
		{
			if (rope[a].x == rope[a + 1].x) //vert
				cross = rope[a].x;
			else
				cross = FindCross (rope[a], rope[a + 1], post[0].x);
			right = !right;
			ind = upper_bound (loc.begin (), loc.end (), (int)cross) - loc.begin ();
			cuts.push_back (ind);
		}
	}

	//try all subsets of rope to remove
	int ans = 1000, cnt, t;
	vector<int> s;
	vector<int> id (n + 1);
	for (int a = 0, b = (1 << n);a < b;a++)
	{
		cnt = 0;
		for (int c = 0;c < n;c++)
			if ((a >> c) & 1)
				cnt++;

		if (cnt >= ans)
			continue;

		//compute the ID of each cross loc with removed points
		t = 0;
		for (int c = 0;c < n;c++)
		{
			id[c] = t;
			if (!((a >> c) & 1))
				t++;
		}
		id[n] = t;

		//stack method, with enhanced crossing
		s.clear ();
		for (int c = 0;c < cuts.size ();c++)
		{
			if (!s.empty () && id[cuts[c]] == s.back ())
				s.pop_back ();
			else
				s.push_back (id[cuts[c]]);
		}

		if (s.empty ())
			ans = cnt;
	}

	cout << ans << "\n";

	return 0;
}