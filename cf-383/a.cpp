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

long long n, x[200001], l, r, ans, lc[200001], rc[200001], y, z;

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	cin >> n;
	r = n;
	l = 1;
	rc[0] = x[0] = 0;

	for (int a = 1;a <= n;a++)
	{
		cin >> x[a];
		if (x[a - 1] == 1)
			rc[a] = rc[a - 1] + 1;
		else
			rc[a] = rc[a - 1];
	}

	lc[n] = 0;
	for (int a = n - 1;a >= 1;a--)
		if (x[a + 1] == 0)
			lc[a] = lc[a + 1] + 1;
		else
			lc[a] = lc[a + 1];

	while (l < r)
	{
		if (x[l] == 1)
		{
			ans += (lc[l] - y);
			z++;
			l++;
		}
		else if (x[r] == 0)
		{
			ans += (rc[r] - z);
			r--;
			y++;
		}
		else
		{
			l++;
			r--;
		}
	}

	cout << ans << "\n";

	return 0;
}