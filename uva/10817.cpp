#include <algorithm>
#include <bitset>
#include <cassert>
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
#include <limits>
#include <map>
#include <queue>
#include <utility>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

int Hash (int *list)
{
}

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	while (true)
	{
		int s, m, n;
		cin >> s >> m >> n;

		if (s == 0)
			break;

		int cost = 0, req[8];
		memset (req, 0, sizeof (req));
		for (int a = 0, b;a < m;a++)
		{
			if (a == 0)
				cin >> b;
			cost += b;
			cin >> b;
			while (b < 10000)
			{
				req[b - 1]--;
				cin >> b;
			}
		}

		int app[100][8], price[100];
		memset (app, 0, sizeof (app));
		for (int a = 0, b;a < n;a++)
		{
			if (a == 0)
				cin >> b;
			price[a] = b;
			cin >> b;
			while (b < 10000)
			{
				app[a][b - 1]++;
				cin >> b;
			}
		}

		int dp[6561];
		for (int a = 1;a < 6561;a++)
			dp[a] = 1e9;
		dp[0] = 0;

		for (int a = 0, b;a < m;a++)
		{
			b = a & 1;

		}
	}

	return 0;
}