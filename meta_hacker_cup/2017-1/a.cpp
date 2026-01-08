#define _CRT_SECURE_NO_WARNINGS

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

typedef long long ll;

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.in", "r", stdin);
	freopen ("output.out", "w", stdout);
#endif

	int t, n, m;
	cin >> t;

	for (int a = 0;a < t;a++) {
		int n, m;
		cin >> n >> m;

		vector<vector<ll>> pc (n, vector<ll>(m));
		for (int b = 0;b < n;b++) {
			for (int c = 0;c < m;c++)
				cin >> pc[b][c];
			sort (pc[b].begin (), pc[b].end ());
		}

		for (int b = 0;b < n;b++) {
			for (int c = 0;c < m;c++) {
				if (c == 0)
					pc[b][c]++;
				else
					pc[b][c] += pc[b][c - 1] + (c + 1) * (c + 1) - c * c;
			}
		}

		vector<vector<ll>> dp (n, vector<ll>(n + 1, 1e15));
		dp[0][0] = 0;
		for (int b = 0;b < m && b < n;b++)
			dp[0][b + 1] = pc[0][b];
		for (int b = 0;b < n - 1;b++) {
			for (int c = 0;c < n + 1;c++) {
				for (int d = 0;d < m + 1;d++) {
					if (d == 0)
						dp[b + 1][c + d] = min (dp[b + 1][c + d], dp[b][c]);
					else
						if (c + d < n + 1)
							dp[b + 1][c + d] = min (dp[b + 1][c + d], dp[b][c] + pc[b + 1][d - 1]);
				}
			}
		}

		cout << "Case #" << a + 1<< ": " << dp[n - 1][n] << endl;
	}

	return 0;
}