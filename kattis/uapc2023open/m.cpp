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
using namespace std;

#pragma hdrstop	 // ------------------------------------------------------------

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

namespace Rain::Algorithm {
	// Segment tree with lazy propagation, supporting range queries and range
	// updates in O(ln N) and O(N) memory.
	//
	// RVO helps with heavier Result types, but is not guaranteed. Value must be
	// zero-initialized to be valid. Update must be light-copyable.
	//
	// Index 0 is unused. For parent i, 2i is the left child and 2i + 1 is the
	// right child. The queries and updates themselves are inclusive and 0-indexed
	// on the represented range.
	//
	// Further performance can be had with manual inlining of the five functions,
	// which are typically not inlined by the compiler due to their virtual-ness.
	// Forced initialization of underlying vectors can be replaced with
	// std::array, and on GCC, loop unrolling may be turned on for further
	// optimization. Removing functions which support lazy propagation will
	// further speed up this implementation.
	//
	// Additionally, consider using the non-lazy version of this tree if range
	// updates are not required.
	//
	// The default Value should be one which serves as an identity when acted upon
	// by aggregate, apply, and propagate, and its converted Result should also be
	// an identity w.r.t aggregate.
	template <
		typename Value,
		typename Update,
		typename Result,
		Value DEFAULT_VALUE,
		// Aggregate values from two children while retracing an update. Aggregating
		// with a default Value should do nothing.
		void (*retrace)(
			std::size_t const,
			typename std::vector<Value>::reference,
			Value const &,
			Value const &,
			std::pair<std::size_t, std::size_t> const &),
		// Aggregate two results from queries on children. Aggregating with a
		// Result converted from a default Value should do nothing.
		Result (*aggregate)(
			std::size_t const,
			Result const &,
			Result const &,
			std::pair<std::size_t, std::size_t> const &),
		// Propagate an update on a parent to its two children. Lazy bits for the
		// children are set beforehand, but can be unset in the function.
		void (*split)(
			std::size_t const,
			Update const &,
			typename std::vector<Update>::reference,
			typename std::vector<Update>::reference,
			std::pair<std::size_t, std::size_t> const &),
		// Apply an update fully to a lazy node.
		void (*apply)(
			std::size_t const,
			typename std::vector<Value>::reference,
			Update const &,
			std::pair<std::size_t, std::size_t> const &),
		// Convert a Value at a leaf node to a Result for base case queries.
		Result (*convert)(std::size_t const, Value const &)>
	class SegmentTreeLazy {
		protected:
		// Aggregate values at each node.
		std::vector<Value> values;

		// True iff node has a pending lazy update to propagate.
		std::vector<bool> lazy;

		// Lazily-stored updates.
		std::vector<Update> updates;

		public:
		// Segment tree for a segment array of size size.
		SegmentTreeLazy(std::size_t const size)
				: values(1_zu << (mostSignificant1BitIdx(size - 1) + 2), DEFAULT_VALUE),
					lazy(values.size(), false),
					updates(values.size()) {}

		// Queries an inclusive range, propagating if necessary then aggregating.
		inline Result query(std::size_t const left, std::size_t const right) {
			return this->query(1, left, right, {0, this->values.size() / 2 - 1});
		}

		// Lazy update an inclusive range.
		inline void update(
			std::size_t const left,
			std::size_t const right,
			Update const &update) {
			this->update(1, left, right, update, {0, this->values.size() / 2 - 1});
		}

		private:
		// Conditionally propagate a node if it is not a leaf and has an update to
		// propagate.
		inline void propagate(
			std::size_t const node,
			std::pair<std::size_t, std::size_t> const &range) {
			if (!this->lazy[node]) {
				return;
			}

			// Propagating on a leaf applies it immediately. Otherwise, split the
			// update to children.
			if (node < this->values.size() / 2) {
				this->lazy[node * 2] = this->lazy[node * 2 + 1] = true;
				split(
					node,
					this->updates[node],
					this->updates[node * 2],
					this->updates[node * 2 + 1],
					range);
			}

			// Clear the update at this node so it doesn’t interfere with later
			// propagations.
			apply(node, this->values[node], this->updates[node], range);
			this->updates[node] = {};
			this->lazy[node] = false;
		}

