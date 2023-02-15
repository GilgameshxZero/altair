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

using LL = int;
using LD = long double;

#define RF(x, from, to)                                                      \
	for (long long x = from, _to = to, _delta{x < _to ? 1LL : -1LL}; x != _to; \
			 x += _delta)

using namespace std;

namespace Rain {
	// Inline namespaces are implicitly accessible by the parent namespace.
	inline namespace Literal {
		// Inject std literals into the Rain namespace.
		using namespace std::literals;

		// User-defined literals.
		inline constexpr std::size_t operator"" _zu(unsigned long long value) {
			return static_cast<std::size_t>(value);
		}
		inline std::regex operator"" _re(char const *value, std::size_t) {
			return std::regex(value);
		}
	}
}

namespace Rain::Algorithm {
	// Most significant 1-bit for unsigned integral types of at most long long in
	// size. Undefined result if x = 0.
	template <typename Integer>
	inline std::size_t mostSignificant1BitIdx(Integer const x) {
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
	inline std::size_t leastSignificant1BitIdx(Integer const x) {
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
	inline std::size_t bitPopcount(Integer const x) {
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

namespace Rain::Algorithm {
	// Segment tree without lazy propagation nor range updates.
	template <
		typename Value,
		typename Update,
		typename Result,
		Value DEFAULT_VALUE,
		// Aggregate values from two children while retracing an update. Aggregating
		// with a default Value should do nothing.
		void (*aggregateValues)(
			typename std::vector<Value>::reference,
			Value const &,
			Value const &),
		// Aggregate two results from queries on children. Aggregating with a
		// Result converted from a default Value should do nothing.
		Result (*aggregateResults)(Result const &, Result const &),
		// Apply an update fully to a node.
		void (*apply)(typename std::vector<Value>::reference, Update const &)>
	class SegmentTree {
		protected:
		// Aggregate values at each node.
		std::vector<Value> values;

		public:
		// Segment tree for a segment array of size size.
		SegmentTree(std::size_t const size)
				: values(
						1_zu << (mostSignificant1BitIdx(size - 1) + 2),
						DEFAULT_VALUE) {}

		// Queries an inclusive range.
		Result query(std::size_t left, std::size_t right) {
			Value resLeft{DEFAULT_VALUE}, resRight{DEFAULT_VALUE};
			for (left += this->values.size() / 2,
					 right += this->values.size() / 2 + 1;
					 left < right;
					 left /= 2, right /= 2) {
				if (left % 2 == 1) {
					resLeft = aggregateResults(resLeft, this->values[left++]);
				}
				if (right % 2 == 1) {
					resRight = aggregateResults(resRight, this->values[--right]);
				}
			}
			return aggregateResults(resLeft, resRight);
		}

		// Point update an index.
		void update(std::size_t idx, Update const &update) {
			idx += this->values.size() / 2;
			apply(this->values[idx], update);
			for (idx /= 2; idx >= 1; idx /= 2) {
				aggregateValues(
					this->values[idx], this->values[idx * 2], this->values[idx * 2 + 1]);
			}
		}
	};
}

void maxAggregateValues(
	typename std::vector<LL>::reference value,
	LL const &left,
	LL const &right) {
	value = max(left, right);
}
LL maxAggregateResults(LL const &left, LL const &right) {
	return max(left, right);
}
void maxApply(typename std::vector<LL>::reference value, LL const &update) {
	value = max(value, update);
}
void minAggregateValues(
	typename std::vector<LL>::reference value,
	LL const &left,
	LL const &right) {
	value = min(left, right);
}
LL minAggregateResults(LL const &left, LL const &right) {
	return min(left, right);
}
void minApply(typename std::vector<LL>::reference value, LL const &update) {
	value = min(value, update);
}

using MaxSegTree = Rain::Algorithm::SegmentTree<
	LL,
	LL,
	LL,
	-1,
	maxAggregateValues,
	maxAggregateResults,
	maxApply>;
using MinSegTree = Rain::Algorithm::SegmentTree<
	LL,
	LL,
	LL,
	INT_MAX,
	minAggregateValues,
	minAggregateResults,
	minApply>;

int main(int, char const *[]) {
#if !defined(ONLINEJUDGE) && (defined(__APPLE__) || defined(__MACH__))
	std::freopen("../build/i.default.txt", "r", stdin);
	std::freopen("../build/o.default.txt", "w", stdout);
#endif

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	LL N, Q;
	cin >> N >> Q;
	vector<LL> A(N);
	RF(i, 0, N) {
		cin >> A[i];
	}
	vector<pair<pair<LL, LL>, LL>> Qs(Q);
	vector<vector<pair<LL, LL>>> Qi(N);
	RF(i, 0, Q) {
		LL L, R;
		cin >> L >> R;
		Qi[R - 1].push_back({L - 1, i});
	}

	MaxSegTree maxst(N + 1);
	MinSegTree minst(N);
	LL rstTo{-1};
	vector<LL> ans(Q);
	RF(i, 0, N) {
		LL limit{N};
		while (true) {
			LL j{maxst.query(A[i] + 1, limit)};
			if (j == -1) {
				break;
			}
			minst.update(j, A[j] - A[i]);
			limit = (A[i] + A[j] + 1) / 2 - 1;
		}

		limit = 1;
		while (true) {
			LL j{maxst.query(limit, A[i] - 1)};
			if (j == -1) {
				break;
			}
			minst.update(j, A[i] - A[j]);
			limit = (A[i] + A[j]) / 2 + 1;
		}

		maxst.update(A[i], i);

		RF(j, 0, Qi[i].size()) {
			ans[Qi[i][j].second] = minst.query(Qi[i][j].first, i);
		}
	}

	RF(i, 0, Q) {
		cout << ans[i] << '\n';
	}
	return 0;
}
