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
		string S, R;
		cin >> N >> S >> R;
		LL c0{0}, c1{0};
		RF(i, 0, N) {
			c0 += S[i] == '0';
			c1 += S[i] == '1';
		}
		bool fail{false};
		RF(i, 0, N - 1) {
			if (c0 == 0 || c1 == 0) {
				fail = true;
				break;
			}
			c0--;
			c1--;
			if (R[i] == '0') {
				c0++;
			} else {
				c1++;
			}
		}
		cout << (fail ? "NO" : "YES") << '\n';
	}

	return 0;
}
