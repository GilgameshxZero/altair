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

		LL M(sqrt(N * 2)), Y;
		RF(i, clamp(M - 50, 0LL, 100000000000LL), M + 1000) {
			if (i * (i - 1) / 2 > N) {
				Y = i - 1;
				break;
			}
		}

		cout << Y + N - Y * (Y - 1) / 2 << '\n';
	}

	return 0;
}
