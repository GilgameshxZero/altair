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

// Most significant 1-bit for unsigned integral types of at most long long in
// size. Undefined result if x = 0.
template <typename Integer>
inline std::size_t mostSignificant1BitIdx(Integer const x) {
#ifdef __has_builtin
#if __has_builtin(__builtin_clzll)
	return 8 * sizeof(unsigned long long) - __builtin_clzll(x) - 1;
#endif
#endif
	for (std::size_t bit = 8 * sizeof(Integer) - 1;
			 bit != std::numeric_limits<std::size_t>::max();
			 bit--) {
		if (x & (static_cast<Integer>(1) << bit)) {
			return bit;
		}
	}
	return std::numeric_limits<std::size_t>::max();
}

// Least significant 1-bit for unsigned integral types of at most long long in
// size. Undefined result if x = 0.
template <typename Integer>
inline std::size_t leastSignificant1BitIdx(Integer const x) {
#ifdef __has_builtin
#if __has_builtin(__builtin_ctzll)
	return __builtin_ctzll(x);
#endif
#endif
	for (std::size_t bit = 0; bit != 8 * sizeof(Integer); bit++) {
		if (x & (static_cast<Integer>(1) << bit)) {
			return bit;
		}
	}
	return std::numeric_limits<std::size_t>::max();
}

// Count of 1-bits in unsigned integral types of at most long long in size.
template <typename Integer>
inline std::size_t bitPopcount(Integer const x) {
#ifdef __has_builtin
#if __has_builtin(__builtin_popcountll)
	return __builtin_popcountll(x);
#endif
#endif
	std::size_t count = 0;
	for (std::size_t bit = 0; bit != 8 * sizeof(Integer); bit++) {
		count += !!(x & (static_cast<Integer>(1) << bit));
	}
	return count;
}

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
		LL N, M;
		cin >> N >> M;

		array<vector<vector<LL>>, 20> A;
		A[0].resize(N);
		RF(i, 0, N) {
			A[0][i].resize(M);
			RF(j, 0, M) {
				cin >> A[0][i][j];
			}
		}
		RF(i, 1, 20) {
			if ((1LL << i) > N || (1LL << i) > M) {
				break;
			}
			A[i].resize(N - (1LL << i) + 1);
			RF(j, 0, N - (1LL << i) + 1) {
				A[i][j].resize(M - (1LL << i) + 1);
				RF(k, 0, M - (1LL << i) + 1) {
					A[i][j][k] = min(
						{A[i - 1][j][k],
						 A[i - 1][j + (1LL << (i - 1))][k],
						 A[i - 1][j][k + (1LL << (i - 1))],
						 A[i - 1][j + (1LL << (i - 1))][k + (1LL << (i - 1))]});
				}
			}
		}

		LL low{1}, high{min(N, M) + 1}, mid;
		while (low + 1 != high) {
			mid = (low + high) / 2;
			LL ms1bi = mostSignificant1BitIdx(mid);
			bool ok{false};
			RF(i, 0, N - mid + 1) {
				RF(j, 0, M - mid + 1) {
					if (
						mid <=
						min(
							{A[ms1bi][i][j],
							 A[ms1bi][i + mid - (1LL << ms1bi)][j],
							 A[ms1bi][i][j + mid - (1LL << ms1bi)],
							 A[ms1bi][i + mid - (1LL << ms1bi)][j + mid - (1LL << ms1bi)]})) {
						ok = true;
						break;
					}
				}
				if (ok) {
					break;
				}
			}
			if (ok) {
				low = mid;
			} else {
				high = mid;
			}
		}
		cout << low << '\n';
	}

	return 0;
}
