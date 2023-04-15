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

	LL T;
	cin >> T;
	while (T--) {
		LL N, M;
		cin >> N >> M;

		RF(i, 0, N) {
			RF(j, 0, M) {
				if (
					((i % 4 == 0 || i % 4 == 3) && (j % 4 == 0 || j % 4 == 3)) ||
					((i % 4 == 1 || i % 4 == 2) && (j % 4 == 1 || j % 4 == 2))) {
					cout << 1 << ' ';
				} else {
					cout << 0 << ' ';
				}
			}
			cout << '\n';
		}
	}

	return 0;
}
