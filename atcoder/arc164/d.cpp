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

LL const M{998244353};
array<array<LL, 6001>, 6001> Z, W;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL N;
	string T;
	cin >> N >> T;

	W[0][N] = 1;
	RF(i, 1, 2 * N + 1) {
		if (T[i - 1] == '-' || T[i - 1] == '?') {
			RF(j, 0, N) {
				W[i][N - j - 1] = (W[i][N - j - 1] + W[i - 1][N - j]) % M;
				Z[i][N - j - 1] = (Z[i][N - j - 1] + Z[i - 1][N - j]) % M;
			}
			RF(j, 1, N + 1) {
				W[i][N + j - 1] = (W[i][N + j - 1] + W[i - 1][N + j]) % M;
				Z[i][N + j - 1] =
					(Z[i][N + j - 1] + Z[i - 1][N + j] + W[i - 1][N + j] * (j * 2 - 1)) %
					M;
			}
		}
		if (T[i - 1] == '+' || T[i - 1] == '?') {
			RF(j, 1, N + 1) {
				W[i][N - j + 1] = (W[i][N - j + 1] + W[i - 1][N - j]) % M;
				Z[i][N - j + 1] =
					(Z[i][N - j + 1] + Z[i - 1][N - j] + W[i - 1][N - j] * (j * 2 - 1)) %
					M;
			}
			RF(j, 0, N) {
				W[i][N + j + 1] = (W[i][N + j + 1] + W[i - 1][N + j]) % M;
				Z[i][N + j + 1] = (Z[i][N + j + 1] + Z[i - 1][N + j]) % M;
			}
		}
	}

	cout << Z[2 * N][N];
	return 0;
}
