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

namespace Rain::Algorithm {
	// Computes the the minimum prime factor and a list of primes for all integers
	// up to and including N. The minFactor array is 1-indexed; that is,
	// minFactor[3] refers to the minimum prime factor of 3, which would be 1,
	// since primes[1] = 3. By definition, minFactor[0] = minfactor[1] = -1 (in
	// the integer representation used, which may be unsigned).
	inline std::pair<std::vector<std::size_t>, std::vector<std::size_t>>
	linearSieve(std::size_t const &N) {
		std::vector<std::size_t> minFactor(
			N + 1, std::numeric_limits<std::size_t>::max()),
			primes;
		for (std::size_t i{2}; i <= N; i++) {
			if (minFactor[i] == std::numeric_limits<std::size_t>::max()) {
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

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	auto [minFactor, primes]{Rain::Algorithm::linearSieve(400000)};

	LL T;
	cin >> T;
	while (T--) {
		LL N;
		cin >> N;
		vector<LL> A(N);
		RF(i, 0, N) {
			cin >> A[i];
		}
		sort(A.begin(), A.end());
		LL cPrimes{0};
		RF(i, 0, N) {
			if (primes[minFactor[A[i]]] == A[i]) {
				cPrimes++;
			}
		}
		if (cPrimes == 0) {
			cout << 2 << '\n';
		} else if (cPrimes >= 2) {
			cout << -1 << '\n';
		} else if (primes[minFactor[A[0]]] != A[0]) {
			cout << -1 << '\n';
		} else {
			bool fail{false};
			RF(i, 1, N) {
				if (A[i] % 2 == 0) {
					if (A[i] < 2 * A[0]) {
						fail = true;
						break;
					}
				} else {
					if (A[i] - primes[minFactor[A[i]]] < 2 * A[0]) {
						fail = true;
						break;
					}
				}
			}
			cout << (fail ? -1 : A[0]) << '\n';
		}
	}

	return 0;
}
