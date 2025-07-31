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

	LL N;
	cin >> N;
	vector<LL> X(N);
	RF(i, 0, N) {
		cin >> X[i];
	}
	vector<LL> Y(N + 1);
	Y[0] = 0;
	RF(i, 1, N + 1) {
		Y[i] = Y[i - 1] + X[i - 1];
	}

	vector<vector<LL>> Z(N, vector<LL>(N));
	RF(i, 0, N) {
		Z[i][i] = X[i];
	}
	RF(i, 0, N - 1) {
		Z[i][i + 1] = max(X[i], X[i + 1]);
	}
	if (N >= 2) {
		RF(i, 2, N) {
			RF(j, 0, N - i) {
				Z[j][j + i] = max(X[j] + min(Z[j + 2][j + i], Z[j + 1][j + i - 1]),
					X[j + i] + min(Z[j][j + i - 2], Z[j + 1][j + i - 1]));
			}
		}
	}
	cout << Z[0][N - 1];

	return 0;
}
