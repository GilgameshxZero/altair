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
	vector<LL> A(N);
	RF(i, 0, N) {
		cin >> A[i];
	}

	LL const MS{200000};
	vector<MR> co(MS);
	LL const SHIFT = co.size() / 2;
	co[SHIFT + A[1]] = 1;
	RF(i, 1, N - 1) {
		vector<MR> co2(MS);
		RF(j, 0, MS) {
			if (co[j] == 0) {
				continue;
			}
			co2[A[i + 1] + (j - SHIFT) + SHIFT] += co[j];
			if (j != SHIFT) {
				co2[A[i + 1] - (j - SHIFT) + SHIFT] += co[j];
			}
		}
		co = move(co2);
	}
	MR ans{0};
	RF(i, 0, co.size()) {
		ans += co[i];
	}
	cout << ans;

	return 0;
}
