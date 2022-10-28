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

long long n, x[100001], dp[100001], ans;

int main ()
{
	ios_base::sync_with_stdio (false);
	
	freopen ("input.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	cin >> n;
	dp[0] = 0;
	for (int a = 1;a <= n;a++)
	{
		cin >> x[a];
		if (x[a] <= 0)
			dp[0]++;
	}
	ans = 100002;
	for (int a = 1;a < n;a++)
	{
		if (x[a] > 0) dp[a] = dp[a - 1] + 1;
		else if (x[a] < 0) dp[a] = dp[a - 1] - 1;
		else dp[a] = dp[a - 1];

		if (dp[a] < ans) ans = dp[a];
	}

	cout << ans << "\n";

	return 0;
}