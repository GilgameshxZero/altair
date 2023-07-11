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
		LL R{(N - 3) / 2};
		if (N == 1) {
			cout << "1\n";
		} else if (N == 2) {
			cout << "2 1\n";
		} else {
			cout << "3 ";
			RF(i, N, N - R) {
				cout << i << ' ';
			}
			cout << "1 ";
			RF(i, N - R, 3) {
				cout << i << ' ';
			}
			cout << "2\n";
		}
	}

	return 0;
}
