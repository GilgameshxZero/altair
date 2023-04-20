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

	LL N, M, K;
	cin >> N >> M >> K;

	// vector<vector<LL>> X(M, vector<LL>(N));
	// RF(i, K, N) {
	// 	X[0][i] = 2;
	// }
	// RF(i, 1, M) {
	// 	RF(j, 0, N) {
	// 		for (LL k{0}; k <= j - K - 1; k++) {
	// 			X[i][j] += 2 * X[i - 1][k];
	// 		}
	// 	}
	// }

	// LL Z{0};
	// RF(i, 0, N) {
	// 	Z += X[M - 1][i];
	// }
	// cout << Z;

	vector<vector<LL>> L(M, vector<LL>(N)), R{L};
	RF(i, K, N) {
		L[0][i] = 1;
	}
	RF(i, 0, N) {
		R[0][i] = 1;
	}
	RF(i, 1, M) {
		RF(j, 0, N) {
			for (LL k{0}; k <= j - K - 1; k++) {
				L[i][j] += L[i - 1][k];
			}
			for (LL k{0}; k <= j - 2 * K - 1; k++) {
				L[i][j] += R[i - 1][k];
			}
			for (LL k{0}; k <= j - 1; k++) {
				R[i][j] += L[i - 1][k];
			}
			for (LL k{0}; k <= j - K - 1; k++) {
				R[i][j] += R[i - 1][k];
			}
		}
	}

	LL Z{0};
	RF(i, 0, N) {
		Z += L[M - 1][i];
		if (i < N - K) {
			Z += R[M - 1][i];
		}
	}
	cout << Z;

	return 0;
}
