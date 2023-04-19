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

LL N, K;
array<LL, 200000> P, S;
array<vector<LL>, 200000> C;

pair<LL, LL> dfs(LL c, LL k) {
	vector<LL> D;
	LL bs{k * S[c]};
	if (C[c].empty()) {
		return {bs, S[c]};
	}
	LL bk(k / C[c].size());
	for (auto &i : C[c]) {
		auto [b, d]{dfs(i, bk)};
		D.push_back(d);
		bs += b;
	}
	sort(D.begin(), D.end());
	RF(i, 0, k - bk * C[c].size()) {
		bs += D.back();
		D.pop_back();
	}
	return {bs, D.back() + S[c]};
}

int main(int, char const *[]) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL T;
	cin >> T;
	while (T--) {
		cin >> N >> K;
		RF(i, 0, N) {
			C[i].clear();
		}
		RF(i, 1, N) {
			cin >> P[i];
			P[i]--;
			C[P[i]].push_back(i);
		}
		RF(i, 0, N) {
			cin >> S[i];
		}
		auto [best, delta]{dfs(0, K)};
		cout << best << '\n';
	}

	return 0;
}
