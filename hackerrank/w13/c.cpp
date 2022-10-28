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

int min_pow[101][1001], power[100][1000], dp[101][1001];

int main ()
{
	ios_base::sync_with_stdio (false);

	freopen ("input0.txt", "r", stdin); freopen ("output.txt", "w", stdout);

	int T, N, M, ans;
	cin >> T;

	for (;T > 0;T--)
	{
		cin >> N >> M;
		memset (min_pow, 63, sizeof (min_pow));
		for (int a = 0;a < N;a++)
			for (int b = 0;b < M;b++)
				cin >> power[a][b];
		for (int a = 1;a <= N;a++)
			for (int b = 0, c;b < M;b++)
				cin >> c,
				min_pow[a][c] = min (min_pow[a][c], power[a - 1][b]);
		for (int a = 0;a <= 1000;a++)
			dp[0][a] = a;
		for (int a = 1;a <= N;a++)
		{
			dp[a][0] = 1e9;
			for (int b = 1;b <= 1000;b++)
				if (min_pow[a][b] < 1e9)
					dp[a][b] = min (dp[a - 1][min_pow[a][b]], dp[a][b - 1] + 1);
				else
					dp[a][b] = dp[a][b - 1] + 1;
			for (int b = 999;b >= 1;b--)
				dp[a][b] = min (dp[a][b], dp[a][b + 1]);
		}
		ans = 1e9;
		for (int a = 1;a <= 1000;a++)
			ans = min (ans, dp[N][a]);
		cout << ans << "\n";
	}

	return 0;
}