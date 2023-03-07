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
#include <random>
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

namespace Rain::Functional {
	// Simple function to combine two hashes, based on
	// <https://stackoverflow.com/questions/2590677/how-do-i-combine-hash-values-in-c0x>.
	template <class Type>
	inline void combineHash(std::size_t &seed, Type const &value) {
		seed ^= std::hash<Type>{}(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
	}

	// SFINAE for const-iterable types (containers). Assumes sizeof(char) and
	// sizeof(int) are not equal.
	template <typename Type>
	struct isConstIterable {
		template <typename TypeInner>
		static char test(typename TypeInner::const_iterator *);
		template <typename TypeInner>
		static int test(...);

		public:
		enum { value = sizeof(test<Type>(0)) == sizeof(char) };
	};

	// Custom hash functor for const-iterable containers. Cannot be placed in std
	// namespace as it is UB for system types (not UB for user-defined types).
	template <
		typename Container,
		typename std::enable_if<isConstIterable<Container>::value>::type * =
			nullptr>
	struct ContainerHash {
		std::size_t operator()(Container const &value) const {
			std::size_t result{0};
			for (auto const &i : value) {
				combineHash(result, i);
			}
			return result;
		}
	};

	// Custom hash functor for std::pair (TODO: implement tuple functor).
	template <typename TypeFirst, typename TypeSecond>
	struct PairHash {
		std::size_t operator()(
			std::pair<TypeFirst, TypeSecond> const &value) const {
			std::size_t result{std::hash<TypeFirst>{}(value.first)};
			combineHash(result, value.second);
			return result;
		}
	};
}

using namespace Rain::Functional;

/* ------------------------ End of primary template. ------------------------ */

int main(int, char const *[]) {
#if !defined(ONLINEJUDGE) && (defined(__APPLE__) || defined(__MACH__))
	std::freopen("../build/i.default.txt", "r", stdin);
	std::freopen("../build/o.default.txt", "w", stdout);
#endif

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int const SZ{6}, KK{2};
	array<int, SZ> cur, orig;
	RF(i, 0, cur.size()) {
		cur[i] = i + 1;
	}
	orig = cur;
	unordered_map<array<int, SZ>, int, ContainerHash<array<int, SZ>>> cnt;
	do {
		array<int, SZ> clone{cur};
		RF(i, 0, KK) {
			RF(j, 0, clone.size() - 1) {
				if (clone[j] > clone[j + 1]) {
					swap(clone[j], clone[j + 1]);
				}
			}
		}
		cnt[clone]++;
		next_permutation(cur.begin(), cur.end());
	} while (cur != orig);

	for (auto const &i : cnt) {
		LL right{0};
		RF(j, 0, SZ) {
			cout << i.first[j] << ' ';
			right += max(0LL, i.first[j] - (j + 1));
		}
		cout << "| " << i.second << " | " << right << '\n';
	}
	return 0;

	// LL T;
	// cin >> T;
	// while (T--) {
	// 	LL N, K;
	// }

	return 0;
}
