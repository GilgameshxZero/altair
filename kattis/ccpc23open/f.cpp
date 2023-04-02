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

	auto [minFactor, primes]{linearSieve(1000000)};
	vector<vector<pair<LL, LL>>> pp(primes.size());
	LL N;
	cin >> N;

	vector<LL> A(N);
	unordered_map<LL, LL> ppx;
	RF(i, 0, N) {
		cin >> A[i];

		LL X{A[i]};
		ppx.clear();
		while (X > 1) {
			ppx[minFactor[X]]++;
			X /= primes[minFactor[X]];
		}

		for (auto &j : ppx) {
			pp[j.first].push_back({j.second, i});
		}
	}

	vector<LL> ptop(primes.size()), pdelta(primes.size());
	vector<vector<LL>> which(N);
	RF(i, 0, pp.size()) {
		if (pp[i].empty()) {
			ptop[i] = -1;
			continue;
		}
		sort(pp[i].begin(), pp[i].end());
		ptop[i] = pp[i].back().first;
		which[pp[i].back().second].push_back(i);
		if (pp[i].size() >= 2) {
			pdelta[i] = pp[i].back().first - pp[i][pp[i].size() - 2].first;
		} else {
			pdelta[i] = pp[i].back().first;
		}
	}

	LL ans, argans{LLONG_MAX / 2};
	RF(i, 0, N) {
		LL cand{1};
		RF(j, 0, which[i].size()) {
			RF(k, 0, pdelta[which[i][j]]) {
				cand *= primes[which[i][j]];
			}
		}
		if (cand < argans) {
			argans = cand;
			ans = i;
		} else if (cand == argans && A[i] < A[ans]) {
			ans = i;
		}
	}

	cout << A[ans];
	return 0;
}
