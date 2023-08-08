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
		LL N, Q;
		cin >> N;
		map<LL, LL> C;
		RF(i, 0, N) {
			LL x;
			cin >> x;
			C[x]++;
		}
		cin >> Q;
		RF(i, 0, Q) {
			LL x, y;
			cin >> x >> y;
			LL c{(x + (LL)sqrt(x * x - 4 * y)) / 2};
			pair<LL, LL> a;
			RF(i, c - 2, c + 2) {
				if (i == 0) {
					continue;
				}
				LL d{x - i};
				if (i * d == y) {
					a = {i, d};
					break;
				}
			}
			if (a.first == a.second) {
				cout << C[a.first] * (C[a.first] - 1) / 2 << ' ';
			} else {
				cout << C[a.first] * C[a.second] << ' ';
			}
		}
		cout << '\n';
	}

	return 0;
}
