#if defined(__GNUC__) && !defined(__clang__) && !defined(__MINGW32__)
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
		LL N;
		cin >> N;
		vector<vector<LL>> G(N + 2, vector<LL>(N + 2, 0));
		RF(i, 1, N + 1) {
			RF(j, 1, N + 1) {
				G[i][j] = (i - 1) * N + j;
			}
		}
		LL Z{0};
		RF(i, 1, N + 1) {
			RF(j, 1, N + 1) {
				Z = max(Z, G[i][j] + G[i - 1][j] + G[i][j + 1] + G[i + 1][j] + G[i][j - 1]);
			}
		}
		cout << Z << '\n';
	}

	return 0;
}
