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

	LL T;
	cin >> T;
	while (T--) {
		LL N;
		cin >> N;
		vector<vector<LL>> B(12);
		B[0].resize(5000);
		RF(i, 0, N) {
			B[0][i] = i;
		}
		B[1].resize(5000);
		for (LL i{0}; i < N; i += 2) {
			if (i + 1 < N) {
				cout << "? " << i + 1 << ' ' << i + 2 << endl;
				LL x;
				cin >> x;
				B[1][i] = x == 0 ? i + 1 : i;
			} else {
				B[1][i] = i;
			}
		}
		RF(i, 2, B.size()) {
			B[i].resize(5000, 1000000000);
			LL s{1LL << i}, qs{s / 4};
			for (LL j{0}; j < N; j += s) {
				if (B[i - 1][j] >= j + qs && B[i - 1][j + 2 * qs] < j + 3 * qs) {
					B[i][j] = B[i - 1][j + qs];
				} else {
					cout << "? " << B[i - 1][j] + 1 << ' ' << B[i - 1][j + 2 * qs] + 1
							 << endl
							 << "? " << B[i - 1][j] + 2 << ' ' << B[i - 1][j + 2 * qs] + 1
							 << endl;
					LL x, y;
					cin >> x >> y;
					if (x - y == B[i - 1][j + 2 * qs] - B[i - 1][j]) {
						B[i][j] = B[i - 1][j];
					} else {
						B[i][j] = B[i - 1][j + 2 * qs];
					}
				}
			}
		}
		cout << "! " << B.back()[0] + 1 << endl;
	}

	return 0;
}
