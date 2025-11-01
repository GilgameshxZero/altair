#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC target("avx", "avx2", "fma", "bmi", "bmi2", "popcnt", "lzcnt")
#pragma GCC optimize("Ofast", "unroll-loops")
#endif

#include <bits/stdc++.h>

namespace Rain {
	// Inline namespaces are implicitly accessible by the parent namespace.
	inline namespace Literal {
		// Inject std literals into the Rain namespace. Injecting the entire
		// namespace via `using namespace std::literals` may cause compilation
		// issues with default arguments using those literals.
		using std::string_literals::operator""s;
		using std::chrono_literals::operator""h;
		using std::chrono_literals::operator""s;
		using std::chrono_literals::operator""ms;

		// User-defined literals.
		inline constexpr std::size_t operator""_zu(unsigned long long value) {
			return static_cast<std::size_t>(value);
		}
		inline std::regex operator""_re(char const *value, std::size_t) {
			return std::regex(value);
		}
		inline constexpr short operator""_ss(unsigned long long value) {
			return static_cast<short>(value);
		}
	}
}

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

	// Similar to `std::is_base_of`, but for template base types.
	namespace {
		template <template <typename...> class Type, typename... TypeTemplate>
		std::true_type isBaseOfTemplateImpl(Type<TypeTemplate...> const *);
		template <template <typename...> class Type>
		std::false_type isBaseOfTemplateImpl(...);
	}
	template <template <typename...> class TypeBase, typename TypeDerived>
	using isBaseOfTemplate =
		decltype(isBaseOfTemplateImpl<TypeBase>(std::declval<TypeDerived *>()));

	template <typename Type, typename = std::void_t<>>
	struct isStdHashable : std::false_type {};
	template <typename Type>
	struct isStdHashable<
		Type,
		std::void_t<decltype(std::declval<std::hash<Type>>()(
			std::declval<Type>()))>> : std::true_type {};

	// SFINAE-friendly comparators.
	template <std::size_t LEFT, std::size_t RIGHT>
	struct isEqualTo {
		static constexpr bool value{LEFT == RIGHT};
	};
	template <std::size_t LEFT, std::size_t RIGHT>
	struct isLessThan {
		static constexpr bool value{LEFT < RIGHT};
	};
	template <std::size_t LEFT, std::size_t RIGHT>
	struct isGreaterThan {
		static constexpr bool value{LEFT > RIGHT};
	};
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
				Functional::isBaseOfTemplate<std::pair, TypeInner>::value>::type * =
				nullptr>
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
				!Functional::isBaseOfTemplate<std::pair, TypeInner>::value &&
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
	// Forward declaration.
	template <std::size_t = 0, bool = false>
	class BigInt;
}

namespace std {
	// Limits.
	template <std::size_t LOG_BITS, bool SIGNED>
	class numeric_limits<Rain::Algorithm::BigInt<LOG_BITS, SIGNED>> {
		public:
		using ThisInt = Rain::Algorithm::BigInt<LOG_BITS, SIGNED>;

		static constexpr ThisInt min() {
			return {
				numeric_limits<typename ThisInt::SmallerIntUnsigned>::min(),
				numeric_limits<typename ThisInt::SmallerInt>::min()};
		};
		static constexpr ThisInt max() {
			return {
				numeric_limits<typename ThisInt::SmallerIntUnsigned>::max(),
				numeric_limits<typename ThisInt::SmallerInt>::max()};
		};
	};
}

namespace Rain::Algorithm {
	template <>
	class BigInt<0, false> {
		public:
		// We must use our own templated SFINAE base class checker, like in
		// `ModulusRingBase`.
		template <std::size_t LOG_BITS, bool SIGNED>
		static std::true_type isDerivedFromBigIntImpl(
			BigInt<LOG_BITS, SIGNED> const *);
		template <std::size_t = 0, bool = true>
		static std::false_type isDerivedFromBigIntImpl(...);
		template <typename TypeDerived>
		using isDerivedFromBigInt =
			decltype(isDerivedFromBigIntImpl(std::declval<TypeDerived *>()));
	};

	// Shorthands.
	template <std::size_t LOG_BITS>
	using BigIntSigned = BigInt<LOG_BITS, true>;

	template <std::size_t LOG_BITS>
	using BigIntUnsigned = BigInt<LOG_BITS, false>;

	// Maps log bits to the system type or big int type. Helps with template
	// specialization recursion.
	template <std::size_t LOG_BITS, bool SIGNED>
	class BigIntTypeMap {
		public:
		using Type = BigInt<LOG_BITS, SIGNED>;
	};

