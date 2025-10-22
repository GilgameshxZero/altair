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
		if (N == 2) {
			cout << -1 << '\n';
			continue;
		} else if (N == 3) {
			cout << "1 3\n2 3\n";
			continue;
		} else if (N == 4) {
			cout << "1 2\n1 3\n1 4\n";
			continue;
		}
		cout << "1 2\n2 3\n3 4\n";
		RF(i, 4, N - 1) {
			cout << "2 " << i + 1 << '\n';
		}
		cout << "1 " << N << '\n';
	}

	return 0;
}
