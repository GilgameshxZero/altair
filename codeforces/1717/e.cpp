#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC target("avx2", "bmi", "bmi2", "popcnt", "lzcnt")
#pragma GCC optimize("Ofast", "unroll-loops")
#endif

#include <bits/stdc++.h>

using LL = long long;
using LD = long double;
using namespace std;

#define RF(x, from, to) \
	for (LL x(from), _to(to), _delta{x < _to ? 1LL : -1LL}; x != _to; x += _delta)

#pragma hdrstop	 // ------------------------------------------------------------

namespace Rain::Algorithm {
	// Implementation for a modulus field over the integers,
	// supporting basic operations add, subtract, multiply in O(1) and divide in
	// O(ln M). Division is generally only valid for prime moduli. For O(1)
	// division, cache multiplicative inverses and multiply with those.
	//
	// A runtime modulus may be specified with MODULUS 0 in the template and the
	// appropriate constructor.
	//
	// Integer must be large enough to store (modulus() - 1)^2.
	template <typename Integer, std::size_t MODULUS_OUTER = 0>
	class ModulusField {
		public:
		Integer const MODULUS;
		Integer value;

		// If the integer specified is signed and negative, we want to wrap it back
		// to the positives first.
		template <
			typename OtherInteger = std::size_t,
			std::size_t MODULUS_INNER = MODULUS_OUTER,
			typename std::enable_if<MODULUS_INNER != 0>::type * = nullptr>
		ModulusField(OtherInteger const &value = 0)
				: MODULUS{MODULUS_OUTER},
					value(
						value < 0 ? this->MODULUS - ((0 - value) % this->MODULUS)
											: value % this->MODULUS) {}

		template <
			typename OtherInteger = std::size_t,
			std::size_t MODULUS_INNER = MODULUS_OUTER,
			typename std::enable_if<MODULUS_INNER == 0>::type * = nullptr>
		ModulusField(Integer const &modulus, OtherInteger const &value = 0)
				: MODULUS{modulus},
					value(
						value < 0 ? this->MODULUS - ((0 - value) % this->MODULUS)
											: value % this->MODULUS) {}

		// Builds a ModulusField<Integer, MODULUS_OUTER> type, but with the same
		// underlying modulus value. Uses more specialized SFINAE to differentiate
		// otherwise identical signatures.
		template <
			typename OtherInteger,
			std::size_t MODULUS_INNER = MODULUS_OUTER,
			typename std::enable_if<MODULUS_INNER != 0>::type * = nullptr>
		static ModulusField<Integer, MODULUS_OUTER> build(
			OtherInteger const &value) {
			return {value};
		}

		template <
			typename OtherInteger,
			std::size_t MODULUS_INNER = MODULUS_OUTER,
			typename std::enable_if<MODULUS_INNER == 0>::type * = nullptr>
		ModulusField<Integer, MODULUS_OUTER> build(
			OtherInteger const &value) const {
			return {this->MODULUS, value};
		}

		// Assignment operators need to be overloaded as this class stores an
		// additional modulus, which implicitly deletes the default assignment
		// operator.
		ModulusField<Integer, MODULUS_OUTER> &operator=(
			ModulusField<Integer, MODULUS_OUTER> const &other) {
			// Runtime moduli may not actually be the same, so we need to take an
			// additional mod here.
			this->value = other.value % this->MODULUS;
			return *this;
		}
		template <typename OtherInteger>
		ModulusField<Integer, MODULUS_OUTER> &operator=(OtherInteger const &other) {
			return *this = build(other);
		}

