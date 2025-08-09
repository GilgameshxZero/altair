#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC target("avx", "avx2", "fma", "bmi", "bmi2", "popcnt", "lzcnt")
#pragma GCC optimize("Ofast", "unroll-loops")
#endif

#include <bits/stdc++.h>

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

using namespace Rain::Algorithm;

using LL = long long;
using LD = long double;
using namespace std;

#define RF(x, from, to) \
	for (LL x(from), _to(to), _delta{x < _to ? 1LL : -1LL}; x != _to; x += _delta)

auto [minFactor, primes]{linearSieve(1000000)};
LL M{1000000007};

LL CZ(vector<pair<LL, LL>> &F, LL p) {
	if (p == F.size()) {
		return 1;
	}
	LL y{1};
	RF(i, 0, F[p].second + 1) {
		y = (y * primes[F[p].first] + 1) % M;
	}
	return CZ(F, p + 1) * y % M;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL N;
	cin >> N;
	vector<pair<LL, LL>> F;
	while (N > 1) {
		if (F.empty() || F.back().first != minFactor[N]) {
			F.push_back({minFactor[N], 0});
		}
		F.back().second++;
		N /= primes[minFactor[N]];
	}
	cout << CZ(F, 0);

	return 0;
}
