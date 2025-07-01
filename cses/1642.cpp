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

	LL N, X;
	cin >> N >> X;
	vector<LL> A(N);
	RF(i, 0, N) {
		cin >> A[i];
	}

	unordered_map<LL, set<pair<LL, LL>>> M;
	RF(i, 0, N) {
		RF(j, i + 1, N) {
			M[A[i] + A[j]].insert({i, j});
		}
	}

	for (auto &i : M) {
		for (auto &j : i.second) {
			auto k{M.find(X - i.first)};
			if (k == M.end()) {
				continue;
			}
			auto l{k->second.lower_bound({j.second + 1, 0})};
			if (l != k->second.end()) {
				cout << j.first + 1 << ' ' << j.second + 1 << ' ' << l->first + 1 << ' '
						 << l->second + 1;
				return 0;
			}
		}
	}
	cout << "IMPOSSIBLE";

	return 0;
}