		// Comparison.
		template <typename OtherInteger>
		inline bool operator==(OtherInteger const &other) const {
			return *this == build(other);
		}
		template <typename OtherInteger>
		inline bool operator==(OtherInteger const &other) {
			return std::as_const(*this) == other;
		}
		inline bool operator==(
			ModulusField<Integer, MODULUS_OUTER> const &other) const {
			// Ignores modulus comparison! Important.
			return this->value == other.value;
		}
		inline bool operator==(ModulusField<Integer, MODULUS_OUTER> const &other) {
			return std::as_const(*this) == other;
		}
		template <typename OtherInteger>
		inline bool operator!=(OtherInteger const &other) const {
			return *this != build(other);
		}
		template <typename OtherInteger>
		inline bool operator!=(OtherInteger const &other) {
			return std::as_const(*this) != other;
		}
		inline bool operator!=(
			ModulusField<Integer, MODULUS_OUTER> const &other) const {
			return !(*this == other);
		}
		inline bool operator!=(ModulusField<Integer, MODULUS_OUTER> const &other) {
			return std::as_const(*this) != other;
		}
		// Other comparison operators don't make that much sense under modulus.

		// Unary.
		inline ModulusField<Integer, MODULUS_OUTER> operator-() const {
			return 0 - *this;
		}
		inline ModulusField<Integer, MODULUS_OUTER> operator-() {
			return -std::as_const(*this);
		}

		// Cast.
		explicit operator bool() const { return this->value != 0; }
		operator std::size_t() const {
			return static_cast<std::size_t>(this->value);
		}
		template <
			typename = typename std::enable_if<
				!std::is_same<Integer, std::size_t>::value>::type>
		operator Integer() const {
			return this->value;
		}

		// Arithmetic.
		template <typename OtherInteger>
		inline ModulusField<Integer, MODULUS_OUTER> operator+(
			OtherInteger const &other) const {
			return *this + build(other);
		}
		template <typename OtherInteger>
		inline ModulusField<Integer, MODULUS_OUTER> operator+(
			OtherInteger const &other) {
			return std::as_const(*this) + other;
		}
		inline ModulusField<Integer, MODULUS_OUTER> operator+(
			ModulusField<Integer, MODULUS_OUTER> const &other) const {
			return build(this->value + other.value);
		}
		inline ModulusField<Integer, MODULUS_OUTER> operator+(
			ModulusField<Integer, MODULUS_OUTER> const &other) {
			return std::as_const(*this) + other;
		}
		template <typename OtherInteger>
		inline ModulusField<Integer, MODULUS_OUTER> &operator+=(
			OtherInteger const &other) {
			return *this = *this + other;
		}
		inline ModulusField<Integer, MODULUS_OUTER> operator++() {
			return *this += 1;
		}
		inline ModulusField<Integer, MODULUS_OUTER> operator++(int) {
			auto tmp(*this);
			*this += 1;
			return tmp;
		}
		template <typename OtherInteger>
		inline ModulusField<Integer, MODULUS_OUTER> operator-(
			OtherInteger const &other) const {
			return *this - build(other);
		}
		template <typename OtherInteger>
		inline ModulusField<Integer, MODULUS_OUTER> operator-(
			OtherInteger const &other) {
			return std::as_const(*this) - other;
		}
		inline ModulusField<Integer, MODULUS_OUTER> operator-(
			ModulusField<Integer, MODULUS_OUTER> const &other) const {
			return build(this->value + this->MODULUS - other.value);
		}
		inline ModulusField<Integer, MODULUS_OUTER> operator-(
			ModulusField<Integer, MODULUS_OUTER> const &other) {
			return std::as_const(*this) - other;
		}
		template <typename OtherInteger>
		inline ModulusField<Integer, MODULUS_OUTER> &operator-=(
			OtherInteger const &other) {
			return *this = *this - other;
		}
		inline ModulusField<Integer, MODULUS_OUTER> operator--() {
			return *this -= 1;
		}
		inline ModulusField<Integer, MODULUS_OUTER> operator--(int) {
			auto tmp(*this);
			*this -= 1;
			return tmp;
		}
		template <typename OtherInteger>
		inline ModulusField<Integer, MODULUS_OUTER> operator*(
			OtherInteger const &other) const {
			return *this * build(other);
		}
		template <typename OtherInteger>
		inline ModulusField<Integer, MODULUS_OUTER> operator*(
			OtherInteger const &other) {
			return std::as_const(*this) * other;
		}
		inline ModulusField<Integer, MODULUS_OUTER> operator*(
			ModulusField<Integer, MODULUS_OUTER> const &other) const {
			return build(this->value * other.value);
		}
		inline ModulusField<Integer, MODULUS_OUTER> operator*(
			ModulusField<Integer, MODULUS_OUTER> const &other) {
			return std::as_const(*this) * other;
		}
		template <typename OtherInteger>
		inline ModulusField<Integer, MODULUS_OUTER> &operator*=(
			OtherInteger const &other) {
			return *this = *this * other;
		}
		template <typename OtherInteger>
		inline ModulusField<Integer, MODULUS_OUTER> operator/(
			OtherInteger const &other) const {
			return *this / build(other);
		}
		template <typename OtherInteger>
		inline ModulusField<Integer, MODULUS_OUTER> operator/(
			OtherInteger const &other) {
			return std::as_const(*this) / other;
		}
		inline ModulusField<Integer, MODULUS_OUTER> operator/(
			ModulusField<Integer, MODULUS_OUTER> const &other) const {
			// This is only true if this has a multiplicative inverse, which is always
			// true if the modulus is prime.
			return *this * other.power(this->MODULUS - 2);
		}
		inline ModulusField<Integer, MODULUS_OUTER> operator/(
			ModulusField<Integer, MODULUS_OUTER> const &other) {
			return std::as_const(*this) / other;
		}
		template <typename OtherInteger>
		inline ModulusField<Integer, MODULUS_OUTER> &operator/=(
			OtherInteger const &other) {
			return *this = *this / other;
		}

