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
		LL N, M;
		cin >> N >> M;
		LL X{-LLONG_MAX / 2}, W, H;
		RF(i, 0, N) {
			RF(j, 0, M) {
				LL x;
				cin >> x;
				X = max(X, x);
				if (X == x) {
					W = max(i + 1, N - i);
					H = max(j + 1, M - j);
				}
			}
		}
		cout << W * H << '\n';
	}

	return 0;
}
