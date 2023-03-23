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

#pragma hdrstop	 // ------------------------------------------------------------

int main(int, char const *[]) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL T;
	cin >> T;
	while (T--) {
		LL N, K, R, C;
		cin >> N >> K >> R >> C;
		vector<string> G(N, string(N, '.'));
		RF(i, 0, N) {
			for (LL j{((C - 1 - (R - 1) + i) % K + K) % K}; j < N; j += K) {
				G[i][j] = 'X';
			}
		}
		RF(i, 0, N) {
			cout << G[i] << '\n';
		}
	}

	return 0;
}
