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

const int MAXN = 100000;

int n;
bool seq[MAXN], goal[MAXN];
vector<int> node[MAXN], ans;

void DFS (int curr, int parent, bool cpar, bool opar)
{
	//Change this node?
	if (seq[curr] ^ goal[curr] != cpar)
	{
		cpar = !cpar;
		ans.push_back (curr);
	}

	//Fix children.
	for (int a = 0;a < node[curr].size ();a++)
		if (node[curr][a] != parent)
			DFS (node[curr][a], curr, opar, cpar);
}

int main ()
{
	ios_base::sync_with_stdio (false);

	#ifndef ONLINE_JUDGE
		freopen ("input0.txt", "r", stdin);
		freopen ("output.txt", "w", stdout);
	#endif

	cin >> n;

	for (int a = 0, b, c;a < n - 1;a++)
	{
		cin >> b >> c;
		node[b - 1].push_back (c - 1);
		node[c - 1].push_back (b - 1);
	}

	for (int a = 0;a < n;a++)
		cin >> seq[a];
	for (int a = 0;a < n;a++)
		cin >> goal[a];

	DFS (0, -1, false, false);

	cout << ans.size () << "\n";

	for (int a = 0;a < ans.size ();a++)
		cout << ans[a] + 1 << "\n";

	return 0;
}