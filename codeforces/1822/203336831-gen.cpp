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

	LL N{9268}, M{20};
	cout << 1 << '\n' << N * M << '\n';
	stringstream S;
	RF(j, 0, M) {
		RF(i, 0, N) {
			S << ' ' << (i + 1) * 107897 + j;
		}
	}
	S.ignore(1);
	cout << S.rdbuf() << '\n';

	return 0;
}
