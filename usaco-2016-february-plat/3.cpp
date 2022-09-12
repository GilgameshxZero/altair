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

//dp[n][n][k]

using namespace std;

typedef long long ll;

vector<int> req;
vector<ll> pre;
int n, k;
ll dp[1000][1001][8];
ll dfirstdoor[1000][1001][8], ld[1000][1001][8];

int main ()
{
	ios_base::sync_with_stdio (false);

	std::freopen ("cbarn.in", "r", stdin);
	std::freopen ("cbarn.out", "w", stdout);

	cin >> n >> k;

	req.resize (n);
	pre.resize (n * 2 + 1);
	pre[0] = 0;
	for (int a = 0; a < n; a++)
	{
		cin >> req[a];
		pre[a + 1] = pre[a + n + 1] = req[a];
	}

	//k = 1
	int test, ans, small = 100000;
	for (int a = 0;a < n;a++)
	{
		test = 0;
		for (int b = (a + 1) % n;b != a;b = (b + 1) % n)
			test += ((b - a + n) % n) * req[b];
		if (test < small)
		{
			small = test;
			ans = a;
		}
	}

	cout << "1: " << ans + 1 << '\t' << small << '\n';

	//k = 2
	int ans2;
	for (int a = 0; a < n - 1; a++)
	{
		for (int b = a + 1; b < n;b++)
		{
			test = 0;
			for (int c = (a + 1) % n; c != b;c = (c + 1) % n)
				test += ((c - a + n) % n) * req[c];
			for (int c = (b + 1) % n; c != a; c = (c + 1) % n)
				test += ((c - b + n) % n) * req[c];
			if (test < small)
			{
				small = test;
				ans = a;
				ans2 = b;
			}
		}
	}

	cout << "2: " << ans + 1 << '\t' << ans2 + 1 << '\t' << small << '\n';

	//k = 3
	int ans3;
	for (int a = 0; a < n - 2; a++)
	{
		for (int b = a + 1; b < n - 1; b++)
		{
			for (int d = b + 1;d < n;d++)
			{
				test = 0;
				for (int c = (a + 1) % n; c != b; c = (c + 1) % n)
					test += ((c - a + n) % n) * req[c];
				for (int c = (b + 1) % n; c != d; c = (c + 1) % n)
					test += ((c - b + n) % n) * req[c];
				for (int c = (d + 1) % n; c != a; c = (c + 1) % n)
					test += ((c - d + n) % n) * req[c];
				if (test < small)
				{
					small = test;
					ans = a;
					ans2 = b;
					ans3 = d;
				}
			}
		}
	}

	cout << "3: " << ans + 1 << '\t' << ans2 + 1 << '\t' << ans3 + 1 << '\t' << small << '\n';

	//k = 4
	int ans4;
	for (int a = 0; a < n - 3; a++)
	{
		for (int b = a + 1; b < n - 2; b++)
		{
			for (int d = b + 1; d < n - 1; d++)
			{
				for (int e = d + 1; e < n; e++)
				{
					test = 0;
					for (int c = (a + 1) % n; c != b; c = (c + 1) % n)
						test += ((c - a + n) % n) * req[c];
					for (int c = (b + 1) % n; c != d; c = (c + 1) % n)
						test += ((c - b + n) % n) * req[c];
					for (int c = (d + 1) % n; c != e; c = (c + 1) % n)
						test += ((c - d + n) % n) * req[c];
					for (int c = (e + 1) % n; c != a; c = (c + 1) % n)
						test += ((c - e + n) % n) * req[c];
					if (test < small)
					{
						small = test;
						ans = a;
						ans2 = b;
						ans3 = d;
						ans4 = e;
					}
				}
			}
		}
	}

	cout << "4: " << ans + 1 << '\t' << ans2 + 1 << '\t' << ans3 + 1 << '\t' << ans4 + 1 << '\t' << small << '\n';

	for (int a = 1;a < n * 2 + 1;a++)
		pre[a] += pre[a - 1];

	for (int a = 0;a < n;a++)
		dp[a][0][0] = 0;

	for (int a = 1;a <= n;a++)
	{
		for (int b = 0;b < n;b++)
		{
			dp[b][a][0] = dp[(b + 1) % n][a - 1][0] + pre[b + a] - pre[b];
		}
	}

	for (int a = 1;a <= k;a++) //doors
	{
		for (int b = 0;b < n;b++)
		{
			dp[b][a][a] = 0;
			dfirstdoor[b][a][a] = 0;
			ld[b][a][a] = 0;
		}
		for (int b = a + 1;b <= n;b++) //len
		{
			for (int c = 0;c < n;c++) //start
			{
				//dp[c][b][a] = 1e17;
				//for (int d = 0;d < b;d++) //first door
				//{
				//	if (dp[c][b][a] > dp[c][d][0] + dp[(c + d + 1) % n][b - 1 - d][a - 1])
				//	{
				//		dp[c][b][a] = dp[c][d][0] + dp[(c + d + 1) % n][b - 1 - d][a - 1];
				//		dfirstdoor[c][b][a] = d;
				//	}
				//}

				if (b == n)
				{
					if (dp[(c + 1) % n][b - 1][a] + pre[dfirstdoor[(c + 1) % n][b - 1][a] + c + 1] - pre[c] + 
						ld[(c + 1) % n][b - 1][a] * (pre[dfirstdoor[(c + 1) % n][b - 1][a] + c + 1] - pre[c]) < 
						dp[(c + 1) % n][b - 1][a - 1])
					{
						//dont use first door
						dp[c][b][a] = dp[(c + 1) % n][b - 1][a] + pre[dfirstdoor[(c + 1) % n][b - 1][a] + c + 1] - pre[c] + 
							ld[(c + 1) % n][b - 1][a] * (pre[dfirstdoor[(c + 1) % n][b - 1][a] + c + 1] - pre[c]);
						dfirstdoor[c][b][a] = dfirstdoor[(c + 1) % n][b - 1][a] + 1;
						ld[c][b][a] = ld[(c + 1) % n][b - 1][a];

						if (a == 1)
							ld[c][b][a] = b - dfirstdoor[c][b][a] - 1;
					}
					else
					{
						//use first door
						dp[c][b][a] = dp[(c + 1) % n][b - 1][a - 1];
						dfirstdoor[c][b][a] = 0;
						ld[c][b][a] = ld[(c + 1) % n][b - 1][a - 1];

						if (a == 1)
							ld[c][b][a] = b - dfirstdoor[c][b][a] - 1;
					}
				}
				else
				{
					if (dp[(c + 1) % n][b - 1][a] + pre[dfirstdoor[(c + 1) % n][b - 1][a] + c + 1] - pre[c] < dp[(c + 1) % n][b - 1][a - 1])
					{
						//dont use first door
						dp[c][b][a] = dp[(c + 1)%n][b - 1][a] + pre[dfirstdoor[(c + 1) % n][b - 1][a] + c + 1] - pre[c];
						dfirstdoor[c][b][a] = dfirstdoor[(c + 1) % n][b - 1][a] + 1;
						ld[c][b][a] = ld[(c + 1) % n][b - 1][a];

						if (a == 1)
							ld[c][b][a] = b - dfirstdoor[c][b][a] - 1;
					}
					else
					{
						//use first door
						dp[c][b][a] = dp[(c + 1) % n][b - 1][a - 1];
						dfirstdoor[c][b][a] = 0;
						ld[c][b][a] = ld[(c + 1) % n][b - 1][a - 1];

						if (a == 1)
							ld[c][b][a] = b - dfirstdoor[c][b][a] - 1;
					}
				}
			}
		}
	}

	ll xans = 1e17;
	for (int a = 0;a < n;a++)
	{
		cout << dp[a][n][k] << '\n';
		xans = min (xans, dp[a][n][k]);
	}
	cout << xans << '\n';

	return 0;
}