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
#include <tuple>
#include <type_traits>
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

namespace Rain::Algorithm {
	// GCD using Euclidean algorithm.
	template <typename Integer>
	inline Integer greatestCommonDivisor(Integer x, Integer y) {
		while (x != 0) {
			std::tie(y, x) = std::make_pair(x, y % x);
		}
		return y;
	}

	// GCD using extended Euclidean algorithm gives Bezout's identity
	// coefficients.
	template <typename Integer>
	inline std::tuple<Integer, Integer, Integer> greatestCommonDivisorExtended(
		Integer x,
		Integer y) {
		Integer cX{0}, cY{1}, nX{1}, nY{0}, ratio;
		while (x != 0) {
			ratio = y / x;
			std::tie(y, x) = std::make_pair(x, y - ratio * x);
			std::tie(cX, nX) = std::make_pair(nX, cX - ratio * nX);
			std::tie(cY, nY) = std::make_pair(nY, cY - ratio * nY);
		}
		return {y, cX, cY};
	}

	// LCM.
	template <typename Integer>
	inline Integer leastCommonMultiple(Integer const &x, Integer const &y) {
		return x / greatestCommonDivisor(x, y) * y;
	}
}

using namespace Rain::Algorithm;

/* ---------------------------- End of template. ---------------------------- */

int main(int, char const *[]) {
#if !defined(ONLINEJUDGE) && (defined(__APPLE__) || defined(__MACH__))
	std::freopen("../build/i.default.txt", "r", stdin);
	std::freopen("../build/o.default.txt", "w", stdout);
#endif

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	LL T;
	cin >> T;
	while (T--) {
		LL N;
		cin >> N;
		vector<LL> A(N);
		RF(i, 0, N) {
			cin >> A[i];
		}
		LL mg{LLONG_MAX};
		RF(i, 0, N) {
			RF(j, i + 1, N) {
				mg = min(mg, greatestCommonDivisor(A[i], A[j]));
			}
		}
		cout << (mg <= 2 ? "YES" : "NO") << '\n';
	}

	return 0;
}
