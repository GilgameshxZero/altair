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

using LL = long long;
using LD = long double;

#define RF(x, from, to)                                                      \
	for (long long x = from, _to = to, _delta{x < _to ? 1LL : -1LL}; x != _to; \
			 x += _delta)

using namespace std;

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
	// The Modulus interface provides one public function which returns a
	// modulus integer. Template specializations may not use dependent types, so
	// we must either use `integral_constant` or `enable_if` to specify the
	// get() function.

	// Implementation for a modulus field over the integers,
	// supporting basic operations add, subtract, multiply in O(1) and divide in
	// O(ln M). Division is generally only valid for prime moduli. For O(1)
	// division, cache multiplicative inverses and multiply with those.
	//
	// A compile-time modulus may be specified with
	//
	// Integer must be large enough to store (modulus() - 1)^2.
	template <typename Integer, std::size_t MODULUS = 0>
	class ModulusField {
		public:
		Integer const modulus;
		Integer value;

		// Add modulus() first to wrap back around in the case of "negative"
		// unsigned Integer.
		template <typename = std::enable_if<MODULUS != 0>::type>
		ModulusField(Integer const value = 0)
				: modulus{MODULUS}, value((value + this->modulus) % this->modulus) {}

		template <typename = std::enable_if<MODULUS == 0>::type>
		ModulusField(Integer const modulus, Integer const value = 0)
				: modulus{modulus}, value((value + this->modulus) % this->modulus) {}

		// Builds a ModulusField<Integer, MODULUS> type, but with the same
		// underlying modulus value. Uses more specialized SFINAE to differentiate
		// otherwise identical signatures.
		template <
			std::size_t MODULUS_INNER = MODULUS,
			typename std::enable_if<MODULUS_INNER != 0>::type * = nullptr>
		static ModulusField<Integer, MODULUS> build(Integer const value) {
			return {value};
		}

		template <
			std::size_t MODULUS_INNER = MODULUS,
			typename std::enable_if<MODULUS_INNER == 0>::type * = nullptr>
		ModulusField<Integer, MODULUS> build(Integer const value) const {
			return {this->modulus, value};
		}

		// Assignment operators need to be overloaded as this class stores an
		// additional modulus, which implicitly deletes the default assignment
		// operator.
		ModulusField<Integer, MODULUS> &operator=(
			ModulusField<Integer, MODULUS> const &other) {
			if (this == &other) {
				return *this;
			}
			this->value = (other.value + this->modulus) % this->modulus;
			return *this;
		}
		template <typename OtherInteger>
		ModulusField<Integer, MODULUS> &operator=(OtherInteger const &other) {
			this->value = (other + this->modulus) % this->modulus;
			return *this;
		}

		// Versions of C++ before C++17 should use static member functions intead of
		// static inline member variables. static inline
		// std::vector<ModulusField<Integer, MODULUS>> 	&factorials() {
		// static std::vector<ModulusField<Integer, MODULUS>> factorials;
		// return factorials;
		// }
		// static inline std::vector<ModulusField<Integer, MODULUS>>
		// 	&invFactorials() {
		// 	static std::vector<ModulusField<Integer, MODULUS>>
		// invFactorials; 	return invFactorials;
		// }
		static inline std::vector<ModulusField<Integer, MODULUS>> factorials,
			invFactorials;

		// Computes the factorials modulus a prime, up to and including N, in O(N).
		// This enables the choose functions.
		static void precomputeFactorials(std::size_t const N) {
			factorials.resize(N + 1);
			invFactorials.resize(N + 1);
			factorials[0] = 1;
			for (std::size_t i{1}; i <= N; i++) {
				factorials[i] = factorials[i - 1] * i;
			}
			invFactorials[N] = 1 / factorials[N];
			for (std::size_t i{0}; i < N; i++) {
				invFactorials[N - i - 1] = invFactorials[N - i] * (N - i);
			}
		}

		// Computes the binomial coefficient (N choose K) modulus a prime, in O(1).
		// Must have called precomputeFactorials for the largest expected value of N
		// first.
		inline ModulusField<Integer, MODULUS> choose(Integer const K) const {
			if (K < 0 || K > this->value) {
				return build(0);
			}
			return factorials[this->value] * invFactorials[K] *
				invFactorials[this->value - K];
		}

		// O(ln N) exponentiation.
		template <typename OtherInteger>
		ModulusField<Integer, MODULUS> power(OtherInteger const &exponent) const {
			if (exponent == 0) {
				return build(1);
			}
			auto half = this->power(exponent / 2);
			if (exponent % 2 == 0) {
				return half * half;
			} else {
				return half * half * *this;
			}
		}

		// Comparison.
		template <typename OtherInteger>
		inline bool operator==(OtherInteger const &other) {
			return *this == build(other);
		}
		inline bool operator==(ModulusField<Integer, MODULUS> const &other) {
			return this->value == other.value;
		}

		// Cast.
		operator std::size_t() const { return this->value; }

		template <
			typename =
				std::enable_if<!std::is_same<Integer, std::size_t>::value>::type>
		operator Integer() const {
			return this->value;
		}

		// Arithmetic operators.
		template <typename OtherInteger>
		inline ModulusField<Integer, MODULUS> operator+(
			OtherInteger const &other) const {
			return *this + build(other);
		}
		template <typename OtherInteger>
		inline ModulusField<Integer, MODULUS> operator+(OtherInteger const &other) {
			return *this + build(other);
		}
		inline ModulusField<Integer, MODULUS> operator+(
			ModulusField<Integer, MODULUS> const &other) {
			return build(this->value + other.value);
		}
		inline ModulusField<Integer, MODULUS> &operator+=(
			ModulusField<Integer, MODULUS> const &other) {
			return *this = *this + other;
		}
		inline ModulusField<Integer, MODULUS> operator++() { return *this += 1; }
		inline ModulusField<Integer, MODULUS> operator++(int) {
			auto tmp(*this);
			*this += 1;
			return tmp;
		}
		template <typename OtherInteger>
		inline ModulusField<Integer, MODULUS> operator-(
			OtherInteger const &other) const {
			return *this - build(other);
		}
		template <typename OtherInteger>
		inline ModulusField<Integer, MODULUS> operator-(OtherInteger const &other) {
			return *this - build(other);
		}
		inline ModulusField<Integer, MODULUS> operator-(
			ModulusField<Integer, MODULUS> const &other) {
			return build(this->value - other.value);
		}
		inline ModulusField<Integer, MODULUS> &operator-=(
			ModulusField<Integer, MODULUS> const &other) {
			return *this = *this - other;
		}
		inline ModulusField<Integer, MODULUS> operator--() { return *this -= 1; }
		inline ModulusField<Integer, MODULUS> operator--(int) {
			auto tmp(*this);
			*this -= 1;
			return tmp;
		}
		template <typename OtherInteger>
		inline ModulusField<Integer, MODULUS> operator*(
			OtherInteger const &other) const {
			return *this * build(other);
		}
		template <typename OtherInteger>
		inline ModulusField<Integer, MODULUS> operator*(OtherInteger const &other) {
			return *this * build(other);
		}
		inline ModulusField<Integer, MODULUS> operator*(
			ModulusField<Integer, MODULUS> const &other) {
			return build(this->value * other.value);
		}
		inline ModulusField<Integer, MODULUS> &operator*=(
			ModulusField<Integer, MODULUS> const &other) {
			return *this = *this * other;
		}
		template <typename OtherInteger>
		inline ModulusField<Integer, MODULUS> operator/(
			OtherInteger const &other) const {
			return *this / build(other);
		}
		template <typename OtherInteger>
		inline ModulusField<Integer, MODULUS> operator/(OtherInteger const &other) {
			return *this / build(other);
		}
		inline ModulusField<Integer, MODULUS> operator/(
			ModulusField<Integer, MODULUS> const &other) {
			return *this * other.power(this->modulus - 2);
		}
		inline ModulusField<Integer, MODULUS> &operator/=(
			ModulusField<Integer, MODULUS> const &other) {
			return *this = *this / other;
		}
	};
}

