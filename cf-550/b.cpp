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

typedef long long ll;

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	int n, l, r, x;
	cin >> n >> l >> r >> x;

	vector<int> diff(n);
	for (int a = 0; a < n; a++)
		cin >> diff[a];

	int ans = 0;
	for (int a = 0; a < (1 << n); a++)
	{
		int mind = 1e9, maxd = 0, cnt = 0, d = 0;
		for (int b = 0; b < n; b++)
		{
			if (a & (1 << b))
			{
				cnt++;
				mind = min(mind, diff[b]);
				maxd = max(maxd, diff[b]);
				d += diff[b];
			}
		}

		if (cnt < 2 || d < l || d > r || maxd - mind < x)
			continue;

		ans++;
	}

	cout << ans;

	return 0;
}