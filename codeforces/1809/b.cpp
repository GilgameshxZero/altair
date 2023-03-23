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

#pragma hdrstop	 // ------------------------------------------------------------

int main(int, char const *[]) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL T;
	cin >> T;
	while (T--) {
		LL N;
		cin >> N;
		LL S(sqrt(N));
		while (S * S < N) {
			S++;
		}
		while ((S - 1) * (S - 1) >= N) {
			S--;
		}
		// LL base{(S / 2) * (S / 2 + 1) * (S / 2 * 2 + 1) / 6 * 16}, rem{N - S *
		// S}; cout << base + rem * (S / 2 + 1) * 2 << '\n';
		cout << S - 1 << '\n';
	}

	return 0;
}