		// Internal recursive query. range is the coverage range of the current node
		// and is inclusive.
		Result query(
			std::size_t const node,
			std::size_t const left,
			std::size_t const right,
			std::pair<std::size_t, std::size_t> const &range) {
			if (right < range.first || left > range.second) {
				return DEFAULT_VALUE;
			}
			this->propagate(node, range);

			// Base case.
			if (range.first >= left && range.second <= right) {
				return convert(node, this->values[node]);
			}

			std::size_t mid{(range.first + range.second) / 2};
			return aggregate(
				node,
				this->query(node * 2, left, right, {range.first, mid}),
				this->query(node * 2 + 1, left, right, {mid + 1, range.second}),
				range);
		}

		// Internal recursive update.
		void update(
			std::size_t const node,
			std::size_t const left,
			std::size_t const right,
			Update const &update,
			std::pair<std::size_t, std::size_t> const &range) {
			if (right < range.first || left > range.second) {
				return;
			}
			// Propagate even if this node is fully covered, since we don’t have a
			// function to combine two updates.
			this->propagate(node, range);

			// Base case.
			if (range.first >= left && range.second <= right) {
				// This node is already non-lazy since it was just propagated.
				this->updates[node] = update;
				this->lazy[node] = true;
			} else {
				std::size_t mid{(range.first + range.second) / 2};
				this->update(node * 2, left, right, update, {range.first, mid});
				this->update(
					node * 2 + 1, left, right, update, {mid + 1, range.second});

				// Substitute parent value with aggregate after update has been
				// propagated. O(1). Guaranteed at least one child, or else the base
				// case would have triggered.
				this->propagate(node * 2, {range.first, mid});
				this->propagate(node * 2 + 1, {mid + 1, range.second});
				retrace(
					node,
					this->values[node],
					this->values[node * 2],
					this->values[node * 2 + 1],
					range);
			}
		}
	};
}

using namespace Rain::Algorithm;

void retrace(
	std::size_t const,
	typename std::vector<LL>::reference node,
	LL const &left,
	LL const &right,
	std::pair<std::size_t, std::size_t> const &) {
	node = max(left, right);
}
LL aggregate(
	std::size_t const,
	LL const &left,
	LL const &right,
	std::pair<std::size_t, std::size_t> const &) {
	return max(left, right);
}
void split(
	std::size_t const,
	LL const &update,
	typename std::vector<LL>::reference left,
	typename std::vector<LL>::reference right,
	std::pair<std::size_t, std::size_t> const &) {
	left = right = update;
}
void apply(
	std::size_t const,
	typename std::vector<LL>::reference node,
	LL const &update,
	std::pair<std::size_t, std::size_t> const &) {
	node = max(node, update);
}
LL convert(std::size_t const, LL const &node) {
	return node;
}

using ST =
	SegmentTreeLazy<LL, LL, LL, 0, retrace, aggregate, split, apply, convert>;

int main(int, char const *[]) {
#if !defined(ONLINEJUDGE) && (defined(__APPLE__) || defined(__MACH__))
	std::freopen("../build/i.default.txt", "r", stdin);
	std::freopen("../build/o.default.txt", "w", stdout);
#endif

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	LL N;
	cin >> N;
	unordered_set<LL> crits;
	vector<pair<LL, LL>> drops(N);
	RF(i, 0, N) {
		cin >> drops[i].first >> drops[i].second;
		crits.insert(drops[i].first);
		crits.insert(drops[i].first + drops[i].second - 1);
	}
	vector<LL> c2;
	unordered_map<LL, LL> c3;
	for (auto const &i : crits) {
		c2.push_back(i);
	}
	sort(c2.begin(), c2.end());
	RF(i, 0, c2.size()) {
		c3[c2[i]] = i;
	}

	ST st(c2.size());
	RF(i, 0, N) {
		LL top{
			st.query(c3[drops[i].first], c3[drops[i].first + drops[i].second - 1])};
		st.update(
			c3[drops[i].first],
			c3[drops[i].first + drops[i].second - 1],
			top + drops[i].second);
		cout << st.query(0, c2.size() - 1) << '\n';
	}

	return 0;
}
