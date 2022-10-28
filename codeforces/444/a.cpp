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

double ans;
int n, m, x[501], v, e;
bool vis[501];
vector< pair<int, int> > edge[501];

void MST (int vert)
{
	v += x[vert];
	vis[vert] = true;

	int sum = 0;
	for (int a = 0;a < edge[vert].size ();a++)
		if (vis[edge[vert][a].first])
			sum += edge[vert][a].second;

	e += sum;
	if (e != 0 && (double)v / e > ans)
		ans = (double)v / e;

	double large = 0;
	int neigh = -1;
	for (int a = 0;a < edge[vert].size ();a++)
	{
		if (!vis[edge[vert][a].first] && (double)(v + x[edge[vert][a].first]) / (e + edge[vert][a].second) > large)
		{
			large = (double)(v + x[edge[vert][a].first]) / (e + edge[vert][a].second);
			neigh = edge[vert][a].first;
		}
	}

	if (neigh != -1)
		MST (neigh);

	e -= sum;
	vis[vert] = false;
	v -= x[vert];
}

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input3.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	cin >> n >> m;
	for (int a = 1;a <= n;a++)
		cin >> x[a];
	for (int a = 0, b, c, d;a < m;a++)
	{
		cin >> b >> c >> d;
		edge[b].push_back (make_pair (c, d));
		edge[c].push_back (make_pair (b, d));
	}

	//MST from every vertex.
	for (int a = 1;a <= n;a++)
		MST (a);

	cout << fixed << setprecision (14) << ans << "\n";

	return 0;
}