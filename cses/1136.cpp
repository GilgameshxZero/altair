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
array<vector<LL>, 200001> E;
array<LL, 200001> Z;
array<unordered_set<LL>, 200001> S;

void CZ(LL i, LL p) {
	for (auto &j : E[i]) {
		if (j == p) {
			continue;
		}
		CZ(j, i);
		if (S[j].size() > S[i].size()) {
			swap(S[i], S[j]);
		}
	}
	for (auto &j : E[i]) {
		if (j == p) {
			continue;
		}
		S[i].merge(S[j]);
	}
	Z[i] += S[i].size();
	for (auto &j : E[i]) {
		if (j == p) {
			continue;
		}
		for (auto &k : S[j]) {
			S[i].erase(k);
		}
	}
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
		if (a == b) {
			Z[a]++;
			continue;
		}
		S[a].insert(i);
		S[b].insert(i);
	}
	CZ(1, 0);
	RF(i, 1, N + 1) {
		cout << Z[i] << ' ';
	}

	return 0;
}
