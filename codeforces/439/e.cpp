#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;
const int MAXN = 100001,
	MOD = 1e9 + 7;
vector<int> factor[MAXN];
int q, n, f, cnt;
ll fact[MAXN], inv[MAXN], arr[MAXN], last[MAXN];

int ModPow (ll n, int p)
{
	ll ret = 1;

	for (;p;p >>= 1)
	{
		if (p & 1)
			ret = ret * n % MOD;
		n = n * n % MOD;
	}

	return ret;
}

int Solve (int cur)
{
	if (cur < f)
		return 0;
	if (last[cur] == cnt)
		return arr[cur];
	last[cur] = cnt;

	ll ret = (((fact[cur - 1] * inv[f - 1]) % MOD) * inv[cur - f]) % MOD,
		a;

	for (a = 0;a < factor[cur].size ();a++)
	{
		if (factor[cur][a] == 1) continue;
		ret = (ret - Solve (cur / factor[cur][a]) + MOD) % MOD;
	}

	return arr[cur] = ret;
}

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	fact[0] = 1;
	inv[0] = 1;

	for (int a = 1;a < MAXN;a++)
	{
		fact[a] = (fact[a - 1] * a) % MOD;
		inv[a] = inv[a - 1] * ModPow (a, MOD - 2) % MOD;

		for (int b = a;b < MAXN;b += a)
			factor[b].push_back (a);
	}

	scanf ("%d", &q);
	for (cnt = 0;cnt < q;)
	{
		scanf ("%d%d", &n, &f);
		cnt++;
		printf ("%d\n", Solve (n));
	}

	return 0;
}