#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
using namespace std;

const int MOD = 1e9+7;
int dp[4001][2001];

int main ()
{
	freopen ("in.txt", "r", stdin);
	freopen ("out.txt", "w", stdout);

	int T;
	cin >> T;

	for (int a = 1;a <= T;a++)
	{
		int sc1, sc2;
		cin >> sc1;
		cin.get ();
		cin >> sc2;
		
		cout << "Case #" << a << ": ";

		memset (dp, 0, sizeof (dp));
		dp[2][2] = 1;
		for (int b = 2;b < sc1 + sc2;b++)
		{
			for (int c = 1;c <= sc1;c++)
			{
				if ((b - c) / 2 < sc2 && c > 1)
					dp[b + 1][c - 1] = (dp[b + 1][c - 1] + dp[b][c]) % MOD;
				if ((b + c) / 2 < sc1)
					dp[b + 1][c + 1] = (dp[b + 1][c + 1] + dp[b][c]) % MOD;
			}
		}

		cout << dp[sc1 + sc2][sc1 - sc2] << " ";

		memset (dp, 0, sizeof (dp));
		int ans = 0;
		dp[1][1] = 1;
		for (int b = 1;b < sc1 + sc2;b++)
		{
			for (int c = 0;c <= sc2;c++)
			{
				if ((b + c) / 2 == sc2)
					ans = (ans + dp[b][c]) % MOD;
				else
				{
					if ((b + c) / 2 < sc2)
						dp[b + 1][c + 1] = (dp[b + 1][c + 1] + dp[b][c]) % MOD;
					if ((b - c) / 2 < sc1 && c >= 1)
						dp[b + 1][c - 1] = (dp[b + 1][c - 1] + dp[b][c]) % MOD;
				}
			}
		}

		cout << ans << "\n";
	}

	return 0;
}