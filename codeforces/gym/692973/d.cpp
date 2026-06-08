// Fenwick/Binary-Indexed Tree implementation. O(ln N) point
// updates and range queries. Not thread-safe.
// #pragma once

#include <cstdint>
#include <vector>

namespace Rain::Algorithm {
	// Fixed-size Fenwick/Binary-Indexed Tree implementation.
	// O(ln N) point updates and range queries. Not
	// thread-safe.
	//
	// Value must support commutative addition. In addition,
	// default initialization should be equivalent to "empty".
	template<typename Value = long long>
	class FenwickTree {
		private:
		std::vector<Value> tree;

		public:
		// Creates a Fenwick tree, which may be resized by
		// operations.
		FenwickTree(std::size_t const size) : tree(size) {}

		// Computes prefix sum up to and including idx.
		Value sum(std::size_t const idx) const {
			Value aggregate{};
			for (
				std::size_t i{idx}; i != SIZE_MAX;
				i &= i + 1, i--) {
				aggregate += this->tree[i];
			}
			return aggregate;
		}

		// Modify index by a delta.
		void modify(std::size_t const idx, Value const &delta) {
			for (
				std::size_t i{idx}; i < this->tree.size();
				i |= i + 1) {
				this->tree[i] += delta;
			}
		}
	};
}

// Utilities for platform and build detection.
//
// Rain supports distinguishing between 3 major platforms:
// Windows, MacOS, and Linux-based.
// #pragma once

#include <iostream>

#if defined(_WIN32) || defined(_WIN64)
	#define RAIN_PLATFORM_WINDOWS
#endif

#if defined(__APPLE__) || defined(__MACH__)
	#define RAIN_PLATFORM_MACOS
#endif

#if defined(__linux__) || defined(linux) || defined(__linux)
	#define RAIN_PLATFORM_LINUX
#endif

#if !defined(RAIN_PLATFORM_WINDOWS) && \
	!defined(RAIN_PLATFORM_MACOS) && \
	!defined(RAIN_PLATFORM_LINUX)
	#define RAIN_PLATFORM_OTHER
#endif

#ifdef NDEBUG
	#define RAIN_PLATFORM_NDEBUG
#endif

namespace Rain::Platform {
	enum class Platform { NONE = 0, WINDOWS, MACOS, LINUX };

