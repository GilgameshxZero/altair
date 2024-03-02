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

bool v1(LL V[], LL x2, LL y2, LL z2, LL x3, LL y3, LL z3) {
	LL v3{
		max(0LL, 7 - max(x2, x3)) * max(0LL, 7 - max(y2, y3)) *
		max(0LL, 7 - max(z2, z3))};
	LL v2p{
		(7 - x2) * (7 - y2) * (7 - z2) +
		max(0LL, 7 - x3) * max(0LL, 7 - y3) * max(0LL, 7 - z3)};
	LL corners[][3]{
		{1, 1, 1},
		{1, 1, -1},
		{1, -1, 1},
		{1, -1, -1},
		{-1, 1, 1},
		{-1, 1, -1},
		{-1, -1, 1},
		{-1, -1, -1}};
	RF(i, 0, 8) {
		LL cg[3]{
			x3 + (corners[i][0] - 1) / 2 * -7,
			y3 + (corners[i][1] - 1) / 2 * -7,
			z3 + (corners[i][2] - 1) / 2 * -7};
		if (
			cg[0] >= x2 && cg[0] <= x2 + 7 && cg[1] >= y2 && cg[1] <= y2 + 7 &&
			cg[2] >= z2 && cg[2] <= z2 + 7) {
			LL other[3]{
				x2 + (corners[i][0] + 1) / 2 * 7,
				y2 + (corners[i][1] + 1) / 2 * 7,
				z2 + (corners[i][2] + 1) / 2 * 7};
			LL volume{
				abs((cg[0] - other[0]) * (cg[1] - other[1]) * (cg[2] - other[2]))};
			v2p += volume;
			break;
		}
	}
	LL v1p{343 * 3};
	LL v2{v2p - v3 * 3};
	LL v1{v1p - v2 * 2 - v3 * 3};
	if (v1 == V[0] && v2 == V[1] && v3 == V[2]) {
		return true;
	} else {
		return false;
	}
}

// bool v2(LL V[], LL x2, LL y2, LL z2, LL x3, LL y3, LL z3) {
// 	LL v3{(7 - x3) * (7 - y3) * (7 - z3)};
// 	LL v2p{
// 		(7 - x2) * (7 - y2) * (7 - z2) + (7 - x3) * (7 - y3) * (7 - z3) +
// 		(x2 + 7 - x3) * (y2 + 7 - y3) * (z2 + 7 - z3)};
// 	LL v1p{343 * 3};
// 	LL v2{v2p - v3 * 3};
// 	LL v1{v1p - v2 * 2 - v3 * 3};
// 	if (v1 == V[0] && v2 == V[1] && v3 == V[2]) {
// 		return true;
// 	} else {
// 		return false;
// 	}
// }

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL V[3];
	RF(i, 0, 3) {
		cin >> V[i];
	}
	RF(i, 0, 8) {
		RF(j, 0, 8) {
			RF(k, 0, 8) {
				RF(l, 0, 8) {
					RF(m, 0, 8) {
						RF(n, 0, 8) {
							if (v1(V, i, j, k, l, m, n)) {
								cout << "Yes\n0 0 0 " << i << ' ' << j << ' ' << k << ' ' << l
										 << ' ' << m << ' ' << n;
								return 0;
							}
							if (v1(V, i, j, k, i + l, j + m, k + n)) {
								cout << "Yes\n0 0 0 " << i << ' ' << j << ' ' << k << ' '
										 << i + l << ' ' << j + m << ' ' << k + n;
								return 0;
							}
						}
					}
				}
			}
		}
	}
	cout << "No";
	return 0;
}
