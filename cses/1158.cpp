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

int N, X;
array<int, 1000> H, S;
array<array<int, 1001>, 100001> Z;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> N >> X;
	RF(i, 0, N) {
		cin >> H[i];
	}
	RF(i, 0, N) {
		cin >> S[i];
	}

	RF(i, 1, X + 1) {
		Z[i][0] = 0;
		RF(j, 1, N + 1) {
			if (i >= H[j - 1]) {
				Z[i][j] = max(Z[i][j - 1], Z[i - H[j - 1]][j - 1] + S[j - 1]);
			} else {
				Z[i][j] = Z[i][j - 1];
			}
		}
	}
	cout << Z[X][N];

	return 0;
}