	// Get the Platform enum Rain is running on.
	inline Platform constexpr getPlatform() noexcept {
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
	inline bool constexpr isDebug() noexcept {
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

// #pragma once

// #include "../platform.hpp"

#include <functional>
#include <type_traits>

namespace Rain::Functional {
	// Similar to `integral_constant`, upgrades a value into a
	// type, but with automatic type deduction on the value.
	template<auto VALUE>
	class TypeUpgrade {
		public:
		static inline auto constexpr UNDERLYING{VALUE};
	};
	// Downgrades a non-type, non-constant template parameter
	// into a type template parameter. Useful to wrap more
	// complex template template types before passing to
	// generic templates accepting `typename...`.
	template<template<typename...> typename Type>
	class TypeDowngrade {
		public:
		template<typename... Args>
		using Underlying = Type<Args...>;
	};

	template<typename... Types>
	class TypeTrait;

	// Type traits for parameter packs where nothing is known.
	// Unpacks variadic templates if possible.
	template<typename... Types>
	class TypeTraitInterface {
		public:
		using HasTypeFirst = std::false_type;
	};
	template<typename First, typename... Types>
	class TypeTraitInterface<First, Types...> {
		public:
		using HasTypeFirst = std::true_type;
		using TypeFirst = First;

		// Get second type via Remaining::First, third type
		// via Remaining::Remaining::First, and so on.
		using TypeTraitRemaining = TypeTrait<Types...>;
	};

	// Type traits for a single type whose upgrade/downgrade
	// status is unknown.
	template<typename>
	class TypeTraitInterfaceFirstInterface {
		public:
		using IsTypeUpgrade = std::false_type;
		using IsTypeSidegrade = std::true_type;
		using IsTypeDowngrade = std::false_type;
	};
	template<auto VALUE>
	class TypeTraitInterfaceFirstInterface<
		TypeUpgrade<VALUE>> {
		public:
		using IsTypeUpgrade = std::true_type;
		using IsTypeSidegrade = std::false_type;
		using IsTypeDowngrade = std::false_type;
	};
	template<template<typename...> typename Type>
	class TypeTraitInterfaceFirstInterface<
		TypeDowngrade<Type>> {
		public:
		using IsTypeUpgrade = std::false_type;
		using IsTypeSidegrade = std::false_type;
		using IsTypeDowngrade = std::true_type;
	};

	// Type traits for a single type which is an upgrade.
	template<typename, typename = void>
	class TypeTraitInterfaceFirstInterfaceUpgrade {};
	template<typename Type>
	class TypeTraitInterfaceFirstInterfaceUpgrade<
		Type,
		typename std::enable_if<
			TypeTraitInterfaceFirstInterface<
				Type>::IsTypeUpgrade::value>::type> {
		public:
		// Usage of these scoped templates as a template
		// template parameter may require the use of the
		// `template` keyword if the outer template is
		// dependent (e.g., `TraitAuto<SIZE>::template
		// isEqualTo`).
		template<auto RIGHT>
		using IsEqualTo = std::
			integral_constant<bool, Type::UNDERLYING == RIGHT>;
		template<auto RIGHT>
		using IsLessThan = std::
			integral_constant<bool, (Type::UNDERLYING < RIGHT)>;
		template<auto RIGHT>
		using IsGreaterThan = std::
			integral_constant<bool, (Type::UNDERLYING > RIGHT)>;
	};

	// Individual overrideable type traits for Sidegrade
	// type arithmetic traits.
	template<typename Type>
	class
		TypeTraitInterfaceFirstInterfaceSidegradeIsIntegral {
		public:
		static inline bool constexpr value{
			std::is_integral<Type>::value};
	};
	template<typename Type>
	class
		TypeTraitInterfaceFirstInterfaceSidegradeIsFloatingPoint {
		public:
		static inline bool constexpr value{
			std::is_floating_point<Type>::value};
	};
	template<typename Type>
	class
		TypeTraitInterfaceFirstInterfaceSidegradeIsArithmetic {
		public:
		static inline bool constexpr value{
			TypeTraitInterfaceFirstInterfaceSidegradeIsIntegral<
				Type>::value ||
			TypeTraitInterfaceFirstInterfaceSidegradeIsFloatingPoint<
				Type>::value};
	};
	template<typename, typename = void>
	class
		TypeTraitInterfaceFirstInterfaceSidegradeIsSignedInterface;
	template<typename Type>
	class
		TypeTraitInterfaceFirstInterfaceSidegradeIsSignedInterface<
			Type,
			typename std::enable_if<
				!TypeTraitInterfaceFirstInterfaceSidegradeIsArithmetic<
					Type>::value>::type> {
		public:
		static inline bool constexpr value{false};
	};
	template<typename Type>
	class
		TypeTraitInterfaceFirstInterfaceSidegradeIsSignedInterface<
			Type,
			typename std::enable_if<
				TypeTraitInterfaceFirstInterfaceSidegradeIsArithmetic<
					Type>::value>::type> {
		public:
		static inline bool constexpr value{Type(-1) < Type(0)};
	};
	template<typename Type>
	class TypeTraitInterfaceFirstInterfaceSidegradeIsSigned :
		public TypeTraitInterfaceFirstInterfaceSidegradeIsSignedInterface<
			Type> {};
	template<typename, typename = void>
	class
		TypeTraitInterfaceFirstInterfaceSidegradeIsUnsignedInterface;
	template<typename Type>
	class
		TypeTraitInterfaceFirstInterfaceSidegradeIsUnsignedInterface<
			Type,
			typename std::enable_if<
				!TypeTraitInterfaceFirstInterfaceSidegradeIsArithmetic<
					Type>::value>::type> {
		public:
		static inline bool constexpr value{false};
	};
	template<typename Type>
	class
		TypeTraitInterfaceFirstInterfaceSidegradeIsUnsignedInterface<
			Type,
			typename std::enable_if<
				TypeTraitInterfaceFirstInterfaceSidegradeIsArithmetic<
					Type>::value>::type> {
		public:
		static inline bool constexpr value{Type(0) < Type(-1)};
	};
	template<typename Type>
	class
		TypeTraitInterfaceFirstInterfaceSidegradeIsUnsigned :
		public TypeTraitInterfaceFirstInterfaceSidegradeIsUnsignedInterface<
			Type> {};

	// Type traits for a single type/sidegrade.
	template<typename, typename = void>
	class TypeTraitInterfaceFirstInterfaceSidegrade {};
	template<typename Type>
	class TypeTraitInterfaceFirstInterfaceSidegrade<
		Type,
		typename std::enable_if<
			TypeTraitInterfaceFirstInterface<
				Type>::IsTypeSidegrade::value>::type> {
		public:
		template<typename>
		static std::false_type isBaseOf(...);
		template<typename TypeBase>
		static std::true_type isBaseOf(TypeBase const *);
		template<
			typename TypeDerived,
			std::enable_if<TypeTraitInterfaceFirstInterface<
				TypeDerived>::IsTypeSidegrade::value>::type * =
				nullptr>
		using IsBaseOf =
			decltype(isBaseOf<typename std::decay<Type>::type>(
				std::declval<
					typename std::decay<TypeDerived>::type *>()));

		template<typename>
		static std::false_type isStdHashable(...);
		template<typename T>
		static std::true_type isStdHashable(
			decltype(std::hash<T>()) *);
		using IsStdHashable = decltype(isStdHashable<
			typename std::decay<Type>::type>(nullptr));

		template<typename>
		static std::false_type isConstIterable(...);
		template<typename T>
		static std::true_type isConstIterable(
			typename T::const_iterator *);
		using IsConstIterable = decltype(isConstIterable<
			typename std::decay<Type>::type>(nullptr));

		template<typename, typename...>
		static std::false_type isCallableWith(...);
		template<typename T, typename... Args>
		static std::true_type isCallableWith(
			decltype(std::declval<T>()(
				std::declval<Args...>())) *);
		template<typename... Args>
		using IsCallableWith = decltype(isCallableWith<
			typename std::decay<Type>::type,
			Args...>(nullptr));

		// Classical arithmetic type traits.
		using IsIntegral =
			TypeTraitInterfaceFirstInterfaceSidegradeIsIntegral<
				typename std::decay<Type>::type>;
		using IsFloatingPoint =
			TypeTraitInterfaceFirstInterfaceSidegradeIsFloatingPoint<
				typename std::decay<Type>::type>;
		using IsArithmetic =
			TypeTraitInterfaceFirstInterfaceSidegradeIsArithmetic<
				typename std::decay<Type>::type>;
		using IsSigned =
			TypeTraitInterfaceFirstInterfaceSidegradeIsSigned<
				typename std::decay<Type>::type>;
		using IsUnsigned =
			TypeTraitInterfaceFirstInterfaceSidegradeIsUnsigned<
				typename std::decay<Type>::type>;
	};

	// Type traits for a single type which is a downgrade.
	template<typename, typename = void>
	class TypeTraitInterfaceFirstInterfaceDowngrade {};
	template<typename Type>
	class TypeTraitInterfaceFirstInterfaceDowngrade<
		Type,
		typename std::enable_if<
			TypeTraitInterfaceFirstInterface<
				Type>::IsTypeDowngrade::value>::type> {
		public:
		// Template specification detection is actually very
		// difficult in this context, largely due to
		// TypeUnderlying being a alias template dependent type,
		// and type deduction failing in general for alias
		// template types. Thus, the standard method of deducing
		// types args (via class template) for TypeSpecific will
		// fail to compile.
		//
		// We bypass this with a deductor based on function
		// arguments. Furthermore, we must define type alias
		// TypeUnderlying or the compiler will fail to see the
		// dependent type as a template type.
		//
		// Some links follow.
		//
		// Before C++20, alias templates are never deduced:
		// <https://en.cppreference.com/cpp/language/template_argument_deduction>.
		// Discussion:
		// <https://stackoverflow.com/questions/41008092/class-template-argument-deduction-not-working-with-alias-template>.
		// Simply trying to deduce TypeUnderlying<Args...> will
		// fail because the dependent type TypeUnderlying names
		// a non-deducible context:
		// <https://stackoverflow.com/questions/25245453/what-is-a-non-deduced-context>.
		//
		// Using a reference instead of a pointer should prevent
		// decays into base types. To detect base types, use
		// specific types with the Sidegrade version of
		// IsBaseOf.
		template<typename... Args>
		using TypeUnderlying =
			typename Type::template Underlying<Args...>;

		// Detects if Type is the template of a base of
		// TypeSpecific.
		template<template<typename...> typename>
		static std::false_type isTemplateBaseOf(...);
		template<
			template<typename...> typename TypeBase,
			typename... Args>
		static std::true_type isTemplateBaseOf(
			TypeBase<Args...> const *);
		// MSVC has a bug where template type deduction here
		// doesn't properly take into account the variadic
		// Args... So we manually overload for up to 2
		// arguments.
		template<
			template<typename...> typename TypeBase,
			typename Arg1,
			typename Arg2>
		static std::true_type isTemplateBaseOf(
			TypeBase<Arg1, Arg2> const *);

		template<typename TypeSpecific>
		using IsTemplateBaseOf =
			decltype(isTemplateBaseOf<TypeUnderlying>(
				std::declval<
					typename std::decay<TypeSpecific>::type *>()));

		// To determine if TypeSpecific is a specification of
		// the Type template, but not a derived class of it,
		// Type must be at least a TemplateBase (template and/or
		// base) of TypeSpecific. Then, we can take the "middle"
		// type, which is a specification of Type. If the middle
		// type is equal to TypeSpecific, then we are not a
		// base, just a template.
		template<typename, typename, typename = void>
		class IsTemplateOfInterface : public std::false_type {};
		template<typename TypeSpecific, typename TypeMiddle>
		class IsTemplateOfInterface<
			TypeSpecific,
			TypeMiddle,
			typename std::enable_if<std::
					is_same<TypeSpecific, TypeMiddle>::value>::type> :
			public std::true_type {};

		template<typename, template<typename...> typename>
		static std::false_type isTemplateOf(...);
		template<
			typename TypeSpecific,
			template<typename...> typename TypeBase,
			typename... Args>
		static IsTemplateOfInterface<
			TypeSpecific,
			TypeBase<Args...>>
			isTemplateOf(TypeBase<Args...> const *);
		// MSVC bug here again. TODO: file it.
		template<
			typename TypeSpecific,
			template<typename...> typename TypeBase,
			typename Arg1,
			typename Arg2>
		static IsTemplateOfInterface<
			TypeSpecific,
			TypeBase<Arg1, Arg2>>
			isTemplateOf(TypeBase<Arg1, Arg2> const *);

		template<typename TypeSpecific>
		using IsTemplateOf = decltype(isTemplateOf<
			typename std::decay<TypeSpecific>::type,
			TypeUnderlying>(std::declval<
			typename std::decay<TypeSpecific>::type *>()));

		// Detects if Type<Args...> is a defined type.
		template<template<typename...> typename, typename...>
		static std::false_type isSpecifiedBy(...);
		template<
			template<typename...> typename TypeTemplate,
			typename... Args>
		static std::true_type isSpecifiedBy(
			decltype(TypeTemplate<Args...>()) *);
		template<typename... Args>
		using IsSpecifiedBy = decltype(isSpecifiedBy<
			TypeUnderlying,
			typename std::decay<Args>::type...>(nullptr));
	};

	// Type traits for a parameter pack where at least the
	// first parameter exists.
	template<typename...>
	class TypeTraitInterfaceFirst {};
	template<typename First, typename... Types>
	class TypeTraitInterfaceFirst<First, Types...> :
		public TypeTraitInterfaceFirstInterface<First>,
		public TypeTraitInterfaceFirstInterfaceUpgrade<First>,
		public TypeTraitInterfaceFirstInterfaceSidegrade<First>,
		public TypeTraitInterfaceFirstInterfaceDowngrade<
			First> {};

	// Type traits inherits from interfaces, which deduces
	// properties about the parameter pack, step by step.
	template<typename... Types>
	class TypeTrait :
		public TypeTraitInterface<Types...>,
		public TypeTraitInterfaceFirst<Types...> {};
}

// #pragma once

// #include "functional/trait.hpp"

#include <chrono>
#include <random>

namespace Rain::Random {
	template<typename, typename = void>
	struct SplitMixHash;

	// Simple function to combine two 32 or 64-bit hashes,
	// based on
	// <https://stackoverflow.com/questions/5889238/why-is-xor-the-default-way-to-combine-hashes>
	// from Boost.
	//
	// SIZE_T_SIZE is a default argument which forces a
	// substitution, and thus SFINAE.
	template<
		std::size_t SIZE_T_SIZE = sizeof(std::size_t),
		typename std::enable_if<SIZE_T_SIZE == 8>::type * =
			nullptr>
	static inline std::size_t combineHash(
		std::size_t &seed,
		std::size_t next) {
		return seed ^=
			next + 0x517cc1b727220a95 + (seed << 6) + (seed >> 2);
	}
	template<
		typename Type,
		std::size_t SIZE_T_SIZE = sizeof(std::size_t),
		typename std::enable_if<SIZE_T_SIZE == 4>::type * =
			nullptr>
	static inline std::size_t combineHash(
		std::size_t &seed,
		std::size_t next) {
		return seed ^=
			next + 0x9e3779b9 + (seed << 6) + (seed >> 2);
	}

	// SFINAE enables SplitMixHash for all std::hash-able
	// types, and defines custom unwrapping hash for
	// pairs/containers/etc.
	template<typename Type>
	struct SplitMixHash<
		Type,
		typename std::enable_if<
			Functional::TypeTrait<Type>::IsStdHashable::value &&
			sizeof(std::size_t) == 8>::type> {
		// 64-bit hash from
		// <https://codeforces.com/blog/entry/62393>.
		std::size_t operator()(Type const &value) const {
			static std::mt19937_64 generator(
				std::random_device{}());
			static const std::size_t FIXED_RANDOM(generator());
			std::size_t hash{
				std::hash<typename std::decay<Type>::type>{}(
					value)};
			hash += FIXED_RANDOM + 0x9e3779b97f4a7c15;
			hash = (hash ^ (hash >> 30)) * 0xbf58476d1ce4e5b9;
			hash = (hash ^ (hash >> 27)) * 0x94d049bb133111eb;
			return hash ^ (hash >> 31);
		}
	};

	template<typename Type>
	struct SplitMixHash<
		Type,
		typename std::enable_if<
			Functional::TypeTrait<Type>::IsStdHashable::value &&
			sizeof(std::size_t) == 4>::type> {
		// 32-bit hash from
		// <https://groups.google.com/g/prng/c/VFjdFmbMgZI>.
		std::size_t operator()(Type const &value) const {
			static std::mt19937 generator(std::random_device{}());
			static const std::size_t FIXED_RANDOM(generator());
			std::size_t hash{
				std::hash<typename std::decay<Type>::type>{}(
					value)};
			hash += FIXED_RANDOM + 0x9e3779b9;
			hash = (hash ^ (hash >> 16)) * 0x85ebca6b;
			hash = (hash ^ (hash >> 13)) * 0xc2b2ae35;
			return hash ^ (hash >> 16);
		}
	};
	template<typename Type>
	struct SplitMixHash<
		Type,
		typename std::enable_if<
			!Functional::TypeTrait<Type>::IsStdHashable::value &&
			Functional::TypeTrait<Type>::IsConstIterable::value>::
			type> {
		// Unwraps a container.
		std::size_t operator()(Type const &value) const {
			std::size_t result{};
			for (auto const &i : value) {
				combineHash(result, SplitMixHash<decltype(i)>{}(i));
			}
			return result;
		}
	};
	template<typename Type>
	struct SplitMixHash<
		Type,
		typename std::enable_if<
			!Functional::TypeTrait<Type>::IsStdHashable::value &&
			!Functional::TypeTrait<
				Type>::IsConstIterable::value>::type> {
		// Unwraps a pair.
		std::size_t operator()(Type const &value) const {
			// MSVC bug: putting this valid SFINAE expression
			// within the class or function template just nukes
			// the entire class specialization. Instead, putting
			// it in the body seems to work.
			//
			// TODO: file it.
			if constexpr (
				Functional::TypeTrait<Functional::TypeDowngrade<
					std::pair>>::IsTemplateBaseOf<Type>::value) {
				std::size_t result{};
				combineHash(
					result,
					SplitMixHash<decltype(value.first)>{}(
						value.first));
				combineHash(
					result,
					SplitMixHash<decltype(value.second)>{}(
						value.second));
				return result;
			} else {
				// Non-pair, non-const-iterable, non-std-hashable
				// SplitMixHash is not yet implemented!
				static_assert(false);
				return {};
			}
		}
	};
}

// User-defined literals. Literals are meant to be resolved
// through the namespace scope: using namespace
// Rain::Literal;.
// #pragma once

// Provides std::literals.
#include <chrono>

#include <regex>

namespace Rain {
	// Inline namespaces are implicitly accessible by the
	// parent namespace.
	inline namespace Literal {
		// Inject std literals into the Rain namespace.
		// Injecting the entire namespace via `using namespace
		// std::literals` may cause compilation issues with
		// default arguments using those literals.
		using std::string_literals::operator""s;
		using std::chrono_literals::operator""h;
		using std::chrono_literals::operator""s;
		using std::chrono_literals::operator""ms;

		// User-defined literals.
		inline constexpr std::size_t operator""_zu(
			unsigned long long value) {
			return static_cast<std::size_t>(value);
		}
		inline std::regex operator""_re(
			char const *value,
			std::size_t) {
			return std::regex(value);
		}
		inline constexpr short operator""_ss(
			unsigned long long value) {
			return static_cast<short>(value);
		}
	}
}

// Implementation for a prime modulus ring over the
// integers, supporting basic operations add, subtract,
// multiply in O(1) and divide in O(ln N).
// #pragma once

// #include "../literal.hpp"
// #include "../random.hpp"
// #include "rain/functional/trait.hpp"

#include <iostream>
#include <vector>

namespace Rain::Math {
	template<
		typename = std::nullptr_t,
		typename = std::nullptr_t,
		typename = Functional::TypeUpgrade<0_zu>>
	class ModulusRingBaseInterface;

	template<
		typename Derived = std::nullptr_t,
		typename Underlying = std::nullptr_t,
		std::size_t MODULUS_OUTER = 0_zu>
	using ModulusRingBase = ModulusRingBaseInterface<
		Derived,
		Underlying,
		Functional::TypeUpgrade<MODULUS_OUTER>>;

	// Implementation for a modulus ring CRTP over the
	// integers, supporting basic operations add, subtract,
	// multiply in O(1) and divide in O(ln M). Division is
	// generally only valid for prime moduli. For O(1)
	// division, cache multiplicative inverses and multiply
	// with those.
	//
	// A runtime modulus may be specified with MODULUS 0 in
	// the template and the appropriate constructor.
	//
	// Underlying must be large enough to store (modulus() -
	// 1)^2.
	//
	// Polymorphism CRTP is similar to the 2D CRTP in
	// Networking, but without the additional layers and
	// complexity.
	template<
		typename Derived,
		typename Underlying,
		typename ModulusOuterValue>
	class ModulusRingBaseInterface {
		public:
		static inline std::size_t constexpr MODULUS_OUTER{
			ModulusOuterValue::UNDERLYING};

		private:
		using TypeThis =
			ModulusRingBase<Derived, Underlying, MODULUS_OUTER>;

		template<typename TypeDerived>
		using IsDerivedFromModulusRing = Functional::TypeTrait<
			Functional::TypeDowngrade<ModulusRingBaseInterface>>::
			IsTemplateBaseOf<TypeDerived>;

		public:
		Underlying const MODULUS;
		Underlying value;

		// Construction with a raw value will directly take the
		// value. Construction with another
		// ModulusRingBaseInterface will call the % operator on
		// the other's value, which will always stay in range of
		// the other's ring. This value is then explicitly cast
		// into the current underlying type.
		//
		// If the integer specified is signed and negative, we
		// want to wrap it back to the positives first.
		//
		// Use () instead of {} for value to explicitly trigger
		// narrowing casts, if necessary.
		template<
			typename Integer = std::size_t,
			typename std::enable_if<!IsDerivedFromModulusRing<
				Integer>::value>::type * = nullptr,
			std::size_t MODULUS_INNER = MODULUS_OUTER,
			typename std::enable_if<MODULUS_INNER != 0>::type * =
				nullptr>
		inline constexpr ModulusRingBaseInterface(
			Integer const &value = 0) :
			MODULUS{MODULUS_OUTER},
			// Writing `Integer() - value` avoids MSVC C4146.
			value(
				value < 0 ? this->MODULUS -
						(static_cast<Underlying>(Integer() - value) %
							this->MODULUS)
									: static_cast<Underlying>(value) %
						this->MODULUS) {}
		template<
			typename Integer = std::size_t,
			typename std::enable_if<!IsDerivedFromModulusRing<
				Integer>::value>::type * = nullptr,
			std::size_t MODULUS_INNER = MODULUS_OUTER,
			typename std::enable_if<MODULUS_INNER == 0>::type * =
				nullptr>
		inline constexpr ModulusRingBaseInterface(
			Underlying const &modulus,
			Integer const &value = 0) :
			MODULUS{modulus},
			// Writing `Integer() - value` avoids MSVC C4146.
			value(
				value < 0 ? this->MODULUS -
						(static_cast<Underlying>(Integer() - value) %
							this->MODULUS)
									: static_cast<Underlying>(value) %
						this->MODULUS) {}
		template<
			typename OtherDerived,
			typename OtherUnderlying,
			std::size_t OTHER_MODULUS_OUTER,
			std::size_t MODULUS_INNER = MODULUS_OUTER,
			typename std::enable_if<MODULUS_INNER != 0>::type * =
				nullptr>
		inline constexpr ModulusRingBaseInterface(
			ModulusRingBase<
				OtherDerived,
				OtherUnderlying,
				OTHER_MODULUS_OUTER> const &other) :
			MODULUS{MODULUS_OUTER},
			value(
				other.value < 0
					? this->MODULUS -
						(static_cast<Underlying>(-other.value) %
							this->MODULUS)
					: static_cast<Underlying>(other.value) %
						this->MODULUS) {}
		template<
			typename OtherDerived,
			typename OtherUnderlying,
			std::size_t OTHER_MODULUS_OUTER,
			std::size_t MODULUS_INNER = MODULUS_OUTER,
			typename std::enable_if<MODULUS_INNER == 0>::type * =
				nullptr>
		inline constexpr ModulusRingBaseInterface(
			Underlying const &modulus,
			ModulusRingBase<
				OtherDerived,
				OtherUnderlying,
				OTHER_MODULUS_OUTER> const &other) :
			MODULUS{modulus},
			value(
				other.value < 0
					? this->MODULUS -
						(static_cast<Underlying>(
							 decltype(other.value)() - other.value) %
							this->MODULUS)
					: static_cast<Underlying>(other.value) %
						this->MODULUS) {}

		// Explicit copy constructor helps avoid compiler
		// warnings on `clang`.
		inline constexpr ModulusRingBaseInterface(
			TypeThis const &other) :
			MODULUS{other.MODULUS},
			value{
				other.value < 0
					? this->MODULUS -
						(static_cast<Underlying>(
							 decltype(other.value)() - other.value) %
							this->MODULUS)
					: static_cast<Underlying>(other.value) %
						this->MODULUS} {}

		// Builds a Derived type, but with the same underlying
		// modulus value. Uses more specialized SFINAE to
		// differentiate otherwise identical signatures.
		template<
			typename Integer,
			std::size_t MODULUS_INNER = MODULUS_OUTER,
			typename std::enable_if<MODULUS_INNER != 0>::type * =
				nullptr>
		static inline constexpr Derived build(
			Integer const &value) {
			return Derived(value);
		}
		template<
			typename Integer,
			std::size_t MODULUS_INNER = MODULUS_OUTER,
			typename std::enable_if<MODULUS_INNER == 0>::type * =
				nullptr>
		inline Derived constexpr build(
			Integer const &value) const {
			return {this->MODULUS, value};
		}

		// Assignment operators need to be overloaded as this
		// class stores an additional modulus, which implicitly
		// deletes the default assignment operator.
		//
		// Assignment only assigns the value. On some compilers
		// (MSVC), it is helpful to have an explicit overload
		// for the current type.
		template<
			typename Integer,
			typename std::enable_if<!IsDerivedFromModulusRing<
				Integer>::value>::type * = nullptr>
		inline auto constexpr &operator=(Integer const &other) {
			return *this = build(other);
		}
		template<
			typename OtherDerived,
			typename OtherUnderlying,
			std::size_t OTHER_MODULUS_FIELD>
		inline auto constexpr &operator=(ModulusRingBase<
			OtherDerived,
			OtherUnderlying,
			OTHER_MODULUS_FIELD> const &other) {
			// Like in the constructor, we should force this
			// modulus first.
			this->value = other.value % this->MODULUS;
			return *this;
		}
		inline auto constexpr &operator=(
			TypeThis const &other) {
			this->value = other.value % this->MODULUS;
			return *this;
		}

		// Casts are explicit to prevent errors. However, this
		// may still be deceptive.
		template<
			typename Integer,
			typename std::enable_if<!IsDerivedFromModulusRing<
				Integer>::value>::type * = nullptr>
		explicit inline constexpr operator Integer() const {
			return static_cast<Integer>(this->value);
		}

		// Comparison on integer types will first bring the
		// integer into the ring. Comparison with other modulus
		// types will compare the value directly. Some operators
		// are generated by the compiler automatically.
		template<
			typename Integer,
			typename std::enable_if<!IsDerivedFromModulusRing<
				Integer>::value>::type * = nullptr>
		inline auto constexpr operator==(
			Integer const &other) const {
			return *this == build(other);
		}
		template<
			typename OtherDerived,
			typename OtherUnderlying,
			std::size_t OTHER_MODULUS_OUTER>
		inline auto constexpr operator==(ModulusRingBase<
			OtherDerived,
			OtherUnderlying,
			OTHER_MODULUS_OUTER> const &other) const {
			// Ignores modulus comparison!
			return this->value == other.value;
		}
		template<
			typename Integer,
			typename std::enable_if<!IsDerivedFromModulusRing<
				Integer>::value>::type * = nullptr>
		inline auto constexpr operator<(
			Integer const &other) const {
			return *this < build(other);
		}
		template<
			typename OtherDerived,
			typename OtherUnderlying,
			std::size_t OTHER_MODULUS_OUTER>
		inline auto constexpr operator<(ModulusRingBase<
			OtherDerived,
			OtherUnderlying,
			OTHER_MODULUS_OUTER> const &other) const {
			return this->value < other.value;
		}
		template<
			typename Integer,
			typename std::enable_if<!IsDerivedFromModulusRing<
				Integer>::value>::type * = nullptr>
		inline auto constexpr operator<=(
			Integer const &other) const {
			return *this <= build(other);
		}
		template<
			typename OtherDerived,
			typename OtherUnderlying,
			std::size_t OTHER_MODULUS_OUTER>
		inline auto constexpr operator<=(ModulusRingBase<
			OtherDerived,
			OtherUnderlying,
			OTHER_MODULUS_OUTER> const &other) const {
			return *this < other || *this == other;
		}
		template<
			typename Integer,
			typename std::enable_if<!IsDerivedFromModulusRing<
				Integer>::value>::type * = nullptr>
		inline auto constexpr operator>(
			Integer const &other) const {
			return *this > build(other);
		}
		template<
			typename OtherDerived,
			typename OtherUnderlying,
			std::size_t OTHER_MODULUS_OUTER>
		inline auto constexpr operator>(ModulusRingBase<
			OtherDerived,
			OtherUnderlying,
			OTHER_MODULUS_OUTER> const &other) const {
			return !(*this <= other);
		}
		template<
			typename Integer,
			typename std::enable_if<!IsDerivedFromModulusRing<
				Integer>::value>::type * = nullptr>
		inline auto constexpr operator>=(
			Integer const &other) const {
			return *this >= build(other);
		}
		template<
			typename OtherDerived,
			typename OtherUnderlying,
			std::size_t OTHER_MODULUS_OUTER>
		inline auto constexpr operator>=(ModulusRingBase<
			OtherDerived,
			OtherUnderlying,
			OTHER_MODULUS_OUTER> const &other) const {
			return *this > other || *this == other;
		}

		// Arithmetic can only be performed between
		// ModulusRingBases with the same moduli, or with raw
		// integers. Arithmetic on raw integers first builds
		// them into this type.
		template<
			typename Integer,
			typename std::enable_if<!IsDerivedFromModulusRing<
				Integer>::value>::type * = nullptr>
		inline auto constexpr operator+(
			Integer const &other) const {
			return *this + build(other);
		}
		template<
			typename OtherDerived,
			typename OtherUnderlying,
			std::size_t OTHER_MODULUS_OUTER>
		inline auto constexpr operator+(ModulusRingBase<
			OtherDerived,
			OtherUnderlying,
			OTHER_MODULUS_OUTER> const &other) const {
			return build(this->value + other.value);
		}
		template<typename Integer>
		inline auto constexpr &operator+=(
			Integer const &other) {
			return *this = *this + other;
		}
		template<
			typename Integer,
			typename std::enable_if<!IsDerivedFromModulusRing<
				Integer>::value>::type * = nullptr>
		inline auto constexpr operator-(
			Integer const &other) const {
			return *this - build(other);
		}
		template<
			typename OtherDerived,
			typename OtherUnderlying,
			std::size_t OTHER_MODULUS_OUTER>
		inline auto constexpr operator-(ModulusRingBase<
			OtherDerived,
			OtherUnderlying,
			OTHER_MODULUS_OUTER> const &other) const {
			// We must explicitly add MODULUS here because the
			// type may be signed.
			return build(
				this->value + this->MODULUS - other.value);
		}
		template<typename Integer>
		inline auto constexpr &operator-=(
			Integer const &other) {
			return *this = *this - other;
		}
		template<
			typename Integer,
			typename std::enable_if<!IsDerivedFromModulusRing<
				Integer>::value>::type * = nullptr>
		inline auto constexpr operator*(
			Integer const &other) const {
			return *this * build(other);
		}
		template<
			typename OtherDerived,
			typename OtherUnderlying,
			std::size_t OTHER_MODULUS_OUTER>
		inline auto constexpr operator*(ModulusRingBase<
			OtherDerived,
			OtherUnderlying,
			OTHER_MODULUS_OUTER> const &other) const {
			return build(this->value * other.value);
		}
		template<typename Integer>
		inline auto constexpr &operator*=(
			Integer const &other) {
			return *this = *this * other;
		}
		// Modulus operates directly on modded operand value.
		template<
			typename Integer,
			typename std::enable_if<!IsDerivedFromModulusRing<
				Integer>::value>::type * = nullptr>
		inline auto constexpr operator%(
			Integer const &other) const {
			return *this % build(other);
		}
		template<
			typename OtherDerived,
			typename OtherUnderlying,
			std::size_t OTHER_MODULUS_OUTER>
		inline auto constexpr operator%(ModulusRingBase<
			OtherDerived,
			OtherUnderlying,
			OTHER_MODULUS_OUTER> const &other) const {
			return build(this->value % other.value);
		}
		template<typename Integer>
		inline auto constexpr &operator%=(
			Integer const &other) {
			return *this = *this % other;
		}

		// Unary operations are mostly shorthands for binary
		// operations.
		inline auto constexpr operator-() const {
			return ModulusRingBaseInterface() - *this;
		}
		inline auto constexpr operator++() {
			return *this += 1;
		}
		inline auto constexpr operator++(int) {
			auto tmp(*this);
			*this += 1;
			return build(tmp);
		}
		inline auto constexpr operator--() {
			return *this -= 1;
		}
		inline auto constexpr operator--(int) {
			auto tmp(*this);
			*this -= 1;
			return build(tmp);
		}

		// The following are algorithmic functions based on the
		// modulus field properties.

		// Versions of C++ before C++17 should use static member
		// functions instead of static inline member variables.
		// static inline std::vector<Derived> 	&factorials() {
		// static std::vector<Derived>
		// factorials; return factorials;
		// }
		// static inline std::vector<Derived>
		// 	&invFactorials() {
		// 	static std::vector<Derived>
		// invFactorials; 	return invFactorials;
		// }
		static inline std::vector<Derived> factorials,
			invFactorials;

		// Computes the factorials modulus a prime, up to and
		// including N, in O(N). This enables the choose
		// functions.
		static inline void precomputeFactorials(
			std::size_t const N) {
			factorials.resize(N + 1);
			invFactorials.resize(N + 1);
			factorials[0] = 1;
			for (std::size_t i{1}; i <= N; i++) {
				factorials[i] = factorials[i - 1] * i;
			}
			invFactorials[N] = build(1) / factorials[N];
			for (std::size_t i{0}; i < N; i++) {
				invFactorials[N - i - 1] =
					invFactorials[N - i] * (N - i);
			}
		}

		// O(ln N) exponentiation. The exponent's value is used.
		template<
			typename Integer,
			typename std::enable_if<!IsDerivedFromModulusRing<
				Integer>::value>::type * = nullptr>
		inline Derived constexpr power(
			Integer const &exponent) const {
			// Double base case to cover 0 but also avoid a single
			// product sometimes.
			if (exponent == 0) {
				return build(1);
			} else if (exponent == 1) {
				return build(*this);
			}
			auto half{this->power(exponent / 2)};
			if (exponent % 2 == 0) {
				return half * half;
			} else {
				return half * half * *this;
			}
		}
		template<
			typename OtherDerived,
			typename OtherUnderlying,
			std::size_t OTHER_MODULUS_OUTER>
		inline Derived constexpr power(
			ModulusRingBase<
				OtherDerived,
				OtherUnderlying,
				OTHER_MODULUS_OUTER> const &exponent) const {
			return this->power(exponent.value);
		}

		// Ease-of-use streaming operators.
		friend inline std::ostream constexpr &operator<<(
			std::ostream &stream,
			Rain::Math::ModulusRingBase<
				Derived,
				Underlying,
				MODULUS_OUTER> const &right) {
			return stream << right.value;
		}
		friend inline std::istream constexpr &operator>>(
			std::istream &stream,
			Rain::Math::
				ModulusRingBase<Derived, Underlying, MODULUS_OUTER>
					&right) {
			stream >> right.value;
			right.value =
				(right.MODULUS + right.value) % right.MODULUS;
			return stream;
		}
	};

	// Any reasonable modulus will suffice, since we do not
	// define multiplicative inverses in a ring.
	template<
		typename Underlying,
		std::size_t MODULUS_OUTER = 0>
	class ModulusRing :
		public ModulusRingBase<
			ModulusRing<Underlying, MODULUS_OUTER>,
			Underlying,
			MODULUS_OUTER> {
		private:
		using TypeThis = ModulusRing<Underlying, MODULUS_OUTER>;
		using TypeSuper =
			ModulusRingBase<TypeThis, Underlying, MODULUS_OUTER>;

		public:
		// Constructors must be inherited with the alias name,
		// not the original name.
		using TypeSuper::TypeSuper;

		// For some reason, we must provide specific
		// constructors for `build`, and they are not inherited.
		template<
			std::size_t MODULUS_INNER = MODULUS_OUTER,
			typename std::enable_if<MODULUS_INNER != 0>::type * =
				nullptr>
		inline constexpr ModulusRing(TypeSuper const &other) :
			TypeSuper(other) {}
		template<
			std::size_t MODULUS_INNER = MODULUS_OUTER,
			typename std::enable_if<MODULUS_INNER == 0>::type * =
				nullptr>
		inline constexpr ModulusRing(
			Underlying const &modulus,
			TypeSuper const &other) :
			TypeSuper(modulus, other) {}

		using TypeSuper::build;

		// `operator=` is always hidden by a dummy one in the
		// derived class:
		// <https://stackoverflow.com/questions/12009865/operator-and-functions-that-are-not-inherited-in-c>.
		template<typename Integer>
		inline TypeThis constexpr operator=(
			Integer const &other) {
			return build(TypeSuper::operator=(other));
		}

		using TypeSuper::factorials;
		using TypeSuper::invFactorials;
	};

	// Must be used with a prime modulus, but this cannot be
	// checked at compile-time. If modulus is not prime, use
	// ModulusRing instead.
	template<
		typename Underlying,
		std::size_t MODULUS_OUTER = 0_zu>
	class ModulusField :
		public ModulusRingBase<
			ModulusField<Underlying, MODULUS_OUTER>,
			Underlying,
			MODULUS_OUTER> {
		private:
		using TypeThis =
			ModulusField<Underlying, MODULUS_OUTER>;
		using TypeSuper =
			ModulusRingBase<TypeThis, Underlying, MODULUS_OUTER>;

		public:
		using TypeSuper::TypeSuper;

		template<
			std::size_t MODULUS_INNER = MODULUS_OUTER,
			typename std::enable_if<MODULUS_INNER != 0>::type * =
				nullptr>
		inline constexpr ModulusField(TypeSuper const &other) :
			TypeSuper(other) {}
		template<
			std::size_t MODULUS_INNER = MODULUS_OUTER,
			typename std::enable_if<MODULUS_INNER == 0>::type * =
				nullptr>
		inline constexpr ModulusField(
			Underlying const &modulus,
			TypeSuper const &other) :
			TypeSuper(modulus, other) {}

		using TypeSuper::build;

		template<typename Integer>
		inline TypeThis constexpr operator=(
			Integer const &other) {
			return build(TypeSuper::operator=(other));
		}

		// Division is only correct in fields, or rings with
		// specific operands.
		template<
			typename Integer,
			typename std::enable_if<
				!std::is_same<TypeThis, Integer>::value>::type * =
				nullptr>
		inline TypeThis constexpr operator/(
			Integer const &other) const {
			return *this / build(other);
		}
		inline TypeThis constexpr operator/(
			TypeThis const &other) const {
			// This is only true if this has a multiplicative
			// inverse, which is always true if the modulus is
			// prime.
			return *this * other.power(this->MODULUS - 2);
		}
		template<typename Integer>
		inline TypeThis constexpr &operator/=(
			Integer const &other) {
			return *this = *this / other;
		}

		using TypeSuper::factorials;
		using TypeSuper::invFactorials;

		// Computes the binomial coefficient (N choose K)
		// modulus a prime, in O(1). Must have called
		// precomputeFactorials for the largest expected value
		// of N first.
		inline TypeThis choose(std::size_t const K) const {
			std::size_t const N{
				static_cast<std::size_t>(this->value)};
			if (K < 0 || K > N) {
				return build(0);
			}
			return factorials[N] * invFactorials[K] *
				invFactorials[N - K];
		}
	};

	// These operators are only called if the left operand is
	// a raw integer.
	template<
		typename Integer,
		typename std::enable_if<!Functional::TypeTrait<
			Functional::TypeDowngrade<ModulusRingBaseInterface>>::
				IsTemplateBaseOf<Integer>::value>::type * = nullptr,
		typename Derived,
		typename Underlying,
		std::size_t MODULUS_OUTER>
	inline auto constexpr operator+(
		Integer const &left,
		ModulusRingBase<
			Derived,
			Underlying,
			MODULUS_OUTER> const &right) {
		return right.build(left) + right;
	}
	template<
		typename Integer,
		typename std::enable_if<!Functional::TypeTrait<
			Functional::TypeDowngrade<ModulusRingBaseInterface>>::
				IsTemplateBaseOf<Integer>::value>::type * = nullptr,
		typename Derived,
		typename Underlying,
		std::size_t MODULUS_OUTER>
	inline auto constexpr operator-(
		Integer const &left,
		ModulusRingBase<
			Derived,
			Underlying,
			MODULUS_OUTER> const &right) {
		return right.build(left) - right;
	}
	template<
		typename Integer,
		typename std::enable_if<!Functional::TypeTrait<
			Functional::TypeDowngrade<ModulusRingBaseInterface>>::
				IsTemplateBaseOf<Integer>::value>::type * = nullptr,
		typename Derived,
		typename Underlying,
		std::size_t MODULUS_OUTER>
	inline auto constexpr operator*(
		Integer const &left,
		ModulusRingBase<
			Derived,
			Underlying,
			MODULUS_OUTER> const &right) {
		return right.build(left) * right;
	}
	template<
		typename Integer,
		typename std::enable_if<!Functional::TypeTrait<
			Functional::TypeDowngrade<ModulusRingBaseInterface>>::
				IsTemplateBaseOf<Integer>::value>::type * = nullptr,
		typename Derived,
		typename Underlying,
		std::size_t MODULUS_OUTER>
	inline auto constexpr operator%(
		Integer const &left,
		ModulusRingBase<
			Derived,
			Underlying,
			MODULUS_OUTER> const &right) {
		return right.build(left) % right;
	}
	template<
		typename Integer,
		typename std::enable_if<!Functional::TypeTrait<
			Functional::TypeDowngrade<ModulusRingBaseInterface>>::
				IsTemplateBaseOf<Integer>::value>::type * = nullptr,
		typename Underlying,
		std::size_t MODULUS_OUTER>
	inline auto constexpr operator/(
		Integer const &left,
		Rain::Math::ModulusField<
			Underlying,
			MODULUS_OUTER> const &right) {
		return right.build(left) / right;
	}
}

// Hash operator for this user-defined type, which hashes
// the inner value (not the modulus). There is no way to
// define hash for only the base class, so we define it for
// all user-facing classes directly:
// <https://stackoverflow.com/questions/21900707/specializing-stdhash-to-derived-classes>.
namespace std {
	template<typename Underlying, std::size_t MODULUS_OUTER>
	struct hash<
		Rain::Math::ModulusRing<Underlying, MODULUS_OUTER>> {
		size_t operator()(Rain::Math::ModulusRing<
			Underlying,
			MODULUS_OUTER> const &value) const {
			return Rain::Random::SplitMixHash<
				decltype(value.value)>{}(value.value);
		}
	};

	template<typename Underlying, std::size_t MODULUS_OUTER>
	struct hash<
		Rain::Math::ModulusField<Underlying, MODULUS_OUTER>> {
		size_t operator()(Rain::Math::ModulusField<
			Underlying,
			MODULUS_OUTER> const &value) const {
			return Rain::Random::SplitMixHash<
				decltype(value.value)>{}(value.value);
		}
	};
}

#if defined(__GNUC__) && !defined(__clang__) && \
	!defined(__MINGW32__)
	// <https://codeforces.com/blog/entry/135127>.
	#include <string>
	#pragma GCC target("arch=core-avx2")
	#pragma GCC optimize("Ofast", "unroll-loops")
#endif

#include <bits/stdc++.h>

using LL = long long;
using LD = long double;
using namespace std;

#define RF(x, from, to) \
	for ( \
		LL x(from), _to(to), _delta{x < _to ? 1LL : -1LL}; \
		x != _to; \
		x += _delta)

template<typename T>
using FW = Rain::Algorithm::FenwickTree<T>;
using MF = Rain::Math::ModulusField<LL, 998244353>;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	MF::precomputeFactorials(300000);

	LL _T;
	cin >> _T;
	while (_T--) {
		LL N;
		cin >> N;
		vector<pair<pair<LL, LL>, LL>> A(N);
		vector<LL> AY(N);
		RF(i, 0, N) {
			cin >> A[i].first.first >> A[i].first.second;
			A[i].second = i;
			AY[i] = A[i].first.second;
		}
		sort(A.begin(), A.end());
		sort(AY.begin(), AY.end());
		unordered_map<LL, LL> AYM;
		RF(i, 0, N) { AYM[AY[i]] = i; }
		FW<LL> FWY1(N), FWY2(N);
		RF(i, 0, N) { FWY2.modify(i, 1); }
		vector<array<LL, 4>> QX(N);
		vector<LL> Z(N);
		RF(i, 0, N) {
			FWY2.modify(AYM[A[i].first.second], -1);
			QX[i][0] = i - FWY1.sum(AYM[A[i].first.second]);
			QX[i][1] =
				N - i - 1 - FWY2.sum(AYM[A[i].first.second]);
			QX[i][2] = FWY1.sum(AYM[A[i].first.second]);
			QX[i][3] = FWY2.sum(AYM[A[i].first.second]);
			FWY1.modify(AYM[A[i].first.second], 1);
			// RF(j, 0, 4) { cout << QX[i][j] << ' '; }
			// cout << '\n';
			Z[A[i].second] =
				(MF{QX[i][0] + QX[i][3]}.choose(QX[i][0]) *
					MF{QX[i][1] + QX[i][2]}.choose(QX[i][1]))
					.value;
		}
		RF(i, 0, N) { cout << Z[i] << ' '; }
		cout << '\n';
	}

	return 0;
}
