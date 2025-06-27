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
	map<LL, bool> M;
	cin >> N;
	RF(i, 0, N) {
		LL x, y;
		cin >> x >> y;
		M[x] = true;
		M[y] = false;
	}
	LL X{0}, Z{0};
	for (auto i : M) {
		X += i.second ? 1 : -1;
		Z = max(Z, X);
	}
	cout << Z;

	return 0;
}
