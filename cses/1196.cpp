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

	LL N, M, K;
	cin >> N >> M >> K;

	vector<vector<pair<LL, LL>>> E(N);
	RF(i, 0, M) {
		LL A, B, C;
		cin >> A >> B >> C;
		E[A - 1].push_back({B - 1, C});
	}

	vector<vector<LL>> D(N);
	priority_queue<pair<LL, LL>, vector<pair<LL, LL>>, greater<pair<LL, LL>>> Q;
	Q.push({0, 0});
	while (!Q.empty() && D[N - 1].size() < K) {
		auto [i, j]{Q.top()};
		Q.pop();
		if (D[j].size() == K) {
			continue;
		}
		D[j].push_back(i);
		for (auto const &k : E[j]) {
			Q.push({i + k.second, k.first});
		}
	}

	RF(i, 0, D[N - 1].size()) {
		cout << D[N - 1][i] << ' ';
	}

	return 0;
}
