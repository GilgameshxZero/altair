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
#include <assert.h>

using namespace std;

const int INF = 2000000000;
long long n, x[200000], dist, last, gap, ans, ser;

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	cin >> n;
	for (int a = 0;a < n;a++)
		cin >> x[a];

	ans = 1;
	last = -1;
	ser = 0;
	dist = INF;
	gap = 0;
	for (int a = 0;a < n;a++)
	{
		if (x[a] == -1)
		{
			if (dist == INF)
				gap++;
			else
			{
				if (x[a - 1] + dist <= 0)
				{
					ans++;
					dist = INF;
					gap = 0;
					last = -1;
					ser = a;
				}
				else
				{
					last = x[a] = x[a - 1] + dist;
					ser = a + 1;
					assert (gap == 0);
				}
			}
		}
		else
		{
			if (dist == INF)
			{
				if (last == -1)
				{
					last = x[a];
					gap = 0;
				}
				else
				{
					if ((x[a] - last) % (gap + 1) != 0)
					{
						ans++;
						gap = 0;
						last = x[a];
						dist = INF;
						ser = a + 1;
					}
					else
					{
						dist = (x[a] - last) / (gap + 1);

						for (int b = a - 1;b >= ser;b--)
						{
							x[b] = (a - b) * -dist + x[a];

							if (x[b] <= 0)
							{
								ans++;
								dist = INF;
								break;
							}
						}

						gap = 0;
						last = x[a];
						ser = a + 1;
					}
				}
			}
			else
			{
				if (x[a] - x[a - 1] != dist)
				{
					ans++;
					dist = INF;
				}
				
				assert (last == x[a - 1]);
				assert (gap == 0);
				ser = a + 1;
				last = x[a];
			}
		}
	}

	cout << ans << "\n";

	return 0;
}