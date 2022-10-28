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

int par[300];

int Find (int x)
{
	if (par[x] < 0) return x;
	return par[x] = Find (par[x]);
}

void Union (int x, int y)
{
	int i = Find (x), j = Find (y);

	if (i == j) return;
	if (-par[i] >= -par[j])
		par[i] += par[j],
		par[j] = i;
	else
		par[j] += par[i],
		par[i] = j;
}

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	int n;
	cin >> n;

	vector<int> perm (n);
	for (int a = 0;a < n;a++)
		cin >> perm[a];

	vector< vector<int> > mat (n, vector<int> (n));
	string s;
	for (int a = 0;a < n;a++)
	{
		cin >> s;
		for (int b = 0;b < n;b++)
			mat[a][b] = s[b];
	}

	memset (par, -1, sizeof (par));
	vector< vector<int> > lists, ind;
	for (int a = 0;a < n;a++)
	{
		for (int b = a + 1;b < n;b++)
			if (mat[a][b] == '1')
				Union (a, b);
	}
	lists.resize (n);
	ind = lists;
	for (int a = 0;a < n;a++)
		lists[Find (a)].push_back (perm[a]),
		ind[Find(a)].push_back (a);
	for (int a = 0;a < n;a++)
		sort (lists[a].begin (), lists[a].end ());
	for (int a = 0;a < n;a++)
		for (int b = 0;b < lists[a].size ();b++)
			perm[ind[a][b]] = lists[a][b];

	for (int a = 0;a < n;a++)
		cout << perm[a] << " ";

	return 0;
}