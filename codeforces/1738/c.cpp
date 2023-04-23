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

	array<array<bool, 101>, 101> C[2];
	C[0][0][0] = true;
	C[1][0][0] = false;
	C[0][0][1] = false;
	C[1][0][1] = true;
	C[0][1][0] = true;
	C[1][1][0] = false;
	RF(i, 2, C[0].size()) {
		C[0][0][i] = C[1][0][i - 2];
		C[1][0][i] = C[0][0][i - 2];
		C[0][i][0] = true;
		C[1][i][0] = false;
	}
	RF(i, 1, C[0].size()) {
		RF(j, 1, C[0].size()) {
			if (j % 2 == 0) {
				C[0][i][j] = !(C[1][i - 1][j] && C[1][i][j - 1]);
				C[1][i][j] = !(C[0][i - 1][j] && C[0][i][j - 1]);
			} else {
				C[0][i][j] = !(C[0][i - 1][j] && C[0][i][j - 1]);
				C[1][i][j] = !(C[1][i - 1][j] && C[1][i][j - 1]);
			}
		}
	}

	LL T;
	cin >> T;
	while (T--) {
		LL N;
		cin >> N;

		LL Z[2]{0, 0};
		RF(i, 0, N) {
			LL X;
			cin >> X;
			X = abs(X);
			Z[X % 2]++;
		}
		cout << (C[0][Z[0]][Z[1]] ? "Alice" : "Bob") << '\n';
	}

	return 0;
}
