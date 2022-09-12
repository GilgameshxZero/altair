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
#include <map>
#include <queue>
#include <utility>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

typedef long long ll;

ll SumMul (ll low, ll high, ll mul, ll mod) //sums all multiples of mul b/t low and high incl
{
	ll divlow = ceil ((double)low / mul), divhigh = high / mul;
	return (divhigh - divlow + 1) * (divhigh + divlow) / 2 % mod * mul % mod;
}

ll CountMul (ll low, ll high, ll mul, ll mod) //counts number of multiples
{
	ll divlow = ceil ((double)low / mul), divhigh = high / mul;
	return (divhigh - divlow + 1) % mod;
}

int main ()
{
	ios_base::sync_with_stdio (false);

	std::freopen ("banner.in", "r", stdin);
	std::freopen ("banner.out", "w", stdout);

	ll M, N, L, H, B;
	cin >> M >> N >> L >> H >> B;

	//get all prime divisors (MlogM by harmonic series)
	vector< vector<ll> > pdiv (max (M, N) + 1);
	for (int a = 2;a <= max (M, N);a++)
		if (pdiv[a].size () == 0)
			for (int b = a;b <= max (M, N);b += a)
				pdiv[b].push_back (a);

	ll ans = 0;
	ll minh, maxh, prod;
	for (ll a = 1, b, f, g;a <= N;a++) //test every width, not including 0
	{
		//find the maximum height and minimum height for this width, incl
		minh = max (1.0, ceil (sqrt (L * L - a * a)));
		maxh = min ((double)M, sqrt (H * H - a * a));

		b = 0; //b is sum of all heights that don't work
		g = 0; //g is number of heights that don't work
		for (int c = 1, d = (1 << pdiv[a].size ()), par = -1;c < d;c++)
		{
			prod = 1;
			for (int e = 0;e < pdiv[a].size ();e++)
			{
				if (c & (1 << e) == 1)
				{
					par *= -1;
					prod *= pdiv[a][e];
				}
			}
			b += par * SumMul (minh, maxh, prod, B);
			g += par * CountMul (minh, maxh, prod, B);
		}

		//get sum of heights that do work
		f = SumMul (minh, maxh, 1, B) - b;
		ans = (ans + 2 * (((1 + M) * (maxh - minh + 1 - g) - f) % B * (N - a + 1))) % B;
		if (ans < 0)
			ans += B;
	}

	if (L <= 1 && H >= 1)
		ans = (ans + N * (M + 1) + M * (N + 1)) % B;

	cout << ans << "\n";

	return 0;
}