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

LL const MOD{1000000007};
array<array<LL, 1LL << 19>, 19> Z;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL N, M;
	cin >> N >> M;
	vector<vector<LL>> E(N, vector<LL>(N, 0));
	RF(i, 0, M) {
		LL A, B;
		cin >> A >> B;
		E[A - 1][B - 1]++;
	}

	RF(i, 0, N - 1) {
		Z[i].fill(-1);
		Z[i][0] = E[i][N - 1];
	}
	RF(i, 1, 1LL << (N - 1)) {
		RF(j, 0, N - 1) {
			LL t{i & (~(1LL << j))};
			if (Z[j][t] != -1) {
				continue;
			}
			Z[j][t] = 0;
			RF(k, 0, N - 1) {
				if (k == j) {
					continue;
				}
				if (!(t & (1LL << k))) {
					continue;
				}
				Z[j][t] = (Z[j][t] + E[j][k] * Z[k][t & (~(1LL << k))]) % MOD;
			}
		}
	}
	cout << Z[0][((1LL << (N - 1)) - 1) ^ 1];

	return 0;
}
