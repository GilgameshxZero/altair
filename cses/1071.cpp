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
		LL X, Y;
		cin >> Y >> X;
		LL ring{max(X, Y)};
		if (ring % 2 == 0) {
			LL pos{Y + (ring - X)};
			cout << (ring - 1) * (ring - 1) + pos << '\n';
		} else {
			LL pos{X + (ring - Y)};
			cout << (ring - 1) * (ring - 1) + pos << '\n';
		}
	}

	return 0;
}
