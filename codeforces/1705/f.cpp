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

using namespace Rain::Random;

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
		rp[i].first = uniform_real_distribution<LD>{0, 1}(generator);
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
	auto count1{[&](LL i) {
		Q++;
		string S(N, 'F');
		S[perm[i]] = 'T';
		// cout << S << endl;
		LL ans{0};
		RF(j, 0, SS.length()) {
			ans += S[j] == SS[j];
		}
		// cin >> ans;
		return (ans + totaltrue - (N - 1)) / 2;
	}};
	auto count2{[&](LL i) {
		Q++;
		string S(N, 'F');
		S[perm[i]] = S[perm[i + 1]] = 'T';
		// cout << S << endl;
		LL ans{0};
		RF(j, 0, SS.length()) {
			ans += S[j] == SS[j];
		}
		// cin >> ans;
		return (ans + totaltrue - (N - 2)) / 2;
	}};

	LL E2{0}, E1{0};
	map<LL, LL> cnt;
	vector<bool> ans(N);
	for (LL i{0}; i < N;) {
		if (i == N - 1) {
			ans[perm[i]] = count1(i) == 1;
			i += 1;
			continue;
		}
		LL res{count2(i)};
		if (res == 0) {
			E2++;
			cnt[1]++;
			ans[perm[i]] = ans[perm[i + 1]] = false;
			i += 2;
			continue;
		} else if (res == 2) {
			E2++;
			cnt[1]++;
			ans[perm[i]] = ans[perm[i + 1]] = true;
			i += 2;
			continue;
		}

		E1++;
		LL j{i + 1};
		while (res == 1) {
			if (j == N - 1) {
				ans[perm[j]] = count1(j) == 1;
				break;
			}
			res = count2(j);
			if (res == 0) {
				ans[perm[j]] = ans[perm[j + 1]] = false;
				break;
			} else if (res == 2) {
				ans[perm[j]] = ans[perm[j + 1]] = true;
				break;
			}
			E1++;
			j++;
		}

		RF(k, j - 1, i - 1) {
			ans[perm[k]] = !ans[perm[k + 1]];
		}
		cnt[j - i + 1]++;
		i = j + 2;
	}

	// RF(i, 0, N) {
	// 	cout << (ans[i] ? 'T' : 'F');
	// }
	cout << Q + 1 << ' ' << E2 << ' ' << E1 << '\n';
	for(auto const &i : cnt) {
		cout << i.first << ' ' << i.second << '\n';
	}
	return 0;
}
