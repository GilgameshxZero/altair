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
		LL Z{0}, N, S;
		cin >> N >> S;
		RF(i, 0, N) {
			LL DX, DY, X, Y;
			cin >> DX >> DY >> X >> Y;
			if (X == Y && DX * DY == 1) {
				Z++;
			}
			if (Y + X == S && DX * DY == -1) {
				Z++;
			}
		}
		cout << Z << '\n';
	}

	return 0;
}
