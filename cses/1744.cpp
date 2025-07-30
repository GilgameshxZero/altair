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

	LL A, B;
	cin >> A >> B;
	if (A > B) {
		swap(A, B);
	}
	vector<vector<LL>> Z(A + 1, vector<LL>(B + 1));
	RF(i, 2, B + 1) {
		Z[1][i] = i - 1;
	}
	RF(i, 2, A + 1) {
		RF(j, 1, B + 1) {
			Z[i][j] = LLONG_MAX;
			RF(k, 1, i) {
				Z[i][j] = min(Z[i][j], 1 + Z[k][j] + Z[i - k][j]);
			}
			RF(k, 1, j) {
				Z[i][j] = min(Z[i][j], 1 + Z[i][k] + Z[i][j - k]);
			}
			if (i == j) {
				Z[i][j] = 0;
			}
		}
	}
	cout << Z.back().back();

	return 0;
}