	// Template recursion base case 2**5 = 32. Requires 64-bit integer to be
	// available to support the overflow multiplication & division defined later.
	template <>
	class BigIntTypeMap<5, true> {
		public:
		using Type = std::int32_t;
	};
	template <>
	class BigIntTypeMap<5, false> {
		public:
		using Type = std::uint32_t;
	};

	// Overflow multiplication and division. Multiplication returns {low, high} of
	// the result. Division returns {low, high} of the result.
	template <std::size_t LOG_BITS, bool SIGNED>
	inline std::pair<
		typename BigIntTypeMap<LOG_BITS, false>::Type,
		typename BigIntTypeMap<LOG_BITS, SIGNED>::Type>
	bigIntMultiply(
		typename BigIntTypeMap<LOG_BITS, SIGNED>::Type const &X,
		typename BigIntTypeMap<LOG_BITS, SIGNED>::Type const &Y) {
		using ThisIntUnsigned = typename BigIntTypeMap<LOG_BITS, false>::Type;
		using ThisInt = typename BigIntTypeMap<LOG_BITS, SIGNED>::Type;
		auto [lll, llh]{bigIntMultiply<LOG_BITS - 1, false>(X.low, Y.low)};
		auto [lhl, lhh]{bigIntMultiply<LOG_BITS - 1, SIGNED>(X.low, Y.high)};
		auto [hll, hlh]{bigIntMultiply<LOG_BITS - 1, SIGNED>(X.high, Y.low)};
		auto [hhl, hhh]{bigIntMultiply<LOG_BITS - 1, SIGNED>(X.high, Y.high)};
		ThisIntUnsigned first{lll, 0};
		ThisInt second{0, hhh};
		char firstHighFlow{0}, secondLowFlow{0};
		firstHighFlow -= (llh < 0);
		first.high += llh;
		firstHighFlow +=
			(first.high >
			 std::numeric_limits<typename ThisIntUnsigned::SmallerInt>::max() - lhl);
		first.high += lhl;
		firstHighFlow +=
			(first.high >
			 std::numeric_limits<typename ThisIntUnsigned::SmallerInt>::max() - hll);
		first.high += hll;
		secondLowFlow -= (firstHighFlow < 0);
		second.low += firstHighFlow;
		secondLowFlow +=
			(lhh > 0 &&
			 second.low >
				 std::numeric_limits<typename ThisInt::SmallerIntUnsigned>::max() -
					 lhh) -
			(lhh < 0 &&
			 second.low <
				 std::numeric_limits<typename ThisInt::SmallerIntUnsigned>::min() -
					 lhh);
		second.low += lhh;
		secondLowFlow +=
			(hlh > 0 &&
			 second.low >
				 std::numeric_limits<typename ThisInt::SmallerIntUnsigned>::max() -
					 hlh) -
			(hlh < 0 &&
			 second.low <
				 std::numeric_limits<typename ThisInt::SmallerIntUnsigned>::min() -
					 hlh);
		second.low += hlh;
		secondLowFlow +=
			(hhl > 0 &&
			 second.low >
				 std::numeric_limits<typename ThisInt::SmallerIntUnsigned>::max() -
					 hhl) -
			(hhl < 0 &&
			 second.low <
				 std::numeric_limits<typename ThisInt::SmallerIntUnsigned>::min() -
					 hhl);
		second.low += hhl;
		second.high += secondLowFlow;
		return {first, second};
	}
	template <>
	inline std::pair<
		typename BigIntTypeMap<5, false>::Type,
		typename BigIntTypeMap<5, false>::Type>
	bigIntMultiply<5, false>(
		typename BigIntTypeMap<5, false>::Type const &X,
		typename BigIntTypeMap<5, false>::Type const &Y) {
		using ThisIntUnsigned = typename BigIntTypeMap<5, false>::Type;

		std::uint64_t result{X};
		result *= Y;
		return {
			static_cast<ThisIntUnsigned>(result),
			static_cast<ThisIntUnsigned>(result >> 32)};
	}
	template <>
	inline std::pair<
		typename BigIntTypeMap<5, false>::Type,
		typename BigIntTypeMap<5, true>::Type>
	bigIntMultiply<5, true>(
		typename BigIntTypeMap<5, true>::Type const &X,
		typename BigIntTypeMap<5, true>::Type const &Y) {
		using ThisIntUnsigned = typename BigIntTypeMap<5, false>::Type;
		using ThisInt = typename BigIntTypeMap<5, true>::Type;

		std::int64_t result{X};
		result *= Y;
		return {
			static_cast<ThisIntUnsigned>(result), static_cast<ThisInt>(result >> 32)};
	}

