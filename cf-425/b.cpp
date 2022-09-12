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

	int n, m, k, x[100][100], ans = 10000;
	cin >> n >> m >> k;

	for (int a = 0;a < n;a++)
		for (int b = 0;b < m;b++)
			cin >> x[a][b];

	if (n <= k)
	{
		for (int a = 0, b, c, d, e;a < (1 << n);a++)
		{
			b = 0;
			for (c = 0;c < m;c++)
			{
				for (d = 0, e = 0;e < n;e++)
					d += x[e][c] ^ ((a >> e) & 1);
				b += min (d, n - d);
			}
			ans = min (ans, b);
		}
	}
	else
	{
		//Choose model row.
		for (int a = 0, b, c, d, e;a < n;a++)
		{
			b = 0;
			for (c = 0;c < n;c++)
			{
				for (d = 0, e = 0;e < m;e++)
					d += x[c][e] ^ x[a][e];
				b += min (d, m - d);
			}
			ans = min (ans, b);
		}
	}

	if (ans <= k)
		cout << ans << "\n";
	else
		cout << "-1\n";

	return 0;
}