template <typename OtherInteger, typename Integer, std::size_t MODULUS>
inline Rain::Algorithm::ModulusField<Integer, MODULUS> operator+(
	OtherInteger const &left,
	Rain::Algorithm::ModulusField<Integer, MODULUS> const &right) {
	return right.build(left) + right;
}

template <typename OtherInteger, typename Integer, std::size_t MODULUS>
inline Rain::Algorithm::ModulusField<Integer, MODULUS> operator-(
	OtherInteger const &left,
	Rain::Algorithm::ModulusField<Integer, MODULUS> const &right) {
	return right.build(left) - right;
}

template <typename OtherInteger, typename Integer, std::size_t MODULUS>
inline Rain::Algorithm::ModulusField<Integer, MODULUS> operator*(
	OtherInteger const &left,
	Rain::Algorithm::ModulusField<Integer, MODULUS> const &right) {
	return right.build(left) * right;
}

template <typename OtherInteger, typename Integer, std::size_t MODULUS>
inline Rain::Algorithm::ModulusField<Integer, MODULUS> operator/(
	OtherInteger const &left,
	Rain::Algorithm::ModulusField<Integer, MODULUS> const &right) {
	return right.build(left) / right;
}

// Ease-of-use streaming operators.
template <typename Integer, std::size_t MODULUS>
inline std::ostream &operator<<(
	std::ostream &stream,
	Rain::Algorithm::ModulusField<Integer, MODULUS> const &right) {
	return stream << right.value;
}
template <typename Integer, std::size_t MODULUS>
inline std::istream &operator>>(
	std::istream &stream,
	Rain::Algorithm::ModulusField<Integer, MODULUS> &right) {
	stream >> right.value;
	right.value = (right.modulus + right.value) % right.modulus;
	return stream;
}

