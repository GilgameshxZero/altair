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
	// inline Generator generator(0);

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

vector<LL> perm;
vector<bool> ans;
LL tTrue;
// LL Q;
// string SS;

LL count(LL pos, LL len) {
	// Q++;
	string S(perm.size(), 'F');
	RF(j, pos, pos + len) {
		S[perm[j]] = 'T';
	}
	LL res{0};
	// RF(j, 0, SS.length()) {
	// 	res += S[j] == SS[j];
	// }
	cout << S << endl;
	cin >> res;
	return (res + tTrue - (perm.size() - len)) / 2;
}

LL solve(LL pos, LL len, LL exist = -1) {
	if (len == 1) {
		ans[perm[pos]] = count(pos, 1) == 1;
		return pos + 1;
	}

	vector<LL> res;
	LL i{pos}, tt{-1};
	for (;; i++) {
		if (i + len > perm.size()) {
			solve(i, len - 1);
			break;
		}

		if (i == pos && exist != -1) {
			res.push_back(exist);
		} else {
			res.push_back(count(i, len));
		}
		if (res.back() == 0 || res.back() == len) {
			RF(j, i, i + len) {
				ans[perm[j]] = res.back() != 0;
			}
			res.pop_back();
			break;
		}
		if (res.size() >= 2 && res.back() != res[res.size() - 2]) {
			ans[perm[i + len - 1]] = res.back() > res[res.size() - 2];
			swap(perm[i], perm[i + len - 1]);
			tt = solve(i + 1, len - 1, min(res.back(), res[res.size() - 2]));
			swap(perm[i], perm[i + len - 1]);
			res.pop_back();
			break;
		}
	}

	RF(j, i - 1, pos - 1) {
		LL sum{0};
		RF(k, j + 1, j + len) {
			sum += ans[perm[k]];
		}
		ans[perm[j]] = res.back() - sum == 1;
		res.pop_back();
	}
	return tt == -1 ? i + len : tt;
}

int main(int, char const *[]) {
#if !defined(ONLINEJUDGE) && (defined(__APPLE__) || defined(__MACH__))
	std::freopen("../build/i.default.txt", "r", stdin);
	std::freopen("../build/o.default.txt", "w", stdout);
#endif

	std::ios_base::sync_with_stdio(false);
	// std::cin.tie(nullptr);

	LL N;
	// N = 1000;
	// RF(i, 0, N) {
	// 	SS += uniform_int_distribution<LL>{0, 1}(generator) == 1 ? 'T' : 'F';
	// }
	cin >> N;
	perm.resize(N);
	ans.resize(N);

	vector<pair<LD, LL>> rp(N);
	RF(i, 0, N) {
		rp[i].first = uniform_real_distribution<LD>{0, 1}(generator);
		// rp[i].first = i;
		rp[i].second = i;
	}
	sort(rp.begin(), rp.end());
	RF(i, 0, N) {
		perm[i] = rp[i].second;
	}

	// RF(j, 0, SS.length()) {
	// 	tTrue += 'T' == SS[j];
	// }
	cout << string(N, 'T') << endl;
	cin >> tTrue;

	// map<LL, LL> qper;
	LL cur{0};
	for (; cur < N;) {
		cur = solve(cur, min(N - cur, 3LL));
	}

	RF(i, 0, N) {
		cout << (ans[i] ? 'T' : 'F');
	}
	// cout << Q + 1 << '\n';
	// LL qs{0}, qt{0};
	// for (auto const &i : qper) {
	// 	cout << i.first << ' ' << i.second << '\n';
	// 	qs += i.first * i.second;
	// 	qt += i.second;
	// }
	// cout << (LD)qs / qt << '\n';
	// LL bad{0};
	// RF(i, 0, N) {
	// 	if ((ans[perm[i]] && SS[i] == 'F') || (!ans[perm[i]] && SS[i] == 'T')) {
	// 		bad++;
	// 	}
	// }
	// cout << bad << '\n';
	return 0;
}
