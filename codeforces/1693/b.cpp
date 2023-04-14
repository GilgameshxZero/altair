#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC target("avx2", "bmi", "bmi2", "popcnt", "lzcnt")
#pragma GCC optimize("Ofast", "unroll-loops")
#endif

#include <bits/stdc++.h>

using LL = long long;
using LD = long double;
using namespace std;

#define RF(x, from, to) \
	for (LL x(from), _to(to), _delta{x < _to ? 1LL : -1LL}; x != _to; x += _delta)

LL dfs(vector<vector<LL>> &E, vector<pair<LL, LL>> &LR, LL &ans, LL cur) {
	if (E[cur].empty()) {
		ans++;
		return LR[cur].second;
	}

	LL best{0};
	RF(i, 0, E[cur].size()) {
		best += dfs(E, LR, ans, E[cur][i]);
	}
	if (best < LR[cur].first) {
		ans++;
		return LR[cur].second;
	}
	return min(best, LR[cur].second);
}

int main(int, char const *[]) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL T;
	cin >> T;
	while (T--) {
		LL N;
		cin >> N;

		vector<vector<LL>> E(N);
		vector<pair<LL, LL>> LR(N);
		RF(i, 1, N) {
			LL P;
			cin >> P;
			E[P - 1].push_back(i);
		}
		RF(i, 0, N) {
			cin >> LR[i].first >> LR[i].second;
		}

		LL ans{0};
		dfs(E, LR, ans, 0);
		cout << ans << '\n';
	}

	return 0;
}
