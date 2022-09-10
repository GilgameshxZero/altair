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

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	int t, n, last;
	vector<int> g[4], sum[2];
	long long ans;
	cin >> t;

	for (;t > 0;t--)
	{
		cin >> n;
		ans = 0;
		sum[0].clear ();
		sum[1].clear ();
		for (int a = 0;a < 4;a++)
			g[a].resize (n);
		for (int a = 0;a < n;a++)
			cin >> g[0][a] >> g[1][a] >> g[2][a] >> g[3][a];
		for (int a = 0;a < n;a++)
		{
			for (int b = 0;b < n;b++)
			{
				sum[0].push_back (g[0][a] + g[1][b]);
				sum[1].push_back (g[2][a] + g[3][b]);
			}
		}

		sort (sum[0].begin (), sum[0].end ());
		sort (sum[1].begin (), sum[1].end ());

		for (int a = 0, b = sum[1].size () - 1, c;a < sum[0].size ();a++)
		{
			if (a != 0 && sum[0][a] == sum[0][a - 1])
			{
				ans += last;
				continue;
			}
			while (b != -1 && sum[1][b] > -sum[0][a])
				b--;
			c = b;
			while (c != -1 && sum[1][c] == -sum[0][a])
				c--;
			last = b - c;
			ans += last;
			b = c;
		}

		cout << ans << "\n";
		if (t != 1)
			cout << "\n";
	}

	return 0;
}