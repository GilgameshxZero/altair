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

	std::freopen ("landscape.in", "r", stdin);
	std::freopen ("landscape.out", "w", stdout);

	ll n, x, y, z;
	cin >> n >> x >> y >> z;

	vector<ll> diff (n);
	ll ans = 0;
	for (int a = 0, b, c;a < n;a++)
	{
		cin >> b >> c;
		diff[a] = b - c;

		if (diff[a] < 0)
			ans += -diff[a] * x;
		else
			ans += diff[a] * y;
	}

	/*queue< pair<int, int> > left;
	for (int a = 0;a < n;a++)
	{
		if (left.empty () || (double)diff[a] / left.front ().second > 0)
			left.push (make_pair (a, diff[a]));
		else
		{
			while (!left.empty () && x + y < (ll)(a - left.front ().first) * z)
				left.pop ();

			while (diff[a] != 0 && !left.empty ())
			{
				int num = min (abs(diff[a]), (ll)abs(left.front ().second));
				if (diff[a] < 0)
					num = -num;
				ans += (ll)(abs (num)) * ((ll)(a - left.front ().first) * z - x - y);

				left.front ().second += num;
				diff[a] -= num;
			
				if (left.front ().second == 0)
					left.pop ();
			}

			if (diff[a] != 0)
			{
				left.push (make_pair (a, diff[a]));
				continue;
			}
		}
	}

	cout << ans << '\n';*/

	/*for (int a = 1;a < n;a++)
	{
		for (int b = 0;b + a < n;b++)
		{
			if ((double)diff[b] / diff[b + a] < 0)
			{
				int num = min (abs (diff[b]), (ll)abs (diff[b + a]));
				if (diff[b] < 0)
					num = -num;
				diff[b] -= num;
				diff[b + a] += num;
				ans += (ll)(abs (num)) * ((ll)(a) * z - x - y);
			}
		}
	}*/

	//Split into single dir sections, take longest transfers first.

	//cout << ans << '\n';

	return 0;
}