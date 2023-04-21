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
		auto C{[&](LL X) {
			if (X == 0) {
				return 0LL;
			}
			LL S(sqrt(X));
			while (S * S == X) {
				S++;
			}
			while (S * S > X) {
				S--;
			}
			return 3 * (S - 1) + (X - S * S) / S + 1;
		}};
		LL L, R;
		cin >> L >> R;
		cout << C(R) - C(L - 1) << '\n';
	}

	return 0;
}
