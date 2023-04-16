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
		cout << (N + 1) / 2 << '\n';
		RF(i, 0, N / 2) {
			cout << 3 * i + 1 << ' ' << 3 * N - 3 * i << '\n';
		}
		if (N % 2 == 1) {
			cout << 3 * (N / 2) + 1 << ' ' << 3 * (N / 2) + 3 << '\n';
		}
	}

	return 0;
}
