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
		LL N, M;
		cin >> N >> M;
		if (N % 2 == 0) {
			if (M % 2 == 0) {
				LL big{(M - (N - 2)) / 2};
				if (big <= 0) {
					cout << "NO\n";
				} else {
					cout << "YES\n";
					RF(i, 0, N - 2) {
						cout << 1 << ' ';
					}
					cout << big << ' ' << big << '\n';
				}
			} else {
				cout << "NO\n";
			}
		} else {
			LL big{M - (N - 1)};
			if (big <= 0) {
				cout << "NO\n";
			} else {
				cout << "YES\n";
				RF(i, 0, N - 1) {
					cout << 1 << ' ';
				}
				cout << big << '\n';
			}
		}
	}

	return 0;
}
