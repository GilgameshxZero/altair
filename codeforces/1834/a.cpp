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
		LL cN{0}, cP{0}, N, Z{0};
		cin >> N;
		RF(i, 0, N) {
			LL X;
			cin >> X;
			cN += X == -1;
			cP += X == 1;
		}
		if (cN % 2 == 1) {
			Z++;
			cN--;
		}
		while (cN > N / 2) {
			cN -= 2;
			Z += 2;
		}
		cout << Z << '\n';
	}

	return 0;
}
