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
		LL N, K;
		cin >> N >> K;

		LL M{1}, C{1}, O{0}, Z;
		while (K > 0) {
			LL X{(N - C + (1LL << M) - 1) / (1LL << M)};
			if (X == 0) {
				Z = O;
				K = 0;
			} else if (X >= K) {
				Z = C + (1LL << M) * (K - 1);
				K = 0;
			} else {
				K -= X;
				if ((N & (1LL << (M - 1)))) {
					C = O;
					O = C + (1LL << M);
				} else {
					C = O + (1LL << M);
				}
				M++;
			}
		}
		cout << Z + 1 << '\n';
	}

	return 0;
}
