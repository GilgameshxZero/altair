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
	if (N == 2 || N == 3) {
		cout << "NO SOLUTION";
		return 0;
	} else if (N == 4) {
		cout << "2 4 1 3";
		return 0;
	}
	for (LL i{N}; i >= 1; i -= 2) {
		cout << i << ' ';
	}
	for (LL i{N - 1}; i >= 1; i -= 2) {
		cout << i << ' ';
	}

	return 0;
}
