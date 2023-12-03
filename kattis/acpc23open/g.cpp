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

	LL F, G, T, R{6378137};
	cin >> F >> G >> T;
	LD D{(LD)2 * R * 3.14159265358979323};
	LL K{(LL)(G * T / D)};
	LD C{G * T - K * D}, A{C / D * 2 * 3.14159265358979323};
	LD X{(LD)R * cos(A)}, Y{(LD)R * sin(A)}, X2{(LD)R}, Y2{(LD)F * T};
	cout << setprecision(10) << fixed
			 << sqrt((X - X2) * (X - X2) + (Y - Y2) * (Y - Y2)) << '\n';

	return 0;
}
