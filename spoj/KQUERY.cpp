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

int n, q, fen[30001], ans[200000]; //fen[i + 1]: # of elems in k range of (kbin[i - 1], kbin[i]]
pair<int, int> x[30000];
pair< pair<int, int> , pair<int, int> > y[200000]; //queries: k, query #, bounds (2)

int Sum (int k)
{
	int r = 0;
	for (;k > 0;k -= k & -k)
		r += fen[k];
	return r;
}

void Add (int k, int i)
{
	for (;k <= 30001;k += k & -k)
		fen[k] += i;
}

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	cin >> n;
	for (int a = 0;a < n;a++)
		cin >> x[a].first,
		x[a].second = a;

	//after sort: sweepline range/seg fenwick: number of nums
	cin >> q;
	for (int a = 0;a < q;a++)
		cin >> y[a].second.first >> y[a].second.second >> y[a].first.first,
		y[a].first.second = a;
	
	sort (y, y + q, greater< pair< pair<int, int> , pair<int, int> > >());
	sort (x, x + n, greater< pair<int, int> >());
	memset (ans, 0, sizeof (ans));
	memset (fen, 0, sizeof (fen));

	for (int a = 0, b = 0;b < q;)
	{
		if (a == n || x[a].first <= y[b].first.first)
		{
			ans[y[b].first.second] = Sum (y[b].second.second) - Sum (y[b].second.first - 1);
			b++;
		}
		else
		{
			Add (x[a].second + 1, 1);
			a++;
		}
	}

	for (int a = 0;a < q;a++)
		cout << ans[a] << "\n";

	return 0;
}