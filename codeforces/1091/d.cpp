#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC target("avx", "avx2", "fma", "bmi", "bmi2", "popcnt", "lzcnt")
#pragma GCC optimize("Ofast", "unroll-loops")
#endif

#include <bits/stdc++.h>

using LL = long long;
using LD = long double;
using namespace std;

#define RF(x, from, to) \
	for (LL x(from), _to(to), _delta{x < _to ? 1LL : -1LL}; x != _to; x += _delta)

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL const MOD{998244353};
	LL N;
	cin >> N;
	if (N == 1) {
		cout << 1;
		return 0;
	}

	vector<LL> P(N + 1);
	P[0] = 1;
	RF(i, 1, N + 1) {
		P[i] = P[i - 1] * i % MOD;
	}

	LL Z{P[N] * N % MOD - N}, rP{N};
	RF(i, N - 1, 1) {
		rP = rP * i % MOD;
		Z = (Z + MOD - rP) % MOD;
	}
	cout << Z;

	return 0;
}
