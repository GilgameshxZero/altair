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

// Fixed-size Fenwick/Binary-Indexed Tree implementation. O(ln N) point
// updates and range queries. Not thread-safe.
//
// Value must support commutative addition. In addition, default
// initialization should be equivalent to "empty".
template <typename Value = long long>
class FenwickTree {
	private:
	std::vector<Value> tree;

	public:
	// Creates a Fenwick tree, which may be resized by operations.
	FenwickTree(std::size_t const size) : tree(size) {}

	// Computes prefix sum up to and including idx.
	Value sum(std::size_t const idx) const {
		Value aggregate{};
		for (std::size_t i = idx; i != SIZE_MAX; i &= i + 1, i--) {
			aggregate += this->tree[i];
		}
		return aggregate;
	}

	// Modify index by a delta.
	void modify(std::size_t const idx, Value const &delta) {
		for (std::size_t i = idx; i < this->tree.size(); i |= i + 1) {
			this->tree[i] += delta;
		}
	}
};

/* ---------------------------- End of template. ---------------------------- */

using MR = ModRing<LL, 998244353>;

int main(int, char const *[]) {
#if !defined(ONLINEJUDGE) && (defined(__APPLE__) || defined(__MACH__))
	std::freopen("../build/i.default.txt", "r", stdin);
	std::freopen("../build/o.default.txt", "w", stdout);
#endif

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	LL N;
	cin >> N;
	vector<pair<LL, LL>> A(N);
	vector<pair<LL, LL>> sA(N);
	RF(i, 0, N) {
		cin >> A[i].first;
		sA[i].first = A[i].first;
		sA[i].second = i;
	}
	sort(sA.begin(), sA.end());
	RF(i, 0, N) {
		A[sA[i].second].second = i;
	}
	FenwickTree amount(N), cnt(N);
	MR num{0};
	RF(i, 0, N) {
		LL nBefore{cnt.sum(A[i].second)};
		cnt.modify(A[i].second, 1);
		LL amtAfter{amount.sum(N - 1) - amount.sum(A[i].second)};
		amount.modify(A[i].second, A[i].first);
		num += (nBefore * 2 + 1) * A[i].first;
		num += 2 * amtAfter;
		cout << num / (i + 1) / (i + 1) << '\n';
	}
	return 0;
}
