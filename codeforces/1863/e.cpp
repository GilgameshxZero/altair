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

	LL T;
	cin >> T;
	while (T--) {
		LL N, M, K;
		cin >> N >> M >> K;

		vector<LL> H(N);
		RF(i, 0, N) {
			cin >> H[i];
		}
		vector<vector<LL>> E(N), W(N), R(N);
		RF(i, 0, M) {
			LL x, y;
			cin >> x >> y;
			E[x - 1].push_back(y - 1);
			W[x - 1].push_back(H[y - 1] < H[x - 1] ? 1 : 0);
			R[y - 1].push_back(x - 1);
		}
		vector<LL> V(N, false), Y(N, -1), U(N, 0);
		vector<pair<LL, LL>> C;
		RF(i, 0, N) {
			if (V[i]) {
				continue;
			}
			queue<LL> P, Q;
			P.push(i);
			V[i] = true;
			C.push_back({K, 0});
			while (!P.empty()) {
				LL j{P.front()};
				P.pop();
				if (R[j].empty()) {
					Y[j] = 0;
					Q.push(j);
					C.back().first = min(C.back().first, H[j]);
				}
				for (auto &k : E[j]) {
					if (!V[k]) {
						V[k] = true;
						P.push(k);
					}
				}
				for (auto &k : R[j]) {
					if (!V[k]) {
						V[k] = true;
						P.push(k);
					}
				}
			}
			pair<LL, LL> X{0, 0};
			while (!Q.empty()) {
				LL j{Q.front()};
				Q.pop();
				if (Y[j] > X.first) {
					X = {Y[j], H[j]};
				} else if (Y[j] == X.first && H[j] > X.second) {
					X.second = H[j];
				}
				RF(k, 0, E[j].size()) {
					if (Y[j] + W[j][k] > Y[E[j][k]]) {
						Y[E[j][k]] = Y[j] + W[j][k];
					}
					U[E[j][k]]++;
					if (U[E[j][k]] == R[E[j][k]].size()) {
						Q.push(E[j][k]);
					}
				}
			}
			C.back().second = (X.first - 1) * K + K - C.back().first + X.second;
		}
		sort(C.begin(), C.end());

		multiset<LL> S[2];
		RF(i, 0, C.size()) {
			S[1].insert(C[i].first + C[i].second);
		}
		LL Z{LLONG_MAX / 2};
		RF(i, 0, C.size()) {
			S[1].erase(S[1].find(C[i].first + C[i].second));
			LL z{C[i].first + C[i].second};
			z = max(z, S[1].empty() ? 0 : *S[1].rbegin());
			z = max(z, S[0].empty() ? 0 : K + *S[0].rbegin());
			Z = min(Z, z - C[i].first);
			S[0].insert(C[i].first + C[i].second);
		}
		cout << Z << '\n';
	}

	return 0;
}
