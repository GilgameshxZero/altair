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

// Implementation for a prime modulus ring over the integers, supporting basic
// operations add, subtract, multiply in O(1) and divide in O(ln N).
//
// Integer must be large enough to store (primeModulus - 1)^2.
//
// For O(1) division, cache multiplicative inverses and multiply with those.
template <typename Integer, Integer primeModulus>
class ModRing {
	public:
	Integer value;

	// Add primeModulus first to wrap back around in the case of "negative"
	// unsigned Integer.
	ModRing(Integer const value = 0)
			: value((primeModulus + value) % primeModulus) {}

	// O(ln N) exponentiation.
	static ModRing<Integer, primeModulus> power(
		ModRing<Integer, primeModulus> const base,
		Integer const exponent) {
		if (exponent == 0) {
			return {1};
		}
		auto half = power(base, exponent / 2);
		if (exponent % 2 == 0) {
			return half * half;
		} else {
			return half * half * base;
		}
	}

	ModRing<Integer, primeModulus> operator+(Integer const other) const {
		return *this + ModRing<Integer, primeModulus>(other);
	}
	ModRing<Integer, primeModulus> operator+(Integer const other) {
		return *this + ModRing<Integer, primeModulus>(other);
	}
	ModRing<Integer, primeModulus> operator+(
		ModRing<Integer, primeModulus> const other) {
		return {this->value + other.value};
	}
	ModRing<Integer, primeModulus> operator+=(
		ModRing<Integer, primeModulus> const other) {
		return *this = *this + other;
	}
	ModRing<Integer, primeModulus> operator++() { return *this += 1; }
	ModRing<Integer, primeModulus> operator++(int) {
		auto tmp(*this);
		*this += 1;
		return tmp;
	}
	ModRing<Integer, primeModulus> operator-(Integer const other) const {
		return *this - ModRing<Integer, primeModulus>(other);
	}
	ModRing<Integer, primeModulus> operator-(Integer const other) {
		return *this - ModRing<Integer, primeModulus>(other);
	}
	ModRing<Integer, primeModulus> operator-(
		ModRing<Integer, primeModulus> const other) {
		return {this->value - other.value};
	}
	ModRing<Integer, primeModulus> operator-=(
		ModRing<Integer, primeModulus> const other) {
		return *this = *this - other;
	}
	ModRing<Integer, primeModulus> operator--() { return *this -= 1; }
	ModRing<Integer, primeModulus> operator--(int) {
		auto tmp(*this);
		*this -= 1;
		return tmp;
	}
	ModRing<Integer, primeModulus> operator*(Integer const other) const {
		return *this * ModRing<Integer, primeModulus>(other);
	}
	ModRing<Integer, primeModulus> operator*(Integer const other) {
		return *this * ModRing<Integer, primeModulus>(other);
	}
	ModRing<Integer, primeModulus> operator*(
		ModRing<Integer, primeModulus> const other) {
		return {this->value * other.value};
	}
	ModRing<Integer, primeModulus> operator*=(
		ModRing<Integer, primeModulus> const other) {
		return *this = *this * other;
	}
	ModRing<Integer, primeModulus> operator/(Integer const other) const {
		return *this / ModRing<Integer, primeModulus>(other);
	}
	ModRing<Integer, primeModulus> operator/(Integer const other) {
		return *this / ModRing<Integer, primeModulus>(other);
	}
	ModRing<Integer, primeModulus> operator/(
		ModRing<Integer, primeModulus> const other) {
		return *this * power(other, primeModulus - 2);
	}
	ModRing<Integer, primeModulus> operator/=(
		ModRing<Integer, primeModulus> const other) {
		return *this = *this / other;
	}

	bool operator==(Integer const other) {
		return *this == ModRing<Integer, primeModulus>(other);
	}
	bool operator==(ModRing<Integer, primeModulus> const other) {
		return this->value == other.value;
	}
};

template <typename LeftInteger, typename Integer, Integer primeModulus>
ModRing<Integer, primeModulus> operator+(
	LeftInteger const left,
	ModRing<Integer, primeModulus> const right) {
	return ModRing<Integer, primeModulus>(left) + right;
}

template <typename LeftInteger, typename Integer, Integer primeModulus>
ModRing<Integer, primeModulus> operator-(
	LeftInteger const left,
	ModRing<Integer, primeModulus> const right) {
	return ModRing<Integer, primeModulus>(left) - right;
}

