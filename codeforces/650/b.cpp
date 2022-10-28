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

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	ll n, A, B, t;
	cin >> n >> A >> B >> t;
	string s;
	cin >> s;

	//check full
	ll test = (n - 1) * A;
	for (int a = 0;a < n;a++)
		if (s[a] == 'h')
			test++;
		else
			test += 1 + B;

	if (test <= t)
	{
		cout << n;
		return 0;
	}
	else
	{
		ll min = 0, max = n, mid;
		s += s;
		vector<ll> cost (s.length ());
		if (s[0] == 'h')
			cost[0] = 1;
		else
			cost[0] = 1 + B;
		for (int a = 1;a < cost.size ();a++)
			if (s[a] == 'h')
				cost[a] = 1 + cost[a - 1];
			else
				cost[a] = 1 + B + cost[a - 1];

		while (min + 1 != max)
		{
			mid = (min + max) / 2;

			ll ans = 1e17;
			for (int a = n; n - a < mid;a--)
			{
				ans = ::min (ans, cost[a + mid - 1] - cost[a - 1] + A * (mid - 1) + A * ::min (n - a, a + mid - 1 - n));
			}
			if (ans <= t)
				min = mid;
			else
				max = mid;
		}

		cout << min;
	}

	return 0;
}