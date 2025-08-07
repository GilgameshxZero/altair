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
array<LL, 200000> D;

void CZ(LL i, LL p, LL d) {
	D[i] = d;
	for (auto &j : E[i]) {
		if (j == p) {
			continue;
		}
		CZ(j, i, d + 1);
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL N;
	cin >> N;
	RF(i, 1, N) {
		LL a, b;
		cin >> a >> b;
		E[a - 1].push_back(b - 1);
		E[b - 1].push_back(a - 1);
	}
	CZ(0, -1, 0);
	LL s{0};
	RF(i, 0, N) {
		if (D[i] > D[s]) {
			s = i;
		}
	}
	CZ(s, -1, 0);
	LL Z{0};
	RF(i, 0, N) {
		Z = max(Z, D[i]);
	}
	cout << Z;

	return 0;
}
