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

array<vector<LL>, 200000> E;
array<LL, 200000> Z;

LL CZ(LL i) {
	Z[i] = 1;
	for (auto &j : E[i]) {
		Z[i] += CZ(j);
	}
	return Z[i];
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL N;
	cin >> N;
	RF(i, 1, N) {
		LL x;
		cin >> x;
		E[x - 1].push_back(i);
	}
	CZ(0);
	RF(i, 0, N) {
		cout << Z[i] - 1 << ' ';
	}

	return 0;
}
