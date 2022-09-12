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
#include <string>
#include <vector>

using namespace std;

typedef long long ll;

int main ()
{
	ios_base::sync_with_stdio (false);

	std::freopen ("nearcows.in", "r", stdin);
	std::freopen ("nearcows.out", "w", stdout);

	int n, k;
	cin >> n >> k;

	vector< vector<int> > edge (n);
	for (int a = 0, b, c;a < n - 1;a++)
	{
		cin >> b >> c;
		edge[b - 1].push_back (c - 1);
		edge[c - 1].push_back (b - 1);
	}

	vector< vector<ll> > dp (n, vector<ll> (k + 1, 0));
	for (int a = 0;a < n;a++)
		cin >> dp[a][0],
		dp[a][1] = dp[a][0];

	cout << clock () << "\n";
	
	for (int a = 0;a < n;a++)
		for (int b = 0;b < edge[a].size ();b++)
			dp[a][1] += dp[edge[a][b]][0];

	for (int a = 2;a <= k;a++)
	{
		for (int b = 0;b < n;b++)
		{
			for (int c = 0;c < edge[b].size ();c++)
				dp[b][a] += dp[edge[b][c]][a - 1] - dp[b][a - 2];
			dp[b][a] += dp[b][a - 2];
		}
	}

	cout << clock () << "\n\n\n";

	for (int a = 0;a < n;a++)
		cout << dp[a][k] << "\n";

	return 0;
}