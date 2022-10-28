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

int n, k, x[100], y[100], real_dp[100][20001], *dp[100];

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif
	
	cin >> n >> k;
	for (int a = 0;a < n;a++)
		cin >> x[a];
	for (int a = 0;a < n;a++)
		cin >> y[a];

	for (int a = 0;a < 100;a++)
		dp[a] = real_dp[a] + 10000;

	memset (real_dp, -1, sizeof (real_dp));
	dp[0][0] = 0;
	dp[0][x[0] - k * y[0]] = x[0];

	for (int a = 1;a < n;a++)
	{
		for (int b = -10000;b <= 10000;b++)
		{
			if (dp[a - 1][b] != -1)
			{
				if (b + x[a] - k * y[a] >= -10000 && b + x[a] - k * y[a] < 10000)
					dp[a][b + x[a] - k * y[a]] = max (dp[a - 1][b] + x[a], dp[a][b + x[a] - k * y[a]]);
				dp[a][b] = max (dp[a - 1][b], dp[a][b]);
			}
		}
	}

	if (dp[n - 1][0] == 0) cout << "-1\n";
	else cout << dp[n - 1][0] << "\n";

	return 0;
}