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
		LL M, K, A, B;
		cin >> M >> K >> A >> B;
		if (B * K >= M) {
			cout << max(M % K - A, 0LL) << '\n';
		} else {
			LL Y{M - B * K}, Z{Y - A};
			if (Z <= 0) {
				cout << 0 << '\n';
			} else {
				LL C{max(A + 1, K)};
				Z = 0;
				if (Y >= C) {
					Z = (Y - C) / K;
					Y -= K * Z;
				}
				while (Y > A && Y >= K) {
					Y -= K;
					Z++;
				}
				cout << max(Y - A, 0LL) + Z << '\n';
			}
		}
	}

	return 0;
}
