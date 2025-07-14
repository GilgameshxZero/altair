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
	vector<pair<LL, LL>> E(M);
	vector<vector<LL>> F(N);
	RF(i, 0, M) {
		cin >> E[i].first >> E[i].second;
		E[i].first--;
		E[i].second--;
		F[E[i].first].push_back(E[i].second);
		F[E[i].second].push_back(E[i].first);
	}
	vector<bool> C(N);
	RF(i, 0, N) {
		LL x;
		cin >> x;
		C[i] = x == 1;
	}

	vector<LL> CC(N, -1);
	LL CCC{0};
	RF(i, 0, N) {
		if (CC[i] != -1) {
			continue;
		}
		queue<LL> Q;
		Q.push(i);
		CC[i] = CCC++;
		while (!Q.empty()) {
			LL j{Q.front()};
			Q.pop();
			RF(k, 0, F[j].size()) {
				if (C[F[j][k]] != C[j] && CC[F[j][k]] == -1) {
					CC[F[j][k]] = CC[j];
					Q.push(F[j][k]);
				}
			}
		}
	}

	RF(i, 0, M) {
		if (C[E[i].first] == C[E[i].second] && CC[E[i].first] == CC[E[i].second]) {
			cout << "Yes";
			return 0;
		}
	}

	cout << "No";
	return 0;
}
