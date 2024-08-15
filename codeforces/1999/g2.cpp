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
		LL low{2}, high{1000}, m1, m2, r;
		while (low + 1 < high) {
			m1 = low + (high - low) / 3;
			m2 = low + (high - low) * 2 / 3;
			cout << "? " << m1 << ' ' << m2 << '\n';
			cout.flush();
			cin >> r;
			if (r == m1 * m2) {
				low = m2 + 1;
			} else if (r == m1 * (m2 + 1)) {
				low = m1 + 1;
				high = m2 + 1;
			} else {
				high = m1 + 1;
			}
		}
		cout << "! " << low << '\n';
		cout.flush();
	}

	return 0;
}
