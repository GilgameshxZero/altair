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

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	long long n, k, d, dp[101][2];
	cin >> n >> k >> d;
	
	memset (dp, 0, sizeof (dp));
	dp[0][0] = 1;

	for (int a = 0;a <= n;a++)
	{
		for (int b = 1;b < d;b++)
			if (a + b <= n)
				dp[a + b][0] = (dp[a + b][0] + dp[a][0]) % 1000000007,
				dp[a + b][1] = (dp[a + b][1] + dp[a][1]) % 1000000007;
		for (int b = d;b <= k;b++)
			if (a + b <= n)
				dp[a + b][1] = (dp[a + b][1] + dp[a][0] + dp[a][1]) % 1000000007;
	}

	cout << dp[n][1] << "\n";

	return 0;
}