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

int main(int, char const *[]) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL N, M;
	cin >> N >> M;
	vector<vector<LL>> S(N);
	vector<vector<LL>> E(1 + M + N + 1);
	RF(i, 0, N) {
		LL A;
		cin >> A;
		S[i].resize(A);
		RF(j, 0, A) {
			cin >> S[i][j];
			S[i][j]--;
			E[1 + M + i].push_back(1 + S[i][j]);
			E[1 + S[i][j]].push_back(1 + M + i);
		}
	}
	E[0].push_back(1);
	E[1].push_back(0);
	E.back().push_back(M);
	E[M].push_back(1 + M + N);

	vector<LL> D(E.size(), LLONG_MAX / 2);
	D[0] = -3;
	priority_queue<pair<LL, LL>, vector<pair<LL, LL>>, greater<pair<LL, LL>>> Q;
	Q.push({D[0], 0});
	while (!Q.empty()) {
		LL C{Q.top().second};
		if (D[C] != Q.top().first) {
			Q.pop();
			continue;
		}
		Q.pop();
		for (auto &j : E[C]) {
			LL X{D[C] + (C <= M)};
			if (X < D[j]) {
				D[j] = X;
				Q.push({D[j], j});
			}
		}
	}
	cout << (D.back() == LLONG_MAX / 2 ? -1 : D.back());
	return 0;
}
