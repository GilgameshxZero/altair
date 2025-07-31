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
	vector<vector<LL>> E(N);
	RF(i, 0, M) {
		LL X, Y;
		cin >> X >> Y;
		E[X - 1].push_back(Y - 1);
		E[Y - 1].push_back(X - 1);
	}

	vector<LL> T(N);
	vector<bool> V(N);
	bool fail{false};
	RF(i, 0, N) {
		if (T[i] != 0) {
			continue;
		}
		queue<LL> Q;
		Q.push(i);
		T[i] = 1;
		while (!Q.empty() && !fail) {
			LL I{Q.front()};
			Q.pop();
			if (V[I]) {
				continue;
			}
			V[I] = true;
			RF(j, 0, E[I].size()) {
				if (T[E[I][j]] == 0) {
					T[E[I][j]] = 3 - T[I];
					Q.push(E[I][j]);
				} else if (T[E[I][j]] == T[I]) {
					fail = true;
					break;
				}
			}
		}
	}
	if (fail) {
		cout << "IMPOSSIBLE";
	} else {
		RF(i, 0, N) {
			cout << T[i] << ' ';
		}
	}

	return 0;
}
