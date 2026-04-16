/*
ID: yangchess1
PROG: vans
LANG: C++
*/

#include <bits/stdc++.h>

using LL = long long;
using LD = long double;
using namespace std;

#define RF(x, from, to)                                   \
	for (LL x(from), _to(to), _delta{x < _to ? 1LL : -1LL}; \
			 x != _to;                                          \
			 x += _delta)

namespace Rain::Algorithm {
	// Most significant 1-bit for unsigned integral types of
	// at most long long in size. Undefined result if x = 0.
	template <typename Integer>
	inline std::size_t mostSignificant1BitIdx(
		Integer const &x) {
#ifdef __has_builtin
#if __has_builtin(__builtin_clzll)
		return 8 * sizeof(unsigned long long) -
			__builtin_clzll(x) - 1;
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

	// Least significant 1-bit for unsigned integral types of
	// at most long long in size. Undefined result if x = 0.
	template <typename Integer>
	inline std::size_t leastSignificant1BitIdx(
		Integer const &x) {
#ifdef __has_builtin
#if __has_builtin(__builtin_ctzll)
		return __builtin_ctzll(x);
#endif
#endif
		for (std::size_t bit{0}; bit != 8 * sizeof(Integer);
				 bit++) {
			if (x & (static_cast<Integer>(1) << bit)) {
				return bit;
			}
		}
		return std::numeric_limits<std::size_t>::max();
	}

	// Count of 1-bits in unsigned integral types of at most
	// long long in size.
	template <typename Integer>
	inline std::size_t bitPopcount(Integer const &x) {
#ifdef __has_builtin
#if __has_builtin(__builtin_popcountll)
		return __builtin_popcountll(x);
#endif
#endif
		std::size_t count{0};
		for (std::size_t bit{0}; bit != 8 * sizeof(Integer);
				 bit++) {
			count += !!(x & (static_cast<Integer>(1) << bit));
		}
		return count;
	}
}

#include <exception>
#include <system_error>

namespace Rain::Error {
	// Subclasses std::exception, implements custom what()
	// string to display error category name, code, and error
	// code message.
	//
	// Default template arguments provided for ease of use in
	// catch blocks.
	template <typename Error, typename ErrorCategory>
	class Exception : public std::exception {
		private:
		// A unique ErrorCategory instance.
		static inline ErrorCategory const errorCategory;

		Error const error;
		std::string const explanation;

		public:
		// Construct an exception with just the error code, in
		// the format "CATEGORY, ERROR: MESSAGE".
		Exception(Error const &error = static_cast<Error>(0))
				: error(error),
					explanation(
						std::string(errorCategory.name()) + ", " +
						std::to_string(static_cast<int>(error)) + ": " +
						errorCategory.message(static_cast<int>(error)) +
						"\n") {}

		// Return the error (code).
		Error const &getError() const noexcept {
			return this->error;
		}

		// Return the ErrorCategory for checking equality.
		static ErrorCategory const &
		getErrorCategory() noexcept {
			return Exception<Error, ErrorCategory>::errorCategory;
		}

		// Return the preconstructed explanation string.
		//
		// Because std::exception::what is virtual, catch blocks
		// only have to catch std::exception to use this version
		// of what.
		char const *what() const noexcept {
			return this->explanation.c_str();
		}
	};

	// Default generic error category.
	class GenericErrorCategory : public std::error_category {
		public:
		// Name of this category of errors.
		char const *name() const noexcept { return "Generic"; }

		// Translates Errors from the enum into string messages.
		std::string message(int) const noexcept {
			return "Generic.";
		}
	};
	using GenericException =
		Exception<int, GenericErrorCategory>;
}

#include <functional>
#include <type_traits>

// For an overloaded function f, this wraps it in an
// rvalue-reference lambda so that it may be resolved via
// perfect forwarding.
#define RAIN_FUNCTIONAL_RESOLVE_OVERLOAD(f)          \
	[](auto &&...args) -> decltype(auto) {             \
		return f(std::forward<decltype(args)>(args)...); \
	}

namespace Rain::Functional {
	// SFINAE for const-iterable types (containers). Assumes
	// sizeof(char) and sizeof(int) are not equal.
	template <typename Type>
	struct isConstIterable {
		template <typename TypeInner>
		static char evaluate(
			typename TypeInner::const_iterator *);
		template <typename TypeInner>
		static int evaluate(...);

		public:
		enum {
			value = sizeof(evaluate<Type>(0)) == sizeof(char)
		};
	};

	// Similar to `std::is_base_of`, but for template base
	// types.
	namespace {
		template <
			template <typename...> class Type,
			typename... TypeTemplate>
		std::true_type isBaseOfTemplateImpl(
			Type<TypeTemplate...> const *);
		template <template <typename...> class Type>
		std::false_type isBaseOfTemplateImpl(...);
	}
	template <
		template <typename...> class TypeBase,
		typename TypeDerived>
	using isBaseOfTemplate =
		decltype(isBaseOfTemplateImpl<TypeBase>(
			std::declval<TypeDerived *>()));

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
	!defined(RAIN_PLATFORM_MACOS) &&     \
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

#include <array>
#include <bitset>
#include <iomanip>
#include <iostream>
#include <type_traits>
#include <utility>

namespace Rain::Math {
	template <typename = std::nullptr_t, std::size_t = 0>
	class Tensor;

	template <>
	class Tensor<std::nullptr_t, 0> {
		template <class, std::size_t>
		friend class Tensor;

		public:
		enum Error { NONE, SIZES_MISMATCH };
		class ErrorCategory : public std::error_category {
			public:
			char const *name() const noexcept {
				return "Rain::Math::Tensor";
			}
			std::string message(int error) const noexcept {
				switch (error) {
					case Error::NONE:
						return "None.";
					case Error::SIZES_MISMATCH:
						return "Tensor(s) are not of compatible size "
									 "for operation.";
					default:
						return "Generic.";
				}
			}
		};
		using Exception =
			Rain::Error::Exception<Error, ErrorCategory>;

		class Range {
			public:
			// `stop`: defaults will be replaced with current
			// `stop` during `slice`. `size`: actual underlying
			// size.
			std::size_t start{
				std::numeric_limits<std::size_t>::max()},
				stop{std::numeric_limits<std::size_t>::max()},
				step{std::numeric_limits<std::size_t>::max()};
		};

		// Standard policy for Tensor products. This forms a
		// ring.
		template <typename Left, typename Right>
		class PlusMultProductPolicy {
			public:
			static constexpr inline auto contract(
				Left const &left,
				Right const &right) {
				return left * right;
			}

			using Result = decltype(contract(
				std::declval<Left>(),
				std::declval<Right>()));
			static inline Result const DEFAULT_RESULT{0};

			static constexpr inline auto aggregate(
				Result const &left,
				Result const &right) {
				return left + right;
			}
		};

		// Policy for Tensor products where + is replaced with
		// min and * is replaced with +. This form a semi-ring.
		template <typename Left, typename Right>
		class MinPlusProductPolicy {
			public:
			static constexpr inline auto contract(
				Left const &left,
				Right const &right) {
				return left + right;
			}

			using Result = decltype(contract(
				std::declval<Left>(),
				std::declval<Right>()));
			static inline Result const DEFAULT_RESULT{
				std::numeric_limits<Result>::max()};

			static constexpr inline auto aggregate(
				Result const &left,
				Result const &right) {
				return std::min(left, right);
			}
		};

		private:
		// SFINAE to check if a type is a tensor.
		template <typename Value, std::size_t ORDER>
		static std::true_type isDerivedFromTensorImpl(
			Tensor<Value, ORDER> *);
		template <typename = std::nullptr_t, std::size_t = 0>
		static std::false_type isDerivedFromTensorImpl(...);
		template <typename TypeDerived>
		using isDerivedFromTensor =
			decltype(isDerivedFromTensorImpl(
				std::declval<typename std::remove_const<
					TypeDerived>::type *>()));

		// SFINAE to check an arbitrary type with a tensor of a
		// given order.
		template <
			std::size_t TARGET_ORDER,
			template <std::size_t, std::size_t> class Comparator,
			typename Value,
			std::size_t ORDER,
			typename std::enable_if<
				Comparator<TARGET_ORDER, ORDER>::value>::type * =
				nullptr>
		static std::true_type isTensorOfComparativeOrderImpl(
			Tensor<Value, ORDER> *);
		template <
			std::size_t = 0,
			template <std::size_t, std::size_t> class =
				Functional::isEqualTo,
			typename = std::nullptr_t,
			std::size_t = 0,
			typename = std::nullptr_t>
		static std::false_type isTensorOfComparativeOrderImpl(
			...);
		template <
			std::size_t TARGET_ORDER,
			template <std::size_t, std::size_t> class Comparator,
			typename TypeDerived>
		using isTensorOfComparativeOrder =
			decltype(isTensorOfComparativeOrderImpl<
							 TARGET_ORDER,
							 Comparator>(
				std::declval<typename std::remove_const<
					TypeDerived>::type *>()));

