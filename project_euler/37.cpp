#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC target("avx", "avx2", "fma", "bmi", "bmi2", "popcnt", "lzcnt")
#pragma GCC optimize("Ofast", "unroll-loops")
#endif

#include <bits/stdc++.h>
#include <rain.hpp>

using LL = long long;
using LD = long double;
using namespace std;

#define RF(x, from, to) \
	for (LL x(from), _to(to), _delta{x < _to ? 1LL : -1LL}; x != _to; x += _delta)

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL Z{0};
	auto [minFactor, primes]{Rain::Algorithm::linearSieve(1000000)};
	RF(i, 11, 1000001) {
		if (primes[minFactor[i]] != i) {
			continue;
		}
		LL c{i};
		bool fail{false};
		c /= 10;
		while (c > 0) {
			if (c <= 1 || primes[minFactor[c]] != c) {
				fail = true;
				break;
			}
			c /= 10;
		}
		if (fail) {
			continue;
		}
		c = i;
		for (LL j{100000}; j > 1; j /= 10) {
			c %= j;
			if (c <= 1 || primes[minFactor[c]] != c) {
				fail = true;
				break;
			}
		}
		if (!fail) {
			cout << i << '\n';
			Z += i;
		}
	}
	cout << Z;
	return 0;
}
