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

LL N, Q;
array<vector<LL>, 200001> E, H;
array<LL, 200001> Z;
unordered_set<LL> A;

void CZ(LL i, LL p) {
	for (auto &j : H[i]) {
		auto k{A.find(j)};
		if (k == A.end()) {
			A.insert(j);
		} else {
			A.erase(k);
		}
	}
	for (auto &j : E[i]) {
		if (j == p) {
			continue;
		}
		CZ(j, i);
	}
	Z[i] = A.size();
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> N >> Q;
	RF(i, 0, N - 1) {
		LL a, b;
		cin >> a >> b;
		E[a].push_back(b);
		E[b].push_back(a);
	}
	RF(i, 0, Q) {
		LL a, b;
		cin >> a >> b;
		H[a].push_back(i);
		H[b].push_back(i);
	}
	CZ(1, 0);

	return 0;
}
