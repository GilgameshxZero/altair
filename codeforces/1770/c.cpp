#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC target("avx2", "bmi", "bmi2", "popcnt", "lzcnt")
#pragma GCC optimize("Ofast", "unroll-loops")
#endif

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <algorithm>
#include <array>
#include <atomic>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cinttypes>
#include <climits>
#include <cmath>
#include <condition_variable>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <mutex>
#include <numeric>
#include <queue>
#include <regex>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <system_error>
#include <thread>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using LL = long long;
using LD = long double;

#define RF(x, from, to)                                                      \
	for (long long x = from, _to = to, _delta{x < _to ? 1LL : -1LL}; x != _to; \
			 x += _delta)

using namespace std;

// GCD using Euclidean algorithm.
template <typename Integer>
inline Integer greatestCommonDivisor(Integer x, Integer y) {
	if (x > y) {
		std::swap(x, y);
	}
	while (x != 0) {
		y %= x;
		std::swap(x, y);
	}
	return y;
}

// LCM. Integer type must be large enough to store product.
template <typename Integer>
inline Integer leastCommonMultiple(Integer const x, Integer const y) {
	return x * y / greatestCommonDivisor(x, y);
}

/* ---------------------------- End of template. ---------------------------- */

namespace Rain::Algorithm {
	// Computes the the minimum prime factor and a list of primes for all integers
	// up to and including N. The minFactor array is 1-indexed; that is,
	// minFactor[1] refers to the minimum prime factor of 1, which we define as 1.
	template <typename Integer>
	inline std::pair<std::vector<Integer>, std::vector<Integer>> linearSieve(
		Integer const &N) {
		std::vector<Integer> minFactor(N + 1), primes;
		minFactor[0] = minFactor[1] = 1;
		for (Integer i{2}; i <= N; i++) {
			if (minFactor[i] == 0) {
				minFactor[i] = i;
				primes.push_back(i);
			}
			for (Integer j{0}; i * primes[j] <= N; j++) {
				minFactor[i * primes[j]] = primes[j];
				if (primes[j] == minFactor[i]) {
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
#if !defined(ONLINEJUDGE) && (defined(__APPLE__) || defined(__MACH__))
	std::freopen("../build/i.default.txt", "r", stdin);
	std::freopen("../build/o.default.txt", "w", stdout);
#endif

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	auto [minFactor, primes]{linearSieve(100)};

	LL T;
	cin >> T;
	while (T--) {
		LL N;
		cin >> N;
		vector<LL> A(N);
		unordered_set<LL> coll;
		bool possible{true};
		RF(i, 0, N) {
			cin >> A[i];
			if (coll.count(A[i])) {
				possible = false;
			} else {
				coll.insert(A[i]);
			}
		}
		if (!possible) {
			cout << "NO\n";
			continue;
		}
		RF(i, 0, primes.size()) {
			vector<LL> mult(primes[i]);
			RF(j, 0, N) {
				mult[A[j] % primes[i]]++;
			}
			LL mm{primes[i]};
			RF(j, 0, primes[i]) {
				mm = min(mm, mult[j]);
			}
			if (mm >= 2) {
				possible = false;
				break;
			}
		}
		cout << (possible ? "YES" : "NO") << '\n';
	}

	return 0;
}
