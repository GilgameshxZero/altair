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

struct CtPt
{
	ll r, c, cnt;
};

const ll MOD = 1e9 + 7;
ll fact[200001];

ll PowerMod (int x, int y, int mod)
{
	if (y == 0)
		return 1;
	else if (y & 1)
	{
		ll k = PowerMod (x, y >> 1, mod);
		return x * (k * k % mod) % mod;
	}
	else
	{
		ll k = PowerMod (x, y >> 1, mod);
		return k * k % mod;
	}
}

ll Pascal (int row, int col, int mod)
{
	if (row < 0 || col < 0 || col > row)
		return 0;

	ll num = fact[row], den = (fact[col] * fact[row - col]) % MOD;

	den = PowerMod (den, mod - 2, mod);
	return (num * den) % mod;
}

bool comp (CtPt x, CtPt y)
{
	if (x.c < y.c)
		return true;
	else if (x.c > y.c)
		return false;
	else
	{
		if (x.r < y.r)
			return true;
		return false;
	}
}

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	fact[0] = 1;
	for (int a = 1; a <= 200000; a++)
		fact[a] = (fact[a - 1] * a) % MOD;

	int R, C, X;
	cin >> R >> C >> X;

	vector<CtPt> crit (X);
	for (int a = 0; a < X; a++)
		cin >> crit[a].r >> crit[a].c,
		crit[a].r--,
		crit[a].c--;

	sort (crit.begin (), crit.end (), comp);
	crit.push_back (CtPt ());
	crit[X].r = R - 1;
	crit[X].c = C - 1;

	for (int a = 0; a < crit.size (); a++)
		crit[a].cnt = Pascal (crit[a].r + crit[a].c, crit[a].c, MOD);

	for (int a = 0; a < crit.size () - 1; a++)
	{
		for (int b = a + 1; b < crit.size (); b++)
		{
			crit[b].cnt = (crit[b].cnt + MOD - crit[a].cnt * Pascal (crit[b].r + crit[b].c - crit[a].r - crit[a].c, crit[b].c - crit[a].c, MOD) % MOD) % MOD;
		}
	}

	cout << crit[X].cnt;

	return 0;
}