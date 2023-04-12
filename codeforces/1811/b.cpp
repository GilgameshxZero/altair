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
		LL N, X1, Y1, X2, Y2;
		cin >> N >> X1 >> Y1 >> X2 >> Y2;
		auto reduce{[&](LL &X, LL &Y) {
			if (X > N / 2) {
				X = N + 1 - X;
			}
			if (Y > N / 2) {
				Y = N + 1 - Y;
			}
		}};
		reduce(X1, Y1);
		reduce(X2, Y2);
		LL B1{min(X1, Y1)}, B2{min(X2, Y2)};
		cout << abs(B1 - B2) << '\n';
	}

	return 0;
}
