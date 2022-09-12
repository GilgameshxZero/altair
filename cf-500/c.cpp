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

	int n, m;
	cin >> n >> m;

	vector<int> wei (n);
	for (int a = 0;a < n;a++)
		cin >> wei[a];

	bool marked[500];
	memset (marked, 0, sizeof (marked));
	vector<int> order, lift (m);
	for (int a = 0;a < m;a++)
	{
		cin >> lift[a];
		if (!marked[--lift[a]])
		{
			marked[lift[a]] = true;
			order.push_back (lift[a]);
		}
	}

	int ans = 0;
	reverse (order.begin (), order.end ());
	for (int a = 0, b;a < m;a++)
	{
		int ww = 0;
		for (b = order.size () - 1;order[b] != lift[a];b--)
			ww += wei[order[b]];
		ans += ww;
		ww = order[b];
		order.erase (order.begin () + b);
		order.push_back (ww);
	}

	cout << ans << "\n";

	return 0;
}