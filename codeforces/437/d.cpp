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
#include <functional>

using namespace std;

vector<int> edge[100000];
pair<int, int> sref[100000];
double ans;
int n, m, par[100000];
bool in_tree[100000];

int Find (int x)
{
	if (par[x] < 0) return x;
	return par[x] = Find (par[x]);
}

int Size (int x)
{
	return -par[Find (x)];
}

bool Union (int x, int y)
{
	int i = Find (x), j = Find (y);

	if (i == j) return false;

	if (-par[i] > -par[j])
		par[i] += par[j],
		par[j] = i;
	else
		par[j] += par[i],
		par[i] = j;

	return true;
}

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	cin >> n >> m;
	for (int a = 0, b;a < n;a++)
		cin >> b,
		sref[a] = make_pair (b, a);
	for (int a = 0, b, c;a < m;a++)
		cin >> b >> c,
		edge[b - 1].push_back (c - 1),
		edge[c - 1].push_back (b - 1);

	memset (par, -1, sizeof (par));
	memset (in_tree, 0, sizeof (in_tree));
	sort (sref, sref + n, greater< pair<int, int> >());

	for (int a = 0, b, c, d, e;a < n;a++)
	{
		b = sref[a].second;
		in_tree[b] = true;
		for (c = 0;c < edge[b].size ();c++)
		{
			if (in_tree[edge[b][c]])
			{
				d = Size (b), e = Size (edge[b][c]);
				if (Union (b, edge[b][c]) == true)
					ans += (double)d * e * sref[a].first / n / (n - 1) * 2;
			}
		}
	}

	cout << fixed << setprecision (6) << ans << "\n";

	return 0;
}