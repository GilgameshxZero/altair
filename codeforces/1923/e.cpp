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

void dfsQualified(
	LL vx,
	LL pr,
	LL &Z,
	vector<LL> &C,
	vector<vector<LL>> &E,
	vector<unordered_map<LL, LL>> &Q) {
	if (E[vx].size() == 1 && pr != -1) {
		Q[vx][C[vx]] = 1;
		return;
	}

	LL lg{-1};
	for (auto &ux : E[vx]) {
		if (ux == pr) {
			continue;
		}
		dfsQualified(ux, vx, Z, C, E, Q);
		if (lg == -1 || Q[ux].size() > Q[lg].size()) {
			lg = ux;
		}
		Z += Q[ux][C[vx]];
	}

	LL z2{0};
	for (auto &ux : E[vx]) {
		if (ux == pr || ux == lg) {
			continue;
		}
		for (auto &p : Q[ux]) {
			if (p.first == C[vx]) {
				continue;
			}
			z2 += p.second * Q[lg][p.first];
		}
	}
	swap(Q[vx], Q[lg]);
	for (auto &ux : E[vx]) {
		if (ux == pr || ux == lg) {
			continue;
		}
		for (auto &p : Q[ux]) {
			Q[vx][p.first] += p.second;
		}
	}
	for (auto &ux : E[vx]) {
		if (ux == pr || ux == lg) {
			continue;
		}
		for (auto &p : Q[ux]) {
			if (p.first == C[vx]) {
				continue;
			}
			z2 += p.second * (Q[vx][p.first] - p.second);
		}
	}
	Z += z2 / 2;

	Q[vx][C[vx]] = 1;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL T;
	cin >> T;
	while (T--) {
		LL N;
		cin >> N;
		vector<LL> C(N);
		vector<unordered_map<LL, LL>> Q(N);
		vector<vector<LL>> E(N);
		RF(i, 0, N) {
			cin >> C[i];
		}
		RF(i, 0, N - 1) {
			LL U, V;
			cin >> U >> V;
			E[U - 1].push_back(V - 1);
			E[V - 1].push_back(U - 1);
		}
		LL Z{0};

		dfsQualified(0, -1, Z, C, E, Q);
		cout << Z << '\n';
	}

	return 0;
}
