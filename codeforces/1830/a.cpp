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
		LL N;
		cin >> N;

		vector<array<LL, 2>> E(N - 1);
		vector<LL> D(N, LLONG_MAX / 2), S(N);
		priority_queue<pair<LL, LL>, vector<pair<LL, LL>>, less<pair<LL, LL>>> Q;
		RF(i, 0, N - 1) {
			cin >> E[i][0] >> E[i][1];
			S[--E[i][0]] = S[--E[i][1]] = i;
			if (E[i][0] == 0 || E[i][1] == 0) {
				D[i] = 0;
				Q.push({0, i});
			}
		}
		vector<vector<array<LL, 2>>> F(N - 1);
		RF(i, 0, N - 1) {
			RF(j, 0, 2) {
				LL C{S[E[i][j]]};
				if (C >= N - 1) {
					C -= N - 1;
				}
				if (C > i) {
					F[C].push_back({i, 1});
				} else {
					F[C].push_back({i, 0});
				}
			}
			S[E[i][0]] = S[E[i][1]] = N - 1 + i;
		}
		LL Z{0};
		while (!Q.empty()) {
			LL C{Q.top().second};
			Q.pop();
			Z = max(Z, D[C]);
			RF(i, 0, F[C].size()) {
				if (F[C][i][1] + D[C] < D[F[C][i][0]]) {
					D[F[C][i][0]] = F[C][i][1] + D[C];
					Q.push({D[F[C][i][0]], F[C][i][0]});
				}
			}
		}
		cout << Z + 1 << '\n';
	}

	return 0;
}
