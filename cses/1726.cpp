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

	LL K;
	cin >> K;

	array<array<array<array<LD, 8>, 8>, 8>, 8> O;
	RF(i, 0, 8) {
		RF(j, 0, 8) {
			RF(k, 0, 8) {
				O[i][j][k].fill(0);
			}
			O[i][j][i][j] = 1;
			RF(k, 0, K) {
				array<array<LD, 8>, 8> R;
				RF(l, 0, 8) {
					R[l].fill(0);
				}
				RF(l, 0, 8) {
					RF(m, 0, 8) {
						LD C{0};
						if (l > 0) {
							C++;
						}
						if (m > 0) {
							C++;
						}
						if (l < 7) {
							C++;
						}
						if (m < 7) {
							C++;
						}
						if (l > 0) {
							R[l - 1][m] += O[i][j][l][m] / C;
						}
						if (m > 0) {
							R[l][m - 1] += O[i][j][l][m] / C;
						}
						if (l < 7) {
							R[l + 1][m] += O[i][j][l][m] / C;
						}
						if (m < 7) {
							R[l][m + 1] += O[i][j][l][m] / C;
						}
					}
				}
				swap(O[i][j], R);
			}
		}
	}

	LD Z{0};
	RF(i, 0, 8) {
		RF(j, 0, 8) {
			LD P{1};
			RF(k, 0, 8) {
				RF(l, 0, 8) {
					P *= 1 - O[k][l][i][j];
				}
			}
			Z += P;
		}
	}
	cout << fixed << setprecision(6) << Z;

	return 0;
}
