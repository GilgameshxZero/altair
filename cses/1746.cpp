#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC target("avx", "avx2", "fma", "bmi", "bmi2", "popcnt", "lzcnt")
#pragma GCC optimize("Ofast", "unroll-loops")
#endif

#include <bits/stdc++.h>
// #include <array>

using LL = long long;
using LD = long double;
using namespace std;

#define RF(x, from, to) \
	for (LL x(from), _to(to), _delta{x < _to ? 1LL : -1LL}; x != _to; x += _delta)

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL const MOD{1000000007};

	LL N, M;
	cin >> N >> M;
	vector<LL> X(N);
	RF(i, 0, N) {
		cin >> X[i];
	}

	vector<vector<LL>> Y(N);
	if (X[0] == 0) {
		Y[0].resize(M + 2, 1);
		Y[0][0] = 0;
		Y[0][M + 1] = 0;
	} else {
		Y[0].resize(M + 2, 0);
		Y[0][X[0]] = 1;
	}
	RF(i, 1, N) {
		Y[i].resize(M + 2, 0);
		if (X[i] == 0) {
			RF(j, 1, M + 1) {
				Y[i][j] = Y[i - 1][j - 1] + Y[i - 1][j] + Y[i - 1][j + 1];
				Y[i][j] %= MOD;
			}
		} else {
			Y[i][X[i]] = Y[i - 1][X[i] - 1] + Y[i - 1][X[i]] + Y[i - 1][X[i] + 1];
			Y[i][X[i]] %= MOD;
		}
	}

	LL Z{0};
	RF(i, 1, M + 1) {
		Z += Y[N - 1][i];
	}
	cout << Z % MOD;

	return 0;
}