namespace Rain::Algorithm {
	// Miller-Rabin helper.
	template <typename Integer>
	bool isMaybePrimeMillerRabinInner(
		Integer const N,
		Integer const A,
		std::size_t const lsb,
		Integer const truncated) {
		ModulusField<Integer> X(N);
		X = X.build(A).power(truncated);

		if (X == 1 || X == -1) {
			return true;
		}
		for (std::size_t j{1}; j < lsb; j++) {
			X *= X;
			if (X == -1) {
				return true;
			}
		}
		return false;
	}

	// Miller-Rabin primality test in O(K ln^3 N), with failure probability upper
	// bounded by 4^-K. Can test numbers up to half the bits in Integer.
	template <typename Integer>
	bool isPrimeMillerRabin(Integer const N, std::size_t const K) {
		if (N < 4) {
			return N == 2 || N == 3;
		}

		std::size_t lsb{leastSignificant1BitIdx(N - 1)};
		Integer truncated{(N - 1) >> lsb};
		for (std::size_t i{0}; i < K; i++) {
			if (!isMaybePrimeMillerRabinInner(
						N, 2 + rand() % (N - 3), lsb, truncated)) {
				return false;
			}
		}
		return true;
	}

	// Miller-Rabin primality test, deterministic, for up to 64-bits, in O(12).
	// Bound by the same conditions on Integer as the random version.
	template <typename Integer>
	bool isPrimeMillerRabinDeterministic(Integer const N) {
		if (N < 2) {
			return false;
		}

		std::size_t lsb{leastSignificant1BitIdx(N - 1)};
		Integer truncated{(N - 1) >> lsb};
		for (Integer A : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
			if (N == A) {
				return true;
			}
			if (!isMaybePrimeMillerRabinInner(N, A, lsb, truncated)) {
				return false;
			}
		}
		return true;
	}
}

using namespace Rain::Algorithm;

/* ---------------------------- End of template. ---------------------------- */

int main(int, char const *[]) {
#if !defined(ONLINEJUDGE) && (defined(__APPLE__) || defined(__MACH__))
	std::freopen("../build/i.default.txt", "r", stdin);
	std::freopen("../build/o.default.txt", "w", stdout);
#endif

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	LL T;
	cin >> T;
	while (T--) {
		LL N;
		cin >> N;
		cout << (isPrimeMillerRabinDeterministic(N) ? "YES" : "NO") << '\n';
	}

	return 0;
}
