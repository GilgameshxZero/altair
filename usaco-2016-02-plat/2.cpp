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

vector<int> vert, horo, vertc, horoc;
int xvert, xhoro;
int A, B, n, m;

int main ()
{
	ios_base::sync_with_stdio (false);

	std::freopen ("fencedin.in", "r", stdin);
	std::freopen ("fencedin.out", "w", stdout);

	cin >> A >> B >> n >> m;

	for (int a = 0, b; a < n; a++)
	{
		cin >> b;
		vert.push_back (b);
	}

	for (int a = 0, b; a < m; a++)
	{
		cin >> b;
		horo.push_back (b);
	}

	sort (vert.begin (), vert.end ());
	sort (horo.begin (), horo.end ());

	if (n != 0)
	{
		vertc.push_back (vert[0]);
		for (int a = 1; a < vert.size (); a++)
			vertc.push_back (vert[a] - vert[a - 1]);
		vertc.push_back (A - vert.back ());
	}
	else
	{
		vertc.push_back (A);
	}

	if (m != 0)
	{
		horoc.push_back (horo[0]);
		for (int a = 1; a < horo.size (); a++)
			horoc.push_back (horo[a] - horo[a - 1]);
		horoc.push_back (B - horo.back ());
	}
	else
		horoc.push_back (B);

	sort (vertc.begin (), vertc.end ());
	sort (horoc.begin (), horoc.end ());
	reverse (vertc.begin (), vertc.end ());
	reverse (horoc.begin (), horoc.end ());

	ll ans = 0;

	while (!vertc.empty () && !horoc.empty ())
	{
		if (vertc.back () <= horoc.back ())
		{
			if (xvert >= 1)
				ans += (ll)vertc.back () * (m - max (0, (xhoro - 1)));
			else
				ans += (ll)vertc.back () * m;
			vertc.pop_back ();
			xvert++;
		}
		else
		{
			if (xhoro >= 1)
				ans += (ll)horoc.back () * (n - max (0, (xvert - 1)));
			else
				ans += (ll)horoc.back () * n;
			horoc.pop_back ();
			xhoro++;
		}
	}

	if (xhoro == 0)
		ans += (ll)horoc.back () * n;
	if (xvert == 0)
		ans += (ll)vertc.back () * m;

	cout << ans << '\n';

	return 0;
}