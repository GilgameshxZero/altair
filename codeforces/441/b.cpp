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

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif
	pair<int, int> y[3010];
	int n, v, ans = 0, tree[3010];
	vector<int *> fruit[3010];

	cin >> n >> v;
	for (int a = 0, b, c;a < n;a++)
		cin >> b >> c,
		y[a] = make_pair (b, c);

	sort (y, y + n);

	for (int a = 0;a < n;a++)
		tree[a] = y[a].second,
		fruit[y[a].first].push_back (&tree[a]),
		fruit[y[a].first + 1].push_back (&tree[a]);
	for (int a = 0;a < 3010;a++)
	{
		int x = 0;
		for (int b = 0;b < fruit[a].size ();b++)
			if (x + *fruit[a][b] <= v)
				x += *fruit[a][b],
				*fruit[a][b] = 0;
			else
				*fruit[a][b] -= (v - x),
				x = v;

		ans += x;
	}

	cout << ans << "\n";

	return 0;
}