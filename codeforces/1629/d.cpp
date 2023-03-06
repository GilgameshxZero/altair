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

	LL T;
	cin >> T;
	while (T--) {
		bool trivial{false};
		LL N;
		cin >> N;
		vector<string> S(N);
		RF(i, 0, N) {
			cin >> S[i];
			if (S[i][0] == S[i].back()) {
				trivial = true;
			}
		}
		if (trivial) {
			cout << "YES\n";
			continue;
		}

		unordered_multiset<array<char, 2>, ContainerHash<array<char, 2>>> tail2;
		RF(i, 0, N) {
			tail2.insert({S[i][S[i].length() - 2], S[i].back()});
		}
		bool found{false};
		RF(i, 0, N) {
			tail2.erase(tail2.find({S[i][S[i].length() - 2], S[i].back()}));
			if (S[i].length() == 3) {
				continue;
			}
			if (tail2.count({S[i][1], S[i][0]})) {
				found = true;
				break;
			}
		}
		if (found) {
			cout << "YES\n";
			continue;
		}

		tail2.clear();
		unordered_multiset<array<char, 3>, ContainerHash<array<char, 3>>> tail3;
		RF(i, 0, N) {
			if (S[i].length() == 3) {
				tail3.insert({S[i][0], S[i][1], S[i][2]});
			} else {
				tail2.insert({S[i][0], S[i][1]});
			}
		}
		RF(i, 0, N) {
			if (S[i].length() == 3) {
				tail3.erase(tail3.find({S[i][0], S[i][1], S[i][2]}));
			} else {
				tail2.erase(tail2.find({S[i][0], S[i][1]}));
			}
			if (S[i].length() == 2) {
				continue;
			}
			if (
				tail2.count({S[i][1], S[i][0]}) ||
				tail3.count({S[i][2], S[i][1], S[i][0]})) {
				found = true;
				break;
			}
		}
		cout << (found ? "YES" : "NO") << '\n';
	}

	return 0;
}
