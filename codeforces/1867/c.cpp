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
		LL next{0};
		RF(i, 0, N) {
			LL x;
			cin >> x;
			if (x == next) {
				next++;
			}
		}
		if (next == 0) {
			cout << 0 << endl;
			LL x;
			cin >> x;
			continue;
		}
		while (next != 0) {
			cout << next << endl;
			LL x;
			cin >> x;
			next = x;
		}
		cout << 0 << endl;
		LL x;
		cin >> x;
	}

	return 0;
}
