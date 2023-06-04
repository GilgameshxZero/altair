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

int main(int, char const *[]) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL T;
	cin >> T;
	while (T--) {
		LL N;
		cin >> N;

		LL maxA{0}, minA{0};
		RF(i, 0, N) {
			LL A;
			cin >> A;
			maxA = max(maxA, A);
			minA = min(minA, A);
		}
		if (minA < 0) {
			cout << minA << '\n';
		} else {
			cout << maxA << '\n';
		}
	}

	return 0;
}