		// Perform an operation over all indices, or over the
		// first few indices.
		//
		// Each function is template-overloaded to handle both
		// `const &` and `&` versions of `result. An additional
		// function is provided to handle `&&` versions by
		// degrading the rvalue reference into an lvalue.
		template <
			std::size_t REMAINING_ORDER,
			typename ResultType,
			typename std::enable_if<isTensorOfComparativeOrder<
				REMAINING_ORDER,
				Functional::isLessThan,
				ResultType>::value>::type * = nullptr>
		static inline void applyOver(
			auto &&callable,
			ResultType &result,
			auto &&...others) {
			for (std::size_t i{0};
					 i < result.SIZES[result.TRANSPOSE[0]];
					 i++) {
				Tensor<>::applyOver<REMAINING_ORDER>(
					std::forward<decltype(callable)>(callable),
					std::forward<decltype(result[i])>(result[i]),
					std::forward<decltype(others[i])>(others[i])...);
			}
		}
		// An explicit overload for `applyOver` which does
		// nothing (i.e. base case), which may be called from
		// `product` if one matrix is completely contracted.
		template <
			std::size_t REMAINING_ORDER,
			typename ResultType,
			typename std::enable_if<isTensorOfComparativeOrder<
				REMAINING_ORDER,
				Functional::isEqualTo,
				ResultType>::value>::type * = nullptr>
		static inline void applyOver(
			auto &&callable,
			ResultType &result,
			auto &&...others) {
			callable(
				result, std::forward<decltype(others)>(others)...);
		}
		// `applyOver` called without a Tensor will simply call
		// the function.
		template <
			std::size_t,
			typename ResultType,
			typename std::enable_if<!isDerivedFromTensor<
				ResultType>::value>::type * = nullptr>
		static inline void applyOver(
			auto &&callable,
			ResultType &result,
			auto &&...others) {
			callable(
				result, std::forward<decltype(others)>(others)...);
		}
		// R-value reference versions of `applyOver`. We degrade
		// `result` into a l-value reference.
		template <
			std::size_t REMAINING_ORDER,
			typename ResultType>
		static inline void applyOver(
			auto &&callable,
			ResultType &&result,
			auto &&...others) {
			Tensor<>::applyOver<REMAINING_ORDER>(
				std::forward<decltype(callable)>(callable),
				result,
				std::forward<decltype(others)>(others)...);
		}

		// Compute the total number of entries in a tensor.
		template <std::size_t TENSOR_ORDER>
		static constexpr inline std::size_t calcSizesProduct(
			std::array<std::size_t, TENSOR_ORDER> const &sizes) {
			std::size_t result{1};
			for (auto const &i : sizes) {
				result *= i;
			}
			return result;
		}
	};

	// Flexible order tensor implementation. Most operations
	// give views of the same underlying data; this is not the
	// case for the binary arithmetic operations.
	template <typename Value, std::size_t ORDER>
	class Tensor {
		// Allow access of any other Tensor for a proper product
		// implementation.
		template <typename, std::size_t>
		friend class Tensor;

		// Allow access from stream operators. It is fine that
		// we only friend one template here, since the template
		// gets expanded into all the versions.
		//
		// Note that the operator is located within the
		// Rain::Math namespace, and this is fine and preferred.
		//
		// Note that we cannot put a default argument for a
		// third argument, simply because this is not a real
		// template definition, but a template declaration.
		template <
			typename TensorValue,
			std::size_t TENSOR_ORDER,
			typename std::enable_if<(TENSOR_ORDER >= 1)>::type *>
		friend std::ostream &operator<<(
			std::ostream &,
			Tensor<TensorValue, TENSOR_ORDER> const &);

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
		// Store a permutation of dimensions for easy transpose
		// & product.
		std::array<std::size_t, ORDER> TRANSPOSE;

		static constexpr inline auto makeRangesDefault(
			std::array<std::size_t, ORDER> const &sizes) {
			std::array<Range, ORDER> ranges;
			for (std::size_t i{0}; i < ORDER; i++) {
				ranges[i] = {0, sizes[i], 1};
			}
			return ranges;
		}
		static constexpr inline auto calcSizes(
			std::array<Range, ORDER> const &ranges) {
			std::array<std::size_t, ORDER> sizes;
			for (std::size_t i{0}; i < ORDER; i++) {
				sizes[i] = (ranges[i].stop - ranges[i].start +
										ranges[i].step - 1) /
					ranges[i].step;
			}
			return sizes;
		}
		static constexpr inline auto makeDimPermDefault() {
			std::array<std::size_t, ORDER> dimPerm;
			for (std::size_t i{0}; i < ORDER; i++) {
				dimPerm[i] = i;
			}
			return dimPerm;
		}
		static constexpr inline auto makeOnesSizes() {
			std::array<std::size_t, ORDER> sizes;
			sizes.fill(1);
			return sizes;
		}

		// DEBUG helpers.
		//
		// Recall that SFINAE requires the expression within
		// `enable_if` to be dependent on a parameter in the
		// current template, which is why we proxy TENSOR_ORDER
		// as the same as ORDER, so that we can use ORDER
		// (through TENSOR_ORDER) in that conditional.
		// Additionally, if the conditional always evaluates
		// true or false, the compiler may refuse to compile.
		template <typename OtherValue>
		inline void debugAssertEqualSizes(
			Tensor<OtherValue, ORDER> const &other) const {
			if (Platform::isDebug()) {
				auto thisSize{this->size()},
					otherSize{other.size()};
				for (std::size_t i{0}; i < ORDER; i++) {
					if (thisSize[i] != otherSize[i]) {
						throw Exception(Error::SIZES_MISMATCH);
					}
				}
			}
		}
		template <
			std::size_t TENSOR_ORDER = ORDER,
			typename std::enable_if<(TENSOR_ORDER == 2)>::type * =
				nullptr>
		inline void debugAssertSquare() const {
			if (Platform::isDebug()) {
				if (this->SIZES[0] != this->SIZES[1]) {
					throw Exception(Error::SIZES_MISMATCH);
				}
			}
		}

		// Additional helpers.

		// Stream out to a std::ostream where each line is
		// padded with additional spaces.
		template <
			std::size_t TENSOR_ORDER = ORDER,
			typename std::enable_if<(TENSOR_ORDER == 1)>::type * =
				nullptr>
		std::ostream &streamOutPadded(
			std::ostream &stream,
			std::size_t) const {
			if (this->SIZES[0] == 0) {
				return stream << "[]";
			}
			stream << '[' << std::setw(4) << (*this)[0];
			for (std::size_t i{1}; i < this->SIZES[0]; i++) {
				stream << ' ' << std::setw(4) << (*this)[i];
			}
			return stream << ']';
		}
		template <
			std::size_t TENSOR_ORDER = ORDER,
			typename std::enable_if<(TENSOR_ORDER >= 2)>::type * =
				nullptr>
		std::ostream &streamOutPadded(
			std::ostream &stream,
			std::size_t padding) const {
			if (this->SIZES[this->TRANSPOSE[0]] == 0) {
				// Attempting to stream a higher order tensor with a
				// 0 dimension will erase traces of the following
				// dimensions.
				return stream << "[]";
			}
			stream << '[';
			(*this)[0].streamOutPadded(stream, padding + 1);
			for (std::size_t i{1};
					 i < this->SIZES[this->TRANSPOSE[0]];
					 i++) {
				stream << "\n" << std::string(padding + 1, ' ');
				(*this)[i].streamOutPadded(stream, padding + 1);
			}
			return stream << ']';
		}

		// Internal constructor for manually specifying
		// underlying.
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
		// Identity, implemented only for matrices.
		template <
			std::size_t TENSOR_ORDER = ORDER,
			typename std::enable_if<(TENSOR_ORDER == 2)>::type * =
				nullptr>
		static constexpr inline auto identity(
			std::size_t size) {
			Tensor<Value, 2> result({size, size});
			for (std::size_t i{0}; i < size; i++) {
				result[i][i] = 1;
			}
			return result;
		}

