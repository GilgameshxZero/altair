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

double dp[2][512][2][602], ans, prob;
ll x, k, p,
	suff, last, cnt;

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	cin >> x >> k >> p;

	memset (dp, 0, sizeof (dp));
	suff = x & ((1 << 9) - 1);
	last = ((x & (1 << 9)) != 0);
	prob = (double)p / 100;
	ans = 0;

	if ((x >> 9) == 0)
		cnt = 300;
	else
	{
		cnt = 0;
		for (ll a = 9;((ll)1 & (x >> a)) == last;a++)
			cnt++;
	}
	dp[0][suff][last][cnt] = 1;

	for (ll a = 0;a < k;a++)
	{
		ll step = a & 1, next = step ^ 1, nmask, nlast, ncnt;
		double cur;
		for (ll b = 0;b < (1 << 9);b++)
			for (ll c = 0;c < 2;c++)
				for (ll d = 0;d < 602;d++)
					dp[next][b][c][d] = 0;

		for (ll b = 0;b < (1 << 9);b++)
			for (ll c = 0;c < 2;c++)
				for (ll d = 0;d < 402;d++)
				{
					cur = dp[step][b][c][d];

					nmask = (b << 1) & (ll)((1 << 9) - 1);
					nlast = (b & (ll)(1 << 8)) != 0;
					
					if (c == nlast)
						ncnt = d + 1;
					else
						ncnt = 1;
					
					dp[next][nmask][nlast][ncnt] += cur * prob;
					
					nmask = b + 1;

					if (nmask == (1 << 9))
					{
						if (c == 0)
							dp[next][0][1][1] += cur * (1 - prob);
						else
							dp[next][0][0][d] += cur * (1 - prob);
					}
					else
						dp[next][nmask][c][d] += cur * (1 - prob);
				}
	}
	
	for (ll a = 0;a < (1 << 9);a++)
		for (ll b = 0;b < 2;b++)
			for (ll c = 0;c < 402;c++)
			{
				if (a == 0)
				{
					if (b == 0)
						ans += dp[k & 1][a][b][c] * (9 + c);
					else
						ans += dp[k & 1][a][b][c] * 9;
				}
				else
				{
					ll cnt = 0;

					for (ll d = 0;((ll)1 & (a >> d)) == 0;d++)
						cnt++;

					ans += dp[k & 1][a][b][c] * (double)cnt;
				}
			}

	cout << fixed << setprecision (13) << ans << "\n";

	return 0;
}