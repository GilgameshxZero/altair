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

const int MAXDP = 1048576, MAXN = 20, MAXSHOW = 1000;
int dur[MAXN];
pair<int, int> dp[MAXDP];
int show[MAXN][MAXSHOW], cshow[MAXN];
int r[MAXN][MAXN][MAXSHOW];

int main ()
{
	ios_base::sync_with_stdio (false);

	std::freopen ("movie.in", "r", stdin);
	std::freopen ("movie.out", "w", stdout);

	int N, L;
	cin >> N >> L;

	for (int a = 0;a < N;a++)
	{
		cin >> dur[a];
		cin >> cshow[a];
		for (int c = 0;c < cshow[a];c++)
			cin >> show[a][c];
	}

	for (int a = 0;a < N;a++)
		for (int b = 0;b < N;b++)
			for (int c = 0;c < cshow[b];c++)
				r[a][b][c] = upper_bound (show[a], show[a] + cshow[a], show[b][c] + dur[b]) - show[a];

	int ans = 50;
	fill (dp, dp + MAXDP, make_pair (-1, -1));
	for (int a = 1;a < (1 << N);a++)
	{
		//try each show as end
		int cnt = 0;
		for (int b = 0, c = a;b < N;b++, c >>= 1)
			if ((c & 1) == 1)
				cnt++;
		if (cnt >= ans)
			continue;

		for (int b = 0, c = a, cur, d;b < N;b++, c >>= 1)
		{
			if ((c & 1) == 1)
			{
				cur = a ^ (1 << b);
				if (dp[cur] != make_pair (-1, -1))
				{
					d = r[b][dp[cur].first][dp[cur].second];
					if (dp[a] == make_pair (-1, -1) || (show[dp[a].first][dp[a].second] + dur[dp[a].first] < show[dp[cur].first][dp[cur].second] + dur[dp[cur].first]))
						dp[a] = dp[cur];
					if (d != 0)
					{
						if (show[dp[a].first][dp[a].second] + dur[dp[a].first] < show[b][d - 1] + dur[b])
							dp[a] = make_pair (b, d - 1);
					}
				}
				else
				{
					if (show[b][0] == 0)
						if (dp[a] == make_pair (-1, -1) || dur[b] > show[dp[a].first][dp[a].second] + dur[dp[a].first])
							dp[a] = make_pair (b, 0);
				}
			}
		}
		if (show[dp[a].first][dp[a].second] + dur[dp[a].first] >= L)
			ans = cnt;
	}

	if (ans == 50)
		cout << "-1\n";
	else
		cout << ans << "\n";

	return 0;
}