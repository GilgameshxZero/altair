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

LL const M{1000000007};
array<LL, 250001> Z;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL N;
	cin >> N;
	Z[0] = 1;
	RF(i, 1, N + 1) {
		RF(j, Z.size() - 1 - i, -1) {
			Z[j + i] += Z[j];
			Z[j + i] %= M;
		}
	}
	cout << (N * (N + 1) % 4 == 0 ? Z[N * (N + 1) / 4] : 0) * 500000004 % M;

	return 0;
}
