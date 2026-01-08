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

	auto [minFactor, primes]{Rain::Algorithm::linearSieve(1000000)};
	LL Z{0};
	RF(i, 2, 1000001) {
		if (primes[minFactor[i]] != i) {
			continue;
		}
		auto s{std::to_string(i)};
		bool fail{false};
		RF(j, 0, s.size() - 1) {
			s.push_back(s[0]);
			s.erase(s.begin());
			auto t{std::stoll(s)};
			if (primes[minFactor[t]] != t) {
				fail = true;
				break;
			}
		}
		if (!fail) {
			Z++;
			cout << i << '\n';
		}
	}

	cout << Z;
	return 0;
}
