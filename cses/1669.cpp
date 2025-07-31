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

	vector<LL> P(N, -1);
	vector<bool> V(N);
	RF(i, 0, N) {
		if (P[i] != -1) {
			continue;
		}
		queue<LL> Q;
		Q.push(i);
		P[i] = i;
		while (!Q.empty()) {
			LL I{Q.front()};
			Q.pop();
			if (V[I]) {
				continue;
			}
			V[I] = true;
			RF(j, 0, E[I].size()) {
				if (E[I][j] == P[I]) {
					continue;
				}
				if (P[E[I][j]] == -1) {
					P[E[I][j]] = I;
					Q.push(E[I][j]);
				} else {
					vector<LL> Z, Y;
					Y.push_back(E[I][j]);
					while (P[I] != I) {
						Z.push_back(I);
						I = P[I];
					}
					Z.push_back(I);
					I = Y.back();
					Y.pop_back();
					while (P[I] != I) {
						Y.push_back(I);
						I = P[I];
					}
					Y.push_back(I);
					LL p;
					while (!Y.empty() && !Z.empty() && Y.back() == Z.back()) {
						p = Y.back();
						Y.pop_back();
						Z.pop_back();
					}
					reverse(Z.begin(), Z.end());
					Z.insert(Z.end(), Y.begin(), Y.end());
					Z.push_back(p);
					Z.push_back(Z[0]);
					cout << Z.size() << '\n';
					RF(i, 0, Z.size()) {
						cout << Z[i] + 1 << ' ';
					}
					return 0;
				}
			}
		}
	}
	cout << "IMPOSSIBLE";

	return 0;
}
