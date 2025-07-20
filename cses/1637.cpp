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

	LL N, Z{0};
	cin >> N;
	while (N != 0) {
		LL mD{0}, n{N};
		while (n != 0) {
			mD = max(n % 10, mD);
			n /= 10;
		}
		N -= mD;
		Z++;
	}
	cout << Z;

	return 0;
}
