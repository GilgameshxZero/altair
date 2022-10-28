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

	int n, m;
	cin >> n >> m;

	vector< pair<ll, ll> > x (n);
	for (int a = 0;a < n;a++)
		cin >> x[a].first,
		x[a].second = a;

	vector< pair<ll, ll> > com;
	for (int a = 0;a < m;a++)
	{
		ll t, r;
		cin >> t >> r;
		r--;

		while (!com.empty ())
		{
			if (r >= com.back ().second)
				com.pop_back ();
			else
				break;
		}

		if (com.empty () || com.back ().first != t)
			com.push_back (make_pair (t, r));
	}

	vector<ll> reva;
	bitset<200000> use;
	use.reset ();
	for (int a = n - 1;a > com[0].second;a--)
		reva.push_back (x[a].first),
		use[x[a].second] = true;

	sort (x.begin (), x.end ());

	ll pt1 = 0, pt2 = n - 1;
	com.push_back (make_pair (1, -1));
	for (int a = 0;a < com.size () - 1;a++)
	{
		for (int b = com[a].second;b > com[a + 1].second;b--)
		{
			if (com[a].first == 1)
			{
				for (;pt2 >= 0;pt2--)
				{
					if (use[x[pt2].second] == false)
					{
						use[x[pt2].second] = true;
						reva.push_back (x[pt2].first);
						break;
					}
				}
			}
			else
			{
				for (;pt1 < n;pt1++)
				{
					if (use[x[pt1].second] == false)
					{
						use[x[pt1].second] = true;
						reva.push_back (x[pt1].first);
						break;
					}
				}
			}
		}
	}

	for (int a = 0;a < n;a++)
		cout << reva[n - 1 - a] << ' ';

	return 0;
}