	template <std::size_t LOG_BITS, bool SIGNED>
	inline typename BigIntTypeMap<LOG_BITS, SIGNED>::Type bigIntDivide(
		typename BigIntTypeMap<LOG_BITS, SIGNED>::Type X,
		typename BigIntTypeMap<LOG_BITS, SIGNED>::Type Y) {
		using ThisInt = typename BigIntTypeMap<LOG_BITS, SIGNED>::Type;
		if (Y == 0) {
			throw std::runtime_error("Cannot divide by 0.");
		}

		bool negative((X < 0) ^ (Y < 0));
		if (X < 0) {
			X *= -1;
		}
		if (Y < 0) {
			Y *= -1;
		}
		if (Y == 1) {
			return negative ? -X : X;
		}

		ThisInt low{0}, high{X};
		while (low + 1 < high) {
			ThisInt mid{low + ((high - low) >> 1)};
			auto [productLow, productHigh]{bigIntMultiply<LOG_BITS, SIGNED>(mid, Y)};
			if (productHigh > 0 || productLow > X) {
				high = mid;
			} else {
				low = mid;
			}
		}
		return negative ? -low : low;
	}
	template <bool SIGNED>
	inline typename BigIntTypeMap<5, SIGNED>::Type bigIntDivide(
		typename BigIntTypeMap<5, SIGNED>::Type X,
		typename BigIntTypeMap<5, SIGNED>::Type Y) {
		return X / Y;
	}

	// Two ints of half the size form a larger int. Implements arithmetic, bit
	// shift, binary, and modulus operators, as well as comparison, i/o, and cast
	// operators. Unsigned overflow/underflow is well-defined, but not signed
	// overflow/underflow.
	template <std::size_t LOG_BITS, bool SIGNED>
	class BigInt {
		public:
		using ThisInt = BigInt<LOG_BITS, SIGNED>;
		using SmallerIntUnsigned =
			typename BigIntTypeMap<LOG_BITS - 1, false>::Type;
		using SmallerInt = typename BigIntTypeMap<LOG_BITS - 1, SIGNED>::Type;

		static std::size_t const halfBits{1_zu << (LOG_BITS - 1)};

		SmallerIntUnsigned low;
		SmallerInt high;

		template <
			typename Integer = int,
			typename std::enable_if<sizeof(Integer) * 8 <= halfBits>::type * =
				nullptr>
		BigInt(Integer const &value = 0) : low(value), high((value < 0) ? -1 : 0) {}
		template <
			typename Integer = int,
			typename std::enable_if<sizeof(Integer) * 8 == halfBits * 2>::type * =
				nullptr>
		BigInt(Integer const &value = 0)
				: low(static_cast<SmallerIntUnsigned>(value)),
					high(static_cast<SmallerInt>(value >> (1_zu << (LOG_BITS - 1)))) {}

		// Constructing with bool.
		BigInt(bool const value) : low(value ? 1 : 0), high(0) {}

		// Constructing with a larger int than storable is ill-advised and disabled.

		// Can also construct with the two components.
		BigInt(SmallerIntUnsigned const &low, SmallerInt const &high = 0)
				: low(low), high(high) {}

		// Explicit copy constructor helps avoid compiler warnings on `clang`.
		BigInt(BigInt<LOG_BITS, SIGNED> const &other)
				: low{other.low}, high(other.high) {}
		template <
			bool OTHER_SIGNED,
			typename std::enable_if<OTHER_SIGNED != SIGNED>::type * = nullptr>
		BigInt(BigInt<LOG_BITS, OTHER_SIGNED> const &other)
				: low{other.low}, high(other.high) {}

		// Assignment.
		template <
			typename OtherInteger,
			typename std::enable_if<!std::is_same<ThisInt, OtherInteger>::value>::type
				* = nullptr>
		ThisInt &operator=(OtherInteger const &other) {
			return *this = ThisInt(other);
		}
		ThisInt &operator=(ThisInt const &other) {
			if (this == &other) {
				return *this;
			}
			this->low = other.low;
			this->high = other.high;
			return *this;
		}

