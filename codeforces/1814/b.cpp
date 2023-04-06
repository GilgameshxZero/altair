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
		LL X, Y;
		cin >> X >> Y;

		LL best{X + Y};
		RF(i, 2, 300000) {
			LL cand{i - 1 + (X + i - 1) / i + (Y + i - 1) / i};
			best = min(best, cand);
		}
		cout << best << '\n';
	}

	return 0;
}
