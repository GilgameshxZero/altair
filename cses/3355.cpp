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

LL const N_MAX{10000001}, X_MAX{3163};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	array<LL, N_MAX> R2;
	R2.fill(-1);
	RF(i, 0, X_MAX) {
		RF(j, i, X_MAX) {
			if (i * i + j * j >= N_MAX) {
				break;
			}
			R2[i * i + j * j] = i;
		}
	}

	LL T;
	cin >> T;
	while (T--) {
		LL N;
		cin >> N;
		RF(i, 0, N / 2 + 1) {
			if (R2[i] >= 0 && R2[N - i] >= 0) {
				cout << R2[i] << ' ' << R2[N - i] << ' ' << sqrt(i - R2[i] * R2[i])
						 << ' ' << sqrt(N - i - R2[N - i] * R2[N - i]) << '\n';
				break;
			}
		}
	}

	return 0;
}
