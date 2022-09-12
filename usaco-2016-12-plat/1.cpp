#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES

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
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

typedef long long ll;

struct dPt {
	double x, y;

	dPt () {
		x = y = 0;
	}

	dPt (double xnew, double ynew) {
		x = xnew;
		y = ynew;
	}
};

tuple<int, int, int> &StTup (tuple<int, int, int> &&t) {
	if (get<0> (t) > get<1> (t))
		swap (get<0> (t), get<1> (t));
	if (get<0> (t) > get<2> (t))
		swap (get<0> (t), get<2> (t));
	if (get<2> (t) < get<1> (t))
		swap (get<2> (t), get<1> (t));
	return t;
}

inline double CP2D (dPt &&a, dPt &&b) {
	return a.x * b.y - a.y * b.x;
}

inline double CP2D3 (dPt &a, dPt &b, dPt &c) {
	return CP2D (dPt (b.x - a.x, b.y - a.y), dPt (c.x - b.x, c.y - b.y));
}

bool InTri (dPt &t, dPt &x, dPt &y, dPt &z) {
	bool t1 = CP2D3 (x, y, t) > 0,
		t2 = CP2D3 (y, z, t) > 0,
		t3 = CP2D3 (z, x, t) > 0;
	return t1 == t2 && t2 == t3;
}

inline int HashTup (tuple<int, int, int> &t) {
	return get<0> (t) * 90000 + get<1> (t) * 300 + get<2> (t);
}

int tt[27000000];

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("triangles.in", "r", stdin);
	freopen ("triangles.out", "w", stdout);
#endif

	int n;
	cin >> n;

	vector<dPt> pt (n);
	for (int a = 0;a < n;a++) {
		cin >> pt[a].x >> pt[a].y;
	}

	pt.shrink_to_fit ();
	sort (pt.begin (), pt.end (), [](const dPt &a, const dPt &b){return a.x < b.x;});

	memset (tt, -1, sizeof (tt));
	tt[HashTup (StTup (make_tuple (0, 1, 2)))] = 0;
	
	for (int a = 3;a < n;a++) {
		vector<pair<double, int>> degppt;
		for (int b = 0;b < a;b++) {
			double c = atan2 (pt[b].y - pt[a].y, pt[b].x - pt[a].x);
			if (c < 0) c += M_PI * 2;
			degppt.push_back (make_pair (c, b));
		}
		sort (degppt.begin (), degppt.end ());

		for (int b = 0;b < a - 1;b++)
			tt[HashTup (StTup (make_tuple (a, degppt[b].second, degppt[b + 1].second)))] = 0;
		for (int b = 2;b < a;b++) {
			for (int c = 0;c + b < a;c++) {
				if (InTri (pt[degppt[c + 1].second], pt[a], pt[degppt[c].second], pt[degppt[c + b].second]))
					tt[HashTup (StTup (make_tuple (a, degppt[c].second, degppt[c + b].second)))] =
						tt[HashTup (StTup (make_tuple (a, degppt[c].second, degppt[c + 1].second)))] +
						tt[HashTup (StTup (make_tuple (a, degppt[c + 1].second, degppt[c + b].second)))] +
						tt[HashTup (StTup (make_tuple (degppt[c].second, degppt[c + 1].second, degppt[c + b].second)))] +
						1;
				else
					tt[HashTup (StTup (make_tuple (a, degppt[c].second, degppt[c + b].second)))] =
						tt[HashTup (StTup (make_tuple (a, degppt[c].second, degppt[c + 1].second)))] +
						tt[HashTup (StTup (make_tuple (a, degppt[c + 1].second, degppt[c + b].second)))] -
						tt[HashTup (StTup (make_tuple (degppt[c].second, degppt[c + 1].second, degppt[c + b].second)))];
			}
		}
	}

	vector<int> ans (n - 2);
	for (auto ttref : tt)
		if (ttref != -1)
			ans[ttref]++;
	for (int a = 0;a < n - 2;a++)
		cout << ans[a] << '\n';

	return 0;
}