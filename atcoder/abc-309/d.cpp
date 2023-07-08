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

	LL N1, N2, M;
	cin >> N1 >> N2 >> M;
	vector<vector<LL>> E(N1 + N2);
	RF(i, 0, M) {
		LL u, v;
		cin >> u >> v;
		u--;
		v--;
		E[u].push_back(v);
		E[v].push_back(u);
	}
	vector<LL> D(E.size(), -1);
	queue<LL> Q;
	Q.push(0);
	D[0] = 0;
	LL Y1{0}, Y2{0};
	while (!Q.empty()) {
		RF(i, 0, E[Q.front()].size()) {
			if (D[E[Q.front()][i]] == -1) {
				D[E[Q.front()][i]] = D[Q.front()] + 1;
				Q.push(E[Q.front()][i]);
				Y1 = max(Y1, D[E[Q.front()][i]]);
			}
		}
		Q.pop();
	}
	Q.push(N1 + N2 - 1);
	fill(D.begin(), D.end(), -1);
	D[Q.front()] = 0;
	while (!Q.empty()) {
		RF(i, 0, E[Q.front()].size()) {
			if (D[E[Q.front()][i]] == -1) {
				D[E[Q.front()][i]] = D[Q.front()] + 1;
				Q.push(E[Q.front()][i]);
				Y2 = max(Y2, D[E[Q.front()][i]]);
			}
		}
		Q.pop();
	}
	cout << Y1 + 1 + Y2 << '\n';

	return 0;
}
