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

	LL N;
	cin >> N;

	map<LL, LL> M;
	LL v{-1}, Z{0};
	RF(i, 0, N) {
		LL x;
		cin >> x;
		if (M.count(x)) {
			v = max(v, M[x]);
		}
		M[x] = i;
		Z = max(Z, i - v);
	}
	cout << Z;

	return 0;
}
