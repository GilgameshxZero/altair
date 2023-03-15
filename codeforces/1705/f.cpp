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
#include <complex>
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

#define RF(x, from, to)                                                      \
	for (long long x = from, _to = to, _delta{x < _to ? 1LL : -1LL}; x != _to; \
			 x += _delta)

using LL = long long;
using LD = long double;
using namespace std;

#pragma hdrstop	 // ------------------------------------------------------------

namespace Rain::Functional {
	// SFINAE for const-iterable types (containers). Assumes sizeof(char) and
	// sizeof(int) are not equal.
	template <typename Type>
	struct isConstIterable {
		template <typename TypeInner>
		static char evaluate(typename TypeInner::const_iterator *);
		template <typename TypeInner>
		static int evaluate(...);

		public:
		enum { value = sizeof(evaluate<Type>(0)) == sizeof(char) };
	};
}

namespace Rain::Random {
	using Generator = std::mt19937_64;

	// Default, generally-safe generator when one is not supplied by caller.
	inline Generator generator(
		std::chrono::duration_cast<std::chrono::nanoseconds>(
			std::chrono::high_resolution_clock::now().time_since_epoch())
			.count());

	// 64-bit hash from <https://codeforces.com/blog/entry/62393>.
	template <typename Type>
	struct SplitMixHash {
		std::size_t operator()(Type const &value) const {
			static const std::size_t FIXED_RANDOM(
				std::chrono::duration_cast<std::chrono::nanoseconds>(
					std::chrono::high_resolution_clock::now().time_since_epoch())
					.count());
			std::size_t hash{std::hash<Type>{}(value)};
			hash += FIXED_RANDOM + 0x9e3779b97f4a7c15;
			hash = (hash ^ (hash >> 30)) * 0xbf58476d1ce4e5b9;
			hash = (hash ^ (hash >> 27)) * 0x94d049bb133111eb;
			return hash ^ (hash >> 31);
		}
	};

	// Simple function to combine two 32 or 64-bit hashes, based on
	// <https://stackoverflow.com/questions/5889238/why-is-xor-the-default-way-to-combine-hashes>
	// from Boost.
	template <typename Type, typename HashFunctor = SplitMixHash<Type>>
	inline void combineHash(
		std::size_t &seed,
		Type const &value,
		HashFunctor hasher = SplitMixHash<Type>{}) {
		if constexpr (sizeof(size_t) >= 8) {
			seed ^= hasher(value) + 0x517cc1b727220a95 + (seed << 6) + (seed >> 2);
		} else {
			seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
		}
	}

