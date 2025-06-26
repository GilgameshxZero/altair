#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC target("avx", "avx2", "fma", "bmi", "bmi2", "popcnt", "lzcnt")
#pragma GCC optimize("Ofast", "unroll-loops")
#endif

#include <bits/stdc++.h>

/*
3
000
001
011
010
110
111
101
100
*/

using LL = long long;
using LD = long double;
using namespace std;

#define RF(x, from, to) \
	for (LL x(from), _to(to), _delta{x < _to ? 1LL : -1LL}; x != _to; x += _delta)

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	array<LL, 1 << 16> Z;
	Z[0] = 0;
	Z[1] = 1;
	RF(i, 2, 17) {
		RF(j, 0, 1LL << (i - 1)) {
			Z[(1LL << (i - 1)) + j] = (1LL << (i - 1)) + Z[(1LL << (i - 1)) - j - 1];
		}
	}

	LL N;
	cin >> N;
	RF(i, 0, 1LL << N) {
		cout << bitset<16>(Z[i]).to_string().substr(16 - N) << '\n';
	}

	return 0;
}