		// Comparison.
		template <
			typename OtherInteger,
			typename std::enable_if<!std::is_same<ThisInt, OtherInteger>::value>::type
				* = nullptr>
		inline bool operator==(OtherInteger const &other) const {
			return *this == ThisInt(other);
		}
		inline bool operator==(ThisInt const &other) const {
			return this->low == other.low && this->high == other.high;
		}
		template <
			typename OtherInteger,
			typename std::enable_if<!std::is_same<ThisInt, OtherInteger>::value>::type
				* = nullptr>
		inline bool operator<(OtherInteger const &other) const {
			return *this < ThisInt(other);
		}
		inline bool operator<(ThisInt const &other) const {
			return this->high < other.high ||
				(this->high == other.high && this->low < other.low);
		}
		template <
			typename OtherInteger,
			typename std::enable_if<!std::is_same<ThisInt, OtherInteger>::value>::type
				* = nullptr>
		inline bool operator<=(OtherInteger const &other) const {
			return *this <= ThisInt(other);
		}
		inline bool operator<=(ThisInt const &other) const {
			return *this < other || *this == other;
		}
		template <
			typename OtherInteger,
			typename std::enable_if<!std::is_same<ThisInt, OtherInteger>::value>::type
				* = nullptr>
		inline bool operator>(OtherInteger const &other) const {
			return *this > ThisInt(other);
		}
		inline bool operator>(ThisInt const &other) const {
			return !(*this <= other);
		}
		template <
			typename OtherInteger,
			typename std::enable_if<!std::is_same<ThisInt, OtherInteger>::value>::type
				* = nullptr>
		inline bool operator>=(OtherInteger const &other) const {
			return *this >= ThisInt(other);
		}
		inline bool operator>=(ThisInt const &other) const {
			return !(*this < other);
		}

		// Shift.
		template <typename OtherInteger>
		inline ThisInt operator>>(OtherInteger const &shift) const {
			if (shift >= static_cast<OtherInteger>(halfBits * 2)) {
				return 0;
			} else if (shift >= static_cast<OtherInteger>(halfBits)) {
				return ThisInt{static_cast<SmallerIntUnsigned>(this->high), 0} >>
					(shift - halfBits);
			}
			ThisInt tmp{this->low >> shift, this->high >> shift};
			SmallerInt lost{this->high - (tmp.high << shift)};
			return {tmp.low + (lost << (halfBits - shift)), tmp.high};
		}
		template <typename OtherInteger>
		inline ThisInt &operator>>=(OtherInteger const &shift) {
			return *this = *this >> shift;
		}
		template <typename OtherInteger>
		inline ThisInt operator<<(OtherInteger const &shift) const {
			if (shift >= static_cast<OtherInteger>(halfBits * 2)) {
				return 0;
			} else if (shift >= static_cast<OtherInteger>(halfBits)) {
				return ThisInt{0, static_cast<SmallerInt>(this->low)}
				<< (shift - halfBits);
			}
			ThisInt tmp{this->low << shift, this->high << shift};
			SmallerIntUnsigned lost{this->low - (tmp.low >> shift)};
			return {
				tmp.low,
				tmp.high + static_cast<SmallerInt>(lost >> (halfBits - shift))};
		}
		template <typename OtherInteger>
		inline ThisInt &operator<<=(OtherInteger const &shift) {
			return *this = *this << shift;
		}

		// Binary.
		inline ThisInt operator&(ThisInt const &other) const {
			return {this->low & other.low, this->high & other.high};
		}
		inline ThisInt operator|(ThisInt const &other) const {
			return {this->low & other.low, this->high & other.high};
		}

		// Cast.
		explicit operator bool() const { return *this != 0; }
		operator BigInt<LOG_BITS, !SIGNED>() const {
			return {
				this->low,
				static_cast<typename BigIntTypeMap<LOG_BITS - 1, !SIGNED>::Type>(
					this->high)};
		}
		operator typename BigIntTypeMap<5, SIGNED>::Type() const {
			if (this->high < 0) {
				auto tmp{
					std::numeric_limits<SmallerIntUnsigned>::max() - this->low + 1};
				return static_cast<typename BigIntTypeMap<5, SIGNED>::Type>(0 - tmp);
			}
			return static_cast<typename BigIntTypeMap<5, SIGNED>::Type>(this->low);
		}

