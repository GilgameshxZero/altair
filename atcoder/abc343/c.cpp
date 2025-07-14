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

	LL N, Z;
	cin >> N;
	LL pZ[]{
		1,
		2,
		7,
		11,
		101,
		111,
		1001,
		2201,
		10001,
		10101,
		11011,
		100001,
		101101,
		110011};
	LL pZs{sizeof(pZ) / sizeof(pZ[0])};
	RF(i, pZs - 1, -1) {
		if (pZ[i] * pZ[i] * pZ[i] <= N) {
			cout << pZ[i] * pZ[i] * pZ[i];
			return 0;
		}
	}
}