	// Custom hash functor for const-iterable containers. Cannot be placed in std
	// namespace as it is UB for system types (not UB for user-defined types).
	template <
		typename Container,
		typename std::enable_if<Functional::isConstIterable<Container>::value>::type
			* = nullptr>
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

namespace Rain::Algorithm {
	// Most significant 1-bit for unsigned integral types of at most long long in
	// size. Undefined result if x = 0.
	template <typename Integer>
	inline std::size_t mostSignificant1BitIdx(Integer const &x) {
#ifdef __has_builtin
#if __has_builtin(__builtin_clzll)
		return 8 * sizeof(unsigned long long) - __builtin_clzll(x) - 1;
#endif
#endif
		for (std::size_t bit{8 * sizeof(Integer) - 1};
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
	inline std::size_t leastSignificant1BitIdx(Integer const &x) {
#ifdef __has_builtin
#if __has_builtin(__builtin_ctzll)
		return __builtin_ctzll(x);
#endif
#endif
		for (std::size_t bit{0}; bit != 8 * sizeof(Integer); bit++) {
			if (x & (static_cast<Integer>(1) << bit)) {
				return bit;
			}
		}
		return std::numeric_limits<std::size_t>::max();
	}

	// Count of 1-bits in unsigned integral types of at most long long in size.
	template <typename Integer>
	inline std::size_t bitPopcount(Integer const &x) {
#ifdef __has_builtin
#if __has_builtin(__builtin_popcountll)
		return __builtin_popcountll(x);
#endif
#endif
		std::size_t count{0};
		for (std::size_t bit{0}; bit != 8 * sizeof(Integer); bit++) {
			count += !!(x & (static_cast<Integer>(1) << bit));
		}
		return count;
	}
}

using namespace Rain::Random;
using namespace Rain::Algorithm;

int main(int, char const *[]) {
#if !defined(ONLINEJUDGE) && (defined(__APPLE__) || defined(__MACH__))
	std::freopen("../build/i.default.txt", "r", stdin);
	std::freopen("../build/o.default.txt", "w", stdout);
#endif

	std::ios_base::sync_with_stdio(false);
	// std::cin.tie(nullptr);

	LL N;

	N = 1000;
	string SS;
	RF(i, 0, N) {
		SS += uniform_int_distribution<LL>{0, 1}(generator) == 1 ? 'T' : 'F';
	}
	// cin >> N;

	vector<pair<LD, LL>> rp(N);
	RF(i, 0, N) {
		rp[i].first = i;
		rp[i].second = i;
	}
	sort(rp.begin(), rp.end());
	vector<LL> perm(N);
	RF(i, 0, N) {
		perm[i] = rp[i].second;
	}

	// cout << string(N, 'T') << endl;
	LL totaltrue{0}, Q{0};
	RF(j, 0, SS.length()) {
		totaltrue += 'T' == SS[j];
	}
	// cin >> totaltrue;
	auto count{[&](LL i, LL X) {
		Q++;
		string S(N, 'F');
		RF(j, i, i + X) {
			S[perm[j]] = 'T';
		}
		// cout << S << endl;
		LL ans{0};
		RF(j, 0, SS.length()) {
			ans += S[j] == SS[j];
		}
		// cin >> ans;
		return (ans + totaltrue - (N - X)) / 2;
	}};

	map<LL, LL> qper;
	vector<bool> ans(N);
	for (LL i{0}; i < N;) {
		LL qc{Q};
		if (i == N - 1) {
			ans[perm[i]] = count(i, 1) == 1;
			break;
		}

		vector<LL> res;
		array<bool, 4> ch;
		array<bool, 8> opt;
		LL j{i};
		ch.fill(true);
		for (;; j++) {
			if (j == N - 2) {
				ans[perm[j]] = count(j, 1) == 1;
				ans[perm[j + 1]] = count(j + 1, 1) == 1;
				break;
			}

			res.push_back(count(j, 3));
			opt.fill(false);
			RF(k, 0, 4) {
				if (ch[k]) {
					opt[k * 2] = opt[k * 2 + 1] = true;
				}
			}
			ch.fill(false);
			RF(k, 0, 8) {
				if (bitPopcount(k) == res.back()) {
					ch[k & 3] = true;
				}
			}

			LL ncht{0}, nchti;
			RF(k, 0, 4) {
				if (ch[k]) {
					ncht++;
					nchti = k;
				}
			}
			if (ncht == 1) {
				ans[perm[j + 2]] = (nchti & 1) != 0;
				ans[perm[j + 1]] = (nchti & 2) != 0;
				ans[perm[j]] = res.back() - ans[perm[j + 1]] - ans[perm[j + 2]] == 1;
				res.pop_back();
				break;
			}
		}

		RF(k, 0, res.size()) {
			ans[perm[j - 1 - k]] =
				res[res.size() - 1 - k] - ans[perm[j - k]] - ans[perm[j - k + 1]] == 1;
		}
		i = j + 3;

		qper[Q - qc]++;
	}

	// RF(i, 0, N) {
	// 	cout << (ans[i] ? 'T' : 'F');
	// }
	cout << Q + 1 << '\n';
	LL qs{0}, qt{0};
	for (auto const &i : qper) {
		cout << i.first << ' ' << i.second << '\n';
		qs += i.first * i.second;
		qt += i.second;
	}
	cout << (LD)qs / qt << '\n';
	LL bad{0};
	RF(i, 0, N) {
		if ((ans[i] && SS[i] == 'F') || (!ans[i] && SS[i] == 'T')) {
			bad++;
		}
	}
	cout << bad << '\n';
	return 0;
}
