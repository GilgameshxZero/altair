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
		vector<pair<LL, LL>> UV(M);
		vector<LL> W(M);
		vector<vector<LL>> D(N, vector<LL>(N, LLONG_MAX / 2));
		RF(i, 0, M) {
			cin >> UV[i].first >> UV[i].second >> W[i];
			UV[i].first--;
			UV[i].second--;
			D[UV[i].first][UV[i].second] = D[UV[i].second][UV[i].first] = 1;
		}
		RF(i, 0, N) {
			D[i][i] = 0;
		}
		RF(k, 0, N) {
			RF(i, 0, N) {
				RF(j, 0, N) {
					D[i][j] = min(D[i][j], D[i][k] + D[k][j]);
				}
			}
		}
		LL Z{LLONG_MAX / 2};
		RF(i, 0, M) {
			Z = min(
				{Z,
				 W[i] * (1 + D[UV[i].first][0] + D[UV[i].second][N - 1]),
				 W[i] * (1 + D[UV[i].first][N - 1] + D[UV[i].second][0])});
			RF(j, 0, N) {
				Z = min(
					{Z,
					 W[i] * (1 + D[UV[i].first][j] + 1 + D[j][0] + D[j][N - 1]),
					 W[i] * (1 + D[UV[i].second][j] + 1 + D[j][0] + D[j][N - 1])});
			}
		}
		cout << Z << '\n';
	}

	return 0;
}
