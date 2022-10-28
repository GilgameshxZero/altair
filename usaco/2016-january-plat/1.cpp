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

//dp

using namespace std;

typedef long long ll;

int main ()
{
	ios_base::sync_with_stdio (false);

	std::freopen ("fortmoo.in", "r", stdin);
	std::freopen ("fortmoo.out", "w", stdout);

	string grid[200];
	int n, m;
	cin >> n >> m;

	for (int a = 0; a < n; a++)
		cin >> grid[a];

	int pref[200][201];
	memset (pref, 0, sizeof (pref));

	for (int a = 0; a < n; a++)
	{
		for (int b = 1; b <= m; b++)
		{
			pref[a][b] = pref[a][b - 1];
			if (grid[a][b - 1] == 'X')
				pref[a][b]++;
		}
	}

	int ans = 0;
	for (int a = 0; a < m; a++)
	{
		for (int b = a; b < m; b++)
		{
			int prev = 0;
			for (int c = n - 1; c >= 0; c--)
			{
				if (grid[c][a] == '.' && grid[c][b] == '.')
					prev++;
				else
				{
					int e, f;
					e = f = -1;
					for (int d = c + 1; d <= c + prev; d++)
					{
						if (pref[d][a + 1] == pref[d][b + 1])
						{
							e = d;
							break;
						}
					}
					for (int d = c + prev; d >= c + 1; d--)
					{
						if (pref[d][a + 1] == pref[d][b + 1])
						{
							f = d;
							break;
						}
					}

					if (e != -1 && f - e >= 0)
						ans = max (ans, (b - a + 1) * (f - e + 1));

					prev = 0;
				}
			}

			if (prev != 0)
			{
				int e, f;
				e = f = -1;
				for (int d = 0; d <= prev - 1; d++)
				{
					if (pref[d][a + 1] == pref[d][b + 1])
					{
						e = d;
						break;
					}
				}
				for (int d = prev - 1; d >= 0; d--)
				{
					if (pref[d][a + 1] == pref[d][b + 1])
					{
						f = d;
						break;
					}
				}

				if (e != -1 && f - e >= 0)
					ans = max (ans, (b - a + 1) * (f - e + 1));
			}
		}
	}

	cout << ans << '\n';

	return 0;
}