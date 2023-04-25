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

LL dfs(vector<LL> &P, vector<vector<LL>> &E, LL &K, LL H, LL cur) {
	LL mr{0};
	for (auto &i : E[cur]) {
		LL res{dfs(P, E, K, H, i)};
		if (res >= H && cur != 0) {
			K--;
		} else {
			mr = max(mr, res);
		}
	}
	return mr + 1;
}

int main(int, char const *[]) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL T;
	cin >> T;
	while (T--) {
		LL N, K;
		cin >> N >> K;

		vector<LL> P(N);
		vector<vector<LL>> E(N);
		P[0] = -1;
		RF(i, 1, N) {
			cin >> P[i];
			P[i]--;
			E[P[i]].push_back(i);
		}

		LL low{0}, high{N}, mid;
		while (low + 1 < high) {
			mid = (low + high) / 2;
			LL kc{K};
			dfs(P, E, kc, mid, 0);
			if (kc < 0) {
				low = mid;
			} else {
				high = mid;
			}
		}
		cout << high << '\n';
	}

	return 0;
}
