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
array<LL, 200000> STD, Z;

void CSTD(LL i, LL p) {
	STD[i] = 0;
	for (auto &j : E[i]) {
		if (j == p) {
			continue;
		}
		CSTD(j, i);
		STD[i] = max(STD[i], 1 + STD[j]);
	}
}

void CZ(LL i, LL p, LL a) {
	Z[i] = max(a, STD[i]);
	LL best[2]{a, LLONG_MIN};
	for (auto &j : E[i]) {
		if (j == p) {
			continue;
		}
		if (1 + STD[j] > best[1]) {
			best[1] = 1 + STD[j];
		}
		if (best[1] > best[0]) {
			swap(best[0], best[1]);
		}
	}
	for (auto &j : E[i]) {
		if (j == p) {
			continue;
		}
		if (1 + STD[j] == best[0]) {
			CZ(j, i, 1 + best[1]);
		} else {
			CZ(j, i, 1 + best[0]);
		}
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
	CSTD(0, -1);
	CZ(0, -1, 0);
	RF(i, 0, N) {
		cout << Z[i] << ' ';
	}

	return 0;
}
