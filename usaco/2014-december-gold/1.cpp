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
#include <string>
#include <vector>

using namespace std;

typedef long long ll;

int main ()
{
	ios_base::sync_with_stdio (false);

	std::freopen ("guard.in", "r", stdin);
	std::freopen ("guard.out", "w", stdout);

	int n, h;
	cin >> n >> h;

	vector< pair< int, pair<int, int> > > cow (n);
	for (int a = 0;a < n;a++)
		cin >> cow[a].first >> cow[a].second.first >> cow[a].second.second;

	//bitmask brute-force
	ll lim = 1 << n, thei, twei, cwei, ans = -1, minpq;
	for (int a = 1;a < lim;a++)
	{
		//get total height, weight, and str. pq running
		thei = twei = 0;
		priority_queue< pair<ll, int>, vector< pair<ll, int> >, less< pair<ll, int> > > pq;
		for (int b = 0, c = a;b < n;b++)
		{
			if ((c & 1))
			{
				thei += cow[b].first;
				twei += cow[b].second.first;
			}
			c >>= 1;
		}

		if (thei < h)
			continue;
		
		for (int b = 0, c = a;b < n;b++)
		{
			if ((c & 1))
				pq.push (make_pair (cow[b].second.second - twei + cow[b].second.first, b));
			c >>= 1;
		}

		//take top of pq each time and maintain minimum pq val.
		cwei = 0;
		minpq = 1e12;
		while (!pq.empty ())
		{
			if (cwei + pq.top ().first < 0)
				break; //not possible
			minpq = min (minpq, pq.top ().first + cwei);
			cwei += cow[pq.top ().second].second.first;
			pq.pop ();
		}

		if (pq.empty ())
			ans = max (ans, minpq);
	}

	if (ans == -1)
		cout << "Mark is too tall\n";
	else
		cout << ans << "\n";

	return 0;
}