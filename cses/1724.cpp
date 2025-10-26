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
	template <
		typename = std::nullptr_t,
		typename = std::nullptr_t,
		std::size_t = 0>
	class ModulusRingBase;

	template <>
	class ModulusRingBase<std::nullptr_t, std::nullptr_t, 0> {
		public:
		// We must use our own templated SFINAE base class checker, since the one
		// provided in Functional cannot work with non-type template parameters.
		template <typename Derived, typename Underlying, std::size_t MODULUS_OUTER>
		static std::true_type isDerivedFromModulusRingImpl(
			ModulusRingBase<Derived, Underlying, MODULUS_OUTER> const *);
		// Must include default types here in case deduction fails (which it almost
		// certainly will, and trigger SFINAE if it does, which is bad, since we
		// need this type to be defined).
		template <typename = void *, typename = void *, std::size_t = 0>
		static std::false_type isDerivedFromModulusRingImpl(...);
		template <typename TypeDerived>
		using isDerivedFromModulusRing =
			decltype(isDerivedFromModulusRingImpl(std::declval<TypeDerived *>()));
	};

	// Implementation for a modulus ring CRTP over the integers,
	// supporting basic operations add, subtract, multiply in O(1) and divide in
	// O(ln M). Division is generally only valid for prime moduli. For O(1)
	// division, cache multiplicative inverses and multiply with those.
	//
	// A runtime modulus may be specified with MODULUS 0 in the template and the
	// appropriate constructor.
	//
	// Underlying must be large enough to store (modulus() - 1)^2.
	//
	// Polymorphism CRTP is similar to the 2D CRTP in Networking, but without the
	// additional layers and complexity.
	template <typename Derived, typename Underlying, std::size_t MODULUS_OUTER>
	class ModulusRingBase {
		private:
		using TypeThis = ModulusRingBase<Derived, Underlying, MODULUS_OUTER>;
		template <typename TypeDerived>
		using isDerivedFromModulusRing =
			ModulusRingBase<>::isDerivedFromModulusRing<TypeDerived>;

		public:
		Underlying const MODULUS;
		Underlying value;

		// Construction with a raw value will directly take the value. Construction
		// with another ModulusRingBase will call the % operator on the other's
		// value, which will always stay in range of the other's ring. This value is
		// then explicitly cast into the current underlying type.
		//
		// If the integer specified is signed and negative, we want to wrap it back
		// to the positives first.
		//
		// Use () instead of {} for value to explicitly trigger narrowing casts, if
		// necessary.
		template <
			typename Integer = std::size_t,
			typename std::enable_if<!isDerivedFromModulusRing<Integer>::value>::type
				* = nullptr,
			std::size_t MODULUS_INNER = MODULUS_OUTER,
			typename std::enable_if<MODULUS_INNER != 0>::type * = nullptr>
		ModulusRingBase(Integer const &value = 0)
				: MODULUS{MODULUS_OUTER},
					value(
						value < 0 ? this->MODULUS - ((0 - value) % this->MODULUS)
											: value % this->MODULUS) {}
		template <
			typename Integer = std::size_t,
			typename std::enable_if<!isDerivedFromModulusRing<Integer>::value>::type
				* = nullptr,
			std::size_t MODULUS_INNER = MODULUS_OUTER,
			typename std::enable_if<MODULUS_INNER == 0>::type * = nullptr>
		ModulusRingBase(Underlying const &modulus, Integer const &value = 0)
				: MODULUS{modulus},
					value(
						value < 0 ? this->MODULUS - ((0 - value) % this->MODULUS)
											: value % this->MODULUS) {}
		template <
			typename OtherDerived,
			typename OtherUnderlying,
			std::size_t OTHER_MODULUS_OUTER,
			std::size_t MODULUS_INNER = MODULUS_OUTER,
			typename std::enable_if<MODULUS_INNER != 0>::type * = nullptr>
		ModulusRingBase(
			ModulusRingBase<OtherDerived, OtherUnderlying, OTHER_MODULUS_OUTER> const
				&other)
				: MODULUS{MODULUS_OUTER},
					value(
						other.value < 0
							? this->MODULUS - ((0 - other.value) % this->MODULUS)
							: other.value % this->MODULUS) {}
		template <
			typename OtherDerived,
			typename OtherUnderlying,
			std::size_t OTHER_MODULUS_OUTER,
			std::size_t MODULUS_INNER = MODULUS_OUTER,
			typename std::enable_if<MODULUS_INNER == 0>::type * = nullptr>
		ModulusRingBase(
			Underlying const &modulus,
			ModulusRingBase<OtherDerived, OtherUnderlying, OTHER_MODULUS_OUTER> const
				&other)
				: MODULUS{modulus},
					value(
						other.value < 0
							? this->MODULUS - ((0 - other.value) % this->MODULUS)
							: other.value % this->MODULUS) {}

		// Explicit copy constructor helps avoid compiler warnings on `clang`.
		ModulusRingBase(TypeThis const &other)
				: MODULUS{other.MODULUS},
					value{
						other.value < 0
							? this->MODULUS - ((0 - other.value) % this->MODULUS)
							: other.value % this->MODULUS} {}

		// Builds a Derived type, but with the same underlying modulus value. Uses
		// more specialized SFINAE to differentiate otherwise identical signatures.
		template <
			typename Integer,
			std::size_t MODULUS_INNER = MODULUS_OUTER,
			typename std::enable_if<MODULUS_INNER != 0>::type * = nullptr>
		static Derived build(Integer const &value) {
			return Derived(value);
		}
		template <
			typename Integer,
			std::size_t MODULUS_INNER = MODULUS_OUTER,
			typename std::enable_if<MODULUS_INNER == 0>::type * = nullptr>
		Derived build(Integer const &value) const {
			return {this->MODULUS, value};
		}

		// Assignment operators need to be overloaded as this class stores an
		// additional modulus, which implicitly deletes the default assignment
		// operator.
		//
		// Assignment only assigns the value. On some compilers (MSVC), it is
		// helpful to have an explicit overload for the current type.
		template <
			typename Integer,
			typename std::enable_if<!isDerivedFromModulusRing<Integer>::value>::type
				* = nullptr>
		auto &operator=(Integer const &other) {
			return *this = build(other);
		}
		template <
			typename OtherDerived,
			typename OtherUnderlying,
			std::size_t OTHER_MODULUS_FIELD>
		auto &operator=(
			ModulusRingBase<OtherDerived, OtherUnderlying, OTHER_MODULUS_FIELD> const
				&other) {
			// Like in the constructor, we should force this modulus first.
			this->value = other.value % this->MODULUS;
			return *this;
		}
		auto &operator=(TypeThis const &other) {
			this->value = other.value % this->MODULUS;
			return *this;
		}

		// Casts are explicit to prevent errors. However, this may still be
		// deceptive.
		template <
			typename Integer,
			typename std::enable_if<!isDerivedFromModulusRing<Integer>::value>::type
				* = nullptr>
		explicit operator Integer() const {
			return static_cast<Integer>(this->value);
		}

		// Comparison on integer types will first bring the integer into the ring.
		// Comparison with other modulus types will compare the value directly.
		// Some operators are generated by the compiler automatically.
		template <
			typename Integer,
			typename std::enable_if<!isDerivedFromModulusRing<Integer>::value>::type
				* = nullptr>
		inline auto operator==(Integer const &other) const {
			return *this == build(other);
		}
		template <
			typename OtherDerived,
			typename OtherUnderlying,
			std::size_t OTHER_MODULUS_OUTER>
		inline auto operator==(
			ModulusRingBase<OtherDerived, OtherUnderlying, OTHER_MODULUS_OUTER> const
				&other) const {
			// Ignores modulus comparison!
			return this->value == other.value;
		}
		template <
			typename Integer,
			typename std::enable_if<!isDerivedFromModulusRing<Integer>::value>::type
				* = nullptr>
		inline auto operator<(Integer const &other) const {
			return *this < build(other);
		}
		template <
			typename OtherDerived,
			typename OtherUnderlying,
			std::size_t OTHER_MODULUS_OUTER>
		inline auto operator<(
			ModulusRingBase<OtherDerived, OtherUnderlying, OTHER_MODULUS_OUTER> const
				&other) const {
			return this->value < other.value;
		}
		template <
			typename Integer,
			typename std::enable_if<!isDerivedFromModulusRing<Integer>::value>::type
				* = nullptr>
		inline auto operator<=(Integer const &other) const {
			return *this <= build(other);
		}
		template <
			typename OtherDerived,
			typename OtherUnderlying,
			std::size_t OTHER_MODULUS_OUTER>
		inline auto operator<=(
			ModulusRingBase<OtherDerived, OtherUnderlying, OTHER_MODULUS_OUTER> const
				&other) const {
			return *this < other || *this == other;
		}
		template <
			typename Integer,
			typename std::enable_if<!isDerivedFromModulusRing<Integer>::value>::type
				* = nullptr>
		inline auto operator>(Integer const &other) const {
			return *this > build(other);
		}
		template <
			typename OtherDerived,
			typename OtherUnderlying,
			std::size_t OTHER_MODULUS_OUTER>
		inline auto operator>(
			ModulusRingBase<OtherDerived, OtherUnderlying, OTHER_MODULUS_OUTER> const
				&other) const {
			return !(*this <= other);
		}
		template <
			typename Integer,
			typename std::enable_if<!isDerivedFromModulusRing<Integer>::value>::type
				* = nullptr>
		inline auto operator>=(Integer const &other) const {
			return *this >= build(other);
		}
		template <
			typename OtherDerived,
			typename OtherUnderlying,
			std::size_t OTHER_MODULUS_OUTER>
		inline auto operator>=(
			ModulusRingBase<OtherDerived, OtherUnderlying, OTHER_MODULUS_OUTER> const
				&other) const {
			return *this > other || *this == other;
		}

		// Arithmetic can only be performed between ModulusRingBases with the same
		// moduli, or with raw integers. Arithmetic on raw integers first builds
		// them into this type.
		template <
			typename Integer,
			typename std::enable_if<!isDerivedFromModulusRing<Integer>::value>::type
				* = nullptr>
		inline auto operator+(Integer const &other) const {
			return *this + build(other);
		}
		template <
			typename OtherDerived,
			typename OtherUnderlying,
			std::size_t OTHER_MODULUS_OUTER>
		inline auto operator+(
			ModulusRingBase<OtherDerived, OtherUnderlying, OTHER_MODULUS_OUTER> const
				&other) const {
			return build(this->value + other.value);
		}
		template <typename Integer>
		inline auto &operator+=(Integer const &other) {
			return *this = *this + other;
		}
		template <
			typename Integer,
			typename std::enable_if<!isDerivedFromModulusRing<Integer>::value>::type
				* = nullptr>
		inline auto operator-(Integer const &other) const {
			return *this - build(other);
		}
		template <
			typename OtherDerived,
			typename OtherUnderlying,
			std::size_t OTHER_MODULUS_OUTER>
		inline auto operator-(
			ModulusRingBase<OtherDerived, OtherUnderlying, OTHER_MODULUS_OUTER> const
				&other) const {
			// We must explicitly add MODULUS here because the type may be signed.
			return build(this->value + this->MODULUS - other.value);
		}
		template <typename Integer>
		inline auto &operator-=(Integer const &other) {
			return *this = *this - other;
		}
		template <
			typename Integer,
			typename std::enable_if<!isDerivedFromModulusRing<Integer>::value>::type
				* = nullptr>
		inline auto operator*(Integer const &other) const {
			return *this * build(other);
		}
		template <
			typename OtherDerived,
			typename OtherUnderlying,
			std::size_t OTHER_MODULUS_OUTER>
		inline auto operator*(
			ModulusRingBase<OtherDerived, OtherUnderlying, OTHER_MODULUS_OUTER> const
				&other) const {
			return build(this->value * other.value);
		}
		template <typename Integer>
		inline auto &operator*=(Integer const &other) {
			return *this = *this * other;
		}
		// Modulus operates directly on modded operand value.
		template <
			typename Integer,
			typename std::enable_if<!isDerivedFromModulusRing<Integer>::value>::type
				* = nullptr>
		inline auto operator%(Integer const &other) const {
			return *this % build(other);
		}
		template <
			typename OtherDerived,
			typename OtherUnderlying,
			std::size_t OTHER_MODULUS_OUTER>
		inline auto operator%(
			ModulusRingBase<OtherDerived, OtherUnderlying, OTHER_MODULUS_OUTER> const
				&other) const {
			return build(this->value % other.value);
		}
		template <typename Integer>
		inline auto &operator%=(Integer const &other) {
			return *this = *this % other;
		}

		// Unary operations are mostly shorthands for binary operations.
		inline auto operator-() const { return 0 - *this; }
		inline auto operator++() { return *this += 1; }
		inline auto operator++(int) {
			auto tmp(*this);
			*this += 1;
			return build(tmp);
		}
		inline auto operator--() { return *this -= 1; }
		inline auto operator--(int) {
			auto tmp(*this);
			*this -= 1;
			return build(tmp);
		}

		// The following are algorithmic functions based on the modulus field
		// properties.

		// Versions of C++ before C++17 should use static member functions instead
		// of static inline member variables. static inline
		// std::vector<Derived> 	&factorials() {
		// static std::vector<Derived>
		// factorials; return factorials;
		// }
		// static inline std::vector<Derived>
		// 	&invFactorials() {
		// 	static std::vector<Derived>
		// invFactorials; 	return invFactorials;
		// }
		static inline std::vector<Derived> factorials, invFactorials;

		// Computes the factorials modulus a prime, up to and including N, in O(N).
		// This enables the choose functions.
		static inline void precomputeFactorials(std::size_t const N) {
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

		// O(ln N) exponentiation. The exponent's value is used.
		template <
			typename Integer,
			typename std::enable_if<!isDerivedFromModulusRing<Integer>::value>::type
				* = nullptr>
		inline Derived power(Integer const &exponent) const {
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
		template <
			typename OtherDerived,
			typename OtherUnderlying,
			std::size_t OTHER_MODULUS_OUTER>
		inline Derived power(
			ModulusRingBase<OtherDerived, OtherUnderlying, OTHER_MODULUS_OUTER> const
				&exponent) const {
			return this->power(exponent.value);
		}
	};

	// Any reasonable modulus will suffice, since we do not define multiplicative
	// inverses in a ring.
	template <typename Underlying, std::size_t MODULUS_OUTER = 0>
	class ModulusRing : public ModulusRingBase<
												ModulusRing<Underlying, MODULUS_OUTER>,
												Underlying,
												MODULUS_OUTER> {
		private:
		using TypeThis = ModulusRing<Underlying, MODULUS_OUTER>;
		using TypeSuper = ModulusRingBase<TypeThis, Underlying, MODULUS_OUTER>;

		public:
		// Constructors must be inherited with the alias name, not the original
		// name.
		using TypeSuper::TypeSuper;

		// For some reason, we must provide specific constructors for `build`, and
		// they are not inherited.
		template <
			std::size_t MODULUS_INNER = MODULUS_OUTER,
			typename std::enable_if<MODULUS_INNER != 0>::type * = nullptr>
		ModulusRing(TypeSuper const &other) : TypeSuper(other) {}
		template <
			std::size_t MODULUS_INNER = MODULUS_OUTER,
			typename std::enable_if<MODULUS_INNER == 0>::type * = nullptr>
		ModulusRing(Underlying const &modulus, TypeSuper const &other)
				: TypeSuper(modulus, other) {}

		using TypeSuper::build;

		// `operator=` is always hidden by a dummy one in the derived class:
		// <https://stackoverflow.com/questions/12009865/operator-and-functions-that-are-not-inherited-in-c>.
		template <typename Integer>
		inline TypeThis operator=(Integer const &other) {
			return build(TypeSuper::operator=(other));
		}

		using TypeSuper::factorials;
		using TypeSuper::invFactorials;
	};

	// Must be used with a prime modulus, but this cannot be checked at
	// compile-time. If modulus is not prime, use ModulusRing instead.
	template <typename Underlying, std::size_t MODULUS_OUTER = 0>
	class ModulusField : public ModulusRingBase<
												 ModulusField<Underlying, MODULUS_OUTER>,
												 Underlying,
												 MODULUS_OUTER> {
		private:
		using TypeThis = ModulusField<Underlying, MODULUS_OUTER>;
		using TypeSuper = ModulusRingBase<TypeThis, Underlying, MODULUS_OUTER>;

		public:
		using TypeSuper::TypeSuper;

		template <
			std::size_t MODULUS_INNER = MODULUS_OUTER,
			typename std::enable_if<MODULUS_INNER != 0>::type * = nullptr>
		ModulusField(TypeSuper const &other) : TypeSuper(other) {}
		template <
			std::size_t MODULUS_INNER = MODULUS_OUTER,
			typename std::enable_if<MODULUS_INNER == 0>::type * = nullptr>
		ModulusField(Underlying const &modulus, TypeSuper const &other)
				: TypeSuper(modulus, other) {}

		using TypeSuper::build;

		template <typename Integer>
		inline TypeThis operator=(Integer const &other) {
			return build(TypeSuper::operator=(other));
		}

		// Division is only correct in fields, or rings with specific operands.
		template <
			typename Integer,
			typename std::enable_if<!std::is_same<TypeThis, Integer>::value>::type * =
				nullptr>
		inline TypeThis operator/(Integer const &other) const {
			return *this / build(other);
		}
		inline TypeThis operator/(TypeThis const &other) const {
			// This is only true if this has a multiplicative inverse, which is always
			// true if the modulus is prime.
			return *this * other.power(this->MODULUS - 2);
		}
		template <typename Integer>
		inline TypeThis &operator/=(Integer const &other) {
			return *this = *this / other;
		}

		using TypeSuper::factorials;
		using TypeSuper::invFactorials;

		// Computes the binomial coefficient (N choose K) modulus a prime, in O(1).
		// Must have called precomputeFactorials for the largest expected value of N
		// first.
		inline TypeThis choose(std::size_t const K) const {
			std::size_t const N{static_cast<std::size_t>(this->value)};
			if (K < 0 || K > N) {
				return build(0);
			}
			return factorials[N] * invFactorials[K] * invFactorials[N - K];
		}
	};
}

// These operators are only called if the left operand is a raw integer.
template <
	typename Integer,
	typename std::enable_if<!Rain::Algorithm::ModulusRingBase<>::
														isDerivedFromModulusRing<Integer>::value>::type * =
		nullptr,
	typename Derived,
	typename Underlying,
	std::size_t MODULUS_OUTER>
inline auto operator+(
	Integer const &left,
	Rain::Algorithm::ModulusRingBase<Derived, Underlying, MODULUS_OUTER> const
		&right) {
	return right.build(left) + right;
}
template <
	typename Integer,
	typename std::enable_if<!Rain::Algorithm::ModulusRingBase<>::
														isDerivedFromModulusRing<Integer>::value>::type * =
		nullptr,
	typename Derived,
	typename Underlying,
	std::size_t MODULUS_OUTER>
inline auto operator-(
	Integer const &left,
	Rain::Algorithm::ModulusRingBase<Derived, Underlying, MODULUS_OUTER> const
		&right) {
	return right.build(left) - right;
}
template <
	typename Integer,
	typename std::enable_if<!Rain::Algorithm::ModulusRingBase<>::
														isDerivedFromModulusRing<Integer>::value>::type * =
		nullptr,
	typename Derived,
	typename Underlying,
	std::size_t MODULUS_OUTER>
inline auto operator*(
	Integer const &left,
	Rain::Algorithm::ModulusRingBase<Derived, Underlying, MODULUS_OUTER> const
		&right) {
	return right.build(left) * right;
}
template <
	typename Integer,
	typename std::enable_if<!Rain::Algorithm::ModulusRingBase<>::
														isDerivedFromModulusRing<Integer>::value>::type * =
		nullptr,
	typename Derived,
	typename Underlying,
	std::size_t MODULUS_OUTER>
inline auto operator%(
	Integer const &left,
	Rain::Algorithm::ModulusRingBase<Derived, Underlying, MODULUS_OUTER> const
		&right) {
	return right.build(left) % right;
}
template <
	typename Integer,
	typename std::enable_if<!Rain::Algorithm::ModulusRingBase<>::
														isDerivedFromModulusRing<Integer>::value>::type * =
		nullptr,
	typename Underlying,
	std::size_t MODULUS_OUTER>
inline auto operator/(
	Integer const &left,
	Rain::Algorithm::ModulusField<Underlying, MODULUS_OUTER> const &right) {
	return right.build(left) / right;
}

// Ease-of-use streaming operators.
template <typename Derived, typename Underlying, std::size_t MODULUS_OUTER>
inline std::ostream &operator<<(
	std::ostream &stream,
	Rain::Algorithm::ModulusRingBase<Derived, Underlying, MODULUS_OUTER> const
		&right) {
	return stream << right.value;
}
template <typename Derived, typename Underlying, std::size_t MODULUS_OUTER>
inline std::istream &operator>>(
	std::istream &stream,
	Rain::Algorithm::ModulusRingBase<Derived, Underlying, MODULUS_OUTER> const
		&right) {
	stream >> right.value;
	right.value = (right.modulus + right.value) % right.modulus;
	return stream;
}

// Hash operator for this user-defined type, which hashes the inner value (not
// the modulus). There is no way to define hash for only the base class, so we
// define it for all user-facing classes directly:
// <https://stackoverflow.com/questions/21900707/specializing-stdhash-to-derived-classes>.
namespace std {
	template <typename Underlying, std::size_t MODULUS_OUTER>
	struct hash<Rain::Algorithm::ModulusRing<Underlying, MODULUS_OUTER>> {
		size_t operator()(
			Rain::Algorithm::ModulusRing<Underlying, MODULUS_OUTER> const &value)
			const {
			return Rain::Random::SplitMixHash<decltype(value.value)>{}(value.value);
		}
	};

	template <typename Underlying, std::size_t MODULUS_OUTER>
	struct hash<Rain::Algorithm::ModulusField<Underlying, MODULUS_OUTER>> {
		size_t operator()(
			Rain::Algorithm::ModulusField<Underlying, MODULUS_OUTER> const &value)
			const {
			return Rain::Random::SplitMixHash<decltype(value.value)>{}(value.value);
		}
	};
}

#if defined(_WIN32) || defined(_WIN64)
#define RAIN_PLATFORM_WINDOWS
#endif

#if defined(__APPLE__) || defined(__MACH__)
#define RAIN_PLATFORM_MACOS
#endif

#if defined(__linux__) || defined(linux) || defined(__linux)
#define RAIN_PLATFORM_LINUX
#endif

#if !defined(RAIN_PLATFORM_WINDOWS) && !defined(RAIN_PLATFORM_MACOS) && \
	!defined(RAIN_PLATFORM_LINUX)
#define RAIN_PLATFORM_OTHER
#endif

#ifdef NDEBUG
#define RAIN_PLATFORM_NDEBUG
#endif

namespace Rain::Platform {
	enum class Platform { NONE = 0, WINDOWS, MACOS, LINUX };

	// Get the Platform enum Rain is running on.
	inline Platform getPlatform() noexcept {
#ifdef RAIN_PLATFORM_WINDOWS
		return Platform::WINDOWS;
#elif defined(RAIN_PLATFORM_MACOS)
		return Platform::MACOS;
#elif defined(RAIN_PLATFORM_LINUX)
		return Platform::LINUX;
#else
		return Platform::NONE;
#endif
	}

	// Returns whether the code was built in debug mode.
	inline bool isDebug() noexcept {
#ifdef RAIN_PLATFORM_NDEBUG
		return false;
#else
		return true;
#endif
	}
}

// Ease-of-stream for Rain::Platform::Platform.
inline std::ostream &operator<<(
	std::ostream &stream,
	Rain::Platform::Platform platform) {
	switch (platform) {
		case Rain::Platform::Platform::WINDOWS:
			return stream << "Windows";
		case Rain::Platform::Platform::MACOS:
			return stream << "MacOS";
		case Rain::Platform::Platform::LINUX:
			return stream << "Linux";
		default:
			return stream << "Other";
	}
}

namespace Rain {
	// errno_t is non-standard; however we define it here to maximize
	// compatibility with overloading library functions which return this.
	typedef int errno_t;
}

namespace Rain {
	// strcasecmp does not exist on Windows.
	inline int strcasecmp(char const *left, char const *right) {
#ifdef RAIN_PLATFORM_WINDOWS
		return _stricmp(left, right);
#else
		return ::strcasecmp(left, right);
#endif
	}
}

namespace Rain::String {
	// Convert ASCII string types to lowercase.
	inline char *toLower(char *const cStr, std::size_t const cStrLen) {
		std::transform(cStr, cStr + cStrLen, cStr, [](unsigned char c) {
			return static_cast<char>(std::tolower(static_cast<int>(c)));
		});
		return cStr;
	}
	inline std::string &toLower(std::string &str) {
		// In C++17, strings are guaranteed to be continuous.
		toLower(&str[0], str.length());
		return str;
	}

	// Trim whitespace characters from both sides of an std::string.
	inline std::string &trimWhitespace(std::string &str) {
		str.erase(
			str.begin(), std::find_if(str.begin(), str.end(), [](unsigned char c) {
				return std::isspace(static_cast<int>(c)) == 0;
			}));
		str.erase(
			std::find_if(
				str.rbegin(),
				str.rend(),
				[](unsigned char c) { return std::isspace(static_cast<int>(c)) == 0; })
				.base(),
			str.end());
		return str;
	}

	// For C-Strings, instead of trimming whitespace, these utilities find the
	// first/last non-whitespace character in the string.
	//
	// If all whitespace, returns cStr + cStrLen.
	inline char *scanUntilNonWhitespace(
		char const *const cStr,
		// Length in the direction to be scanned.
		std::size_t const cStrLen,
		// Scanning direction.
		bool const scanRight = true) {
		std::size_t index{0};
		for (; index < cStrLen && std::isspace(static_cast<int>(cStr[index]));
				 index += (scanRight ? 1 : -1));
		return const_cast<char *>(cStr) + index;
	}
	inline char *scanUntilWhitespace(
		char const *const cStr,
		std::size_t const cStrLen,
		bool const scanRight = true) {
		std::size_t index{0};
		for (; index < cStrLen && !std::isspace(static_cast<int>(cStr[index]));
				 index += (scanRight ? 1 : -1));
		return const_cast<char *>(cStr) + index;
	}

	// Convert any time to any other type using std::stringstream. Thread-safe.
	// Prefer specialized methods if available (strtoll, to_string, etc.).
	//
	// Internally, rain uses the strto* variants instead of the sto* variants as
	// the former returns valid results on error and do not throw.
	template <typename To, typename From>
	inline To anyToAny(From from) {
		To to;
		std::stringstream ss;
		ss << from;
		ss >> to;
		return to;
	}
	// Comparison operator for ASCII C-strings for use in std::maps and the like.
	struct CStringCompare {
		bool operator()(char const *left, char const *right) const {
			return std::strcmp(left, right) < 0;
		}
	};

	// Comparison operator for case-agnostic comparison.
	struct CaseAgnosticCompare {
		bool operator()(std::string const &left, std::string const &right) const {
			return strcasecmp(left.c_str(), right.c_str()) < 0;
		}
	};

	// Case-agnostic hash & equality for std::unordered_map.
	struct CaseAgnosticHash {
		std::size_t operator()(std::string const &str) const {
			std::string strLower(str);
			return std::hash<std::string>{}(toLower(strLower));
		}
	};
	struct CaseAgnosticEqual {
		bool operator()(std::string const &left, std::string const &right) const {
			return strcasecmp(left.c_str(), right.c_str()) == 0;
		}
	};
}

namespace Rain::Error {
	// Subclasses std::exception, implements custom what() string to display error
	// category name, code, and error code message.
	//
	// Default template arguments provided for ease of use in catch blocks.
	template <typename Error, typename ErrorCategory>
	class Exception : public std::exception {
		private:
		// A unique ErrorCategory instance.
		static inline ErrorCategory const errorCategory;

		Error const error;
		std::string const explanation;

		public:
		// Construct an exception with just the error code, in the format "CATEGORY,
		// ERROR: MESSAGE".
		Exception(Error const &error = static_cast<Error>(0))
				: error(error),
					explanation(
						std::string(errorCategory.name()) + ", " +
						std::to_string(static_cast<int>(error)) + ": " +
						errorCategory.message(static_cast<int>(error)) + "\n") {}

		// Return the error (code).
		Error const &getError() const noexcept { return this->error; }

		// Return the ErrorCategory for checking equality.
		static ErrorCategory const &getErrorCategory() noexcept {
			return Exception<Error, ErrorCategory>::errorCategory;
		}

		// Return the preconstructed explanation string.
		//
		// Because std::exception::what is virtual, catch blocks only have to catch
		// std::exception to use this version of what.
		char const *what() const noexcept { return this->explanation.c_str(); }
	};

	// Default generic error category.
	class GenericErrorCategory : public std::error_category {
		public:
		// Name of this category of errors.
		char const *name() const noexcept { return "Generic"; }

		// Translates Errors from the enum into string messages.
		std::string message(int) const noexcept { return "Generic."; }
	};
	using GenericException = Exception<int, GenericErrorCategory>;
}

namespace Rain::Math {
	template <typename = std::nullptr_t, std::size_t = 0>
	class Tensor;

	template <>
	class Tensor<std::nullptr_t, 0> {
		template <class OtherValue, std::size_t OTHER_ORDER>
		friend class Tensor;

		public:
		enum Error { NONE, SIZES_MISMATCH };
		class ErrorCategory : public std::error_category {
			public:
			char const *name() const noexcept { return "Rain::Math::Tensor"; }
			std::string message(int error) const noexcept {
				switch (error) {
					case Error::NONE:
						return "None.";
					case Error::SIZES_MISMATCH:
						return "Tensor(s) are not of compatible size for operation.";
					default:
						return "Generic.";
				}
			}
		};
		typedef Rain::Error::Exception<Error, ErrorCategory> Exception;

		class Range {
			public:
			// `stop`: defaults will be replaced with current `stop` during `slice`.
			// `size`: actual underlying size.
			std::size_t start{std::numeric_limits<std::size_t>::max()},
				stop{std::numeric_limits<std::size_t>::max()},
				step{std::numeric_limits<std::size_t>::max()};
		};

		// Standard policy for Tensor products.
		template <typename Left, typename Right>
		class PlusMultProductPolicy {
			public:
			static decltype(std::declval<Left>() * std::declval<Right>())
				const DEFAULT_RESULT{0};

			static constexpr inline auto sum(Left const &left, Right const &right) {
				return left + right;
			}
			static constexpr inline auto product(
				Left const &left,
				Right const &right) {
				return left * right;
			}
		};

		// Policy for Tensor products where + is replaced with min and * is replaced
		// with +.
		template <typename Left, typename Right>
		class MinPlusProductPolicy {
			public:
			static decltype(std::declval<Left>() + std::declval<Right>())
				const DEFAULT_RESULT{std::numeric_limits<
					decltype(std::declval<Left>() + std::declval<Right>())>::max()};

			static constexpr inline auto sum(Left const &left, Right const &right) {
				return std::min(left, right);
			}
			static constexpr inline auto product(
				Left const &left,
				Right const &right) {
				return left + right;
			}
		};

		private:
		// Perform an operation over all indices, or over the first few indices.
		template <std::size_t REMAINING_ORDER, typename ResultValue>
		static void applyOver(
			auto &&callable,
			Tensor<ResultValue, REMAINING_ORDER + 1> const &result,
			auto &&...others) {
			for (std::size_t i{0}; i < result.size()[0]; i++) {
				callable(
					result[i], std::forward<decltype(others)>(others).operator[](i)...);
			}
		}
		// An explicit overload for `applyOver` which does nothing, which may be
		// called from `product` if one matrix is completely contracted.
		template <std::size_t REMAINING_ORDER, typename ResultValue>
		static void applyOver(
			auto &&callable,
			Tensor<ResultValue, REMAINING_ORDER> const &result,
			auto &&...others) {
			callable(result, std::forward<decltype(others)>(others)...);
		}
		// `applyOver` which reduces ORDER.
		template <
			std::size_t REMAINING_ORDER,
			typename ResultValue,
			std::size_t RESULT_ORDER,
			bool isReducing = (REMAINING_ORDER < RESULT_ORDER),
			typename std::enable_if<isReducing>::type * = nullptr>
		static void applyOver(
			auto &&callable,
			Tensor<ResultValue, RESULT_ORDER> const &result,
			auto &&...others) {
			for (std::size_t i{0}; i < result.size()[0]; i++) {
				Tensor<>::applyOver<REMAINING_ORDER>(
					std::forward<decltype(callable)>(callable),
					result[i],
					std::forward<decltype(others)>(others).operator[](i)...);
			}
		}

		// L-value versions of `applyOver`.
		template <std::size_t REMAINING_ORDER, typename ResultValue>
		static void applyOver(
			auto &&callable,
			Tensor<ResultValue, REMAINING_ORDER + 1> &result,
			auto &&...others) {
			for (std::size_t i{0}; i < result.size()[0]; i++) {
				callable(
					result[i], std::forward<decltype(others)>(others).operator[](i)...);
			}
		}
		template <std::size_t REMAINING_ORDER, typename ResultValue>
		static void applyOver(
			auto &&callable,
			Tensor<ResultValue, REMAINING_ORDER> &result,
			auto &&...others) {
			callable(result, std::forward<decltype(others)>(others)...);
		}
		template <
			std::size_t REMAINING_ORDER,
			typename ResultValue,
			std::size_t RESULT_ORDER,
			bool isReducing = (REMAINING_ORDER < RESULT_ORDER),
			typename std::enable_if<isReducing>::type * = nullptr>
		static void applyOver(
			auto &&callable,
			Tensor<ResultValue, RESULT_ORDER> &result,
			auto &&...others) {
			for (std::size_t i{0}; i < result.size()[0]; i++) {
				Tensor<>::applyOver<REMAINING_ORDER>(
					std::forward<decltype(callable)>(callable),
					result[i],
					std::forward<decltype(others)>(others).operator[](i)...);
			}
		}

		// R-value reference versions of `applyOver`. We cannot have one set of
		// functions call another set, because that degrades the qualifiers on
		// `result`, which need to be exact when passed to `callable`.
		template <std::size_t REMAINING_ORDER, typename ResultValue>
		static void applyOver(
			auto &&callable,
			Tensor<ResultValue, REMAINING_ORDER + 1> &&result,
			auto &&...others) {
			for (std::size_t i{0}; i < result.size()[0]; i++) {
				callable(
					std::forward<decltype(result[i])>(result[i]),
					std::forward<decltype(others)>(others).operator[](i)...);
			}
		}
		template <std::size_t REMAINING_ORDER, typename ResultValue>
		static void applyOver(
			auto &&callable,
			Tensor<ResultValue, REMAINING_ORDER> &&result,
			auto &&...others) {
			callable(
				std::forward<decltype(result)>(result),
				std::forward<decltype(others)>(others)...);
		}
		template <
			std::size_t REMAINING_ORDER,
			typename ResultValue,
			std::size_t RESULT_ORDER,
			bool isReducing = (REMAINING_ORDER < RESULT_ORDER),
			typename std::enable_if<isReducing>::type * = nullptr>
		static void applyOver(
			auto &&callable,
			Tensor<ResultValue, RESULT_ORDER> &&result,
			auto &&...others) {
			for (std::size_t i{0}; i < result.size()[0]; i++) {
				Tensor<>::applyOver<REMAINING_ORDER>(
					std::forward<decltype(callable)>(callable),
					std::forward<decltype(result[i])>(result[i]),
					std::forward<decltype(others)>(others).operator[](i)...);
			}
		}
	};

	// Flexible order tensor implementation. Most operations give views of the
	// same underlying data; this is not the case for the binary arithmetic
	// operations.
	template <typename Value, std::size_t ORDER>
	class Tensor {
		// Allow access of any other Tensor for proper product implementation.
		template <class OtherValue, std::size_t OTHER_ORDER>
		friend class Tensor;

		private:
		using TypeThis = Tensor<Value, ORDER>;
		using Range = Tensor<>::Range;

		using Error = Tensor<>::Error;
		using Exception = Tensor<>::Exception;

		std::shared_ptr<Value[]> VALUES;
		std::array<Range, ORDER> RANGES;
		// Perceived size based on range.
		std::array<std::size_t, ORDER> SIZES, SIZES_UNDERLYING;
		// Offset caused by previous indexing.
		std::size_t OFFSET;
		// Store a permutation of dimensions for easy transpose & product.
		std::array<std::size_t, ORDER> TRANSPOSE;

		// Only used by the wrapping variant of the scalar constructor.
		Value *P_SCALAR{nullptr};

		static constexpr inline std::size_t calcSizesProduct(
			std::array<std::size_t, ORDER> const &sizes) {
			std::size_t result{1};
			for (auto const &i : sizes) {
				result *= i;
			}
			return result;
		}
		static constexpr inline std::array<Range, ORDER> makeRangesDefault(
			std::array<std::size_t, ORDER> const &sizes) {
			std::array<Range, ORDER> ranges;
			for (std::size_t i{0}; i < ORDER; i++) {
				ranges[i] = {0, sizes[i], 1};
			}
			return ranges;
		}
		static constexpr inline std::array<std::size_t, ORDER> calcSizes(
			std::array<Range, ORDER> const &ranges) {
			std::array<std::size_t, ORDER> sizes;
			for (std::size_t i{0}; i < ORDER; i++) {
				sizes[i] = (ranges[i].stop - ranges[i].start + ranges[i].step - 1) /
					ranges[i].step;
			}
			return sizes;
		}
		static constexpr inline std::array<std::size_t, ORDER>
		makeDimPermDefault() {
			std::array<std::size_t, ORDER> dimPerm;
			for (std::size_t i{0}; i < ORDER; i++) {
				dimPerm[i] = i;
			}
			return dimPerm;
		}
		static constexpr inline std::array<std::size_t, ORDER> makeOnesSizes() {
			std::array<std::size_t, ORDER> sizes;
			sizes.fill(1);
			return sizes;
		}

		template <typename OtherValue>
		inline void debugAssertEqualSizes(
			Tensor<OtherValue, ORDER> const &other) const {
			if (Platform::isDebug()) {
				auto thisSize{this->size()}, otherSize{other.size()};
				for (std::size_t i{0}; i < ORDER; i++) {
					if (thisSize[i] != otherSize[i]) {
						throw Exception(Error::SIZES_MISMATCH);
					}
				}
			}
		}
		template <
			bool isVector = ORDER == 2,
			typename std::enable_if<isVector>::type * = nullptr>
		inline void debugAssertSquare() const {
			if (Platform::isDebug()) {
				if (this->SIZES[0] != this->SIZES[1]) {
					throw Exception(Error::SIZES_MISMATCH);
				}
			}
		}

		Tensor(
			std::shared_ptr<Value[]> values,
			std::array<Range, ORDER> const &ranges,
			std::array<std::size_t, ORDER> const &sizesUnderlying,
			std::size_t offset,
			std::array<std::size_t, ORDER> const &dimPerm)
				: VALUES{values},
					RANGES{ranges},
					SIZES{TypeThis::calcSizes(ranges)},
					SIZES_UNDERLYING{sizesUnderlying},
					OFFSET{offset},
					TRANSPOSE{dimPerm} {}

		public:
		Tensor(std::array<std::size_t, ORDER> const &sizes, auto &&...values)
				: VALUES{new Value[TypeThis::calcSizesProduct(sizes)]{
						std::forward<decltype(values)>(values)...}},
					RANGES{TypeThis::makeRangesDefault(sizes)},
					SIZES{sizes},
					SIZES_UNDERLYING{sizes},
					OFFSET{0},
					TRANSPOSE{TypeThis::makeDimPermDefault()} {}
		Tensor(TypeThis const &other)
				: VALUES{other.VALUES},
					RANGES{other.RANGES},
					SIZES{other.SIZES},
					SIZES_UNDERLYING{other.SIZES_UNDERLYING},
					OFFSET{other.OFFSET},
					TRANSPOSE{other.TRANSPOSE} {}

		// The default constructor generates a Tensor with only a single element.
		Tensor() : Tensor(TypeThis::makeOnesSizes()) {}

		// Scalar constructor elides sizes. Allows for free conversion between
		// scalars and Values, alongside the relevant `operator`s.
		template <
			bool isScalar = ORDER == 0,
			typename std::enable_if<isScalar>::type * = nullptr>
		Tensor(Value const &value) : Tensor({}, value) {}
		// A scalar tensor can also wrap an existing value, but this needs special
		// treatment.
		template <
			bool isScalar = ORDER == 0,
			typename std::enable_if<isScalar>::type * = nullptr>
		Tensor(Value &value) : Tensor({}) {
			this->P_SCALAR = &value;
		}

		// Identity, implemented only for matrices.
		template <
			bool isMatrix = ORDER == 2,
			typename std::enable_if<isMatrix>::type * = nullptr>
		static constexpr inline auto identity(std::size_t size) {
			Tensor<Value, 2> result({size, size});
			for (std::size_t i{0}; i < size; i++) {
				result[i][i] = 1;
			}
			return result;
		}

		// Copy assignment copies a reference, and not the underlying data.
		//
		// We offer a template but also a specialization to the current class to
		// help compilers recognize the copy assignment operator.
		template <typename OtherValue>
		auto &operator=(Tensor<OtherValue, ORDER> const &other) {
			this->VALUES = other.VALUES;
			this->RANGES = other.RANGES;
			this->SIZES = other.SIZES;
			this->SIZES_UNDERLYING = other.SIZES_UNDERLYING;
			this->OFFSET = other.OFFSET;
			this->TRANSPOSE = other.TRANSPOSE;
			return *this;
		}
		auto &operator=(TypeThis const &other) {
			this->VALUES = other.VALUES;
			this->RANGES = other.RANGES;
			this->SIZES = other.SIZES;
			this->SIZES_UNDERLYING = other.SIZES_UNDERLYING;
			this->OFFSET = other.OFFSET;
			this->TRANSPOSE = other.TRANSPOSE;
			return *this;
		}

		// Equality operator checks sizes and every index.
		template <typename OtherValue>
		bool operator==(Tensor<OtherValue, ORDER> const &other) const {
			auto thisSize{this->size()}, otherSize{other.size()};
			for (std::size_t i{0}; i < ORDER; i++) {
				if (thisSize[i] != otherSize[i]) {
					return false;
				}
			}

			bool isEqual{true};
			Tensor<>::applyOver<0>(
				[&isEqual](Value const &thisValue, OtherValue const &otherValue) {
					isEqual &= thisValue == otherValue;
				},
				*this,
				other);
			return isEqual;
		}

		// A 0-order Tensor converts to/from automatically a scalar. This is
		// necessary for degenerate cases in `product`.
		//
		// Two versions necessary depending on if *this is const or not.
		//
		// It is always constructed without specifying SIZES, and so its underlying
		// size is 1 and must contain a scalar.
		template <
			bool isScalar = ORDER == 0,
			typename std::enable_if<isScalar>::type * = nullptr>
		inline operator Value const &() const {
			if (this->P_SCALAR != nullptr) {
				return *this->P_SCALAR;
			}
			return this->VALUES[0];
		}
		template <
			bool isScalar = ORDER == 0,
			typename std::enable_if<isScalar>::type * = nullptr>
		inline operator Value &() {
			return const_cast<Value &>(this->operator Value const &());
		}

		// Indexing is the main operation of a tensor, and most other operations
		// build on it.
		//
		// Checks in-range iff DEBUG.
		template <
			bool isVector = ORDER == 1,
			typename std::enable_if<isVector>::type * = nullptr>
		inline Value const &operator[](std::size_t idx) const {
			return this->VALUES
				[this->OFFSET + this->RANGES[0].start + this->RANGES[0].step * idx];
		}
		template <
			bool isVector = ORDER == 1,
			typename std::enable_if<isVector>::type * = nullptr>
		inline Value &operator[](std::size_t idx) {
			return const_cast<Value &>(
				const_cast<TypeThis const *>(this)->operator[](idx));
		}
		// We provide two versions of the higher-order indexing operator, to
		// preserve const-ness.
		template <
			bool isNotVector = (ORDER > 1),
			typename std::enable_if<isNotVector>::type * = nullptr>
		Tensor<Value, ORDER - 1> const operator[](std::size_t idx) const {
			if (Platform::isDebug()) {
				if (idx >= this->SIZES[this->TRANSPOSE[0]]) {
					throw Exception(Error::SIZES_MISMATCH);
				}
			}

			// Must take into account transpose.
			std::array<std::size_t, ORDER - 1> newDimPerm;
			for (std::size_t i{1}; i < ORDER; i++) {
				newDimPerm[i - 1] = this->TRANSPOSE[i] +
					(this->TRANSPOSE[i] > this->TRANSPOSE[0] ? -1 : 0);
			}

			std::array<Range, ORDER - 1> ranges;
			std::array<std::size_t, ORDER - 1> sizesUnderlying;
			std::size_t rangeShift{
				this->RANGES[this->TRANSPOSE[0]].start +
				this->RANGES[this->TRANSPOSE[0]].step * idx};
			for (std::size_t i{1}; i < ORDER; i++) {
				sizesUnderlying[newDimPerm[i - 1]] =
					this->SIZES_UNDERLYING[this->TRANSPOSE[i]];
				if (this->TRANSPOSE[i] > this->TRANSPOSE[0]) {
					rangeShift *= this->SIZES_UNDERLYING[this->TRANSPOSE[i]];
					ranges[newDimPerm[i - 1]] = this->RANGES[this->TRANSPOSE[i]];
				} else {
					// `stop` and `start` are calculated from the new `step`.
					ranges[newDimPerm[i - 1]].step =
						this->RANGES[this->TRANSPOSE[i]].step *
						this->SIZES_UNDERLYING[this->TRANSPOSE[0]];
					ranges[newDimPerm[i - 1]].start =
						this->RANGES[this->TRANSPOSE[i]].start *
						this->SIZES_UNDERLYING[this->TRANSPOSE[0]];
					ranges[newDimPerm[i - 1]].stop = ranges[newDimPerm[i - 1]].start +
						this->RANGES[this->TRANSPOSE[i]].step *
							this->SIZES_UNDERLYING[this->TRANSPOSE[0]] *
							this->SIZES[this->TRANSPOSE[i]];
				}
			}
			return {
				this->VALUES,
				ranges,
				sizesUnderlying,
				this->OFFSET + rangeShift,
				newDimPerm};
		}
		template <
			bool isNotVector = (ORDER > 1),
			typename std::enable_if<isNotVector>::type * = nullptr>
		Tensor<Value, ORDER - 1> operator[](std::size_t idx) {
			return const_cast<Tensor<Value, ORDER - 1> &&>(
				const_cast<TypeThis const *>(this)->operator[](idx));
		}

		// Binary operators. Checks dimension equality iff DEBUG.
		//
		// Binary assignment operators perform operations in-place. Non-assignment
		// versions are constant and will perform allocations of the appropriate
		// size.
		template <typename OtherValue>
		auto operator+(Tensor<OtherValue, ORDER> const &other) const {
			using ResultValue =
				decltype(std::declval<Value>() + std::declval<OtherValue>());
			this->debugAssertEqualSizes(other);
			Tensor<ResultValue, ORDER> result(this->size());
			Tensor<>::applyOver<0>(
				[](ResultValue &result, Value const &that, OtherValue const &other) {
					result = that + other;
				},
				result,
				*this,
				other);
			return result;
		}
		template <typename OtherValue>
		auto &operator+=(Tensor<OtherValue, ORDER> const &other) {
			Tensor<>::applyOver<0>(
				[](Value &thatValue, OtherValue const &otherValue) {
					thatValue += otherValue;
				},
				*this,
				other);
			return *this;
		}
		template <typename OtherValue>
		auto operator+(OtherValue const &other) const {
			using ResultValue =
				decltype(std::declval<Value>() * std::declval<OtherValue>());
			Tensor<ResultValue, ORDER> result(this->size());
			Tensor<>::applyOver<0>(
				[&other](ResultValue &result, Value const &that) {
					result = that + other;
				},
				result,
				*this);
			return result;
		}
		template <typename OtherValue>
		auto &operator+=(OtherValue const &other) {
			Tensor<>::applyOver<0>([&other](Value &that) { that += other; }, *this);
			return *this;
		}
		template <typename OtherValue>
		auto operator-(Tensor<OtherValue, ORDER> const &other) const {
			using ResultValue =
				decltype(std::declval<Value>() - std::declval<OtherValue>());
			this->debugAssertEqualSizes(other);
			Tensor<ResultValue, ORDER> result(this->size());
			Tensor<>::applyOver<0>(
				[](ResultValue &result, Value const &that, OtherValue const &other) {
					result = that - other;
				},
				result,
				*this,
				other);
			return result;
		}
		template <typename OtherValue>
		auto &operator-=(Tensor<OtherValue, ORDER> const &other) {
			Tensor<>::applyOver<0>(
				[](Value &thatValue, OtherValue const &otherValue) {
					thatValue -= otherValue;
				},
				*this,
				other);
			return *this;
		}
		template <typename OtherValue>
		auto operator-(OtherValue const &other) const {
			using ResultValue =
				decltype(std::declval<Value>() * std::declval<OtherValue>());
			Tensor<ResultValue, ORDER> result(this->size());
			Tensor<>::applyOver<0>(
				[&other](ResultValue &result, Value const &that) {
					result = that - other;
				},
				result,
				*this);
			return result;
		}
		template <typename OtherValue>
		auto &operator-=(OtherValue const &other) {
			Tensor<>::applyOver<0>([&other](Value &that) { that -= other; }, *this);
			return *this;
		}
		// Binary operators *, *= are defined with another Tensor operand iff they
		// are both ORDER 2 and of compatible size. This is a shorthand for
		// `product`.
		template <
			typename OtherValue,
			bool isMatrix = ORDER == 2,
			typename std::enable_if<isMatrix>::type * = nullptr>
		auto operator*(Tensor<OtherValue, ORDER> const &other) const {
			// No need to check sizes here, since `product` will do it.
			return this->product<1>(other, {1}, {0});
		}
		template <
			typename OtherValue,
			bool isMatrix = ORDER == 2,
			typename std::enable_if<isMatrix>::type * = nullptr>
		auto &operator*=(Tensor<OtherValue, ORDER> const &other) {
			// Since allocation will happen anyway, we don't care about doing it
			// in-place.
			return *this = *this * other;
		}
		template <typename OtherValue>
		auto operator*(OtherValue const &other) const {
			using ResultValue =
				decltype(std::declval<Value>() * std::declval<OtherValue>());
			Tensor<ResultValue, ORDER> result(this->size());
			Tensor<>::applyOver<0>(
				[&other](ResultValue &result, Value const &that) {
					result = that * other;
				},
				result,
				*this);
			return result;
		}
		template <typename OtherValue>
		auto &operator*=(OtherValue const &other) {
			Tensor<>::applyOver<0>([&other](Value &that) { that *= other; }, *this);
			return *this;
		}
		template <typename OtherValue>
		auto operator/(OtherValue const &other) const {
			using ResultValue =
				decltype(std::declval<Value>() * std::declval<OtherValue>());
			Tensor<ResultValue, ORDER> result(this->size());
			Tensor<>::applyOver<0>(
				[&other](ResultValue &result, Value const &that) {
					result = that / other;
				},
				result,
				*this);
			return result;
		}
		template <typename OtherValue>
		auto &operator/=(OtherValue const &other) {
			Tensor<>::applyOver<0>([&other](Value &that) { that /= other; }, *this);
			return *this;
		}

		// Utility functions.

		// Transposition does not change `SIZES`, and so some functions should use
		// `SIZES`, while others should use `size()`.
		//
		// TODO: Consider caching this each time `transpose` is called.
		inline std::array<std::size_t, ORDER> size() const {
			std::array<std::size_t, ORDER> sizesTransposed;
			for (std::size_t i{0}; i < ORDER; i++) {
				sizesTransposed[i] = this->SIZES[this->TRANSPOSE[i]];
			}
			return sizesTransposed;
		}
		inline bool isEmpty() const {
			for (auto const &i : this->SIZES) {
				if (i == 0) {
					return true;
				}
			}
			return false;
		}
		// Slicing returns a view.
		TypeThis asSlice(std::array<Range, ORDER> const &ranges) const {
			std::array<Range, ORDER> mergedRanges;
			for (std::size_t i{0}; i < ORDER; i++) {
				mergedRanges[i].step =
					ranges[i].step == std::numeric_limits<std::size_t>::max()
					? this->RANGES[i].step
					: this->RANGES[i].step * ranges[i].step;
				mergedRanges[i].start =
					ranges[i].start == std::numeric_limits<std::size_t>::max()
					? this->RANGES[i].start
					: this->RANGES[i].start + this->RANGES[i].step * ranges[i].start;
				mergedRanges[i].stop =
					ranges[i].stop == std::numeric_limits<std::size_t>::max()
					? this->RANGES[i].stop
					: this->RANGES[i].start + this->RANGES[i].step * ranges[i].stop;
				// We do not check that start < stop here, since zero-dimensions are
				// technically valid.
			}
			return {
				this->VALUES,
				mergedRanges,
				this->SIZES_UNDERLYING,
				this->OFFSET,
				this->TRANSPOSE};
		}
		TypeThis slice(std::array<Range, ORDER> const &ranges) {
			return *this = this->asSlice(ranges);
		}
		void fill(Value const &other) {
			Tensor<>::applyOver<0>([&other](Value &that) { that = other; }, *this);
		}
		// Must be a valid permutation of [0, ORDER). Checked iff DEBUG.
		TypeThis asTranspose(std::array<std::size_t, ORDER> const &dimPerm) const {
			if (Platform::isDebug()) {
				std::array<std::size_t, ORDER> dimPermSorted{this->TRANSPOSE};
				std::sort(dimPermSorted.begin(), dimPermSorted.end());
				for (std::size_t i{0}; i < ORDER; i++) {
					if (dimPermSorted[i] != i) {
						throw Exception(Error::SIZES_MISMATCH);
					}
				}
			}
			std::array<std::size_t, ORDER> newDimPerm{};
			for (std::size_t i{0}; i < ORDER; i++) {
				newDimPerm[i] = this->TRANSPOSE[dimPerm[i]];
			}
			return {
				this->VALUES,
				this->RANGES,
				this->SIZES_UNDERLYING,
				this->OFFSET,
				newDimPerm};
		}
		TypeThis transpose(std::array<std::size_t, ORDER> const &dimPerm) {
			return *this = this->asTranspose(dimPerm);
		}

		// Tensor product is defined with a list of pairs of indices to contract.
		//
		// Type of result tensor is the same as the type of Value * OtherValue,
		// without consideration for the contraction + operation.
		//
		// Contraction (+) should be presumed to be commutative. Expansion (*) need
		// not be. Result values are first default-constructed, and should be
		// assumed to be identity w.r.t. contraction.
		//
		// Checks that contraction dimensions are identical iff DEBUG.
		template <
			std::size_t CONTRACT_ORDER,
			template <typename, typename> typename Policy =
				Tensor<>::PlusMultProductPolicy,
			typename OtherValue,
			std::size_t OTHER_ORDER,
			typename ResultValue = decltype(Policy<Value, OtherValue>::product(
				std::declval<Value>(),
				std::declval<OtherValue>())),
			std::size_t RESULT_ORDER = ORDER + OTHER_ORDER - CONTRACT_ORDER * 2>
		auto product(
			Tensor<OtherValue, OTHER_ORDER> const &other,
			std::array<std::size_t, CONTRACT_ORDER> const &thisContractDims,
			std::array<std::size_t, CONTRACT_ORDER> const &otherContractDims) const {
			if (Platform::isDebug()) {
				for (std::size_t i{0}; i < CONTRACT_ORDER; i++) {
					if (
						this->SIZES[this->TRANSPOSE[thisContractDims[i]]] !=
						other.SIZES[other.TRANSPOSE[otherContractDims[i]]]) {
						throw Exception(Error::SIZES_MISMATCH);
					}
				}
			}

			// Transpose all contracted dimensions to the end.
			std::bitset<ORDER> isThisContracted;
			std::bitset<OTHER_ORDER> isOtherContracted;
			for (std::size_t i{0}; i < CONTRACT_ORDER; i++) {
				isThisContracted[thisContractDims[i]] = true;
				isOtherContracted[otherContractDims[i]] = true;
			}
			std::array<std::size_t, ORDER> thisDimPerm;
			std::array<std::size_t, OTHER_ORDER> otherDimPerm;
			for (std::size_t i{0}, j{0}; i < ORDER; i++) {
				if (isThisContracted[i]) {
					continue;
				}
				thisDimPerm[j++] = i;
			}
			for (std::size_t i{0}, j{0}; i < OTHER_ORDER; i++) {
				if (isOtherContracted[i]) {
					continue;
				}
				otherDimPerm[j++] = i;
			}
			for (std::size_t i{CONTRACT_ORDER}; i > 0; i--) {
				thisDimPerm[ORDER - i] = thisContractDims[CONTRACT_ORDER - i];
				otherDimPerm[OTHER_ORDER - i] = otherContractDims[CONTRACT_ORDER - i];
			}
			auto thisTransposed{this->asTranspose(thisDimPerm)};
			auto otherTransposed{other.asTranspose(otherDimPerm)};

			std::array<std::size_t, RESULT_ORDER> resultSize;
			auto thisSize{thisTransposed.size()};
			auto otherSize{otherTransposed.size()};
			for (std::size_t i{0}; i < ORDER - CONTRACT_ORDER; i++) {
				resultSize[i] = thisSize[i];
			}
			for (std::size_t i{0}; i < OTHER_ORDER - CONTRACT_ORDER; i++) {
				resultSize[ORDER - CONTRACT_ORDER + i] = otherSize[i];
			}

			// Iterate over all non-contracted dimensions, and compute contraction
			// (sum) of inner product over all remaining dimensions.
			Tensor<ResultValue, RESULT_ORDER> result(resultSize);
			Tensor<>::applyOver<OTHER_ORDER - CONTRACT_ORDER>(
				[&otherTransposed](
					Tensor<ResultValue, OTHER_ORDER - CONTRACT_ORDER> &&resultOuter,
					Tensor<Value, CONTRACT_ORDER> const &thatInner) {
					Tensor<>::applyOver<0>(
						[&thatInner](
							ResultValue &resultInner,
							Tensor<OtherValue, CONTRACT_ORDER> const &otherInner) {
							// Actually, both `thatInner` and `otherInner` are kept `const`,
							// but we are lazy and don't code the `const` override for
							// `applyOver`.
							resultInner = Policy<Value, OtherValue>::DEFAULT_RESULT;
							Tensor<>::applyOver<0>(
								[&resultInner](
									Value const &thatValue, OtherValue const &otherValue) {
									resultInner = Policy<Value, OtherValue>::sum(
										resultInner,
										Policy<Value, OtherValue>::product(thatValue, otherValue));
								},
								thatInner,
								otherInner);
						},
						resultOuter,
						otherTransposed);
				},
				result,
				thisTransposed);
			return result;
		}
		// Inner and outer product are defined iff ORDER == 1 (vectors).
		template <
			typename OtherValue,
			bool isVector = ORDER == 1,
			typename std::enable_if<isVector>::type * = nullptr>
		auto productInner(Tensor<OtherValue, 1> const &other) const {
			return this->product<1>(other, {0}, {0});
		}
		template <
			typename OtherValue,
			bool isVector = ORDER == 1,
			typename std::enable_if<isVector>::type * = nullptr>
		auto productOuter(Tensor<OtherValue, 1> const &other) const {
			return this->product<0>(other, {}, {});
		}
		// Square matrices also allow for log power. If not square, `*` will throw
		// iff DEBUG.
		//
		// If the goal is to multiply with a Vector later, it is more efficient (by
		// a constant factor) to manually compute the power product each step along
		// the way. This is because each `1` bit will cause a vector mult as opposed
		// to a matrix mult.
		template <
			bool isMatrix = ORDER == 2,
			typename std::enable_if<isMatrix>::type * = nullptr>
		auto power(std::size_t exponent) const {
			if (exponent == 0) {
				this->debugAssertSquare();
				return TypeThis::identity(this->SIZES[this->TRANSPOSE[0]]);
			} else if (exponent == 1) {
				return *this;
			}
			auto half{this->power(exponent / 2)};
			if (exponent % 2 == 0) {
				return half * half;
			} else {
				return half * half * *this;
			}
		}
		// Helper function for various recursive algorithms which depend on D&C.
		// Extends the matrix with 1s on the diagonal and 0s everywhere else.
		//
		// May not allocate if this is already a power of 2.
		template <
			bool isMatrix = ORDER == 2,
			typename std::enable_if<isMatrix>::type * = nullptr>
		auto asNearestPowerOf2() const {
			this->debugAssertSquare();
			auto mSig{Algorithm::mostSignificant1BitIdx(this->SIZES[0])};
			if ((1_zu << mSig) == this->SIZES[0]) {
				return *this;
			}
			auto resultSize{1_zu << (mSig + 1)};
			Tensor<Value, 2> result{{resultSize, resultSize}};
			// Pass `result` second so that we iterate over indices of `*this`.
			Tensor<>::applyOver<0>(
				[](Value &resultValue, Value const &thisValue) {
					resultValue = thisValue;
				},
				result.asSlice({{{1, this->SIZES[0]}, {1, this->SIZES[0]}}}),
				*this);
			return result;
		}
		// Strassen's exists for higher orders, but we do not provide it here.
		// Current Strassen's pads at the beginning, so only use for large matrices
		// where the n^0.17 matters.
		//
		// Under and including size (1_zu << BASE_SIZE_POWER), Strassen will switch
		// to use standard computation instead.
		//
		// TODO: There should be additional options to optimize square MM w.r.t
		// memory locality & re-allocation.
		//
		// TODO: Refactor into product policy.
		template <
			std::size_t BASE_SIZE_POWER = 8,
			typename OtherValue,
			bool isMatrix = ORDER == 2,
			typename std::enable_if<isMatrix>::type * = nullptr,
			typename ResultValue =
				decltype(std::declval<Value>() * std::declval<OtherValue>())>
		auto productStrassen(Tensor<OtherValue, 2> const &other) const {
			this->debugAssertSquare();
			other.debugAssertSquare();
			if (Platform::isDebug()) {
				if (this->SIZES[0] != other.SIZES[0]) {
					throw Exception(Error::SIZES_MISMATCH);
				}
			}
			if (this->SIZES[0] <= (1_zu << BASE_SIZE_POWER)) {
				return *this * other;
			}
			auto a{this->asNearestPowerOf2()}, b{other.asNearestPowerOf2()};
			auto halfSize{a.SIZES[0] / 2};
			auto a11{a.asSlice({{{0, halfSize}, {0, halfSize}}})},
				a12{a.asSlice({{{0, halfSize}, {halfSize, halfSize * 2}}})},
				a21{a.asSlice({{{halfSize, halfSize * 2}, {0, halfSize}}})},
				a22{a.asSlice({{{halfSize, halfSize * 2}, {halfSize, halfSize * 2}}})},
				b11{b.asSlice({{{0, halfSize}, {0, halfSize}}})},
				b12{b.asSlice({{{0, halfSize}, {halfSize, halfSize * 2}}})},
				b21{b.asSlice({{{halfSize, halfSize * 2}, {0, halfSize}}})},
				b22{b.asSlice({{{halfSize, halfSize * 2}, {halfSize, halfSize * 2}}})};
			std::array<Tensor<ResultValue, 2>, 7> m{
				{{(a11 + a22).productStrassen(b11 + b22)},
				 {(a21 + a22).productStrassen(b11)},
				 {a11.productStrassen(b12 - b22)},
				 {a22.productStrassen(b21 - b11)},
				 {(a11 + a12).productStrassen(b22)},
				 {(a21 - a11).productStrassen(b11 + b12)},
				 {(a12 - a22).productStrassen(b21 + b22)}}};
			Tensor<ResultValue, 2> c{{halfSize * 2, halfSize * 2}};
			Tensor<>::applyOver<0>(
				[](
					ResultValue &c11,
					ResultValue const &m1,
					ResultValue const &m4,
					ResultValue const &m5,
					ResultValue const &m7) { c11 = m1 + m4 - m5 + m7; },
				c.asSlice({{{0, halfSize}, {0, halfSize}}}),
				m[0],
				m[3],
				m[4],
				m[6]);
			Tensor<>::applyOver<0>(
				[](ResultValue &c12, ResultValue const &m3, ResultValue const &m5) {
					c12 = m3 + m5;
				},
				c.asSlice({{{0, halfSize}, {halfSize, halfSize * 2}}}),
				m[2],
				m[4]);
			Tensor<>::applyOver<0>(
				[](ResultValue &c21, ResultValue const &m2, ResultValue const &m4) {
					c21 = m2 + m4;
				},
				c.asSlice({{{halfSize, halfSize * 2}, {0, halfSize}}}),
				m[1],
				m[3]);
			Tensor<>::applyOver<0>(
				[](
					ResultValue &c22,
					ResultValue const &m1,
					ResultValue const &m2,
					ResultValue const &m3,
					ResultValue const &m6) { c22 = m1 - m2 + m3 + m6; },
				c.asSlice({{{halfSize, halfSize * 2}, {halfSize, halfSize * 2}}}),
				m[0],
				m[1],
				m[2],
				m[5]);
			return c.asSlice({{{0, this->SIZES[0]}, {0, this->SIZES[0]}}});
		}
		// Inverses may exist for higher orders, but we do not provide it here.
		template <
			bool isMatrix = ORDER == 2,
			typename std::enable_if<isMatrix>::type * = nullptr>
		auto inverse() const {
			if (Platform::isDebug()) {
				if (this->SIZES[0] != this->SIZES[1]) {
					throw Exception(Error::SIZES_MISMATCH);
				}
			}

			// TODO: Implement `inverse`.
			return *this;
		}
		template <
			bool isMatrix = ORDER == 2,
			typename std::enable_if<isMatrix>::type * = nullptr>
		auto invert() {
			return *this = this->inverse();
		}
	};
}

template <typename Value>
inline std::ostream &operator<<(
	std::ostream &stream,
	Rain::Math::Tensor<Value, 1> const &right) {
	using namespace std;
	if (right.isEmpty()) {
		return stream << "[]";
	}
	stream << '[' << setw(4) << right[0];
	for (std::size_t i{1}; i < right.size()[0]; i++) {
		stream << ' ' << setw(4) << right[i];
	}
	return stream << ']';
}
template <
	typename Value,
	std::size_t ORDER,
	bool isNotVector = (ORDER > 1),
	typename std::enable_if<isNotVector>::type * = nullptr>
inline std::ostream &operator<<(
	std::ostream &stream,
	Rain::Math::Tensor<Value, ORDER> const &right) {
	using namespace std;
	if (right.isEmpty()) {
		return stream << "[]";
	}
	stream << '[' << right[0];
	for (std::size_t i{1}; i < right.size()[0]; i++) {
		stream << "\n " << right[i];
	}
	return stream << ']';
}

using LL = long long;
using LD = long double;
using namespace std;

#define RF(x, from, to) \
	for (LL x(from), _to(to), _delta{x < _to ? 1LL : -1LL}; x != _to; x += _delta)

using MF = Rain::Algorithm::ModulusField<LL, 1000000007>;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	std::size_t N, M, K;
	cin >> N >> M >> K;

	Rain::Math::Tensor<LL, 1> Z{{N}};
	LL const INF{LLONG_MAX / 4};
	Z[0] = 0;
	RF(i, 1, N) {
		Z[i] = INF;
	}

	Rain::Math::Tensor<LL, 2> A{{N, N}};
	RF(i, 0, N) {
		RF(j, 0, N) {
			A[i][j] = INF;
		}
	}
	RF(i, 0, M) {
		LL u, v, w;
		cin >> u >> v >> w;
		A[v - 1][u - 1] = min(A[v - 1][u - 1], w);
	}

	while (K > 0) {
		if (K & 1) {
			Z = A.product<1, Rain::Math::Tensor<>::MinPlusProductPolicy>(Z, {1}, {0});
		}
		K >>= 1;
		A = A.product<1, Rain::Math::Tensor<>::MinPlusProductPolicy>(A, {1}, {0});
	}
	cout << (Z[N - 1] >= INF ? -1 : Z[N - 1]);
	return 0;
}
