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

auto CO() {
	array<array<LD, 601>, 601> O;
	O[0].fill(0);
	O[0][0] = 1;
	RF(i, 1, O.size()) {
		O[i] = O[i - 1];
		RF(j, O[i].size() - 1, -1) {
			O[i][j] = 0;
			RF(k, 1, 7) {
				if (j - k < 0) {
					break;
				}
				O[i][j] += O[i][j - k];
			}
		}
	}
	return O;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	auto O{CO()};
	LL N, A, B;
	cin >> N >> A >> B;
	LD S{0};
	RF(i, A, B + 1) {
		S += O[N][i];
	}
	cout << fixed << setprecision(6) << S / (pow(6.0l, N));

	return 0;
}
