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

	int p, q, l, r;
	bitset<2001> z;
	vector< pair<int, int> > x;

	cin >> p >> q >> l >> r;
	z.reset ();
	for (int a = 0, b, c;a < p;a++)
	{
		cin >> b >> c;
		for (;b <= c;b++)
			z[b] = true;
	}
	for (int a = 0, b, c;a < q;a++)
		cin >> b >> c,
		x.push_back (make_pair (b, c));

	int ans = 0;
	for (int a = l;a <= r;a++)
	{
		bool f = false;
		for (int b = 0;b < x.size ();b++)
			for (int c = x[b].first;c <= x[b].second;c++)
				if (z[a + c] == true)
					f = true;
		ans += f;
	}

	cout << ans << "\n";

	return 0;
}