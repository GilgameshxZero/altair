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

	ll c, h[2], w[2];
	cin >> c >> h[0] >> h[1] >> w[0] >> w[1];

	if (max (w[0], w[1]) > 1e4)
	{
		ll x = (w[1] > w[0]), ans = 0;
		for (ll a = 0;a <= (c / w[x]);a++)
			ans = max (ans, a * h[x] + h[!x] * ((c - w[x] * a) / w[!x]));
		cout << ans;
	}
	else
	{
		ll x = ((double)h[1] / w[1] > (double)h[0] / w[0]);
		ll ans = (c / w[x]) * h[x], left = c % w[x];
		ans += (left / w[!x]) * h[!x];
		left %= w[!x];

		ll cur = ans;
		for (ll a = 1;a <= w[!x];a++)
		{
			cur = cur - h[x];
			left += w[x];
			cur += (left / w[!x]) * h[!x];
			left %= w[!x];
			ans = max (ans, cur);
		}

		cout << ans;
	}

	return 0;
}