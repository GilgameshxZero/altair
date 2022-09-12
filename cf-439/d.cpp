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
#include <stack>
#include <string>
#include <vector>

using namespace std;

long long n, m, x[100000], y[100000], low, high, moves, ans, intop, inbot;
vector< pair<long long, int> > range; //max 200000

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	cin >> n >> m;
	for (int a = 0;a < n;a++)
		cin >> x[a];
	for (int a = 0;a < m;a++)
		cin >> y[a];

	sort (x, x + n);
	sort (y, y + m);

	//Find range. TODO: BSearch.
	for (low = m - 1;low >= 0;low--)
		if (y[low] <= x[0])
			break;
		else
			range.push_back (make_pair (y[low], 1));

	for (high = 0;high < n;high++)
		if (x[high] >= y[m - 1])
			break;
		else
			range.push_back (make_pair (x[high], 0));

	//range.push_back (make_pair (x[0], 0));
	//range.push_back (make_pair (y[m - 1], 1));
	sort (range.begin (), range.end ());

	intop = 1; //Lowest will always be x[0] unless degenerate.
	inbot = m - low - 1;

	//Find starting params.
	moves = 0;
	for (int a = 1;a < range.size ();a++)
		if (range[a].second == 1)
			moves += range[a].first - range[0].first;

	//Sweep line.
	ans = moves;
	for (int a = 1;a < range.size ();a++) //Handles degenerate.
	{
		//Update what we left behind.
		moves -= inbot * (range[a].first - range[a - 1].first);
		moves += intop * (range[a].first - range[a - 1].first);

		if (range[a - 1].second == 1)
		{
			inbot--;
			moves += range[a].first - range[a - 1].first;
		}
		if (range[a].second == 0)
			intop++;

		//Check moves.
		ans = min (moves, ans);
	}

	cout << ans << "\n";

	return 0;
}