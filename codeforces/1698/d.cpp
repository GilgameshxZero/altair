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
		LL N;
		cin >> N;

		LL low{1}, s{N};
		while (s > 1) {
			LL high{low + s / 2};
			cout << "? " << low << ' ' << high - 1 << endl;
			LL bad{0};
			RF(i, 0, s / 2) {
				LL X;
				cin >> X;
				if (X < low || X >= high) {
					bad++;
				}
			}
			if (s / 2 % 2 == 0) {
				if (bad % 2 == 0) {
					low = high;
					s -= s / 2;
				} else {
					s /= 2;
				}
			} else {
				if (bad % 2 == 0) {
					s /= 2;
				} else {
					low = high;
					s -= s / 2;
				}
			}
		}
		cout << "! " << low << endl;
	}

	return 0;
}
