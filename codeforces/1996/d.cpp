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
		LL N, X;
		cin >> N >> X;
		LL Z{0};
		RF(a, 1, N) {
			RF(b, 1, N) {
				if (a * b >= N) {
					break;
				}
				if (a + b >= X) {
					break;
				}
				Z += min(X - a - b, (N - a * b) / (a + b));
			}
		}
		cout << Z << '\n';
	}

	return 0;
}
