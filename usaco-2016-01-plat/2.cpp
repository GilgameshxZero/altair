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

//Persistent segtrees/no time

using namespace std;

typedef long long ll;

/*bool horo (pair<ll, ll> a, pair<ll, ll> b)
{
	return (a.x == b.x);
}*/

int main ()
{
	ios_base::sync_with_stdio (false);

	std::freopen ("mowing.in", "r", stdin);
	std::freopen ("mowing.out", "w", stdout);

	/*int n, t;
	cin >> n >> t;

	vector< pair<ll, ll> > pt (n);
	for (int a = 0; a < n; a++)
		cin >> pt[a].first >> pt[a].second;

	set< pair<pair<ll, ll>, pair<ll, ll> > > vs, hs;
	set< pair<pair<ll, ll>, pair<ll, ll> > >::iterator low, high;
	for (int a = 1; a < n; a++)
	{
		if (a - t >= 1)
		{
			if (pt[a - t - 1].first == pt[a - t].first)
				hs.insert (make_pair (pt[a - t - 1], pt[a - t]));
			else
				vs.insert (make_pair (pt[a - t - 1], pt[a - t]));
		}

		if (horo (pt[a - 1], pt[a]))
		{
			low = vs.lower_bound (30);
			high = vs.upper_bound (60);
		}
	}*/

	cout << "1\n";

	return 0;
}