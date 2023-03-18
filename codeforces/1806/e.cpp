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

vector<LL> A, P, H;
vector<pair<LL, LL>> Q;
vector<vector<LL>> E;
unordered_map<pair<LL, LL>, LL, PairHash<LL, LL>> Z;
unordered_map<pair<LL, LL>, pair<LL, LL>, PairHash<LL, LL>> QD;
vector<vector<LL>> QH;

void dfsH(LL cur) {
	if (P[cur] != -1) {
		H[cur] = H[P[cur]] + 1;
	}
	for (auto const &i : E[cur]) {
		dfsH(i);
	}
}

int main(int, char const *[]) {
#if !defined(ONLINEJUDGE) && (defined(__APPLE__) || defined(__MACH__))
	std::freopen("../build/i.default.txt", "r", stdin);
	std::freopen("../build/o.default.txt", "w", stdout);
#endif

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	LL N, Q_;
	cin >> N >> Q_;
	A.resize(N);
	P.resize(N);
	H.resize(N);
	E.resize(N);
	P[0] = -1;
	RF(i, 0, N) {
		cin >> A[i];
	}
	RF(i, 1, N) {
		cin >> P[i];
		P[i]--;
		E[P[i]].push_back(i);
	}
	H[0] = 0;
	dfsH(0);

	Z.resize(Q_);
	QD.resize(Q_, -1);
	Q.resize(Q_);
	QH.resize(N);
	RF(i, 0, Q.size()) {
		cin >> Q[i].first >> Q[i].second;
		Q[i].first--;
		Q[i].second--;
		auto j{QM.find(Q[i])};
		if (j != QM.end()) {
			QD[i] = j->second;
		} else {
			QM[Q[i]] = i;
			QH[H[Q[i].first]].push_back(i);
		}
	}

	while (!QH.empty()) {
		while (!QH.back().empty()) {
			LL q = QH.back().back();
			QH.back().pop_back();
			QM.erase(Q[q]);
			Z[q] += A[Q[q].first] * A[Q[q].second];
			Q[q].first = P[Q[q].first];
			Q[q].second = P[Q[q].second];
			if (Q[q].first == -1) {
				continue;
			}
			auto i{QM.find(Q[q])};
			if (i != QM.end()) {
				QD[q] = i->second;
			} else {
				QM[Q[q]] = q;
				QH[H[Q[q].first]].push_back(q);
			}
		}
		QH.pop_back();
	}

	return 0;
}
