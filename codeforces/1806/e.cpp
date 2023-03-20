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

	template <typename>
	struct isPair : std::false_type {};

	template <typename TypeFirst, typename TypeSecond>
	struct isPair<std::pair<TypeFirst, TypeSecond>> : std::true_type {};

	template <typename Type, typename = std::void_t<>>
	struct isStdHashable : std::false_type {};

	template <typename Type>
	struct isStdHashable<
		Type,
		std::void_t<decltype(std::declval<std::hash<Type>>()(
			std::declval<Type>()))>> : std::true_type {};
}

namespace Rain::Random {
	using Generator = std::mt19937_64;

	// Default, generally-safe generator when one is not supplied by caller.
	inline Generator generator(
		std::chrono::duration_cast<std::chrono::nanoseconds>(
			std::chrono::high_resolution_clock::now().time_since_epoch())
			.count());

	template <typename>
	struct SplitMixHash;

	// Simple function to combine two 32 or 64-bit hashes, based on
	// <https://stackoverflow.com/questions/5889238/why-is-xor-the-default-way-to-combine-hashes>
	// from Boost.
	//
	// SIZE_T_SIZE is a default argument which forces a substitution, and thus
	// SFINAE.
	template <
		std::size_t SIZE_T_SIZE = sizeof(std::size_t),
		typename std::enable_if<SIZE_T_SIZE == 8>::type * = nullptr>
	static inline std::size_t combineHash(std::size_t &seed, std::size_t next) {
		return seed ^= next + 0x517cc1b727220a95 + (seed << 6) + (seed >> 2);
	}
	template <
		typename Type,
		std::size_t SIZE_T_SIZE = sizeof(std::size_t),
		typename std::enable_if<SIZE_T_SIZE == 4>::type * = nullptr>
	static inline std::size_t combineHash(std::size_t &seed, std::size_t next) {
		return seed ^= next + 0x9e3779b9 + (seed << 6) + (seed >> 2);
	}

	// SFINAE enables SplitMixHash for all std::hash-able types, and defines
	// custom unwrapping hash for pairs/containers/etc.
	template <typename Type>
	struct SplitMixHash {
		// 64-bit hash from <https://codeforces.com/blog/entry/62393>.
		template <
			typename TypeInner = Type,
			std::size_t SIZE_T_SIZE = sizeof(std::size_t),
			typename std::enable_if<Functional::isStdHashable<TypeInner>::value>::type
				* = nullptr,
			typename std::enable_if<SIZE_T_SIZE == 8>::type * = nullptr>
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

		// 32-bit hash from <https://groups.google.com/g/prng/c/VFjdFmbMgZI>.
		template <
			typename TypeInner = Type,
			std::size_t SIZE_T_SIZE = sizeof(std::size_t),
			typename std::enable_if<Functional::isStdHashable<TypeInner>::value>::type
				* = nullptr,
			typename std::enable_if<SIZE_T_SIZE == 4>::type * = nullptr>
		std::size_t operator()(Type const &value) const {
			static const std::size_t FIXED_RANDOM(
				std::chrono::duration_cast<std::chrono::nanoseconds>(
					std::chrono::high_resolution_clock::now().time_since_epoch())
					.count());
			std::size_t hash{std::hash<Type>{}(value)};
			hash += FIXED_RANDOM + 0x9e3779b9;
			hash = (hash ^ (hash >> 16)) * 0x85ebca6b;
			hash = (hash ^ (hash >> 13)) * 0xc2b2ae35;
			return hash ^ (hash >> 16);
		}

		// Unwraps a pair.
		template <
			typename TypeInner = Type,
			typename std::enable_if<
				!Functional::isStdHashable<TypeInner>::value &&
				Functional::isPair<TypeInner>::value>::type * = nullptr>
		std::size_t operator()(Type const &value) const {
			std::size_t result{0};
			combineHash(result, SplitMixHash<decltype(value.first)>{}(value.first));
			combineHash(result, SplitMixHash<decltype(value.second)>{}(value.second));
			return result;
		}

		// Unwraps a container.
		template <
			typename TypeInner = Type,
			typename std::enable_if<
				!Functional::isStdHashable<TypeInner>::value &&
				!Functional::isPair<TypeInner>::value &&
				Functional::isConstIterable<TypeInner>::value>::type * = nullptr>
		std::size_t operator()(Type const &value) const {
			std::size_t result{0};
			for (auto const &i : value) {
				combineHash(result, SplitMixHash<decltype(i)>{}(i));
			}
			return result;
		}
	};

	// Saves the use of std::remove_reference and std::remove_const.
	template <typename Type>
	struct SplitMixHash<Type &> : SplitMixHash<Type> {};
	template <typename Type>
	struct SplitMixHash<Type const> : SplitMixHash<Type> {};
}

