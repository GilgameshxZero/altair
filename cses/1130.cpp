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
array<array<LL, 2>, 200000> Z;

void CZ(LL i, LL p, LL d) {
	if (E[i].size() == 1 || p == -1 && E[i].size() == 0) {
		Z[i][0] = Z[i][1] = 0;
	}
	LL mn{LLONG_MAX};
	for (auto &j : E[i]) {
		if (j == p) {
			continue;
		}
		CZ(j, i, 1 - d);
		Z[i][0] += max(Z[j][0], Z[j][1]);
		Z[i][1] += max(Z[j][0], Z[j][1]);
		mn = min(mn, max(Z[j][0], Z[j][1]) - Z[j][0]);
	}
	Z[i][1] += 1 - mn;
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
	cout << max(Z[0][0], Z[0][1]);

	return 0;
}
