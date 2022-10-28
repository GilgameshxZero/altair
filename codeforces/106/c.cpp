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
#include <stack>
#include <string>
#include <vector>

using namespace std;

int n, m, c0, d0, a[11], b[11], c[11], d[11], x[11], dp[1001][11];

int Ans (int dough, int limit)
{
	if (dp[dough][limit] != -1)
		return dp[dough][limit];
	if (dough == 0)
		return 0;
	if (limit == 0)
		return (dough / c0) * d0;

	int r = Ans (dough, limit - 1);
	
	if (dough - c0 >= 0)
		r = max (r, Ans (dough - c0, limit - 1) + d0);

	for (int i = dough - c[limit], j = d[limit], k = 1;i >= 0 && k <= x[limit];i -= c[limit], j += d[limit], k++)
		r = max (r, Ans (i, limit - 1) + j);

	return dp[dough][limit] = r;
}

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	int dp[12][1001], ans;

	cin >> n >> m >> c0 >> d0;
	for (int i = 1;i <= m;i++)
		cin >> a[i] >> b[i] >> c[i] >> d[i],
		x[i] = a[i] / b[i];

	memset (dp, 0, sizeof (dp));
	for (int i = 0;i <= m;i++)
		for (int j = 0;j <= n;j++)
			for (int k = 0;k <= x[i + 1] && j + k * c[i + 1] <= n;k++)
				dp[i + 1][j + k * c[i + 1]] = max (dp[i + 1][j + k * c[i + 1]], dp[i][j] + k * d[i + 1]);

	ans = dp[m][n];
	for (int i = n - 1;i >= 0;i--)
		ans = max (ans, dp[m][i] + (n - i) / c0 * d0);

	cout << ans;

	return 0;
}