// namespace Rain::Algorithm {
// 	// From <https://arxiv.org/pdf/2107.01250.pdf>. Value must be
// 	// default-constructable. The load of the table is ideally 1 - 1 /
// IDEAL_LOAD. 	template < 		typename Key, 		typename Value, 		std::size_t
// IDEAL_LOAD = 4, 		std::size_t INITIAL_SIZE = 4 * IDEAL_LOAD, 		typename
// Hasher = Random::SplitMixHash<Key>, 		typename Equator = std::equal_to<Key>>
// class GraveyardHashMap { 		public: 		Hasher HASHER{}; 		Equator
// EQUATOR{};

// 		Key EMPTY, TOMBSTONE;
// 		std::vector<std::pair<Key, Value>> table;
// 		std::size_t untilRebuild{1}, residents{0};

// 		// Insert into a specified table.
// 		std::pair<bool, Value &> insertInto(
// 			std::vector<std::pair<Key, Value>> &table,
// 			Key const &key,
// 			Value const &value) {
// 			std::size_t initial{HASHER(key) % table.size()};
// 			for (std::size_t i{initial}; i < table.size(); i++) {
// 				if (
// 					EQUATOR(table[i].first, this->EMPTY) ||
// 					EQUATOR(table[i].first, this->TOMBSTONE)) {
// 					table[i] = {key, value};
// 					return {true, table[i].second};
// 				} else if (EQUATOR(table[i].first, key)) {
// 					return {false, table[i].second};
// 				}
// 			}
// 			for (std::size_t i{0}; i < initial; i++) {
// 				if (
// 					EQUATOR(table[i].first, this->EMPTY) ||
// 					EQUATOR(table[i].first, this->TOMBSTONE)) {
// 					table[i] = {key, value};
// 					this->residents++;
// 					return {true, table[i].second};
// 				} else if (EQUATOR(table[i].first, key)) {
// 					return {false, table[i].second};
// 				}
// 			}

// 			// If the table is full, throw.
// 			throw std::length_error("");
// 		}

// 		// Increment rebuild counter and maybe rebuild.
// 		void decrementRebuild() {
// 			this->untilRebuild--;
// 			if (this->untilRebuild == 0) {
// 				// Rebuild.
// 				std::vector<std::pair<Key, Value>> newTable(
// 					max(
// 						this->table.size(),
// 						this->residents * IDEAL_LOAD / (IDEAL_LOAD - 1)),
// 					{this->EMPTY, Value{}});
// 				for (std::size_t i{0}; i < this->table.size(); i++) {
// 					if (
// 						!EQUATOR(this->table[i].first, this->EMPTY) &&
// 						!EQUATOR(this->table[i].first, this->TOMBSTONE)) {
// 						this->insertInto(
// 							newTable, this->table[i].first, this->table[i].second);
// 					}
// 				}

// 				swap(this->table, newTable);
// 				this->untilRebuild = this->table.size() / (4 * IDEAL_LOAD);
// 			}
// 		}

// 		public:
// 		GraveyardHashMap(Key const &empty, Key const &tombstone)
// 				: EMPTY(empty), TOMBSTONE(tombstone) {
// 			this->table.resize(INITIAL_SIZE, {EMPTY, Value{}});
// 			for (std::size_t i{0}; i < this->table.size() / (2 * IDEAL_LOAD); i++) {
// 				this->table[i * 2 * IDEAL_LOAD].first = TOMBSTONE;
// 			}
// 		}
// 		// GraveyardHashMap(GraveyardHashMap const &) = delete;
// 		// GraveyardHashMap &operator=(GraveyardHashMap const &) = delete;

// 		// Returns a reference to either an existing element or newly inserted
// one.
// 		// More efficient than running count, then insert.
// 		Value &operator[](Key const &key) {
// 			this->decrementRebuild();

// 			std::size_t initial{HASHER(key) % this->table.size()},
// 				firstInsertable{SIZE_MAX};
// 			bool notFound{false};
// 			for (std::size_t i{initial}; i < this->table.size(); i++) {
// 				if (EQUATOR(this->table[i].first, this->EMPTY)) {
// 					if (firstInsertable == SIZE_MAX) {
// 						firstInsertable = i;
// 					}
// 					notFound = true;
// 					break;
// 				} else if (
// 					firstInsertable == SIZE_MAX &&
// 					EQUATOR(this->table[i].first, this->TOMBSTONE)) {
// 					firstInsertable = i;
// 				} else if (EQUATOR(this->table[i].first, key)) {
// 					return this->table[i].second;
// 				}
// 			}
// 			if (!notFound) {
// 				for (std::size_t i{0}; i < initial; i++) {
// 					if (EQUATOR(this->table[i].first, this->EMPTY)) {
// 						if (firstInsertable == SIZE_MAX) {
// 							firstInsertable = i;
// 						}
// 						notFound = true;
// 						break;
// 					} else if (
// 						firstInsertable == SIZE_MAX &&
// 						EQUATOR(this->table[i].first, this->TOMBSTONE)) {
// 						firstInsertable = i;
// 					} else if (EQUATOR(this->table[i].first, key)) {
// 						return this->table[i].second;
// 					}
// 				}
// 			}

