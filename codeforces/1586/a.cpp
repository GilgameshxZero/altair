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

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	auto [minFactor, primes]{linearSieve(20000)};

	LL T;
	cin >> T;
	while (T--) {
		LL N;
		cin >> N;
		LL S{0};
		vector<LL> A(N);
		RF(i, 0, N) {
			cin >> A[i];
			S += A[i];
		}
		if (primes[minFactor[S]] != S) {
			cout << N << '\n';
			RF(i, 0, N) {
				cout << i + 1 << ' ';
			}
			cout << '\n';
		} else {
			cout << N - 1 << '\n';
			RF(i, 0, N) {
				if (primes[minFactor[S - A[i]]] != S - A[i]) {
					RF(j, 0, N) {
						if (j == i) {
							continue;
						}
						cout << j + 1 << ' ';
					}
					break;
				}
			}
			cout << '\n';
		}
	}

	return 0;
}
