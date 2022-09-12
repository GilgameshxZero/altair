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

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	vector< pair<int, int> > type[2], orig[2];
	int n, x, ans[2], h, a, b;
	cin >> n >> x;
	for (int a = 0, b, c, d;a < n;a++)
	{
		cin >> b >> c >> d;
		type[b].push_back (make_pair (c, d));
	}

	sort (type[0].begin (), type[0].end ());
	sort (type[1].begin (), type[1].end ());
	orig[0] = type[0];
	orig[1] = type[1];

	h = x;
	for (ans[0] = 0;;)
	{
		int cross = ans[0] % 2, most = -1;

		for (int a = 0;a < type[cross].size ();a++)
			if (type[cross][a].first <= h && (most == -1 || type[cross][a].second > type[cross][most].second))
				most = a;

		if (most == -1)
			break;
		else
		{
			h += type[cross][most].second;
			ans[0]++;
			type[cross].erase (type[cross].begin () + most);
		}
	}

	h = x;
	type[0] = orig[0];
	type[1] = orig[1];
	for (ans[1] = 0;;)
	{
		int cross = (ans[1] + 1) % 2, most = -1;

		for (int a = 0;a < type[cross].size ();a++)
			if (type[cross][a].first <= h && (most == -1 || type[cross][a].second > type[cross][most].second))
				most = a;

		if (most == -1)
			break;
		else
		{
			h += type[cross][most].second;
			ans[1]++;
			type[cross].erase (type[cross].begin () + most);
		}
	}

	cout << max (ans[0], ans[1]) << "\n";

	return 0;
}