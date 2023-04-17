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
	RF(t, 0, T) {
		LL N, M;
		cin >> N >> M;
		vector<string> G(N + 2, string(M + 2, '.'));
		vector<vector<LL>> W(N + 2, vector<LL>(M + 2, LLONG_MAX / 2));
		RF(i, 1, N + 1) {
			cin >> G[i];
			G[i] = '.' + G[i] + '.';
		}
		RF(i, 1, N + 1) {
			if (G[i][M] == '#') {
				W[i][M] = 0;
			} else if (
				G[i - 1][M] == '.' && G[i][M + 1] == '.' && G[i + 1][M] == '.' &&
				G[i][M - 1] == '.') {
				W[i][M] = 1;
			}
		}
		RF(j, M - 1, 0) {
			RF(i, 1, N + 1) {
				if (G[i][j] == '#') {
					W[i][j] = min(W[i - 1][j + 1], W[i + 1][j + 1]);
				} else if (
					G[i - 1][j] == '.' && G[i][j + 1] == '.' && G[i + 1][j] == '.' &&
					G[i][j - 1] == '.') {
					W[i][j] = 1 + min(W[i - 1][j + 1], W[i + 1][j + 1]);
				}
			}
		}
		LL K{1};
		RF(i, 1, N + 1) {
			if (W[i][1] < W[K][1]) {
				K = i;
			}
		}
		if (W[K][1] >= LLONG_MAX / 2) {
			cout << "NO\n";
			continue;
		}
		cout << "YES\n";
		RF(j, 1, M + 1) {
			G[K][j] = '#';
			if (W[K - 1][j + 1] <= W[K + 1][j + 1]) {
				K--;
			} else {
				K++;
			}
		}
		RF(i, 1, N + 1) {
			cout << G[i].substr(1, M) << '\n';
		}
	}

	return 0;
}