template <typename LeftInteger, typename Integer, Integer primeModulus>
ModRing<Integer, primeModulus> operator*(
	LeftInteger const left,
	ModRing<Integer, primeModulus> const right) {
	return ModRing<Integer, primeModulus>(left) * right;
}

template <typename LeftInteger, typename Integer, Integer primeModulus>
ModRing<Integer, primeModulus> operator/(
	LeftInteger const left,
	ModRing<Integer, primeModulus> const right) {
	return ModRing<Integer, primeModulus>(left) / right;
}

// Ease-of-use streaming operator.
template <typename Integer, Integer primeModulus>
inline std::ostream &operator<<(
	std::ostream &stream,
	ModRing<Integer, primeModulus> const right) {
	return stream << right.value;
}

inline constexpr std::size_t operator"" _zu(unsigned long long value) {
	return static_cast<std::size_t>(value);
}

// Segment tree with lazy propagation, supporting range queries and range
// updates in O(ln N) and O(N) memory.
//
// RVO helps with heavier Result types, but is not guaranteed. Value must be
// zero-initialized to be valid. Update must be light-copyable.
//
// Index 0 is unused. For parent i, 2i is the left child and 2i + 1 is the
// right child.
//
// Further performance can be had with manual inlining of the five functions,
// which are typically not inlined by the compiler due to their virtual-ness.
// Forced initialization of underlying vectors can be replaced with
// std::array, and on GCC, loop unrolling may be turned on for further
// optimization.
template <typename _Value, typename _Update, typename _Result = _Value>
class SegmentTree {
	private:
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

	protected:
	using Value = _Value;
	using Update = _Update;
	using Result = _Result;

	// Aggregate values at each node.
	std::vector<Value> values;

	// True iff node has a pending lazy update to propagate.
	std::vector<bool> lazy;

	// Lazily-stored updates.
	std::vector<Update> updates;

	// Aggregate values from two children while retracing an update. Aggregating
	// with a default-initialized Value or Update should do nothing.
	virtual void aggregate(
		std::size_t const node,
		typename std::vector<Value>::reference value,
		Value const &left,
		Value const &right,
		std::pair<std::size_t, std::size_t> const &range) = 0;

	// Aggregate two results from queries on children. Aggregating with a
	// default-initialized Result should do nothing.
	virtual Result aggregate(
		std::size_t const node,
		Result const &left,
		Result const &right,
		std::pair<std::size_t, std::size_t> const &range) = 0;

	// Propagate an update on a parent to its two children. Lazy bits for the
	// children are set beforehand, but can be unset in the function.
	virtual void split(
		std::size_t const node,
		Update const &update,
		typename std::vector<Update>::reference left,
		typename std::vector<Update>::reference right,
		std::pair<std::size_t, std::size_t> const &range) = 0;

	// Convert a Value at a leaf node to a Result for base case queries.
	virtual Result convert(std::size_t const node, Value const &value) = 0;

	// Apply an update fully to a lazy node.
	virtual void apply(
		std::size_t const node,
		typename std::vector<Value>::reference value,
		Update const &update,
		std::pair<std::size_t, std::size_t> const &range) = 0;

	public:
	// Segment tree for a segment array of size size.
	SegmentTree(std::size_t const size)
			: values(1_zu << (mostSignificant1BitIdx(size - 1) + 2)),
				lazy(values.size(), false),
				updates(values.size()) {}

	// Queries a range, propagating if necessary then aggregating.
	Result query(std::size_t const left, std::size_t const right) {
		return this->query(1, left, right, {0, this->values.size() / 2 - 1});
	}

	// Lazy update a range.
	void update(
		std::size_t const left,
		std::size_t const right,
		Update const &update) {
		this->update(1, left, right, update, {0, this->values.size() / 2 - 1});
	}

	private:
	// Conditionally propagate a node if it is not a leaf and has an update to
	// propagate.
	void propagate(
		std::size_t const node,
		std::pair<std::size_t, std::size_t> const &range) {
		if (!this->lazy[node]) {
			return;
		}

		// Propagating on a leaf applies it immediately. Otherwise, split the
		// update to children.
		if (node < this->values.size() / 2) {
			this->lazy[node * 2] = this->lazy[node * 2 + 1] = true;
			this->split(
				node,
				this->updates[node],
				this->updates[node * 2],
				this->updates[node * 2 + 1],
				range);
		}

		// Clear the update at this node so it doesn’t interfere with later
		// propagations.
		this->apply(node, this->values[node], this->updates[node], range);
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
			return {};
		}
		this->propagate(node, range);

