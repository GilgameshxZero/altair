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

struct HSeg
{
	int c, x1, x2;
	HSeg (int x, int y, int z)
	{
		c = x;
		x1 = y;
		x2 = z;
	}
};

struct VSeg
{
	int c, x1, x2;
	VSeg (int x, int y, int z)
	{
		c = x;
		x1 = y;
		x2 = z;
	}
};

bool Intersect (HSeg x, VSeg y)
{
	return (x.c >= y.x1 && x.c <= y.x2 && y.c >= x.x1 && y.c <= x.x2);
}

bool Augment (bitset<250>& vis, vector< vector<int> >& edge, vector<int>& match, int x)
{
	for (int a = 0;a < edge[x].size ();a++)
	{
		if (!vis[edge[x][a]])
		{
			vis[edge[x][a]] = true;
			if (match[edge[x][a]] == -1 || Augment (vis, edge, match, match[edge[x][a]]))
			{
				match[edge[x][a]] = x;
				return true;
			}
		}
	}

	return false;
}

int main ()
{
	ios_base::sync_with_stdio (false);

	std::freopen ("steeple.in", "r", stdin);
	std::freopen ("steeple.out", "w", stdout);

	//ans = N - maxflow
	int n;
	cin >> n;
	
	vector< pair<int, HSeg> > horo;
	vector< pair<int, VSeg> > vert;
	for (int a = 0, b, c, d, e;a < n;a++)
	{
		cin >> b >> c >> d >> e;
		if (b == d)
			vert.push_back (make_pair (a,VSeg (b, min (c, e), max (c, e))));
		else
			horo.push_back (make_pair (a, HSeg (c, min (b, d), max (b, d))));
	}

	vector< vector<int> > edge; //available edges from each vert
	edge.resize (n);
	for (int a = 0;a < horo.size ();a++)
	{
		for (int b = 0;b < vert.size ();b++)
		{
			if (Intersect (horo[a].second, vert[b].second))
			{
				edge[horo[a].first].push_back (vert[b].first);
				edge[vert[b].first].push_back (horo[a].first);
			}
		}
	}

	//find the maxflow using dfs
	vector<int> match;
	bitset<250> vis;
	int ans = 0;
	match.resize (n, -1);
	for (int a = 0;a < horo.size ();a++)
	{
		vis.reset ();
		ans += Augment (vis, edge, match, horo[a].first);
	}

	cout << n - ans << "\n";

	return 0;
}