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

LL N;
array<vector<LL>, 200000> E;
array<LL, 200000> SZ, SD, Z;

void CSD(LL i, LL p) {
	SZ[i] = 1;
	SD[i] = 0;
	for (auto &j : E[i]) {
		if (j == p) {
			continue;
		}
		CSD(j, i);
		SZ[i] += SZ[j];
		SD[i] += SZ[j] + SD[j];
	}
}

void CZ(LL i, LL p, LL a) {
	Z[i] = SD[i] + a;
	LL TSCD{0};
	for (auto &j : E[i]) {
		if (j == p) {
			continue;
		}
		TSCD += SZ[j] + SD[j];
	}
	for (auto &j : E[i]) {
		if (j == p) {
			continue;
		}
		CZ(j, i, a + TSCD - (SZ[j] + SD[j]) + (N - SZ[j]));
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> N;
	RF(i, 1, N) {
		LL a, b;
		cin >> a >> b;
		E[a - 1].push_back(b - 1);
		E[b - 1].push_back(a - 1);
	}
	CSD(0, -1);
	CZ(0, -1, 0);
	RF(i, 0, N) {
		cout << Z[i] << ' ';
	}

	return 0;
}
