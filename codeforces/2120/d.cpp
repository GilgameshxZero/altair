#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC target("avx", "avx2", "fma", "bmi", "bmi2", "popcnt", "lzcnt")
#pragma GCC optimize("Ofast", "unroll-loops")
#endif

#include <bits/stdc++.h>

// For an overloaded function f, this wraps it in an rvalue-reference lambda so
// that it may be resolved via perfect forwarding.
#define RAIN_FUNCTIONAL_RESOLVE_OVERLOAD(f)          \
	[](auto &&...args) -> decltype(auto) {             \
		return f(std::forward<decltype(args)>(args)...); \
	}

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
	struct isStdHashable<Type,
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
	template <std::size_t SIZE_T_SIZE = sizeof(std::size_t),
		typename std::enable_if<SIZE_T_SIZE == 8>::type * = nullptr>
	static inline std::size_t combineHash(std::size_t &seed, std::size_t next) {
		return seed ^= next + 0x517cc1b727220a95 + (seed << 6) + (seed >> 2);
	}
	template <typename Type,
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
		template <typename TypeInner = Type,
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
		template <typename TypeInner = Type,
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
		template <typename TypeInner = Type,
			typename std::enable_if<!Functional::isStdHashable<TypeInner>::value &&
				Functional::isPair<TypeInner>::value>::type * = nullptr>
		std::size_t operator()(Type const &value) const {
			std::size_t result{0};
			combineHash(result, SplitMixHash<decltype(value.first)>{}(value.first));
			combineHash(result, SplitMixHash<decltype(value.second)>{}(value.second));
			return result;
		}

		// Unwraps a container.
		template <typename TypeInner = Type,
			typename std::enable_if<!Functional::isStdHashable<TypeInner>::value &&
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

		// Explicit copy constructor helps avoid compiler warnings on `clang`.
		ModulusField(ModulusField<Integer, MODULUS_OUTER> const &other)
				: MODULUS{MODULUS_OUTER}, value(other.value) {}

		// If the integer specified is signed and negative, we want to wrap it back
		// to the positives first.
		template <typename OtherInteger = std::size_t,
			std::size_t MODULUS_INNER = MODULUS_OUTER,
			typename std::enable_if<MODULUS_INNER != 0>::type * = nullptr,
			typename std::enable_if<
				!std::is_same<ModulusField<Integer, MODULUS_OUTER>,
					OtherInteger>::value>::type * = nullptr>
		ModulusField(OtherInteger const &value = 0)
				: MODULUS{MODULUS_OUTER},
					value(value < 0 ? this->MODULUS - ((0 - value) % this->MODULUS)
													: value % this->MODULUS) {}

		template <typename OtherInteger = std::size_t,
			std::size_t MODULUS_INNER = MODULUS_OUTER,
			typename std::enable_if<MODULUS_INNER == 0>::type * = nullptr>
		ModulusField(Integer const &modulus, OtherInteger const &value = 0)
				: MODULUS{modulus},
					value(value < 0 ? this->MODULUS - ((0 - value) % this->MODULUS)
													: value % this->MODULUS) {}

		// Builds a ModulusField<Integer, MODULUS_OUTER> type, but with the same
		// underlying modulus value. Uses more specialized SFINAE to differentiate
		// otherwise identical signatures.
		template <typename OtherInteger,
			std::size_t MODULUS_INNER = MODULUS_OUTER,
			typename std::enable_if<MODULUS_INNER != 0>::type * = nullptr>
		static ModulusField<Integer, MODULUS_OUTER> build(
			OtherInteger const &value) {
			return {value};
		}

		template <typename OtherInteger,
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
		// Other comparison operators only compare value and are prone to error.
		inline bool operator>(ModulusField<Integer, MODULUS_OUTER> const &other) {
			return this->value > other.value;
		}
		inline bool operator>=(ModulusField<Integer, MODULUS_OUTER> const &other) {
			return this->value >= other.value;
		}
		inline bool operator<(ModulusField<Integer, MODULUS_OUTER> const &other) {
			return this->value < other.value;
		}
		inline bool operator<=(ModulusField<Integer, MODULUS_OUTER> const &other) {
			return this->value <= other.value;
		}

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
		template <typename OtherInteger,
			typename std::enable_if<
				!std::is_same<OtherInteger, std::size_t>::value>::type * = nullptr>
		operator OtherInteger() const {
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
			invFactorials[N] = build(1) / factorials[N];
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
inline std::ostream &operator<<(std::ostream &stream,
	Rain::Algorithm::ModulusField<Integer, MODULUS_OUTER> const &right) {
	return stream << right.value;
}
template <typename Integer, std::size_t MODULUS_OUTER>
inline std::istream &operator>>(std::istream &stream,
	Rain::Algorithm::ModulusField<Integer, MODULUS_OUTER> &right) {
	stream >> right.value;
	right.value = (right.modulus + right.value) % right.modulus;
	return stream;
}

// Hash operator for this user-defined type, which hashes the inner value (not
// the modulus).
namespace std {
	template <typename Integer, std::size_t MODULUS_OUTER>
	struct hash<Rain::Algorithm::ModulusField<Integer, MODULUS_OUTER>> {
		size_t operator()(
			Rain::Algorithm::ModulusField<Integer, MODULUS_OUTER> const &value)
			const {
			return Rain::Random::SplitMixHash<Integer>{}(value.value);
		}
	};
}

using LL = long long;
using LD = long double;
using namespace std;

#define RF(x, from, to) \
	for (LL x(from), _to(to), _delta{x < _to ? 1LL : -1LL}; x != _to; x += _delta)

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL T;
	cin >> T;
	while (T--) {
		LL A, B, K;
		cin >> A >> B >> K;

		LL RT{(A - 1) * K + 1}, R{A};
		Rain::Algorithm::ModulusField<LL, 1000000007> ZR{RT}, ZC{RT};
		ZC = ZC.choose(A);
		ZC *= K;
		ZC *= B - 1;
		ZC++;

		cout << ZR << ' ' << ZC << '\n';
	}

	return 0;
}