		// Arithmetic.
		template <
			typename OtherInteger,
			typename std::enable_if<!std::is_same<ThisInt, OtherInteger>::value>::type
				* = nullptr>
		inline ThisInt operator+(OtherInteger const &other) const {
			return *this + ThisInt(other);
		}
		inline ThisInt operator+(ThisInt const &other) const {
			// Unsigned overflow is well-defined.
			return {
				this->low + other.low,
				this->high + other.high +
					(other.low >
					 std::numeric_limits<SmallerIntUnsigned>::max() - this->low)};
		}
		template <typename OtherInteger>
		inline ThisInt &operator+=(OtherInteger const &other) {
			return *this = *this + other;
		}
		template <
			typename OtherInteger,
			typename std::enable_if<!std::is_same<ThisInt, OtherInteger>::value>::type
				* = nullptr>
		inline ThisInt operator-(OtherInteger const &other) const {
			return *this - ThisInt(other);
		}
		inline ThisInt operator-(ThisInt const &other) const {
			// Unsigned overflow is well-defined.
			return {
				this->low - other.low,
				this->high - other.high - (this->low < other.low)};
		}
		template <typename OtherInteger>
		inline ThisInt &operator-=(OtherInteger const &other) {
			return *this = *this - other;
		}
		template <
			typename OtherInteger,
			typename std::enable_if<!std::is_same<ThisInt, OtherInteger>::value>::type
				* = nullptr>
		inline ThisInt operator*(OtherInteger const &other) const {
			return *this * ThisInt(other);
		}
		inline ThisInt operator*(ThisInt const &other) const {
			auto [first, second]{bigIntMultiply<LOG_BITS, SIGNED>(*this, other)};
			if (second < 0) {
				auto tmp{
					std::numeric_limits<
						typename BigIntTypeMap<LOG_BITS, false>::Type>::max() -
					first + 1};
				return ThisInt(0, 0) - ThisInt(tmp.low, tmp.high);
			}
			return first;
		}
		template <typename OtherInteger>
		inline ThisInt &operator*=(OtherInteger const &other) {
			return *this = *this * other;
		}
		template <
			typename OtherInteger,
			typename std::enable_if<!std::is_same<ThisInt, OtherInteger>::value>::type
				* = nullptr>
		inline ThisInt operator/(OtherInteger const &other) const {
			return *this / ThisInt(other);
		}
		inline ThisInt operator/(ThisInt const &other) const {
			return bigIntDivide<LOG_BITS, SIGNED>(*this, other);
		}
		template <typename OtherInteger>
		inline ThisInt &operator/=(OtherInteger const &other) {
			return *this = *this / other;
		}
		template <
			typename OtherInteger,
			typename std::enable_if<!std::is_same<ThisInt, OtherInteger>::value>::type
				* = nullptr>
		inline ThisInt operator%(OtherInteger const &other) const {
			return *this % ThisInt(other);
		}
		inline ThisInt operator%(ThisInt const &other) const {
			auto quotient{*this / other};
			return *this - other * quotient;
		}
		template <typename OtherInteger>
		inline ThisInt &operator%=(OtherInteger const &other) {
			return *this = *this % other;
		}

		// Unary.
		inline ThisInt operator-() const { return ThisInt(0, 0) - *this; }
		inline ThisInt operator++() { return *this += 1; }
		inline ThisInt operator++(int) {
			auto tmp(*this);
			*this += 1;
			return tmp;
		}
		inline ThisInt operator--() { return *this -= 1; }
		inline ThisInt operator--(int) {
			auto tmp(*this);
			*this -= 1;
			return tmp;
		}
	};
}

template <
	typename OtherInteger,
	std::size_t LOG_BITS,
	bool SIGNED,
	typename std::enable_if<!Rain::Algorithm::BigInt<>::isDerivedFromBigInt<
		OtherInteger>::value>::type * = nullptr>
inline Rain::Algorithm::BigInt<LOG_BITS, SIGNED> operator+(
	OtherInteger const &left,
	Rain::Algorithm::BigInt<LOG_BITS, SIGNED> const &right) {
	return Rain::Algorithm::BigInt<LOG_BITS, SIGNED>(left) + right;
}
template <
	typename OtherInteger,
	std::size_t LOG_BITS,
	bool SIGNED,
	typename std::enable_if<!Rain::Algorithm::BigInt<>::isDerivedFromBigInt<
		OtherInteger>::value>::type * = nullptr>
inline Rain::Algorithm::BigInt<LOG_BITS, SIGNED> operator-(
	OtherInteger const &left,
	Rain::Algorithm::BigInt<LOG_BITS, SIGNED> const &right) {
	return Rain::Algorithm::BigInt<LOG_BITS, SIGNED>(left) - right;
}
template <
	typename OtherInteger,
	std::size_t LOG_BITS,
	bool SIGNED,
	typename std::enable_if<!Rain::Algorithm::BigInt<>::isDerivedFromBigInt<
		OtherInteger>::value>::type * = nullptr>
