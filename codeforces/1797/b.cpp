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
		LL N, K;
		cin >> N >> K;

		LL ans{0};
		vector<vector<bool>> G(N, vector<bool>(N));
		RF(i, 0, N) {
			RF(j, 0, N) {
				LL X;
				cin >> X;
				G[i][j] = X == 1;
			}
		}
		RF(i, 0, N) {
			RF(j, 0, N) {
				ans += G[i][j] != G[N - 1 - i][N - 1 - j];
			}
		}
		ans /= 2;
		cout << (ans <= K && ((K - ans) % 2 == 0 || N % 2 == 1) ? "YES" : "NO")
				 << '\n';
	}

	return 0;
}
