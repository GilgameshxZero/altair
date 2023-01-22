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

namespace Rain::Algorithm {
	// The Modulus interface provides one public function which returns a prime
	// modulus integer. Template specializations may not use dependent types, so
	// we must either use `integral_constant` or `enable_if` to specify the
	// this->primeModulus().
	template <typename Integer, Integer PRIME_MODULUS = 0, typename = void>
	class PrimeModulus {
		public:
		virtual inline Integer primeModulus() const = 0;
	};

	template <typename Integer, Integer PRIME_MODULUS>
	class PrimeModulus<
		Integer,
		PRIME_MODULUS,
		typename std::enable_if<PRIME_MODULUS != 0>::type> {
		public:
		virtual inline Integer primeModulus() const { return PRIME_MODULUS; }
	};

	// A non-compile-time prime modulus may be specified by overriding
	// `PrimeModulus<Integer, 0>`, e.g.
	//
	// class PM : public PrimeModulus<LL> {
	// 	public:
	// 	virtual LL primeModulus() const override { return M; }
	// };

	// Implementation for a prime modulus ring over the integers, supporting basic
	// operations add, subtract, multiply in O(1) and divide in O(ln N). For O(1)
	// division, cache multiplicative inverses and multiply with those.
	//
	// Integer must be large enough to store (primeModulus() - 1)^2.
	template <typename Integer, typename PrimeModulus>
	class PrimeModulusRing : public PrimeModulus {
		public:
		Integer value;

		// Add primeModulus() first to wrap back around in the case of "negative"
		// unsigned Integer.
		PrimeModulusRing(Integer const value = 0)
				: value((this->primeModulus() + value) % this->primeModulus()) {}

		// Versions of C++ before C++17 should use static member functions intead of
		// static inline member variables. static inline
		// std::vector<PrimeModulusRing<Integer, PrimeModulus>> 	&factorials() {
		// static std::vector<PrimeModulusRing<Integer, PrimeModulus>> factorials;
		// return factorials;
		// }
		// static inline std::vector<PrimeModulusRing<Integer, PrimeModulus>>
		// 	&invFactorials() {
		// 	static std::vector<PrimeModulusRing<Integer, PrimeModulus>>
		// invFactorials; 	return invFactorials;
		// }
		static inline std::vector<PrimeModulusRing<Integer, PrimeModulus>>
			factorials, invFactorials;

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
		inline PrimeModulusRing<Integer, PrimeModulus> choose(
			Integer const K) const {
			if (K < 0 || K > this->value) {
				return {0};
			}
			return factorials[this->value] * invFactorials[K] *
				invFactorials[this->value - K];
		}

		// O(ln N) exponentiation.
		PrimeModulusRing<Integer, PrimeModulus> power(
			std::size_t const exponent) const {
			if (exponent == 0) {
				return {1};
			}
			auto half = this->power(exponent / 2);
			if (exponent % 2 == 0) {
				return half * half;
			} else {
				return half * half * *this;
			}
		}

		// Arithmetic operators.
		template <typename OtherInteger>
		inline PrimeModulusRing<Integer, PrimeModulus> operator+(
			OtherInteger const other) const {
			return *this + PrimeModulusRing<Integer, PrimeModulus>(other);
		}
		template <typename OtherInteger>
		inline PrimeModulusRing<Integer, PrimeModulus> operator+(
			OtherInteger const other) {
			return *this + PrimeModulusRing<Integer, PrimeModulus>(other);
		}
		inline PrimeModulusRing<Integer, PrimeModulus> operator+(
			PrimeModulusRing<Integer, PrimeModulus> const other) {
			return {this->value + other.value};
		}
		inline PrimeModulusRing<Integer, PrimeModulus> operator+=(
			PrimeModulusRing<Integer, PrimeModulus> const other) {
			return *this = *this + other;
		}
		inline PrimeModulusRing<Integer, PrimeModulus> operator++() {
			return *this += 1;
		}
		inline PrimeModulusRing<Integer, PrimeModulus> operator++(int) {
			auto tmp(*this);
			*this += 1;
			return tmp;
		}
		template <typename OtherInteger>
		inline PrimeModulusRing<Integer, PrimeModulus> operator-(
			OtherInteger const other) const {
			return *this - PrimeModulusRing<Integer, PrimeModulus>(other);
		}
		template <typename OtherInteger>
		inline PrimeModulusRing<Integer, PrimeModulus> operator-(
			OtherInteger const other) {
			return *this - PrimeModulusRing<Integer, PrimeModulus>(other);
		}
		inline PrimeModulusRing<Integer, PrimeModulus> operator-(
			PrimeModulusRing<Integer, PrimeModulus> const other) {
			return {this->value - other.value};
		}
		inline PrimeModulusRing<Integer, PrimeModulus> operator-=(
			PrimeModulusRing<Integer, PrimeModulus> const other) {
			return *this = *this - other;
		}
		inline PrimeModulusRing<Integer, PrimeModulus> operator--() {
			return *this -= 1;
		}
		inline PrimeModulusRing<Integer, PrimeModulus> operator--(int) {
			auto tmp(*this);
			*this -= 1;
			return tmp;
		}
		template <typename OtherInteger>
		inline PrimeModulusRing<Integer, PrimeModulus> operator*(
			OtherInteger const other) const {
			return *this * PrimeModulusRing<Integer, PrimeModulus>(other);
		}
		template <typename OtherInteger>
		inline PrimeModulusRing<Integer, PrimeModulus> operator*(
			OtherInteger const other) {
			return *this * PrimeModulusRing<Integer, PrimeModulus>(other);
		}
		inline PrimeModulusRing<Integer, PrimeModulus> operator*(
			PrimeModulusRing<Integer, PrimeModulus> const other) {
			return {this->value * other.value};
		}
		inline PrimeModulusRing<Integer, PrimeModulus> operator*=(
			PrimeModulusRing<Integer, PrimeModulus> const other) {
			return *this = *this * other;
		}
		template <typename OtherInteger>
		inline PrimeModulusRing<Integer, PrimeModulus> operator/(
			OtherInteger const other) const {
			return *this / PrimeModulusRing<Integer, PrimeModulus>(other);
		}
		template <typename OtherInteger>
		inline PrimeModulusRing<Integer, PrimeModulus> operator/(
			OtherInteger const other) {
			return *this / PrimeModulusRing<Integer, PrimeModulus>(other);
		}
		inline PrimeModulusRing<Integer, PrimeModulus> operator/(
			PrimeModulusRing<Integer, PrimeModulus> const other) {
			return *this * other.power(this->primeModulus() - 2);
		}
		inline PrimeModulusRing<Integer, PrimeModulus> operator/=(
			PrimeModulusRing<Integer, PrimeModulus> const other) {
			return *this = *this / other;
		}

