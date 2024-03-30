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

	LL N, Q;
	cin >> N >> Q;
	vector<LL> X(N), Y(Q), Z(N);
	unordered_set<LL> S;
	vector<vector<pair<LL, bool>>> E(N);
	RF(i, 0, Q) {
		LL x;
		cin >> x;
		x--;
		if (S.count(x)) {
			S.erase(x);
			Z[x] += Y[i - 1] - (E[x].back().first > 0 ? Y[E[x].back().first - 1] : 0);
			E[x].emplace_back(i, false);
		} else {
			S.insert(x);
			E[x].emplace_back(i, true);
		}
		Y[i] = S.size() + (i > 0 ? Y[i - 1] : 0);
	}
	RF(i, 0, N) {
		if (!E[i].empty() && E[i].back().second) {
			Z[i] += Y[Q - 1] - (E[i].back().first > 0 ? Y[E[i].back().first - 1] : 0);
		}
		cout << Z[i] << ' ';
	}

	return 0;
}