		// The following are algorithmic functions based on the modulus field
		// properties.

		// Versions of C++ before C++17 should use static member functions intead of
		// static inline member variables. static inline
		// std::vector<ModulusField<Integer, MODULUS_OUTER>> 	&factorials() {
		// static std::vector<ModulusField<Integer, MODULUS_OUTER>> factorials;
		// return factorials;
		// }
		// static inline std::vector<ModulusField<Integer, MODULUS_OUTER>>
		// 	&invFactorials() {
		// 	static std::vector<ModulusField<Integer, MODULUS_OUTER>>
		// invFactorials; 	return invFactorials;
		// }
		static inline std::vector<ModulusField<Integer, MODULUS_OUTER>> factorials,
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
		inline ModulusField<Integer, MODULUS_OUTER> choose(
			std::size_t const K) const {
			std::size_t const N{static_cast<std::size_t>(this->value)};
			if (K < 0 || K > N) {
				return build(0);
			}
			return factorials[N] * invFactorials[K] * invFactorials[N - K];
		}

		// O(ln N) exponentiation.
		template <typename OtherInteger>
		ModulusField<Integer, MODULUS_OUTER> power(
			OtherInteger const &exponent) const {
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
	};
}

template <typename OtherInteger, typename Integer, std::size_t MODULUS_OUTER>
inline Rain::Algorithm::ModulusField<Integer, MODULUS_OUTER> operator+(
	OtherInteger const &left,
	Rain::Algorithm::ModulusField<Integer, MODULUS_OUTER> const &right) {
	return right.build(left) + right;
}

template <typename OtherInteger, typename Integer, std::size_t MODULUS_OUTER>
inline Rain::Algorithm::ModulusField<Integer, MODULUS_OUTER> operator-(
	OtherInteger const &left,
	Rain::Algorithm::ModulusField<Integer, MODULUS_OUTER> const &right) {
	return right.build(left) - right;
}

template <typename OtherInteger, typename Integer, std::size_t MODULUS_OUTER>
inline Rain::Algorithm::ModulusField<Integer, MODULUS_OUTER> operator*(
	OtherInteger const &left,
	Rain::Algorithm::ModulusField<Integer, MODULUS_OUTER> const &right) {
	return right.build(left) * right;
}

template <typename OtherInteger, typename Integer, std::size_t MODULUS_OUTER>
inline Rain::Algorithm::ModulusField<Integer, MODULUS_OUTER> operator/(
	OtherInteger const &left,
	Rain::Algorithm::ModulusField<Integer, MODULUS_OUTER> const &right) {
	return right.build(left) / right;
}

// Ease-of-use streaming operators.
template <typename Integer, std::size_t MODULUS_OUTER>
inline std::ostream &operator<<(
	std::ostream &stream,
	Rain::Algorithm::ModulusField<Integer, MODULUS_OUTER> const &right) {
	return stream << right.value;
}
template <typename Integer, std::size_t MODULUS_OUTER>
inline std::istream &operator>>(
	std::istream &stream,
	Rain::Algorithm::ModulusField<Integer, MODULUS_OUTER> &right) {
	stream >> right.value;
	right.value = (right.modulus + right.value) % right.modulus;
	return stream;
}

namespace Rain::Algorithm {
	// Computes the the minimum prime factor and a list of primes for all integers
	// up to and including N. The minFactor array is 1-indexed; that is,
	// minFactor[3] refers to the minimum prime factor of 3, which would be 1,
	// since primes[1] = 3. By definition, minFactor[0] = minfactor[1] = -1 (in
	// the integer representation used, which may be unsigned).
	template <typename Integer>
	inline std::pair<std::vector<Integer>, std::vector<Integer>> linearSieve(
		Integer const &N) {
		std::vector<Integer> minFactor(N + 1, -1), primes;
		for (Integer i{2}; i <= N; i++) {
			if (minFactor[i] == -1) {
				minFactor[i] = primes.size();
				primes.push_back(i);
			}
			for (Integer j{0}; i * primes[j] <= N; j++) {
				minFactor[i * primes[j]] = j;
				if (primes[j] == primes[minFactor[i]]) {
					break;
				}
			}
		}

		// C++17: guaranteed either NRVO or move.
		return {minFactor, primes};
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
	// GCD using Euclidean algorithm.
	template <typename Integer>
	inline Integer greatestCommonDivisor(Integer x, Integer y) {
		while (x != 0) {
			std::tie(y, x) = std::make_pair(x, y % x);
		}
		return y;
	}

	// GCD using extended Euclidean algorithm gives Bezout's identity
	// coefficients.
	template <typename Integer>
	inline std::tuple<Integer, Integer, Integer> greatestCommonDivisorExtended(
		Integer x,
		Integer y) {
		Integer cX{0}, cY{1}, nX{1}, nY{0}, ratio;
		while (x != 0) {
			ratio = y / x;
			std::tie(y, x) = std::make_pair(x, y - ratio * x);
			std::tie(cX, nX) = std::make_pair(nX, cX - ratio * nX);
			std::tie(cY, nY) = std::make_pair(nY, cY - ratio * nY);
		}
		return {y, cX, cY};
	}

	// LCM.
	template <typename Integer>
	inline Integer leastCommonMultiple(Integer const &x, Integer const &y) {
		return x / greatestCommonDivisor(x, y) * y;
	}
}

using namespace Rain::Algorithm;
using MF = ModulusField<LL, 1000000007>;

LL const MOD{1000000007};
LL N, C, ans{0};
unordered_map<LL, LL> pp, pc;

void fad(unordered_map<LL, LL>::iterator cur, LL divisor) {
	if (cur == pp.end()) {
		LL cnt{(N - C) / divisor};
		for (auto &i : pc) {
			if (i.second != pp[i.first]) {
				cnt = cnt * (i.first - 1) / i.first;
			}
		}
		if (cnt == (N - C) / divisor) {
			cnt--;
		}

		// cout << (N - C) << ": " << divisor << ": " << cnt << ": "
		// 		 << leastCommonMultiple(C, divisor) << '\n';
		ans = (ans + (leastCommonMultiple(C, divisor) * cnt) % MOD) % MOD;
		return;
	}
	RF(i, 0, cur->second + 1) {
		pc[cur->first] = i;
		fad(next(cur), divisor);
		divisor *= cur->first;
	}
}

int main(int, char const *[]) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> N;
	auto [minFactor, primes]{linearSieve(N)};
	RF(i, 1, N - 1) {
		C = i;
		pp.clear();
		pc.clear();
		for (LL i{N - C}; i > 1;) {
			pp[primes[minFactor[i]]]++;
			i /= primes[minFactor[i]];
		}

		// cout << '\t' << N - C << '\n';
		fad(pp.begin(), 1);
	}
	cout << ans << '\n';

	return 0;
}