		// Equality operators.
		template <typename OtherInteger>
		inline bool operator==(OtherInteger const other) {
			return *this == PrimeModulusRing<Integer, PrimeModulus>(other);
		}
		inline bool operator==(
			PrimeModulusRing<Integer, PrimeModulus> const other) {
			return this->value == other.value;
		}

		// Cast operators.
		operator std::size_t() const { return this->value; }
		operator Integer() const { return this->value; }
	};
}

template <typename OtherInteger, typename Integer, typename PrimeModulus>
inline Rain::Algorithm::PrimeModulusRing<Integer, PrimeModulus> operator+(
	OtherInteger const left,
	Rain::Algorithm::PrimeModulusRing<Integer, PrimeModulus> const right) {
	return Rain::Algorithm::PrimeModulusRing<Integer, PrimeModulus>(left) + right;
}

template <typename OtherInteger, typename Integer, typename PrimeModulus>
inline Rain::Algorithm::PrimeModulusRing<Integer, PrimeModulus> operator-(
	OtherInteger const left,
	Rain::Algorithm::PrimeModulusRing<Integer, PrimeModulus> const right) {
	return Rain::Algorithm::PrimeModulusRing<Integer, PrimeModulus>(left) - right;
}

template <typename OtherInteger, typename Integer, typename PrimeModulus>
inline Rain::Algorithm::PrimeModulusRing<Integer, PrimeModulus> operator*(
	OtherInteger const left,
	Rain::Algorithm::PrimeModulusRing<Integer, PrimeModulus> const right) {
	return Rain::Algorithm::PrimeModulusRing<Integer, PrimeModulus>(left) * right;
}

template <typename OtherInteger, typename Integer, typename PrimeModulus>
inline Rain::Algorithm::PrimeModulusRing<Integer, PrimeModulus> operator/(
	OtherInteger const left,
	Rain::Algorithm::PrimeModulusRing<Integer, PrimeModulus> const right) {
	return Rain::Algorithm::PrimeModulusRing<Integer, PrimeModulus>(left) / right;
}

// Ease-of-use streaming operators.
template <typename Integer, typename PrimeModulus>
inline std::ostream &operator<<(
	std::ostream &stream,
	Rain::Algorithm::PrimeModulusRing<Integer, PrimeModulus> const right) {
	return stream << right.value;
}
template <typename Integer, typename PrimeModulus>
inline std::istream &operator>>(
	std::istream &stream,
	Rain::Algorithm::PrimeModulusRing<Integer, PrimeModulus> right) {
	stream >> right.value;
	right.value = (right.primeModulus() + right.value) % right.primeModulus();
	return stream;
}

/* ---------------------------- End of template. ---------------------------- */

using namespace Rain::Algorithm;

LL M;

class PM : public PrimeModulus<LL> {
	public:
	virtual LL primeModulus() const override { return M; }
};

using PMR = PrimeModulusRing<LL, PM>;

int main(int, char const *[]) {
#if !defined(ONLINEJUDGE) && (defined(__APPLE__) || defined(__MACH__))
	std::freopen("../build/i.default.txt", "r", stdin);
	std::freopen("../build/o.default.txt", "w", stdout);
#endif

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	LL N;
	cin >> N >> M;

	PMR::precomputeFactorials(3 * N + 1);
	PMR ones{2 * PMR::factorials[2 * N] - PMR::factorials[N] - 1 + 5 * M};
	PMR twos{0};
	RF(i, 0, N + 1) {
		twos += PMR(N).choose(i) * PMR(N).choose(N - i) * PMR(2 * N - i).choose(N);
	}
	twos =
		PMR(2 * N).choose(N) * PMR::factorials[N] * PMR::factorials[2 * N] * 2 -
		twos * PMR::factorials[N] * PMR::factorials[N] * PMR::factorials[N] - ones -
		1;
	PMR threes{PMR::factorials[3 * N] - twos - ones - 1};
	cout << ones + twos * 2 + threes * 3;
	return 0;
}
