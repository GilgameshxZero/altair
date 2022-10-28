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

	map< int, vector<int> > loc;
	vector< pair<int, int> > last, nlast;
	int n, m;

	cin >> n >> m;
	for (int a = 0, b, c;a < m;a++)
	{
		cin >> b >> c;
		loc[b].push_back (c);
		loc.insert (make_pair (b + 1, vector<int>()));
	}

	last.push_back (make_pair (1, 1));
	loc.insert (make_pair (1, vector<int>()));

	for (map< int, vector<int> >::iterator a = loc.begin ();a != loc.end () && a->first <= n;a++)
	{
		int cur = 1, i = 0;
		nlast.clear ();

		sort (a->second.begin (), a->second.end ());
		for (int b = 0; b < last.size () && i <= a->second.size ();b++)
		{
			if (last[b].second >= cur)
			{
				cur = max (cur, last[b].first);
				if (i < a->second.size ())
				{
					if (cur < a->second[i])
						nlast.push_back (make_pair (cur, a->second[i] - 1));
					cur = a->second[i] + 1;
					b--;
				}
				else if (cur <= n)
				{
					nlast.push_back (make_pair (cur, n));
					b--;
				}
				i++;
			}
		}

		last = nlast;
	}

	if (last.size () == 0 || (last.end () - 1)->second != n)
		cout << "-1\n";
	else if ((last.end () - 1)->second == n)
		cout << 2 * n - 2 << "\n";

	return 0;
}