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
ll n, m;
ll k;

//<=
ll Eval (ll num)
{
	//calc each row
	ll r = 0;
	for (ll a = 1;a <= n;a++)
	{
		ll b = num / a;
		if (b >= m)
			r += m;
		else
			r += b;
	}

	return r;
}

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	//bsearch on ans - 1.
	cin >> n >> m >> k;

	ll bot = 0, top = n * m + 1, mid, eval;
	while (bot + 1 < top)
	{
		mid = (bot + top) / 2;
		eval = Eval (mid);

		if (eval >= k)
			top = mid;
		else if (eval < k)
			bot = mid;
	}

	cout << bot + 1 << "\n";

	return 0;
}