// 			// We should insert if not found and insertable.
// 			if (notFound && firstInsertable != SIZE_MAX) {
// 				this->residents++;
// 				this->table[firstInsertable].first = key;
// 				return this->table[firstInsertable].second;
// 			}

// 			throw std::length_error("");
// 		}

// 		// Returns (true, R) if insertion of a new key happened, and (false, R) if
// 		// an old element R prevented insertion.
// 		std::pair<bool, Value &> insert(Key const &key, Value const &value) {
// 			this->decrementRebuild();
// 			auto result{this->insertInto(this->table, key, value)};
// 			if (result.first) {
// 				this->residents++;
// 			}
// 			return result;
// 		}

// 		// Erases a key-value pair if it exists. Does nothing otherwise.
// 		void erase(Key const &key) {
// 			this->decrementRebuild();

// 			std::size_t initial{HASHER(key) % this->table.size()};
// 			for (std::size_t i{initial}; i < this->table.size(); i++) {
// 				if (EQUATOR(this->table[i].first, this->EMPTY)) {
// 					return;
// 				} else if (EQUATOR(this->table[i].first, key)) {
// 					this->table[i].first = this->TOMBSTONE;
// 					this->residents--;
// 					return;
// 				}
// 			}
// 			for (std::size_t i{0}; i < initial; i++) {
// 				if (EQUATOR(this->table[i].first, this->EMPTY)) {
// 					return;
// 				} else if (EQUATOR(this->table[i].first, key)) {
// 					this->table[i].first = this->TOMBSTONE;
// 					this->residents--;
// 					return;
// 				}
// 			}
// 		}

// 		// Returns 0 if the key does not exist, otherwise returns 1.
// 		std::size_t count(Key const &key) {
// 			std::size_t initial{HASHER(key) % this->table.size()};
// 			for (std::size_t i{initial}; i < this->table.size(); i++) {
// 				if (EQUATOR(this->table[i].first, this->EMPTY)) {
// 					return 0;
// 				} else if (EQUATOR(this->table[i].first, key)) {
// 					return 1;
// 				}
// 			}
// 			for (std::size_t i{0}; i < initial; i++) {
// 				if (EQUATOR(this->table[i].first, this->EMPTY)) {
// 					return 0;
// 				} else if (EQUATOR(this->table[i].first, key)) {
// 					return 1;
// 				}
// 			}
// 			return 0;
// 		}
// 	};
// }

using namespace Rain::Random;
// using namespace Rain::Algorithm;

#if __has_include(<ext/pb_ds/assoc_container.hpp>)
#include <ext/pb_ds/assoc_container.hpp>
template <typename Key, typename Value, typename Hasher = std::hash<Key>>
using UnorderedMap = __gnu_pbds::gp_hash_table<Key, Value, Hasher>;
#else
template <typename Key, typename Value, typename Hasher = std::hash<Key>>
using UnorderedMap = std::unordered_map<Key, Value, Hasher>;
#endif

array<int, 100000> P, H, CH;
array<LL, 100000> A;
array<vector<int>, 100000> E, QQ;
UnorderedMap<pair<int, int>, LL, SplitMixHash<pair<int, int>>> Z;
array<pair<int, int>, 100000> Q, NH;

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

	// Z.resize(100000, GraveyardHashMap<int, LL>(INT_MAX, INT_MAX - 1));

	LL N, Q_;
	cin >> N >> Q_;
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

	RF(i, 0, N) {
		NH[i] = {H[i], i};
		CH[H[i]]++;
	}
	sort(NH.begin(), NH.begin() + N);
	// #ifdef ONLINE_JUDGE
	// 	Z.resize(30000000);
	// #else
	// 	Z.reserve(30000000);
	// #endif

	RF(i, 0, Q_) {
		cin >> Q[i].first >> Q[i].second;
		Q[i].first--;
		Q[i].second--;
		if (Q[i].first > Q[i].second) {
			swap(Q[i].first, Q[i].second);
		}
		auto X{Q[i]};
		while (X.first != -1 && Z.find(X) == Z.end()) {
			Z[X] = -1;
			QQ[X.first].push_back(X.second);
			X = {P[X.first], P[X.second]};
			if (X.first > X.second) {
				swap(X.first, X.second);
			}
		}
	}

	Z[{0, 0}] = A[0] * A[0];
	RF(i, 1, N) {
		for (auto &j : QQ[NH[i].second]) {
			pair<LL, LL> X{P[NH[i].second], P[j]};
			if (X.first > X.second) {
				swap(X.first, X.second);
			}
			Z[{NH[i].second, j}] = Z[X] + A[NH[i].second] * A[j];
		}
	}

	RF(i, 0, Q_) {
		cout << Z[Q[i]] << '\n';
	}
	return 0;
}
