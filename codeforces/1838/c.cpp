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

int main(int, char const *[]) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	auto [minFactor, primes]{linearSieve(1000)};

	LL T;
	cin >> T;
	while (T--) {
		LL N, M;
		cin >> N >> M;
		bool S{false};
		if (primes[minFactor[N]] != N) {
			S = true;
			swap(N, M);
		}
		vector<vector<LL>> Z(N, vector<LL>(M));
		if (primes[minFactor[M]] != M) {
			RF(i, 0, N) {
				RF(j, 0, M) {
					Z[i][j] = 1 + i * M + j;
				}
			}
		} else {
			RF(i, 0, N) {
				Z[i][0] = N * (M - 1) + i + 1;
				RF(j, 0, M - 1) {
					Z[i][j + 1] = i * (M - 1) + j + 1;
				}
			}
		}
		if (S) {
			RF(i, 0, M) {
				RF(j, 0, N) {
					cout << Z[j][i] << ' ';
				}
				cout << '\n';
			}
			cout << '\n';
		} else {
			RF(i, 0, N) {
				RF(j, 0, M) {
					cout << Z[i][j] << ' ';
				}
				cout << '\n';
			}
			cout << '\n';
		}
	}

	return 0;
}
