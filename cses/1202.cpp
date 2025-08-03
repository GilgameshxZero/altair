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

	LL N, M;
	cin >> N >> M;

	vector<vector<pair<LL, LL>>> E(N);
	RF(i, 0, M) {
		LL A, B, C;
		cin >> A >> B >> C;
		A--;
		B--;
		E[A].emplace_back(B, C);
	}

	vector<LL> D(N, LLONG_MAX), C(N), X(N), Y(N);
	priority_queue<pair<LL, LL>> Q;
	Q.push({0, 0});
	D[0] = 0;
	C[0] = 1;
	X[0] = 0;
	Y[0] = 0;
	while (!Q.empty()) {
		if (Q.top().first != -D[Q.top().second]) {
			Q.pop();
			continue;
		}
		LL i{Q.top().second};
		Q.pop();
		for (auto &j : E[i]) {
			if (D[i] + j.second < D[j.first]) {
				D[j.first] = D[i] + j.second;
				C[j.first] = C[i];
				X[j.first] = X[i] + 1;
				Y[j.first] = Y[i] + 1;
				Q.push({-D[j.first], j.first});
			} else if (D[i] + j.second == D[j.first]) {
				static LL const MOD{1000000007};
				C[j.first] = (C[j.first] + C[i]) % MOD;
				X[j.first] = min(X[j.first], X[i] + 1);
				Y[j.first] = max(Y[j.first], Y[i] + 1);
			}
		}
	}
	cout << D[N - 1] << ' ' << C[N - 1] << ' ' << X[N - 1] << ' ' << Y[N - 1];

	return 0;
}
