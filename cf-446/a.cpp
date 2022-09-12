#include <algorithm>
#include <bitset>
#include <limits>
#include <climits>
#include <cmath>
#include <cassert>
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

	int l[100000], r[100000];
	int n, x[100010];

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	memset (x, -1, sizeof (x));
	cin >> n;
	for (int a = 0;a < n;a++)
		cin >> x[a];
	l[0] = 1;
	for (int a = 1;a < n;a++)
		l[a] = x[a] > x[a - 1] ? l[a - 1] + 1 : 1;
	r[n - 1] = 1;
	for (int a = n - 2;a >= 0;a--)
		r[a] = x[a] < x[a + 1] ? r[a + 1] + 1 : 1;

	int ans = 1;
	for (int a = 1;a < n - 1;a++)
		if (x[a + 1] - 1 > x[a - 1])
			ans = max (ans, l[a - 1] + 1 + r[a + 1]);
	for (int a = 0;a < n - 1;a++)
		ans = max (ans, r[a + 1] + 1);
	for (int a = 1;a < n;a++)
		ans = max (ans, l[a - 1] + 1);

	cout << ans << "\n";

	return 0;
}