inline Rain::Algorithm::BigInt<LOG_BITS, SIGNED> operator*(
	OtherInteger const &left,
	Rain::Algorithm::BigInt<LOG_BITS, SIGNED> const &right) {
	return Rain::Algorithm::BigInt<LOG_BITS, SIGNED>(left) * right;
}
template <
	typename OtherInteger,
	std::size_t LOG_BITS,
	bool SIGNED,
	typename std::enable_if<!Rain::Algorithm::BigInt<>::isDerivedFromBigInt<
		OtherInteger>::value>::type * = nullptr>
inline Rain::Algorithm::BigInt<LOG_BITS, SIGNED> operator/(
	OtherInteger const &left,
	Rain::Algorithm::BigInt<LOG_BITS, SIGNED> const &right) {
	return Rain::Algorithm::BigInt<LOG_BITS, SIGNED>(left) / right;
}
template <
	typename OtherInteger,
	std::size_t LOG_BITS,
	bool SIGNED,
	typename std::enable_if<!Rain::Algorithm::BigInt<>::isDerivedFromBigInt<
		OtherInteger>::value>::type * = nullptr>
inline Rain::Algorithm::BigInt<LOG_BITS, SIGNED> operator%(
	OtherInteger const &left,
	Rain::Algorithm::BigInt<LOG_BITS, SIGNED> const &right) {
	return Rain::Algorithm::BigInt<LOG_BITS, SIGNED>(left) % right;
}

template <std::size_t LOG_BITS, bool SIGNED>
inline std::ostream &operator<<(
	std::ostream &stream,
	Rain::Algorithm::BigInt<LOG_BITS, SIGNED> const &right) {
	if (right < 0) {
		stream.put('-');
		return stream << -right;
	}
	if (right > 9) {
		stream << (right / 10);
	}
	auto first{right % 10};
	auto second{
		static_cast<typename Rain::Algorithm::BigIntTypeMap<5, SIGNED>::Type>(
			first)};
	return stream.put(second + '0');
}
template <std::size_t LOG_BITS, bool SIGNED>
inline std::istream &operator>>(
	std::istream &stream,
	Rain::Algorithm::BigInt<LOG_BITS, SIGNED> &right) {
	std::string s;
	stream >> s;
	right = 0;
	for (char const &i : s) {
		right = right * 10 + (i - '0');
	}
	return stream;
}

// Hash operator for this user-defined type, which combines hashes of the inner
// type.
namespace std {
	template <std::size_t LOG_BITS, bool SIGNED>
	struct hash<Rain::Algorithm::BigInt<LOG_BITS, SIGNED>> {
		size_t operator()(
			Rain::Algorithm::BigInt<LOG_BITS, SIGNED> const &value) const {
			size_t result{
				Rain::Random::SplitMixHash<decltype(value.high)>{}(value.high)};
			Rain::Random::combineHash(
				result, Rain::Random::SplitMixHash<decltype(value.low)>{}(value.low));
			return result;
		}
	};
}

using LL = long long;
using LD = long double;
using namespace std;

#define RF(x, from, to) \
	for (LL x(from), _to(to), _delta{x < _to ? 1LL : -1LL}; x != _to; x += _delta)

using BI = Rain::Algorithm::BigIntUnsigned<10>;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL N;
	cin >> N;
	vector<LL> R(N);
	vector<BI> P(N);
	RF(i, 0, N) {
		cin >> R[i];
	}
	P[0] = R[0];
	RF(i, 1, N) {
		P[i] = P[i - 1] * R[i];
	}
	BI Z{0}, A{1};
	RF(i, N - 1, 0) {
		BI B{A};
		RF(j, i - 1, -1) {
			LL D{0};
			RF(k, 1, R[i] + 1) {
				D += max(R[j] - k, 0LL);
			}
			Z += D * (j > 0 ? B * P[j - 1] : B);
			B *= R[j];
		}
		A *= R[i];
	}
	BI F{1000000000000};
	F *= F;
	BI G{F * 1000000}, F2{F / 2};
	BI Y(Z * G / P[N - 1]), X{Y % G}, W{X / F};
	// cout << Y << '\n';
	if (X % F == F2) {
		if (W % 2 == 0) {
			X--;
		}
	}
	X += F2;
	cout << Y / G << '.' << setfill('0') << setw(6) << (LL)(X / F);

	return 0;
}
