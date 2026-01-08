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

namespace Rain::Algorithm {
	// Computes the the minimum prime factor and a list of primes for all integers
	// up to and including N. The minFactor array is 1-indexed; that is,
	// minFactor[3] refers to the minimum prime factor of 3, which would be 1,
	// since primes[1] = 3. By definition, minFactor[0] = minfactor[1] = -1 (in
	// the integer representation used, which may be unsigned).
	inline std::pair<std::vector<std::size_t>, std::vector<std::size_t>>
	linearSieve(std::size_t const &N) {
		std::vector<std::size_t> minFactor(N + 1, -1), primes;
		for (std::size_t i{2}; i <= N; i++) {
			if (minFactor[i] == -1) {
				minFactor[i] = primes.size();
				primes.push_back(i);
			}
			for (std::size_t j{0}; i * primes[j] <= N; j++) {
				minFactor[i * primes[j]] = j;
				if (primes[j] == primes[minFactor[i]]) {
					break;
				}
			}
		}

		// C++17: guaranteed either NRVO or move.
		return {minFactor, primes};
	}
}

using namespace Rain::Algorithm;

int main(int, char const *[]) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	auto [minFactor, primes]{linearSieve(10000)};
	vector<LL> D(10000);
	D[0] = 0;
	D[1] = 0;
	RF(i, 2, D.size()) {
		D[i] = 1;
		LL P{0}, C{i}, A{1};
		while (C > 1) {
			if (primes[minFactor[C]] != P) {
				if (P != 0) {
					D[i] *= (A * P - 1) / (P - 1);
				}
				P = primes[minFactor[C]];
				A = P;
			} else {
				A *= P;
			}
			C /= P;
		}
		D[i] *= (A * P - 1) / (P - 1);
		D[i] -= i;
	}

	LL Z{0};
	RF(i, 2, D.size()) {
		if (D[i] < D.size() && D[i] != i && D[D[i]] == i) {
			Z += i;
		}
	}
	cout << Z;
	return 0;
}
