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
		LL R, X, D, N, Z{0};
		string S;
		cin >> R >> X >> D >> N >> S;
		RF(i, 0, N) {
			if (S[i] == '1') {
				Z++;
				R -= D;
			} else {
				if (R < X) {
					Z++;
					R -= D;
				}
			}
		}
		cout << Z << '\n';
	}

	return 0;
}
