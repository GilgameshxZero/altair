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
vector<long long> near[100001];
long long n, m, arr[100001], cost[100001], save, ans;

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input3.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	cin >> n >> m;
	for (long long a = 0;a < m;a++)
		cin >> arr[a];

	if (m == 1)
	{
		cout << "0\n";
		return 0;
	}

	memset (cost, 0, sizeof (cost));
	ans = save = 0;

	for (long long a = 0;a < m;a++)
		if (a == 0 && arr[0] != arr[1])
		{
			near[arr[0]].push_back (arr[1]);
			cost[arr[0]] += abs (arr[1] - arr[0]);
		}
		else if (a == m - 1 && arr[m - 2] != arr[m - 1])
		{
			near[arr[a]].push_back (arr[m - 2]);
			cost[arr[a]] += abs (arr[a] - arr[m - 2]);
		}
		else if (a != 0 && a != m - 1)
		{
			if (arr[a] != arr[a + 1])
			{
				near[arr[a]].push_back (arr[a + 1]);
				cost[arr[a]] += abs (arr[a] - arr[a + 1]); 
			}
			if (arr[a] != arr[a - 1])
			{
				near[arr[a]].push_back (arr[a - 1]);
				cost[arr[a]] += abs (arr[a] - arr[a - 1]);
			}
		}

	for (long long a = 1, ncost;a <= n;a++)
	{
		sort (near[a].begin (), near[a].end ());
		ncost = 0;
		ans += cost[a];
		for (long long b = 0;b < near[a].size ();b++)
			ncost += abs (near[a][b] - near[a][(near[a].size () - 1) / 2]);
		
		if (cost[a] - ncost > save)
			save = cost[a] - ncost;
	}

	cout << ans / 2 - save << "\n";

	return 0;
}