		Tensor(
			std::array<std::size_t, ORDER> const &sizes,
			auto &&...values)
				: VALUES{
						new Value[Tensor<>::calcSizesProduct(sizes)]{
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

		// The default constructor generates a Tensor with only
		// a single element.
		Tensor() : Tensor(TypeThis::makeOnesSizes()) {}

		// Copy assignment copies a reference, and not the
		// underlying data.
		//
		// We offer a template but also a specialization to the
		// current class to help compilers recognize the copy
		// assignment operator.
		template <typename OtherValue>
		auto &operator=(
			Tensor<OtherValue, ORDER> const &other) {
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

		// Convenience operator for scalar tensors.
		template <
			std::size_t TENSOR_ORDER = ORDER,
			typename std::enable_if<(TENSOR_ORDER == 0)>::type * =
				nullptr>
		inline auto &operator=(Value const &other) {
			this->VALUES[this->OFFSET] = other;
			return *this;
		}

		// Equality operator checks sizes and every index.
		template <typename OtherValue>
		bool operator==(
			Tensor<OtherValue, ORDER> const &other) const {
			auto thisSize{this->size()}, otherSize{other.size()};
			for (std::size_t i{0}; i < ORDER; i++) {
				if (thisSize[i] != otherSize[i]) {
					return false;
				}
			}

			bool isEqual{true};
			Tensor<>::applyOver<0>(
				[&isEqual](
					Value const &thisValue,
					OtherValue const &otherValue) {
					isEqual &= thisValue == otherValue;
				},
				*this,
				other);
			return isEqual;
		}

		// A 0-order Tensor converts to/from automatically a
		// scalar. This is necessary for degenerate cases in
		// `product`.
		//
		// Two versions necessary depending on if *this is const
		// or not.
		//
		// It is always constructed without specifying SIZES,
		// and so its underlying size is 1 and must contain a
		// scalar.
		template <
			std::size_t TENSOR_ORDER = ORDER,
			typename std::enable_if<(TENSOR_ORDER == 0)>::type * =
				nullptr>
		inline operator Value const &() const {
			return this->VALUES[this->OFFSET];
		}
		template <
			std::size_t TENSOR_ORDER = ORDER,
			typename std::enable_if<(TENSOR_ORDER == 0)>::type * =
				nullptr>
		inline operator Value &() {
			return const_cast<Value &>(
				this->operator Value const &());
		}

		// Public shorthand for `applyOver`.
		template <std::size_t REMAINING_ORDER>
		inline void applyOver(
			auto &&callable,
			auto &&...others) {
			Tensor<>::applyOver<REMAINING_ORDER>(
				std::forward<decltype(callable)>(callable),
				*this,
				std::forward<decltype(others)>(others)...);
		}

		// Indexing is the main operation of a tensor, and most
		// other operations build on it.
		//
		// Checks in-range iff DEBUG.
		//
		// We provide two versions of the indexing operator, to
		// preserve const-ness.
		//
		// The base level indexing operator MUST return a Value
		// reference, and NOT a scalar tensor. While scalar
		// tensors are valid and will work, the conversion
		// during `applyOver` dominates the runtime  and incurs
		// a heavy performance penalty.
		template <
			std::size_t TENSOR_ORDER = ORDER,
			typename std::enable_if<(TENSOR_ORDER == 1)>::type * =
				nullptr>
		inline Value const &operator[](std::size_t idx) const {
			if (Platform::isDebug()) {
				if (idx >= this->SIZES[this->TRANSPOSE[0]]) {
					throw Exception(Error::SIZES_MISMATCH);
				}
			}
			return this->VALUES
				[this->OFFSET + this->RANGES[0].start +
				 this->RANGES[0].step * idx];
		}
		template <
			std::size_t TENSOR_ORDER = ORDER,
			typename std::enable_if<(TENSOR_ORDER == 1)>::type * =
				nullptr>
		inline Value &operator[](std::size_t idx) {
			return const_cast<Value &>(
				const_cast<TypeThis const *>(this)->operator[](
					idx));
		}
		template <
			std::size_t TENSOR_ORDER = ORDER,
			typename std::enable_if<(TENSOR_ORDER > 1)>::type * =
				nullptr>
		Tensor<Value, ORDER - 1> const operator[](
			std::size_t idx) const {
			if (Platform::isDebug()) {
				if (idx >= this->SIZES[this->TRANSPOSE[0]]) {
					throw Exception(Error::SIZES_MISMATCH);
				}
			}

			// Must take into account transpose.
			std::array<std::size_t, ORDER - 1> newDimPerm;
			for (std::size_t i{1}; i < ORDER; i++) {
				newDimPerm[i - 1] = this->TRANSPOSE[i] +
					(this->TRANSPOSE[i] > this->TRANSPOSE[0] ? -1
																									 : 0);
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
					rangeShift *=
						this->SIZES_UNDERLYING[this->TRANSPOSE[i]];
					ranges[newDimPerm[i - 1]] =
						this->RANGES[this->TRANSPOSE[i]];
				} else {
					// `stop` and `start` are calculated from the new
					// `step`.
					ranges[newDimPerm[i - 1]].step =
						this->RANGES[this->TRANSPOSE[i]].step *
						this->SIZES_UNDERLYING[this->TRANSPOSE[0]];
					ranges[newDimPerm[i - 1]].start =
						this->RANGES[this->TRANSPOSE[i]].start *
						this->SIZES_UNDERLYING[this->TRANSPOSE[0]];
					ranges[newDimPerm[i - 1]].stop =
						ranges[newDimPerm[i - 1]].start +
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
			std::size_t TENSOR_ORDER = ORDER,
			typename std::enable_if<(TENSOR_ORDER > 1)>::type * =
				nullptr>
		inline Tensor<Value, ORDER - 1> operator[](
			std::size_t idx) {
			return const_cast<Tensor<Value, ORDER - 1> &&>(
				const_cast<TypeThis const *>(this)->operator[](
					idx));
		}

		// Binary operators. Checks dimension equality iff
		// DEBUG.
		//
		// Binary assignment operators perform operations
		// in-place. Non-assignment versions are constant and
		// will perform allocations of the appropriate size.
		template <typename OtherValue>
		auto operator+(
			Tensor<OtherValue, ORDER> const &other) const {
			using ResultValue =
				decltype(std::declval<Value>() + std::declval<OtherValue>());
			this->debugAssertEqualSizes(other);
			Tensor<ResultValue, ORDER> result(this->size());
			Tensor<>::applyOver<0>(
				[](
					ResultValue &result,
					Value const &that,
					OtherValue const &other) {
					result = that + other;
				},
				result,
				*this,
				other);
			return result;
		}
		template <typename OtherValue>
		inline auto &operator+=(
			Tensor<OtherValue, ORDER> const &other) {
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
		inline auto &operator+=(OtherValue const &other) {
			Tensor<>::applyOver<0>(
				[&other](Value &that) { that += other; }, *this);
			return *this;
		}
		template <typename OtherValue>
		auto operator-(
			Tensor<OtherValue, ORDER> const &other) const {
			using ResultValue =
				decltype(std::declval<Value>() - std::declval<OtherValue>());
			this->debugAssertEqualSizes(other);
			Tensor<ResultValue, ORDER> result(this->size());
			Tensor<>::applyOver<0>(
				[](
					ResultValue &result,
					Value const &that,
					OtherValue const &other) {
					result = that - other;
				},
				result,
				*this,
				other);
			return result;
		}
		template <typename OtherValue>
		inline auto &operator-=(
			Tensor<OtherValue, ORDER> const &other) {
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
		inline auto &operator-=(OtherValue const &other) {
			Tensor<>::applyOver<0>(
				[&other](Value &that) { that -= other; }, *this);
			return *this;
		}
		// Binary operators *, *= are defined with another
		// Tensor operand iff they are of compatible size. This
		// is a shorthand for `product`.
		template <typename OtherValue>
		inline auto operator*(
			Tensor<OtherValue, ORDER> const &other) const {
			// No need to check sizes here, since `product` will
			// do it.
			return this->product<1>(other, {ORDER - 1}, {0});
		}
		template <typename OtherValue>
		inline auto &operator*=(
			Tensor<OtherValue, ORDER> const &other) {
			// Since allocation will happen anyway, we don't care
			// about doing it in-place.
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
		inline auto &operator*=(OtherValue const &other) {
			Tensor<>::applyOver<0>(
				[&other](Value &that) { that *= other; }, *this);
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
		inline auto &operator/=(OtherValue const &other) {
			Tensor<>::applyOver<0>(
				[&other](Value &that) { that /= other; }, *this);
			return *this;
		}

		// Memory functions.

		// A tensor is "clean" if its elements are contiguous,
		// in order of dimension (i.e. default
		// start/stop/step/transpose). Usually, transposing or
		// taking a view via slicing will give a "dirty" tensor.
		// However, some views remain clean.
		bool isClean() const {
			std::array<std::size_t, ORDER> transposeSorted{
				this->TRANSPOSE};
			std::sort(
				transposeSorted.begin(), transposeSorted.end());
			if (transposeSorted != this->TRANSPOSE) {
				return false;
			}
			for (std::size_t i{0}; i < ORDER; i++) {
				if (
					this->RANGES[i].start != 0 ||
					this->RANGES[i].stop != this->SIZES[i] ||
					this->RANGES[i].step != 1) {
					return false;
				}
			}
			return true;
		}
		inline auto asClean() const {
			Tensor<Value, ORDER> result{this->size()};
			Tensor<>::applyOver<0>(
				[](Value &resultValue, Value const &thisValue) {
					resultValue = thisValue;
				},
				result,
				*this);
			return result;
		}
		inline auto clean() { return *this = this->asClean(); }
		// Alias for `asClean`.
		inline auto copy() const { return this->asClean(); }

		// Property functions.

		// Transposition does not change `SIZES`, and so some
		// functions should use `SIZES`, while others should use
		// `size()`.
		inline auto size() const {
			std::array<std::size_t, ORDER> sizesTransposed;
			for (std::size_t i{0}; i < ORDER; i++) {
				sizesTransposed[i] =
					this->SIZES[this->TRANSPOSE[i]];
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
		// Fills every value with the quality operator.
		void fill(Value const &other) {
			Tensor<>::applyOver<0>(
				[&other](Value &that) { that = other; }, *this);
		}
		// Public access to underlying. Can test for views.
		// `const` version is a little fake.
		inline std::shared_ptr<Value const[]> data() const {
			return this->VALUES;
		}
		inline std::shared_ptr<Value[]> data() {
			return this->VALUES;
		}

		// View functions.

		// Slicing returns a view.
		TypeThis asSlice(
			std::array<Range, ORDER> const &ranges) const {
			std::array<Range, ORDER> mergedRanges;
			for (std::size_t i{0}; i < ORDER; i++) {
				mergedRanges[i].start = ranges[i].start ==
						std::numeric_limits<std::size_t>::max()
					? this->RANGES[i].start
					: this->RANGES[i].start +
						this->RANGES[i].step * ranges[i].start;
				mergedRanges[i].stop = ranges[i].stop ==
						std::numeric_limits<std::size_t>::max()
					? this->RANGES[i].stop
					: this->RANGES[i].start +
						this->RANGES[i].step * ranges[i].stop;
				mergedRanges[i].step = ranges[i].step ==
						std::numeric_limits<std::size_t>::max()
					? this->RANGES[i].step
					: this->RANGES[i].step * ranges[i].step;
				// We do not check that start < stop here, since
				// zero-dimensions are technically valid.
			}
			return {
				this->VALUES,
				mergedRanges,
				this->SIZES_UNDERLYING,
				this->OFFSET,
				this->TRANSPOSE};
		}
		inline TypeThis slice(
			std::array<Range, ORDER> const &ranges) {
			return *this = this->asSlice(ranges);
		}
		// Must be a valid permutation of [0, ORDER). Checked
		// iff DEBUG.
		TypeThis asTranspose(
			std::array<std::size_t, ORDER> const &dimPerm) const {
			if (Platform::isDebug()) {
				std::array<std::size_t, ORDER> dimPermSorted{
					this->TRANSPOSE};
				std::sort(
					dimPermSorted.begin(), dimPermSorted.end());
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
		inline TypeThis transpose(
			std::array<std::size_t, ORDER> const &dimPerm) {
			return *this = this->asTranspose(dimPerm);
		}
		// Reshape preserves the transpose. Use `0` to attempt
		// to infer the dimension from the total number of
		// entries. Do not use more than one `0`. Will throw if
		// sizes are incompatible.
		//
		// If Tensor has default start/stop/step and default
		// transpose (i.e. is "clean"), reshape will return a
		// view. Otherwise, reshape returns a copy.
		template <std::size_t NEW_ORDER>
		auto asReshape(
			std::array<std::size_t, NEW_ORDER> const &sizes)
			const {
			std::size_t toInfer{NEW_ORDER}, newTotalSize{1},
				totalSize{Tensor<>::calcSizesProduct(this->SIZES)};
			for (std::size_t i{0}; i < NEW_ORDER; i++) {
				if (sizes[i] == 0) {
					if (toInfer != NEW_ORDER) {
						throw Exception(Error::SIZES_MISMATCH);
					}
					toInfer = i;
					continue;
				}
				newTotalSize *= sizes[i];
			}
			std::array<std::size_t, NEW_ORDER> newSizes{sizes};
			if (toInfer != NEW_ORDER) {
				if (totalSize % newTotalSize != 0) {
					throw Exception(Error::SIZES_MISMATCH);
				}
				newSizes[toInfer] = totalSize / newTotalSize;
			} else {
				if (totalSize != newTotalSize) {
					throw Exception(Error::SIZES_MISMATCH);
				}
			}

			if (this->isClean()) {
				std::array<Range, NEW_ORDER> newRanges;
				for (std::size_t i{0}; i < NEW_ORDER; i++) {
					newRanges[i] = {0, newSizes[i], 1};
				}
				std::array<std::size_t, NEW_ORDER> newTranspose;
				for (std::size_t i{0}; i < NEW_ORDER; i++) {
					newTranspose[i] = i;
				}
				return Tensor<Value, NEW_ORDER>{
					this->VALUES,
					newRanges,
					newSizes,
					this->OFFSET,
					newTranspose};
			} else {
				Tensor<Value, NEW_ORDER> result{newSizes};
				std::size_t idx{0};
				Tensor<>::applyOver<0>(
					[&idx, &result](Value const &thisValue) {
						result.VALUES[idx++] = thisValue;
					},
					*this);
				return result;
			}
		}
		// No `reshape` exists for different orders since they
		// are different types.
		inline auto reshape(
			std::array<std::size_t, ORDER> const &sizes) {
			return *this = this->asReshape(sizes);
		}
		// Swaps two top-level indices, considering
		// transposition. Not a transpose.
		inline void swap(
			std::array<std::size_t, 2> const &idx) {
			Tensor<>::applyOver<0>(
				[](Value &firstValue, Value &secondValue) {
					std::swap(firstValue, secondValue);
				},
				(*this)[idx[0]],
				(*this)[idx[1]]);
		}

		// Product functions.

		// Tensor product is defined with a list of pairs of
		// indices to contract.
		//
		// Type of result tensor is the same as the type of
		// Value * OtherValue, without consideration for the
		// contraction + operation.
		//
		// Contraction (+) should be presumed to be commutative.
		// Expansion (*) need not be. Result values are first
		// default-constructed, and should be assumed to be
		// identity w.r.t. contraction.
		//
		// Checks that contraction dimensions are identical iff
		// DEBUG.
		template <
			std::size_t CONTRACT_ORDER,
			template <typename, typename> typename Policy =
				Tensor<>::PlusMultProductPolicy,
			typename OtherValue,
			std::size_t OTHER_ORDER,
			typename ResultValue =
				typename Policy<Value, OtherValue>::Result,
			std::size_t RESULT_ORDER = ORDER + OTHER_ORDER -
				CONTRACT_ORDER * 2>
		auto product(
			Tensor<OtherValue, OTHER_ORDER> const &other,
			std::array<std::size_t, CONTRACT_ORDER> const
				&thisContractDims,
			std::array<std::size_t, CONTRACT_ORDER> const
				&otherContractDims) const {
			if (Platform::isDebug()) {
				for (std::size_t i{0}; i < CONTRACT_ORDER; i++) {
					if (
						this->SIZES
							[this->TRANSPOSE[thisContractDims[i]]] !=
						other.SIZES
							[other.TRANSPOSE[otherContractDims[i]]]) {
						throw Exception(Error::SIZES_MISMATCH);
					}
				}
			}

			// Transpose all contracted dimensions to the end in
			// *this, and to the beginning in other.
			//
			// This transposition order helps with cache-locality
			// and vectorization:
			// <https://codeforces.com/blog/entry/129292?locale=en>.
			//
			// Using a custom mod class via the product policy may
			// also help performance.
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
			for (std::size_t i{0}, j{CONTRACT_ORDER};
					 i < OTHER_ORDER;
					 i++) {
				if (isOtherContracted[i]) {
					continue;
				}
				otherDimPerm[j++] = i;
			}
			for (std::size_t i{CONTRACT_ORDER}; i > 0; i--) {
				thisDimPerm[ORDER - i] =
					thisContractDims[CONTRACT_ORDER - i];
			}
			for (std::size_t i{0}; i < CONTRACT_ORDER; i++) {
				otherDimPerm[i] = otherContractDims[i];
			}
			auto thisTransposed{this->asTranspose(thisDimPerm)};
			auto otherTransposed{other.asTranspose(otherDimPerm)};

			std::array<std::size_t, RESULT_ORDER> resultSize;
			auto thisSize{thisTransposed.size()};
			auto otherSize{otherTransposed.size()};
			for (std::size_t i{0}; i < ORDER - CONTRACT_ORDER;
					 i++) {
				resultSize[i] = thisSize[i];
			}
			for (std::size_t i{0};
					 i < OTHER_ORDER - CONTRACT_ORDER;
					 i++) {
				resultSize[ORDER - CONTRACT_ORDER + i] =
					otherSize[i + CONTRACT_ORDER];
			}

			// Iterate over all non-contracted dimensions, and
			// compute contraction (aggregate) of inner product
			// over all remaining dimensions.
			Tensor<ResultValue, RESULT_ORDER> result(resultSize);
			result.fill(
				Policy<Value, OtherValue>::DEFAULT_RESULT);
			Tensor<>::applyOver<OTHER_ORDER - CONTRACT_ORDER>(
				[&otherTransposed](
					// Based on how much `applyOver` unravels, we
					// either end up with a base Value or a higher
					// order Tensor. We need to be able to handle both
					// here.
					typename std::conditional<
						OTHER_ORDER - CONTRACT_ORDER == 0,
						ResultValue,
						Tensor<
							ResultValue,
							OTHER_ORDER - CONTRACT_ORDER>>::type
						&resultOuter,
					typename std::conditional<
						CONTRACT_ORDER == 0,
						Value,
						Tensor<Value, CONTRACT_ORDER>>::type const
						&thisInner) {
					Tensor<>::applyOver<0>(
						[&resultOuter](
							Value const &thisValue,
							typename std::conditional<
								OTHER_ORDER - CONTRACT_ORDER == 0,
								Value,
								Tensor<
									OtherValue,
									OTHER_ORDER - CONTRACT_ORDER>>::type const
								&otherInner) {
							Tensor<>::applyOver<0>(
								[&thisValue](
									ResultValue &resultInner,
									OtherValue const &otherValue) {
									resultInner =
										Policy<Value, OtherValue>::aggregate(
											resultInner,
											Policy<Value, OtherValue>::contract(
												thisValue, otherValue));
								},
								resultOuter,
								otherInner);
						},
						thisInner,
						otherTransposed);
				},
				// For some reason, our implementation of
				// `applyOver` only allows non-const parameters in
				// the first position.
				result,
				thisTransposed);
			return result;
		}
		// Inner and outer product are defined iff ORDER == 1
		// (vectors).
		template <
			typename OtherValue,
			std::size_t TENSOR_ORDER = ORDER,
			typename std::enable_if<(TENSOR_ORDER == 1)>::type * =
				nullptr>
		inline auto productInner(
			Tensor<OtherValue, 1> const &other) const {
			return this->product<1>(other, {0}, {0});
		}
		template <
			typename OtherValue,
			std::size_t TENSOR_ORDER = ORDER,
			typename std::enable_if<(TENSOR_ORDER == 1)>::type * =
				nullptr>
		inline auto productOuter(
			Tensor<OtherValue, 1> const &other) const {
			return this->product<0>(other, {}, {});
		}
		// Square matrices also allow for log power. If not
		// square, `*` will throw iff DEBUG.
		//
		// If the goal is to multiply with a Vector later, it is
		// more efficient (by a constant factor) to manually
		// compute the power product each step along the way.
		// This is because each `1` bit will cause a vector mult
		// as opposed to a matrix mult.
		template <
			std::size_t TENSOR_ORDER = ORDER,
			typename std::enable_if<(TENSOR_ORDER == 2)>::type * =
				nullptr>
		auto power(std::size_t exponent) const {
			if (exponent == 0) {
				this->debugAssertSquare();
				return TypeThis::identity(
					this->SIZES[this->TRANSPOSE[0]]);
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
		// Helper function for various recursive algorithms
		// which depend on D&C. Extends the matrix with 1s on
		// the diagonal and 0s everywhere else.
		//
		// May not allocate if this is already a power of 2.
		template <
			std::size_t TENSOR_ORDER = ORDER,
			typename std::enable_if<(TENSOR_ORDER == 2)>::type * =
				nullptr>
		auto asNearestSquarePowerOf2(
			std::size_t atLeast = 0) const {
			auto size{this->size()};
			auto mSig{Algorithm::mostSignificant1BitIdx(
				std::max({size[0], size[1], atLeast}))};
			if (
				(1_zu << mSig) == size[0] &&
				(1_zu << mSig) == size[1]) {
				return *this;
			}
			auto resultSize{1_zu << (mSig + 1)};
			Tensor<Value, 2> result{{resultSize, resultSize}};
			// Pass `result` second so that we iterate over
			// indices of `*this`.
			Tensor<>::applyOver<0>(
				[](Value &resultValue, Value const &thisValue) {
					resultValue = thisValue;
				},
				result.asSlice({{{0, size[0]}, {0, size[1]}}}),
				*this);
			return result;
		}
		// Strassen's exists for higher orders, but we do not
		// provide it here. Current Strassen's pads at the
		// beginning, so only use for large matrices where the
		// n^0.19 matters.
		//
		// Strassen's does not work on semi-rings (such as
		// min-plus), and thus does not admit a product policy
		// in this form.
		//
		// Under and including size (1_zu << BASE_SIZE_POWER),
		// Strassen will switch to use standard computation
		// instead.
		template <
			std::size_t BASE_SIZE_POWER = 5,
			typename OtherValue,
			std::size_t TENSOR_ORDER = ORDER,
			typename std::enable_if<(TENSOR_ORDER == 2)>::type * =
				nullptr,
			typename ResultValue =
				decltype(std::declval<Value>() * std::declval<OtherValue>())>
		auto productStrassen(
			Tensor<OtherValue, 2> const &other) const {
			auto thisSize{this->size()}, otherSize{other.size()};
			if (Platform::isDebug()) {
				if (thisSize[1] != otherSize[0]) {
					throw Exception(Error::SIZES_MISMATCH);
				}
			}
			if (
				std::max(
					{thisSize[0], thisSize[1], otherSize[1]}) <=
				(1_zu << BASE_SIZE_POWER)) {
				return *this * other;
			}
			auto a{this->asNearestSquarePowerOf2(
				std::max(otherSize[0], otherSize[1]))},
				b{other.asNearestSquarePowerOf2(
					std::max(thisSize[0], thisSize[1]))};
			auto halfSize{a.SIZES[0] / 2};
			auto a11{a.asSlice({{{0, halfSize}, {0, halfSize}}})},
				a12{a.asSlice(
					{{{0, halfSize}, {halfSize, halfSize * 2}}})},
				a21{a.asSlice(
					{{{halfSize, halfSize * 2}, {0, halfSize}}})},
				a22{a.asSlice(
					{{{halfSize, halfSize * 2},
						{halfSize, halfSize * 2}}})},
				b11{b.asSlice({{{0, halfSize}, {0, halfSize}}})},
				b12{b.asSlice(
					{{{0, halfSize}, {halfSize, halfSize * 2}}})},
				b21{b.asSlice(
					{{{halfSize, halfSize * 2}, {0, halfSize}}})},
				b22{b.asSlice(
					{{{halfSize, halfSize * 2},
						{halfSize, halfSize * 2}}})};
			std::array<Tensor<ResultValue, 2>, 7> m{
				{{(a11 + a22)
						.template productStrassen<BASE_SIZE_POWER>(
							b11 + b22)},
				 {(a21 + a22)
						.template productStrassen<BASE_SIZE_POWER>(
							b11)},
				 {a11.template productStrassen<BASE_SIZE_POWER>(
					 b12 - b22)},
				 {a22.template productStrassen<BASE_SIZE_POWER>(
					 b21 - b11)},
				 {(a11 + a12)
						.template productStrassen<BASE_SIZE_POWER>(
							b22)},
				 {(a21 - a11)
						.template productStrassen<BASE_SIZE_POWER>(
							b11 + b12)},
				 {(a12 - a22)
						.template productStrassen<BASE_SIZE_POWER>(
							b21 + b22)}}};
			Tensor<ResultValue, 2> c{
				{halfSize * 2, halfSize * 2}};
			Tensor<>::applyOver<0>(
				[](
					ResultValue &c11,
					ResultValue const &m1,
					ResultValue const &m4,
					ResultValue const &m5,
					ResultValue const &m7) {
					c11 = m1 + m4 - m5 + m7;
				},
				c.asSlice({{{0, halfSize}, {0, halfSize}}}),
				m[0],
				m[3],
				m[4],
				m[6]);
			Tensor<>::applyOver<0>(
				[](
					ResultValue &c12,
					ResultValue const &m3,
					ResultValue const &m5) { c12 = m3 + m5; },
				c.asSlice(
					{{{0, halfSize}, {halfSize, halfSize * 2}}}),
				m[2],
				m[4]);
			Tensor<>::applyOver<0>(
				[](
					ResultValue &c21,
					ResultValue const &m2,
					ResultValue const &m4) { c21 = m2 + m4; },
				c.asSlice(
					{{{halfSize, halfSize * 2}, {0, halfSize}}}),
				m[1],
				m[3]);
			Tensor<>::applyOver<0>(
				[](
					ResultValue &c22,
					ResultValue const &m1,
					ResultValue const &m2,
					ResultValue const &m3,
					ResultValue const &m6) {
					c22 = m1 - m2 + m3 + m6;
				},
				c.asSlice(
					{{{halfSize, halfSize * 2},
						{halfSize, halfSize * 2}}}),
				m[0],
				m[1],
				m[2],
				m[5]);
			return c.asSlice(
				{{{0, thisSize[0]}, {0, otherSize[1]}}});
		}

		// Advanced functions.

		// Reduces all other rows by the first nonzero
		// coordinate in selected row. Does nothing if the row
		// is zero.
		//
		// Returns the index of the leading column in the row,
		// or size[1] if it is zero.
		template <
			std::size_t TENSOR_ORDER = ORDER,
			typename std::enable_if<(TENSOR_ORDER == 2)>::type * =
				nullptr>
		std::size_t reduceByRow(std::size_t row) {
			auto size{this->size()};
			auto tensorRow{(*this)[row]};
			std::size_t col{0};
			for (; col < size[1]; col++) {
				if (tensorRow[col] != 0) {
					break;
				}
			}
			if (col == size[1]) {
				return col;
			}
			Value factor{1 / tensorRow[col]};
			for (std::size_t i{0}; i < size[0]; i++) {
				if (i == row) {
					continue;
				}
				auto thisRow{(*this)[i]};
				Value ratio{thisRow[col] * factor};
				for (std::size_t j{0}; j < size[1]; j++) {
					thisRow[j] -= ratio * tensorRow[j];
				}
			}
			return col;
		}
		// Normalize row so that the leading coefficient is 1.
		// Optionally provide the index of the leading
		// coefficient.
		//
		// Returns the normalization factor (1 / original
		// leading coefficient).
		template <
			std::size_t TENSOR_ORDER = ORDER,
			typename std::enable_if<(TENSOR_ORDER == 2)>::type * =
				nullptr>
		Value normalizeRow(std::size_t row) {
			auto tensorRow{(*this)[row]};
			Value factor{0};
			for (std::size_t i{0};
					 i < this->SIZES[this->TRANSPOSE[1]];
					 i++) {
				if (tensorRow[i] != 0 && factor == 0) {
					factor = 1 / tensorRow[i];
					tensorRow[i] = 1;
				} else if (factor != 0) {
					tensorRow[i] *= factor;
				}
			}
			return factor == 0 ? 1 : factor;
		}
		// Reduce to reduced row echelon form.
		//
		// Returns the total modification factor to the
		// determinant during the process.
		template <
			std::size_t TENSOR_ORDER = ORDER,
			typename std::enable_if<(TENSOR_ORDER == 2)>::type * =
				nullptr>
		Value reduceToRre() {
			auto size{this->size()};
			Value factor{1};
			std::unique_ptr<std::pair<std::size_t, std::size_t>[]>
				leadingPerRow{
					new std::pair<std::size_t, std::size_t>[size[0]]};
			for (std::size_t i{0}; i < size[0]; i++) {
				leadingPerRow[i] = {this->reduceByRow(i), i};
				factor *= this->normalizeRow(i);
			}
			std::sort(
				leadingPerRow.get(), leadingPerRow.get() + size[0]);
			std::size_t cSwaps{0};
			std::unique_ptr<bool[]> visitedRow{new bool[size[0]]};
			std::fill(
				visitedRow.get(),
				visitedRow.get() + size[0],
				false);
			for (std::size_t i{0}; i < size[0]; i++) {
				if (visitedRow[i]) {
					continue;
				}
				std::size_t current{i};
				while (leadingPerRow[current].second != i) {
					this->swap(
						{current, leadingPerRow[current].second});
					cSwaps++;
					visitedRow[current] = true;
					current = leadingPerRow[current].second;
				}
				visitedRow[current] = true;
			}
			return factor * (cSwaps % 2 == 0 ? 1 : -1);
		}
		// Inverses may exist for higher orders, but we do not
		// provide it here.
		template <
			std::size_t TENSOR_ORDER = ORDER,
			typename std::enable_if<(TENSOR_ORDER == 2)>::type * =
				nullptr>
		auto inverse() const {
			// TODO: Implement `inverse`.
			return *this;
		}
		template <
			std::size_t TENSOR_ORDER = ORDER,
			typename std::enable_if<(TENSOR_ORDER == 2)>::type * =
				nullptr>
		inline auto invert() {
			return *this = this->inverse();
		}
	};

	// Declare the operators here so they can be friended.
	// Streaming a scalar converts automatically to the base
	// type.
	template <
		typename Value,
		std::size_t OTHER_ORDER,
		typename std::enable_if<(OTHER_ORDER >= 1)>::type * =
			nullptr>
	std::ostream &operator<<(
		std::ostream &stream,
		Rain::Math::Tensor<Value, OTHER_ORDER> const &right) {
		return right.streamOutPadded(stream, 0);
	}
}

#include <chrono>
#include <random>

namespace Rain::Random {
	using Generator = std::mt19937_64;

	// Default, generally-safe generator when one is not
	// supplied by caller.
	inline Generator generator(
		std::chrono::duration_cast<std::chrono::nanoseconds>(
			std::chrono::high_resolution_clock::now()
				.time_since_epoch())
			.count());

	template <typename>
	struct SplitMixHash;

	// Simple function to combine two 32 or 64-bit hashes,
	// based on
	// <https://stackoverflow.com/questions/5889238/why-is-xor-the-default-way-to-combine-hashes>
	// from Boost.
	//
	// SIZE_T_SIZE is a default argument which forces a
	// substitution, and thus SFINAE.
	template <
		std::size_t SIZE_T_SIZE = sizeof(std::size_t),
		typename std::enable_if<SIZE_T_SIZE == 8>::type * =
			nullptr>
	static inline std::size_t combineHash(
		std::size_t &seed,
		std::size_t next) {
		return seed ^=
			next + 0x517cc1b727220a95 + (seed << 6) + (seed >> 2);
	}
	template <
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
	template <typename Type>
	struct SplitMixHash {
		// 64-bit hash from
		// <https://codeforces.com/blog/entry/62393>.
		template <
			typename TypeInner = Type,
			std::size_t SIZE_T_SIZE = sizeof(std::size_t),
			typename std::enable_if<Functional::isStdHashable<
				TypeInner>::value>::type * = nullptr,
			typename std::enable_if<SIZE_T_SIZE == 8>::type * =
				nullptr>
		std::size_t operator()(Type const &value) const {
			static const std::size_t FIXED_RANDOM(
				std::chrono::duration_cast<
					std::chrono::nanoseconds>(
					std::chrono::high_resolution_clock::now()
						.time_since_epoch())
					.count());
			std::size_t hash{std::hash<Type>{}(value)};
			hash += FIXED_RANDOM + 0x9e3779b97f4a7c15;
			hash = (hash ^ (hash >> 30)) * 0xbf58476d1ce4e5b9;
			hash = (hash ^ (hash >> 27)) * 0x94d049bb133111eb;
			return hash ^ (hash >> 31);
		}

		// 32-bit hash from
		// <https://groups.google.com/g/prng/c/VFjdFmbMgZI>.
		template <
			typename TypeInner = Type,
			std::size_t SIZE_T_SIZE = sizeof(std::size_t),
			typename std::enable_if<Functional::isStdHashable<
				TypeInner>::value>::type * = nullptr,
			typename std::enable_if<SIZE_T_SIZE == 4>::type * =
				nullptr>
		std::size_t operator()(Type const &value) const {
			static const std::size_t FIXED_RANDOM(
				std::chrono::duration_cast<
					std::chrono::nanoseconds>(
					std::chrono::high_resolution_clock::now()
						.time_since_epoch())
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
				Functional::isBaseOfTemplate<std::pair, TypeInner>::
					value>::type * = nullptr>
		std::size_t operator()(Type const &value) const {
			std::size_t result{0};
			combineHash(
				result,
				SplitMixHash<decltype(value.first)>{}(value.first));
			combineHash(
				result,
				SplitMixHash<decltype(value.second)>{}(
					value.second));
			return result;
		}

		// Unwraps a container.
		template <
			typename TypeInner = Type,
			typename std::enable_if<
				!Functional::isStdHashable<TypeInner>::value &&
				!Functional::
					isBaseOfTemplate<std::pair, TypeInner>::value &&
				Functional::isConstIterable<TypeInner>::value>::type
				* = nullptr>
		std::size_t operator()(Type const &value) const {
			std::size_t result{0};
			for (auto const &i : value) {
				combineHash(result, SplitMixHash<decltype(i)>{}(i));
			}
			return result;
		}
	};

	// Saves the use of std::remove_reference and
	// std::remove_const.
	template <typename Type>
	struct SplitMixHash<Type &> : SplitMixHash<Type> {};
	template <typename Type>
	struct SplitMixHash<Type const> : SplitMixHash<Type> {};
}

#include <cstdint>
#include <iostream>
#include <limits>
#include <type_traits>
#include <utility>

namespace Rain::Algorithm {
	// Forward declaration.
	template <std::size_t = 0, bool = false>
	class BigInt;
}

namespace std {
	// Limits.
	template <std::size_t LOG_BITS, bool SIGNED>
	class numeric_limits<
		Rain::Algorithm::BigInt<LOG_BITS, SIGNED>> {
		public:
		using ThisInt =
			Rain::Algorithm::BigInt<LOG_BITS, SIGNED>;

		static constexpr ThisInt min() {
			return {
				numeric_limits<
					typename ThisInt::SmallerIntUnsigned>::min(),
				numeric_limits<
					typename ThisInt::SmallerInt>::min()};
		};
		static constexpr ThisInt max() {
			return {
				numeric_limits<
					typename ThisInt::SmallerIntUnsigned>::max(),
				numeric_limits<
					typename ThisInt::SmallerInt>::max()};
		};
	};
}

namespace Rain::Algorithm {
	template <>
	class BigInt<0, false> {
		public:
		// We must use our own templated SFINAE base class
		// checker, like in `ModulusRingBase`.
		template <std::size_t LOG_BITS, bool SIGNED>
		static std::true_type isDerivedFromBigIntImpl(
			BigInt<LOG_BITS, SIGNED> const *);
		template <std::size_t = 0, bool = true>
		static std::false_type isDerivedFromBigIntImpl(...);
		template <typename TypeDerived>
		using isDerivedFromBigInt =
			decltype(isDerivedFromBigIntImpl(
				std::declval<TypeDerived *>()));
	};

	// Shorthands.
	template <std::size_t LOG_BITS>
	using BigIntSigned = BigInt<LOG_BITS, true>;

	template <std::size_t LOG_BITS>
	using BigIntUnsigned = BigInt<LOG_BITS, false>;

	// Maps log bits to the system type or big int type. Helps
	// with template specialization recursion.
	template <std::size_t LOG_BITS, bool SIGNED>
	class BigIntTypeMap {
		public:
		using Type = BigInt<LOG_BITS, SIGNED>;
	};

	// Template recursion base case 2**5 = 32. Requires 64-bit
	// integer to be available to support the overflow
	// multiplication & division defined later.
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

	// Overflow multiplication and division. Multiplication
	// returns {low, high} of the result. Division returns
	// {low, high} of the result.
	template <std::size_t LOG_BITS, bool SIGNED>
	inline std::pair<
		typename BigIntTypeMap<LOG_BITS, false>::Type,
		typename BigIntTypeMap<LOG_BITS, SIGNED>::Type>
	bigIntMultiply(
		typename BigIntTypeMap<LOG_BITS, SIGNED>::Type const &X,
		typename BigIntTypeMap<LOG_BITS, SIGNED>::Type const
			&Y) {
		using ThisIntUnsigned =
			typename BigIntTypeMap<LOG_BITS, false>::Type;
		using ThisInt =
			typename BigIntTypeMap<LOG_BITS, SIGNED>::Type;
		auto [lll, llh]{
			bigIntMultiply<LOG_BITS - 1, false>(X.low, Y.low)};
		auto [lhl, lhh]{
			bigIntMultiply<LOG_BITS - 1, SIGNED>(X.low, Y.high)};
		auto [hll, hlh]{
			bigIntMultiply<LOG_BITS - 1, SIGNED>(X.high, Y.low)};
		auto [hhl, hhh]{
			bigIntMultiply<LOG_BITS - 1, SIGNED>(X.high, Y.high)};
		ThisIntUnsigned first{lll, 0};
		ThisInt second{0, hhh};
		char firstHighFlow{0}, secondLowFlow{0};
		firstHighFlow -= (llh < 0);
		first.high += llh;
		firstHighFlow +=
			(first.high >
			 std::numeric_limits<
				 typename ThisIntUnsigned::SmallerInt>::max() -
				 lhl);
		first.high += lhl;
		firstHighFlow +=
			(first.high >
			 std::numeric_limits<
				 typename ThisIntUnsigned::SmallerInt>::max() -
				 hll);
		first.high += hll;
		secondLowFlow -= (firstHighFlow < 0);
		second.low += firstHighFlow;
		secondLowFlow +=
			(lhh > 0 &&
			 second.low >
				 std::numeric_limits<
					 typename ThisInt::SmallerIntUnsigned>::max() -
					 lhh) -
			(lhh < 0 &&
			 second.low <
				 std::numeric_limits<
					 typename ThisInt::SmallerIntUnsigned>::min() -
					 lhh);
		second.low += lhh;
		secondLowFlow +=
			(hlh > 0 &&
			 second.low >
				 std::numeric_limits<
					 typename ThisInt::SmallerIntUnsigned>::max() -
					 hlh) -
			(hlh < 0 &&
			 second.low <
				 std::numeric_limits<
					 typename ThisInt::SmallerIntUnsigned>::min() -
					 hlh);
		second.low += hlh;
		secondLowFlow +=
			(hhl > 0 &&
			 second.low >
				 std::numeric_limits<
					 typename ThisInt::SmallerIntUnsigned>::max() -
					 hhl) -
			(hhl < 0 &&
			 second.low <
				 std::numeric_limits<
					 typename ThisInt::SmallerIntUnsigned>::min() -
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
		using ThisIntUnsigned =
			typename BigIntTypeMap<5, false>::Type;

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
		using ThisIntUnsigned =
			typename BigIntTypeMap<5, false>::Type;
		using ThisInt = typename BigIntTypeMap<5, true>::Type;

		std::int64_t result{X};
		result *= Y;
		return {
			static_cast<ThisIntUnsigned>(result),
			static_cast<ThisInt>(result >> 32)};
	}

	template <std::size_t LOG_BITS, bool SIGNED>
	inline typename BigIntTypeMap<LOG_BITS, SIGNED>::Type
	bigIntDivide(
		typename BigIntTypeMap<LOG_BITS, SIGNED>::Type X,
		typename BigIntTypeMap<LOG_BITS, SIGNED>::Type Y) {
		using ThisInt =
			typename BigIntTypeMap<LOG_BITS, SIGNED>::Type;
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
			auto [productLow, productHigh]{
				bigIntMultiply<LOG_BITS, SIGNED>(mid, Y)};
			if (productHigh > 0 || productLow > X) {
				high = mid;
			} else {
				low = mid;
			}
		}
		return negative ? -low : low;
	}
	template <bool SIGNED>
	inline typename BigIntTypeMap<5, SIGNED>::Type
	bigIntDivide(
		typename BigIntTypeMap<5, SIGNED>::Type X,
		typename BigIntTypeMap<5, SIGNED>::Type Y) {
		return X / Y;
	}

	// Two ints of half the size form a larger int. Implements
	// arithmetic, bit shift, binary, and modulus operators,
	// as well as comparison, i/o, and cast operators.
	// Unsigned overflow/underflow is well-defined, but not
	// signed overflow/underflow.
	template <std::size_t LOG_BITS, bool SIGNED>
	class BigInt {
		public:
		using ThisInt = BigInt<LOG_BITS, SIGNED>;
		using SmallerIntUnsigned =
			typename BigIntTypeMap<LOG_BITS - 1, false>::Type;
		using SmallerInt =
			typename BigIntTypeMap<LOG_BITS - 1, SIGNED>::Type;

		static std::size_t const halfBits{
			1_zu << (LOG_BITS - 1)};

		SmallerIntUnsigned low;
		SmallerInt high;

		template <
			typename Integer = int,
			typename std::enable_if<
				sizeof(Integer) * 8 <= halfBits>::type * = nullptr>
		BigInt(Integer const &value = 0)
				: low(value), high((value < 0) ? -1 : 0) {}
		template <
			typename Integer = int,
			typename std::enable_if<
				sizeof(Integer) * 8 == halfBits * 2>::type * =
				nullptr>
		BigInt(Integer const &value = 0)
				: low(static_cast<SmallerIntUnsigned>(value)),
					high(
						static_cast<SmallerInt>(
							value >> (1_zu << (LOG_BITS - 1)))) {}

		// Constructing with bool.
		BigInt(bool const value)
				: low(value ? 1 : 0), high(0) {}

		// Constructing with a larger int than storable is
		// ill-advised and disabled.

		// Can also construct with the two components.
		BigInt(
			SmallerIntUnsigned const &low,
			SmallerInt const &high = 0)
				: low(low), high(high) {}

		// Explicit copy constructor helps avoid compiler
		// warnings on `clang`.
		BigInt(BigInt<LOG_BITS, SIGNED> const &other)
				: low{other.low}, high(other.high) {}
		template <
			bool OTHER_SIGNED,
			typename std::enable_if<OTHER_SIGNED != SIGNED>::type
				* = nullptr>
		BigInt(BigInt<LOG_BITS, OTHER_SIGNED> const &other)
				: low{other.low}, high(other.high) {}

		// Assignment.
		template <
			typename OtherInteger,
			typename std::enable_if<
				!std::is_same<ThisInt, OtherInteger>::value>::type
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
			typename std::enable_if<
				!std::is_same<ThisInt, OtherInteger>::value>::type
				* = nullptr>
		inline bool operator==(
			OtherInteger const &other) const {
			return *this == ThisInt(other);
		}
		inline bool operator==(ThisInt const &other) const {
			return this->low == other.low &&
				this->high == other.high;
		}
		template <
			typename OtherInteger,
			typename std::enable_if<
				!std::is_same<ThisInt, OtherInteger>::value>::type
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
			typename std::enable_if<
				!std::is_same<ThisInt, OtherInteger>::value>::type
				* = nullptr>
		inline bool operator<=(
			OtherInteger const &other) const {
			return *this <= ThisInt(other);
		}
		inline bool operator<=(ThisInt const &other) const {
			return *this < other || *this == other;
		}
		template <
			typename OtherInteger,
			typename std::enable_if<
				!std::is_same<ThisInt, OtherInteger>::value>::type
				* = nullptr>
		inline bool operator>(OtherInteger const &other) const {
			return *this > ThisInt(other);
		}
		inline bool operator>(ThisInt const &other) const {
			return !(*this <= other);
		}
		template <
			typename OtherInteger,
			typename std::enable_if<
				!std::is_same<ThisInt, OtherInteger>::value>::type
				* = nullptr>
		inline bool operator>=(
			OtherInteger const &other) const {
			return *this >= ThisInt(other);
		}
		inline bool operator>=(ThisInt const &other) const {
			return !(*this < other);
		}

		// Shift.
		template <typename OtherInteger>
		inline ThisInt operator>>(
			OtherInteger const &shift) const {
			if (
				shift >= static_cast<OtherInteger>(halfBits * 2)) {
				return 0;
			} else if (
				shift >= static_cast<OtherInteger>(halfBits)) {
				return ThisInt{
								 static_cast<SmallerIntUnsigned>(
									 this->high),
								 0} >>
					(shift - halfBits);
			}
			ThisInt tmp{this->low >> shift, this->high >> shift};
			SmallerInt lost{this->high - (tmp.high << shift)};
			return {
				tmp.low + (lost << (halfBits - shift)), tmp.high};
		}
		template <typename OtherInteger>
		inline ThisInt &operator>>=(OtherInteger const &shift) {
			return *this = *this >> shift;
		}
		template <typename OtherInteger>
		inline ThisInt operator<<(
			OtherInteger const &shift) const {
			if (
				shift >= static_cast<OtherInteger>(halfBits * 2)) {
				return 0;
			} else if (
				shift >= static_cast<OtherInteger>(halfBits)) {
				return ThisInt{
								 0, static_cast<SmallerInt>(this->low)}
				<< (shift - halfBits);
			}
			ThisInt tmp{this->low << shift, this->high << shift};
			SmallerIntUnsigned lost{
				this->low - (tmp.low >> shift)};
			return {
				tmp.low,
				tmp.high +
					static_cast<SmallerInt>(
						lost >> (halfBits - shift))};
		}
		template <typename OtherInteger>
		inline ThisInt &operator<<=(OtherInteger const &shift) {
			return *this = *this << shift;
		}

		// Binary.
		inline ThisInt operator&(ThisInt const &other) const {
			return {
				this->low & other.low, this->high & other.high};
		}
		inline ThisInt operator|(ThisInt const &other) const {
			return {
				this->low & other.low, this->high & other.high};
		}

		// Cast.
		explicit operator bool() const { return *this != 0; }
		operator BigInt<LOG_BITS, !SIGNED>() const {
			return {
				this->low,
				static_cast<typename BigIntTypeMap<
					LOG_BITS - 1,
					!SIGNED>::Type>(this->high)};
		}
		operator typename BigIntTypeMap<5, SIGNED>::Type()
			const {
			if (this->high < 0) {
				auto tmp{
					std::numeric_limits<SmallerIntUnsigned>::max() -
					this->low + 1};
				return static_cast<
					typename BigIntTypeMap<5, SIGNED>::Type>(0 - tmp);
			}
			return static_cast<
				typename BigIntTypeMap<5, SIGNED>::Type>(this->low);
		}

		// Arithmetic.
		template <
			typename OtherInteger,
			typename std::enable_if<
				!std::is_same<ThisInt, OtherInteger>::value>::type
				* = nullptr>
		inline ThisInt operator+(
			OtherInteger const &other) const {
			return *this + ThisInt(other);
		}
		inline ThisInt operator+(ThisInt const &other) const {
			// Unsigned overflow is well-defined.
			return {
				this->low + other.low,
				this->high + other.high +
					(other.low >
					 std::numeric_limits<SmallerIntUnsigned>::max() -
						 this->low)};
		}
		template <typename OtherInteger>
		inline ThisInt &operator+=(OtherInteger const &other) {
			return *this = *this + other;
		}
		template <
			typename OtherInteger,
			typename std::enable_if<
				!std::is_same<ThisInt, OtherInteger>::value>::type
				* = nullptr>
		inline ThisInt operator-(
			OtherInteger const &other) const {
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
			typename std::enable_if<
				!std::is_same<ThisInt, OtherInteger>::value>::type
				* = nullptr>
		inline ThisInt operator*(
			OtherInteger const &other) const {
			return *this * ThisInt(other);
		}
		inline ThisInt operator*(ThisInt const &other) const {
			auto [first, second]{
				bigIntMultiply<LOG_BITS, SIGNED>(*this, other)};
			if (second < 0) {
				auto tmp{
					std::numeric_limits<
						typename BigIntTypeMap<LOG_BITS, false>::Type>::
						max() -
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
			typename std::enable_if<
				!std::is_same<ThisInt, OtherInteger>::value>::type
				* = nullptr>
		inline ThisInt operator/(
			OtherInteger const &other) const {
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
			typename std::enable_if<
				!std::is_same<ThisInt, OtherInteger>::value>::type
				* = nullptr>
		inline ThisInt operator%(
			OtherInteger const &other) const {
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
		inline ThisInt operator-() const {
			return ThisInt(0, 0) - *this;
		}
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
	typename std::enable_if<
		!Rain::Algorithm::BigInt<>::isDerivedFromBigInt<
			OtherInteger>::value>::type * = nullptr>
inline Rain::Algorithm::BigInt<LOG_BITS, SIGNED> operator+(
	OtherInteger const &left,
	Rain::Algorithm::BigInt<LOG_BITS, SIGNED> const &right) {
	return Rain::Algorithm::BigInt<LOG_BITS, SIGNED>(left) +
		right;
}
template <
	typename OtherInteger,
	std::size_t LOG_BITS,
	bool SIGNED,
	typename std::enable_if<
		!Rain::Algorithm::BigInt<>::isDerivedFromBigInt<
			OtherInteger>::value>::type * = nullptr>
inline Rain::Algorithm::BigInt<LOG_BITS, SIGNED> operator-(
	OtherInteger const &left,
	Rain::Algorithm::BigInt<LOG_BITS, SIGNED> const &right) {
	return Rain::Algorithm::BigInt<LOG_BITS, SIGNED>(left) -
		right;
}
template <
	typename OtherInteger,
	std::size_t LOG_BITS,
	bool SIGNED,
	typename std::enable_if<
		!Rain::Algorithm::BigInt<>::isDerivedFromBigInt<
			OtherInteger>::value>::type * = nullptr>
inline Rain::Algorithm::BigInt<LOG_BITS, SIGNED> operator*(
	OtherInteger const &left,
	Rain::Algorithm::BigInt<LOG_BITS, SIGNED> const &right) {
	return Rain::Algorithm::BigInt<LOG_BITS, SIGNED>(left) *
		right;
}
template <
	typename OtherInteger,
	std::size_t LOG_BITS,
	bool SIGNED,
	typename std::enable_if<
		!Rain::Algorithm::BigInt<>::isDerivedFromBigInt<
			OtherInteger>::value>::type * = nullptr>
inline Rain::Algorithm::BigInt<LOG_BITS, SIGNED> operator/(
	OtherInteger const &left,
	Rain::Algorithm::BigInt<LOG_BITS, SIGNED> const &right) {
	return Rain::Algorithm::BigInt<LOG_BITS, SIGNED>(left) /
		right;
}
template <
	typename OtherInteger,
	std::size_t LOG_BITS,
	bool SIGNED,
	typename std::enable_if<
		!Rain::Algorithm::BigInt<>::isDerivedFromBigInt<
			OtherInteger>::value>::type * = nullptr>
inline Rain::Algorithm::BigInt<LOG_BITS, SIGNED> operator%(
	OtherInteger const &left,
	Rain::Algorithm::BigInt<LOG_BITS, SIGNED> const &right) {
	return Rain::Algorithm::BigInt<LOG_BITS, SIGNED>(left) %
		right;
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
		static_cast<typename Rain::Algorithm::
									BigIntTypeMap<5, SIGNED>::Type>(first)};
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

// Hash operator for this user-defined type, which combines
// hashes of the inner type.
namespace std {
	template <std::size_t LOG_BITS, bool SIGNED>
	struct hash<Rain::Algorithm::BigInt<LOG_BITS, SIGNED>> {
		size_t operator()(
			Rain::Algorithm::BigInt<LOG_BITS, SIGNED> const
				&value) const {
			size_t result{
				Rain::Random::SplitMixHash<decltype(value.high)>{}(
					value.high)};
			Rain::Random::combineHash(
				result,
				Rain::Random::SplitMixHash<decltype(value.low)>{}(
					value.low));
			return result;
		}
	};
}

using namespace Rain::Algorithm;
using namespace Rain::Math;

using BI = BigInt<10>;
using TT = Tensor<BI, 2>;

// #define ONLINE_JUDGE

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
#ifdef ONLINE_JUDGE
	std::freopen("vans.in", "r", stdin);
	std::freopen("vans.out", "w", stdout);
#endif

	LL N;
	cin >> N;

	// TT T{{5, 5}, 1, 0, 0, 0, 0, 2, 2, 2, -2, 1, 0, 1,
	// 		 0,			 0, 0, 0, 0, 1, 0, 0, 0, 0,	 0, 1, 0},
	// 	B{{5, 1}, 1, 6, 2, 0, 0};
	// if (N <= 3) {
	// 	cout << (B[4 - N] - B[5 - N])[0] << '\n';
	// 	return 0;
	// }
	// TT Z{TT::identity(5)};
	// N -= 3;
	// while (N > 0) {
	// 	if (N % 2 == 1) {
	// 		Z *= T;
	// 	}
	// 	N /= 2;
	// 	T *= T;
	// }
	// Z *= B;
	// cout << (Z[1] - Z[2])[0] << '\n';

	array<BI, 1001> B;
	B[0] = 0;
	B[1] = 0;
	B[2] = 2;
	B[3] = 6;
	RF(i, 4, B.size()) {
		B[i] = ((1 + B[i - 1] + B[i - 2] - B[i - 3]) << 1) +
			B[i - 4];
	}
	RF(i, 0, B.size()) {
		cout << B[i] << '\n';
	}
	// cout << B[N] - B[N - 1] << '\n';

	return 0;
}
