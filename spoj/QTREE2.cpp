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

int t, n, par[10001][14], dist[10001], dep[10001];
vector< pair<int, int> > edge[10001];

void DFS (int vert, int fa, int d)
{
	par[vert][0] = fa;
	dep[vert] = d + 1;
	//update dist to children
	for (int a = 0;a < edge[vert].size ();a++)
	{
		if (edge[vert][a].first == fa) continue;
		dist[edge[vert][a].first] = dist[vert] + edge[vert][a].second;
		DFS (edge[vert][a].first, vert, d + 1);
	}
}

int LCA (int v1, int v2)
{
	//get deeper vert to same dep
	if (dep[v1] > dep[v2])
		swap (v1, v2);

	int x = dep[v2] - dep[v1];
	for (int a = 0;a < 31;a++)
		if (x & (1 << a))
			v2 = par[v2][a];

	if (v1 == v2)
		return v1;

	//get LCA
	for (int a = 13;a >= 0;a--)
		if (par[v1][a] != par[v2][a])
			v1 = par[v1][a], v2 = par[v2][a];

	return par[v1][0];
}

int KAnc (int vert, int k)
{
	for (int a = 0;a < 31;a++)
		if (k & (1 << a))
			vert = par[vert][a];

	return vert;
}

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	cin >> t;

	for (;t > 0;t--)
	{
		cin >> n;
		
		//root at 1
		for (int a = 0;a < 10001;a++)
			edge[a].clear ();
		for (int a = 1, b, c, d;a < n;a++)
		{
			cin >> b >> c >> d;
			edge[b].push_back (make_pair (c, d));
			edge[c].push_back (make_pair (b, d));
		}

		//build dist array/init par array/dep array
		dist[1] = 0;
		DFS (1, 1, 0);

		//finish par w/ dp
		for (int a = 1;a < 14;a++)
			for (int b = 1;b <= n;b++)
				par[b][a] = par[par[b][a - 1]][a - 1];

		//get queries until done
		string s;
		while (true)
		{
			cin >> s;
			if (s == "DIST")
			{
				int x, y;
				cin >> x >> y;
				cout << dist[x] + dist[y] - 2 * dist[LCA (x, y)] << "\n";
			}
			else if (s == "KTH")
			{
				int x, y, z, t;
				cin >> x >> y >> z;
				t = LCA (x, y);
				if (z > dep[x] - dep[t])
					swap (x, y),
					z = dep[x] + dep[y] - 2 * dep[t] + 1 - z;
				cout << KAnc (x, z) << "\n";
			}
			else
				break;
		}
	}

	return 0;
}