		// Base case.
		if (range.first >= left && range.second <= right) {
			return this->convert(node, this->values[node]);
		}

		std::size_t mid = (range.first + range.second) / 2;
		return this->aggregate(
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
			std::size_t mid = (range.first + range.second) / 2;
			this->update(node * 2, left, right, update, {range.first, mid});
			this->update(node * 2 + 1, left, right, update, {mid + 1, range.second});

			// Substitute parent value with aggregate after update has been
			// propagated. O(1). Guaranteed at least one child, or else the base
			// case would have triggered.
			this->propagate(node * 2, {range.first, mid});
			this->propagate(node * 2 + 1, {mid + 1, range.second});
			this->aggregate(
				node,
				this->values[node],
				this->values[node * 2],
				this->values[node * 2 + 1],
				range);
		}
	}
};

/* ---------------------------- End of template. ---------------------------- */

using MR = ModRing<LL, 998244353>;

class ST : public SegmentTree<MR, pair<bool, MR>, MR> {
	using SegmentTree<MR, pair<bool, MR>, MR>::SegmentTree;

	// Aggregate values from two children while retracing an update. Aggregating
	// with a default-initialized Value or Update should do nothing.
	virtual void aggregate(
		std::size_t const node,
		typename std::vector<Value>::reference value,
		Value const &left,
		Value const &right,
		std::pair<std::size_t, std::size_t> const &range) override {
		value = left + right;
	}

	// Aggregate two results from queries on children. Aggregating with a
	// default-initialized Result should do nothing.
	virtual Result aggregate(
		std::size_t const node,
		Result const &left,
		Result const &right,
		std::pair<std::size_t, std::size_t> const &range) override {
		return left + right;
	}

	// Propagate an update on a parent to its two children. Lazy bits for the
	// children are set beforehand, but can be unset in the function.
	virtual void split(
		std::size_t const node,
		Update const &update,
		typename std::vector<Update>::reference left,
		typename std::vector<Update>::reference right,
		std::pair<std::size_t, std::size_t> const &range) override {
		left = right = update;
	}

	// Convert a Value at a leaf node to a Result for base case queries.
	virtual Result convert(std::size_t const node, Value const &value) override {
		return value;
	}

	// Apply an update fully to a lazy node.
	virtual void apply(
		std::size_t const node,
		typename std::vector<Value>::reference value,
		Update const &update,
		std::pair<std::size_t, std::size_t> const &range) override {
		if (update.first) {
			value *= update.second;
		} else {
			value += update.second;
		}
	}
};

int main(int, char const *[]) {
#if !defined(ONLINEJUDGE) && (defined(__APPLE__) || defined(__MACH__))
	std::freopen("../build/i.default.txt", "r", stdin);
	std::freopen("../build/o.default.txt", "w", stdout);
#endif

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	LL N;
	cin >> N;
	vector<pair<LL, LL>> O(N);
	RF(i, 0, N) {
		cin >> O[i].first;
		if (O[i].first != 3) {
			cin >> O[i].second;
		}
	}

	LL const STS{200005};
	ST st(STS);
	LL tx{0}, shift{0};
	RF(i, 0, N) {
		if (O[i].first == 1) {
			LL pos{(shift + O[i].second) % STS};
			st.update(pos, pos, {false, 1});
		} else if (O[i].first == 2) {
			if (shift + O[i].second >= STS) {
				st.update(shift, STS, {true, 0});
				st.update(0, shift + O[i].second - STS, {true, 0});
				shift += O[i].second - STS;
			} else {
				st.update(shift, shift + O[i].second, {true, 0});
				shift += O[i].second;
			}
			tx += O[i].second;
		} else {
			if (tx == 0) {
				st.update(0, STS, {true, 2});
			} else if (tx >= STS) {
				;
			} else {
				RF(j, tx + 1, STS + 1) {
					LL pos{(shift + j) % STS}, pos2{(shift + j - tx) % STS};
					MR val{st.query(pos, pos)};
					if (val.value != 0) {
						st.update(pos2, pos2, {false, val});
					}
				}
				tx *= 2;
			}
		}
	}

	cout << st.query(0, STS);
	return 0;
}
