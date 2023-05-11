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

	LL T;
	cin >> T;
	while (T--) {
		LL N, M;
		cin >> N >> M;

		vector<vector<LL>> E(N);
		RF(i, 0, M) {
			LL U, V;
			cin >> U >> V;
			U--;
			V--;
			E[U].push_back(V);
			E[V].push_back(U);
		}

		bool fail{true};
		RF(i, 0, N) {
			if (E[i].size() < 4) {
				continue;
			}

			vector<bool> V(N, false);
			vector<LL> P(N);
			V[i] = true;
			pair<LL, LL> Z{-1, -1};
			for (auto &j : E[i]) {
				queue<LL> Q;
				Q.push(j);
				P[j] = i;
				while (!Q.empty()) {
					LL k{Q.front()};
					Q.pop();
					V[k] = true;
					for (auto &l : E[k]) {
						if (l == i && k != j) {
							Z = {j, k};
							break;
						}
						if (V[l]) {
							continue;
						}
						Q.push(l);
						P[l] = k;
					}
					if (Z.first != -1) {
						break;
					}
				}
				if (Z.first != -1) {
					break;
				}
			}
			if (Z.first == -1) {
				continue;
			}

			cout << "YES\n";
			fail = false;
			vector<pair<LL, LL>> W;
			for (auto &j : E[i]) {
				if (j == Z.first || j == Z.second) {
					continue;
				}
				W.push_back({i, j});
				if (W.size() == 2) {
					break;
				}
			}
			LL C{Z.second};
			while (C != i) {
				W.push_back({C, P[C]});
				C = P[C];
			}
			W.push_back({i, Z.second});
			cout << W.size() << '\n';
			for (auto &j : W) {
				cout << j.first + 1 << ' ' << j.second + 1 << '\n';
			}
			break;
		}
		if (fail) {
			cout << "NO\n";
		}
	}

	return 0;
}
