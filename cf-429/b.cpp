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

long long r, c, x[1000][1000], dp[4][1002][1002], ans;

//dp[0]: from 1, 1 to x, y
//dp[1]: from x, y to r, c
//dp[2]: from r, 1 to x, y
//dp[3]: from x, y to 1, c

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	cin >> r >> c;
	for (int a = 0;a < r;a++)
		for (int b = 0;b < c;b++)
			cin >> x[a][b];

	memset (dp, 0, sizeof (dp));

	for (int a = 1;a <= r;a++)
		for (int b = 1;b <= c;b++)
			dp[0][a][b] = x[a - 1][b - 1] + max (dp[0][a - 1][b], dp[0][a][b - 1]);

	for (int a = r;a >= 1;a--)
		for (int b = c;b >= 1;b--)
			dp[1][a][b] = x[a - 1][b - 1] + max (dp[1][a + 1][b], dp[1][a][b + 1]);

	for (int a = r;a >= 1;a--)
		for (int b = 1;b <= c;b++)
			dp[2][a][b] = x[a - 1][b - 1] + max (dp[2][a + 1][b], dp[2][a][b - 1]);

	for (int a = 1;a <= r;a++)
		for (int b = c;b >= 1;b--)
			dp[3][a][b] = x[a - 1][b - 1] + max (dp[3][a - 1][b], dp[3][a][b + 1]);

	ans = 0;
	for (int a = 2;a < r;a++)
	{
		for (int b = 2;b < c;b++)
		{
			ans = max (ans, dp[0][a - 1][b] + dp[1][a + 1][b] + dp[2][a][b - 1] + dp[3][a][b + 1]);
			ans = max (ans, dp[0][a][b - 1] + dp[1][a][b + 1] + dp[2][a + 1][b] + dp[3][a - 1][b]);
		}
	}

	cout << ans << "\n";

	return 0;
}