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

int n, x[100000], dp[100001], ans;

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	cin >> n;
	for (int a = 0;a < n;a++)
		cin >> x[a];

	ans = 1;
	memset (dp, 0, sizeof (dp));

	for (int a = 1;a * a <= x[0];a++)
		if (x[0] % a == 0)
			dp[a] = dp[x[0]/a] = 1;

	dp[1] = 0;

	for (int a = 1, c;a < n;a++, dp[1] = 0)
	{
		c = 0;
		for (int b = 1;b * b <= x[a];b++)
			if (x[a] % b == 0)
				c = max (c, max (dp[b] + 1, dp[x[a]/b] + 1));

		for (int b = 1;b * b <= x[a];b++)
			if (x[a] % b == 0)
				dp[b] = max (dp[b], c),
				dp[x[a]/b] = max (dp[x[a]/b], c);

		if (c > ans)
			ans = c;
	}

	cout << ans << "\n";

	return 0;
}