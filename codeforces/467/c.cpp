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

long long dp[2][5001];

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	long long n, m, k, x[5001];

	cin >> n >> m >> k;
	x[0] = 0;
	for (int a = 1, b;a <= n;a++)
		cin >> b,
		x[a] = b + x[a - 1];

	memset (dp[0], 0, sizeof (dp[0]));
	for (int a = 1, b, c = 1;a <= k;a++, c = !c)
		for (b = m * a;b <= n;b++)
			dp[c][b] = max (dp[c][b - 1], dp[!c][b - m] + x[b] - x[b - m]);

	cout << dp[k & 1][n] << "\n";

	return 0;
}