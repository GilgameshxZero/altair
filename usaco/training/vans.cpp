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
	auto quo{right / 1000000000};
	if (right > 999999999) {
		stream << quo;
	}
	auto first{right - quo * 1000000000};
	auto second{
		static_cast<typename Rain::Algorithm::
									BigIntTypeMap<5, SIGNED>::Type>(first)};
	auto third{std::to_string(second)};
	third = std::string(9 - third.length(), '0') + third;
	return stream << third;
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

using BI = BigInt<11>;
using TT = Tensor<BI, 2>;

string S{R"""(0
2
4
12
28
74
184
472
1192
3034
7692
19540
49588
125906
319600
811376
2059728
5228914
13274132
33698012
85546188
217169050
551308584
1399560904
3552947064
9019567818
22897216540
58127235492
147562715492
374605036706
950978249952
2414168377824
6128645897632
15558277087714
39496487464996
100266405687980
254537878028156
646173869589994
1640387171325336
4164312731462328
10571589944423496
26837204878710970
68129351354669612
172954245309376500
439064373515093780
1114615739818312306
2829581087402728784
7183219152721271120
18235433374126468976
46292758618708334930
117519526767629794356
298336923177144591740
757362816026258571308
1922653183490255072314
4880877679446367898120
12390673016997873389992
31455157841934231002904
79852559542461728061866
202714966414242539247676
514615409246537946003268
1306410790078571745381060
3316475025364196032335170
8419255778806702202673600
21373255437431190925258688
54258483171825965936575296
137741440686265105350655938
349672592620126462926618692
887684355706562395606657356
2253489498452673472301815516
5720743963764483915314364298
14522770805641316446945663608
36867734897612816175523082136
93593012977431970886610578408
237596698102571425145690358170
603166723170422476160501372492
1531208551488736677014685386644
3887150166090607426945603380340
9867980686920414680745265147154
25051011326214993337512867654192
63594892245578337859639744228656
161442995935836440459760296851728
409841734397319984644519611999538
1040430687501371167826793196899412
2641253744171287761882744768323100
6705128390486514330589797003297676
17021744628710181833936016761442266
43211669237552187973112931189733096
109697824695722998714801046664078472
278480626999616524038545719188036280
706955309544284851394403686086205578
1794687892933908941409409648410059868
4556022975652877536245336277280536804
11565991745084619776559230198396818468
29361608965151461594184717340620796386
74537843362100316610406632171884215968
189222944139987194392309574905496924576
480364348818956718593622209671917506784
1219460508158838654345235022151681227170
3095741669037716673703501946008087834724
7858898600895184413302539091881200034796
19950723872367081583915234241147130791484
50647222116607937301373777796192167210282
128573836445197385617676447836924283768664
326399567979771667083572521875819840409720
828603088489089312383665618074251044727688
2103504862163935125000497162022485369947770
5339990601791702926218856964278757432300140
13556184318912869144754949538329803355450164
34413943205570363204330284299246401880332756
87363778707546993970733250908617380976913330
221783065790200678986836028303346716435891984
563021986903267488651232939363765194420395280
1429296491177412710539001717816235461639080624
3628434603288506034377530508661925260224081170
9211201280915503191517434602532137771321425012
23383700772956460519363159726119420334233246396
59362231392344328063545129357795501152300261100
150697896372059076817159239471427492690648246138
382564055263809391914199852808739284788751946696
971183141260004741854991085570861972988433109864
2465460831695854441967608527174143031325373881944
6258857731756158660633958759343958931740758336362
15888834899647826113407352254703219264944150163580
40335646740676265406002396059316932303707502345860
102396708648831720159519187636526528305147162228100
259945898711476477564862421641624441619561787157122
659902756138911690750165778692371294506947044242304
1675239539143789161717020421454255347946430840688512
4252789501791280469964166744646530929972779357775488
10796198468303792359426905196458454408444088095600514
27407399618041479026098268817993831275447820269617284
69576856708251770992839034961065764855784688855573132
176628905217770195788984963909848814375549621416955292
448392923084264767870878365302299950320217068101422794
1138297342805607864360146857320159830955411821595227192
2889699578052456643876919552386287698655943225414962520
7335836900765369676521361052718143972957825579234489128
18622871195108701679947145860870843631636931034209871706
47276314378448837289543321579725559642833038597654023820
120016396923636795229815132328142806301680231330673775316
304675517114719231355343977146713188598710503367470343988
773454070514923080271178721651131714146752323235190062674
1963502695790459870082958454519129752530398229141627286512
4984578895304964233227401530375239362458560329349367785712
12653930558275721277433706503633187990283122973879080363088
32123467586095374361427477880629726914569322471408831787250
81549141193922722681350524162294480837318168461018716015764
207021935338789715763915992608957278885667296246446302665564
525549148451509849445111784284877253607115407445991454151244
1334167352778849059416781983343709830225498392934246913389338
3386938272977061108877306074201554090731211176728602845765800
8598134889947590353461868539129730613584855620680162912673352
21827360768743114655289897044260027001788252216395029144250872
55411282124206136859165701001720116879509291713627425335706186
140667954278980383430864765087902380626156587795413185980333212
357101886158834401622943006629854671621340110205971327256250404
906544477395960411044574038476333897737763064791909204946005732
2301368100675834995332470261038292494345402466118562117779552034
5842289338104902392939067350857445821549807429204413176918947936
14831327808928388356076870153468663507936233771268103506761238880
37651042570110871918411508525051967568019040533499818336747275296
95581530182544550758431092916364663003156336217245579450958684514
242644779225558971034470529926753379948028093388159001738808389796
615981861484913688105057098789600814274267011915077629212800836908
1563741263625967088680604580125031030006296578705481921338048359676
3969738221953188162260813390892121591668227330682046677075040298090
10077640027414042096707192274381856994748541888333060940139384031512
25583255832967440028679859269087495927095212292534329020965552776760
64946056540482555014933080885279493690357350279076168489397841380040
164873082914025094056072309150862386837076268697236919817523060548666
418549407270494460181358253808490626195425355255890579512050082335404
1062536123121041438473674823417234534611383759640636990701316155784820
2697370951495504164212854617035005041629823042677657469281084196523156
6847588417606127379066414682438360286928639162822044680758223600493810
17383395899231674669792547205920752214089582246974020898188033364799696
44129762853805637207765889366065449453388180493877453210031661693325520
112028511622357873161196898396130687802728070198736516324204027111785968
284397345571469798777406895794989130370981976054101941952853534481117394
721975584579275744131468356856029489654733313764896031032239833163955380
1832818599910580976703122597875841313899362619734400366531810342759899132
4652822189459131717275565016269894034168955985089125427546597309997260204
11811727755152343698471845410374400847198152558171361468045189173667525306
29985438273981064622220044014392936624590225160817069089152192114973728136
76121506279259134183535771414870728189138206087533010625833378300047885608
193243255785634841931843505054048421967229513365446561921427359792705437080
490570375336978166684790310319426827910753141142496368384262281129226714410
1245369687960688813488416131931601980002279122001636908448864717358742259900
3161515121303323410666261645808831500080743705644906440449232655690574960068
8025872123639702956871618439896061726311768886373540522949097543632886448196
20374605489301653274783718217866009320691220081176116478283193245058665011138
51723294671236754455466566155838081073846769645811138030014980983360695258432
131305571195100732957423593513424888836533185386872334411147386025263522602816
333334392877711371233084501342689982905689238789388252448707445070763992148416
846207944292452352744866775618419590657442529142075014137962893470392303996738
2148196826621362736496521933051207450527043934734993002381060886015146242343108
5453446327267308168974032008167299005394127635562231862551780054854812630985676
13844204812070148476684458832542863713433147321099687954038463539869897130812508
35145116569724640171068804590936330127257904572995928642556328310889519342906890
89219946935676323694054984763674997121120892451801762470467084477824353927810552
226495163713928938945852693052304226075285427042958238180521678552542764910795544
574984192971831393414362205282628649851729977164627831970903332978825096122210920
1459663936069892657503388631733452087739046928084564544004472182417976533553298714
3705525877591266547637851272691228020152103848864270038060174758166342083457238732
9406906405092584562399608091336407142154127026611371738368008893763529806687448596
23880520886199748298482503669870994798986097871946782296818326272002615809304988148
60623466763472025283991909608765799929715289027472332538256792997617583598623694738
153899688366749644587787461647292003193246623594479756231474395509879681285939707312
390692174893136427708993343263710023790105756526621984684193733364752827957204276400
991817313879027842324060294274343448906260280059205599051640998026032467098345566096
2517843067574301276174524261390288738935954115010167987546977464759428811137843965106
6391836101487135026166969886449136331297463900679982960060323854351296581843910216916
16226415885257953347743861050393873266444421227788512681795514375534138679724021508252
41192635152220602037796673645179785166518122306975860907669362528278045367958521086220
104572272939557141994921653879639332942266113383178949246356083563681203742815108720218
265468820514526716396115902835299626015977092825412577904520187287201517443943126813288
673923332488984466054225627189912220849894589031019845168209331020743490317323450402824
1710832395280128682948636425936324813013729259253482808560416232016805653404861458078008
4343146087448730007208413954461514148637559624301359100894566835064376456299298672055306
11025579120994275164601765409251153107618765681873056706478067659408078756217616486274268
27989708958814737443777311502742597107335086682872885842792645855932042608541430850905956
71055116380000693885289962341000796945646314740142649705312709592568295470324358788327844
180381638523091042336139430823445996039362831106586316784149142413248895101595644977974370
457919671009548272719905928732659544862966884009585217999816479959178374682974762317066784
1162482095264091979785288105932952085020701887434930656000098471415649991237033527864332576
2951095371881099114223399170025332064634258195416001764136844327515727237107149649195177824
7491697230794376684913702125274695205623349228789280721058401780357646602424012474462861602
19018540685832315911423532307466809915336777957550288876390111752874626071271231953904480484
48280767184755278944012958631365298197672439869282066322623436882848740864413223086208661100
122566316651467535455268976797140157879405995391502150720047138038247167903628034780495737788
311148783531575373660630508367351987529106663835257137053619328116800211995964064300062698410
789887206682407576255196585373720504337017216672504731778476170297271904141628983942604030680
2005220114309786107865129192519229966171108210101801502546720157634498637332343250010550643704
5090483391572704156374659515848337123837443521269600345263201137668187826859644374086679689736
12922781381931740749629814754355045158872175693233051369116509578127629332096681344609315303930
32805976525071725172533886740742025137414039225474205155444457286619908947389593921313492730604
83281769145171309639443213151016696311068651004977113861142251611793199542585605033682807333300
211420411968195292281069229790655689703058472595706135640203599778239146142616679594860649209684
536715190558521494245586927156215766912298344443651140060919297784952502807722062759069242928690
1362513643288162678946959774332451545745990371294234528835405749189416807762895868561807662340752
3458898612902149071462398156547039942221529137289336180373385146004053528398588108485715319452816
8780814543231775804608611237237207131813500800875545273935946794595274812850140508171768126939440
22291114216250045888493686166059806823490377478184944991008771680604775569779387558950420811031698
56588573936447507922226758267832399571910688654836542697978072407581410516224775785834754899377396
143656645831833705083686064549857038469396659801581221010475179733185876074706633781712530486392124
364689025647294110039446884540496469567447442757341182708824907714920296855154184525365497276415084
925805309301610660290306067811102023753357205286356667033652801761654300397051472601436966537891322
2350263952170589638414360533871315309274726665139069800161983131894358852871222822476014621555205960
5966417117481646082414125498833698765390669515137751789984097231615371588900946854885884712119756520
15146440546348544231115806814328320571391525392738271028933680031211072579605390594046290231550557400
38450992732620812010521449626392510078768293690760262704545241063625824931667280725513757610768107242
97612296275146009956860622417645579078813025801860633687151630858337410697614671751824340881953022204
247800114040318201554946655958253235937770257714903002515510481013119697688254070621469501234460900612
629069275712035343233687464313340930447021505044745018025167421646873639488008313889606459242842188548
1596965179687035881674068445334289684690725767606335036411597784666937677888962706244016996801468241154
4054080978992652056662479129796400337478767055674214737529661081459720650075048570776132250501652080384
10291753879975623391760666877592951419382712894186512514347693369972689074640259996882555077355017166592
26126808634274514476731842588423465074788529869553529448956680755177817733140700036718947121353244200192
66325928250202007505334129117774321998075677183737989487961023872048509993300785631894756893214686813954
168376046987994449237273088787006071644441755373884227582669683595966997953677499914238430124927479775492
427442087087819507923511417510306808554840518270323887757695746795648069502315431015711034870932861945100
1085111220285498413787632596947500581477201722790493781153765493794310932658524990632828363326644554013468
2754680449020848952453075980459376958773276648557604872145544137860032518407626629100496693038514559180106
6993075211425050165871667408580147535035717461529433758665897453313357761081349877349466473113379982272440
17752730967408620916997733001694354633218425292863413587073047941553806763163218462649980640521432836823256
45067362679911142674620281456577751000438933934460978728340568007808574944332408412430729204519241073844648
114408717320810275803945770079843293156016560180147521985640981129958080411236180624562983436893102415971034
290439773278050645289008304478033526581509855105019608012482899845739054945892091026036930474895201288257292
737314986805308177753665319204292492107393387994275716126639673877330927588754944938988350055059558097590612
1871759448205008237152075988661543202066212299772756583035303753194032379191154119093355323390642555013598388
4751678040785341815037411776855447628340208225504172904284562035581206584079270126637176469378506926061834450
12062684777648134394160653197103430203179564129670327150398935129641555126309230692609123815903075047243941744
30622521727262244121845643289798961751014513498797762659423026497934789589983448345244878273836938394681946224
77738816376455081639089845408755431853773951105700590394110102937184308643617971941527006564113655586741705424
197348984692923724548587082779757374431558009175160224710552950646536292798663649314962698513473544794421254258
500993243461881258525823222994531119271814457693796432040878989301213178830905576515098777423403599020205968660
1271829345283962046992486564020865085450211545025309895374066700519065115561885956122313817019363914850452981212
3228686024482294243578535253880033092434709938193592795802895581284668311831873738586426798422701593739217096652
8196393237301673788638984272592491491657772060225372742982719535651576789924371885702246374550797363933349472666
20807493076461893228975889147897850116556355364481107718863975822135573151219624912847817489331673684664433144872
52822229923846507595065162897241482117009046518051085227461666253524028374186132076049587947938902824567584022984
134095345550495748314382670798973714576249969582807233202488740661300717782794643944976744923862259884336552487032
340416558033062399149582873369227184645063093532979794165155581721029922801446674102059277139489775412412756202954
864186840395885172966776651689816684325164388559952991999229288079748797571329996854820685720157938629027882478876
2193838335680750155199018871417381790904964071538302191151253924532480033554150186099856023819509811138775756412580
5569312581637641606346807970274916295746380702713358011173144002443698534430861661650211609724218208595118317864036
14138344711878075576307683253374189989297423864916394214815492859513889463628810375892553172786629937622145139798434
35891824756065819227877721356153265672602845380742853061673995162929964726582373699740638203102834608786003284978656
91115552108293256550876212149922460523212741157430080721783941964532791345114795014065815556150002486764835970238688
231307376886599642011239308475677988708782706049226437148458032538341431750567578337478012782656632524452506548701856
587200553189532234244783281792268557108082627516743723831951451539402406201828809679498933444194230742484823607722210
1490676580691743058638170477592201436259908030197823013578925079389352057941145559705562899544504556169130991657349412
3784255066097644558294305113967506469841628644488110681246620938745358856129928377109233455968234311261091453402978220
9606769564086310407386623928010556686695690800387606379135647165728958447489057832608072856919745905899927749453912700
24387896652173956048330300410563991997662905456872531817438637501709332897557510109702985760131145552726261246006805226
61911498881016986853483408926806285865293843255741878044234252536775217035774424690109213221709818850899326075772828824
157169507004306909547148475932686948822363744468941717646321106684256541827815682311517485705810671306712410598054420920
398992988030386191111989792825869042066685055336009734125369090604373810379554251616455499191698435115670878605094801736
1012889888959526183659640020074063402045172818555291679272350527005419603240748528585430529111729720695694187500759592890
2571338238852227917302446082861297276444282102100461269547031274387848960620748620470846298416944787860204637091372776236
6527639786567042729247341096151670221667903475108428147034346528262046048791701477191160142379762818187168302572129555700
16571169260949875116892284110703677234200710572643205208743423641893324622722957389769607322561654205819028382930580279828
42067831506288906041333998268062163760893836709857635851733828318540463025028569021565272862160674192987678284323433711474
106794060200195704775260328648089638823297569716885287096432842138731332158540398488758286383102075949099281366455141647440
271109084677636514128651426707047920921649295183307863625880840159018987170483721718299063987781954690723030838268119713872
688241796004036500842047798284854469202306766953314234949903131600313037230714059760753762340008367099488296223730235579504
1747181472469243526432211790955687666362210821549331258810436087559741847510343335002154352751537165875211769675409861003346
4435422427791482731066476653715078068109034156355560547365349600140803127299687744577976388590629232517053351488199095385396
11259833293191016027441932719478870451459525717086463006077645952359482862329117761357053021992098017276276680718025561332348
28584390293030546964994442962761376175615004870738698824215022061481401321467638401626503878002388534935724821285359827008300
72564783789329404049172009848006024784293203684488533824665072914959903960504480171813315375559251805265108070705782446913850
184214104006129352704515516836292139085006399832637099832970247648304447966585689368743508851729713878366165774034432520565000
467648828298047435604828100162552445838828723009860332672918242955925384073574180039217693720565252314667374727627735842273448
1187180687322725315485337657264438496454698843186756496186661857440021257480778416873922278271473817310472589683198131658857496
3013795607018616200820472491029403631201335536412447991877884778410244291136038295260606241656177963298812705344288652408045738
7650869036092717514106479613098871502719417713011325410616227033436984777053070753559365161265902770467602006373752528969824572
19422616739875264234488056993890225720770937535483894145287818151770341005490235443931315943021779085226551618797313835280299076
49306561025221456411033465889183825681032738267352299624238982671034184240295314221334072003534481602101154429336753555343013316
125170413065026622463650559030979763429369851716062184709699032357145325228600996118672651812236893797019020788864918375715021378
317759583736838346794498415465645598281982722608872505787916620786255321703865220545710180906765095398254849205182468720525295808
806669488293162289928719074208773297781410609650648675892041159096503266389832040330028837373956794271571982748218580917074906816
2047823878955169484930167327176062090949079699354270293564756477722260709970487843735466804940504473347716776758409016079113375808
5198637980088013478592426530869359344326385024508155112047461064422162634541510323158243574627629238239086841391755174927040995010
13197344325236879693982247983138941873270090951032425965228269386882095477948197473673073265295118930028718120009073688898684223812
33502986341032609665217733447873251551076203162023270243313989106260498071428271946521728907338444184111748352033058276410298592844
85051209251318121246145277127461730250988897876449352486554351335163122539640406037808584000952372225150476038059162596842997019100
215912340514315715913353951715261439201916405199388548641327603173505212900782471344472722860619024196706099381558049543636263771274
548118471174439334682545238772838777676928290778661687734364200191697770215937408345192229173761023405518372255177381417036608618872
1391462191215906468364725560169150224806787799365225038021588893166340219225587219250234464974193794938259739549385595004070049334936
3532387853003378295513978971580916856814588267765445706715805331704228675621124718539716526575623960519294500884069016351783785384168
8967375486604006574305672537669718047090811957903406662647387652531247462162331530233990247612732488300777835738112509421270715971738
22764720767957396137592397136935808135874153143385916350417572382329969607331675467392136847602086331169143566400769242955005512660812
57790878994331955301132906966218368877107541466412979650719898299480317006971351777423055602252583512839513542059011067053054935831700
146708836404374068024353242102549834788596353571556424383695971390262306979902516147702120931059498671935053046327404617525363250425716
372437364748101260950093176401334509106750295747070382030643982267356556221246716445700069619032724195511623879709405392668096063164946
945475365084244143484219420212267758172352368847813569877657683098607061995687437099350406743281365040383470334356367129235814268178736
2400198665850274628121051615988323233858120163513068034699931286250882939481034626572119766464761764640759595877535746875810149097667632
6093182168777209089334708961701062800636040826799178869477585945554529197490853210599242328109080309643197937710692821842281097855788560
15468248303834580408893175491355571061750367538675937050630363079680966706173647516589723445280154142682659750387453808570378961433719858
39267938978607273883697885094348889015228928772771909340693693161067832990362619638333042420592226740410579654775578134202935634651860308
99686208893179565034633754863995117786544631132810403078392871876639423937571862515219166841991362911540842530782213988737877145557250844
253064981304681726108211637895677934280682425560611929606389989861607109641012522484524213962715951328180722808051369450583148735406571148
642434750742342614927188190822003897165746623379976783738808700234038367882617178239410400213510329141304631118503464418806559454057643226
1630894985286296825885230032801722316334997764388328529874305329599079940162478296055763937089062061856299602446320817895506597722465787368
4140215718341094994443046926320091676226668555548197171091840951819661820745737766136519413521704242250387864044328039716197894027790969736
10510416887074780136910389174495298125072521818673709764061065152231013895692210290390270114757227901258946393552342155836379013327804798904
26681909991001499225863600326849338867094131843047133594296010249137229920433556699181461582593250492447373941419202219732947178720317605770
67735117304756665562547115182850812948214967976733620904404774228696243930922536742926188504746610364768164544300753489601763193763128657244
171953436535707864297443699596729799056699824557762286640371279603024581732073504069571279358686970154163572048379555146712860612339073897956
436523704586000841405164818079957844400713843201571257665021152317398205380817178517022282676437887954227671696074554988999732268091574697764
1108165957624905579505986405314522999885491531408246980396271325632590316284369848386516208643349745979693532341725915511954606552055357482722
2813207568655153778789962162778352903407226068080845523746247170922624123797149582410860612426947937924283428523142584198084719609378845222304
7141653079923824898079011199622565916840707337132804779595365968078657051133478008630280356146406562053662150385967444588792048399024329912480
18129913086494147036131138732252749485125597590812377903555704779054779922673332663826271802536447395950731764830842781538844055180787210001888
46024883153150541890346361943508447997003649251136921299205918478054216016303692028477899301155161786139914505729061199371057374492920746866850
116839493888096881835586941115055616033984305077713834370078761748983301899484242949758642107517353177998251668871015656840303482158746099134820
296610580989430378277683339852245195008565420813209560311053316864044133037362682637450819568418541698428530969924435593933825651340783601912044
752980296535247583481978976779837475576217750870385324667408025049001217763759799781289396552097913576524468030963622884344987573194005118361916
1911527650426312701738497112977562557098601382462899022515971078806178313819580170966441047327153365980049409169763146842248076859245005989145130
4852634225832356695721172440925365291366491730117863408114730335731254098991438819170317890729182828894288944130475683922158781044355201110324824
12318973740436274006233064494098425940786316144233963772237640095840906523131881063348389902576895104294056301508474851354057566312153187564128120
31273140928219883583913458620872294825684630734648241640340206730580965834371239222885822888509947047993116140969338399752281528567720770488977544
79390488536073914490589198461068273507307511679991583031442204060187414830842943105094230848042472012765816405864438281210608704530282519874706810
201541945673547404832260357616609650075778144270929585207204271725586202383156041348433645558680230741824041434781079343139824114616055406709437292
511637560303239145484105259407709683455588366576779816968850178206226209282387371524632496939002406517487539700860833300550360147469387499754461236
1298851175809645155235466295747374414873802629070083879929564698473830959503772178758829646187790277541084645600524287124711432643678041543667360980
3297284069414747706265211593538017170014533214431859806413863413969129347636849960975151225984267378646262104139072520445454546057593029793299476658
8370537315515854836865405617371973452941273098121257323956360140199054398099625577767130396024790730081542461512253027882371061222219423081134190096
21249577978545153921274407089732942099619595733542846317850167889594931781747794091491536448581538068890927379802463355706778709419738210161287072784
53944513625102167258984668522881171179966473863534571550714893930123544623924911595325860883431913118193500119951812013412101881812407248441910933424
136944392645677680393052551584022296823304126212344180895631266773007973362783010179075685097961588292652032180623117202918473606077445100837427108882
347649193899985242298391031651713025260243281782793069580948345767272226808019880943587149461648717413990752303057184749129964618162447701317236129140
882547723819666664786192236515441243906781463996748204169579605109908242875503753146165483800938323245789496107259443232979451394274709317586791681980
2240449563773050620642046101689145115867407712997928757260508262138468537265406159416679757212682817852449932579338833571793986694531831084575112337900
5687640580031141766652747164689768965851195916636111964593910309735217080028563073417591868201906435661149384947705301314205420547365630502526762890362
14438734033869036687315593091378658700883887613057378104950626279294826975644950840319799432688950577949610395142626568055169876313407952240347403221704
36654397824073922331438780545274006345642133097387870828737636258893059279691719261787588571157286714762409191129245514828142071726758212634184899230312
93051432119596685124845299045614937277217057300616202695449212719043806887881620216796272028501344531954190335227672396710007041680132899828586191461208
236221832399634283304589720163710338809801801486529502803066355707019295463885340349945714202141267773195127647376287988280163894734331950947374137829994
599676467424183128883308070419481198183637338992573047444506490613634913119795433450228594751659601758723427978092056308379227605688821228523898263343484
1522348133232515376457543763620427205778086299454360565932984903462113862671290026428543662421756336714691139771610589314726910989212798771919557318654852
3864656968633725129197369526798011067581060731221424423844299289456502767542281859274449357971050685932393070539880387666361956442014708998820749079797892
9810879101283749036847800160161624489160821184852953387468621760316982729651438244855474565484436109549916692314174129333699443545811705035380190408048514
24906052340794100708058559917097897900111228572232607538204378783236378182164655588852989116819120519293960674142979911679048205602916051753086662601726592
63226897080120764607875524864543449849160064351182633569590387411655830151218913975296572311086768222537659731606157896007498296402638894351211765178609280
160508797607895957687369938769757457587802004208345999864496588158606953975006544497862623082813955950495800497409807744372056073361501191136657223824372608
407470163795728992211221607594567643562862501159445005179233815334369794617773044013467887119647643417028915802060145586734711771868259772504944843210559106
1034410180987802471289490602916661200503120110605449350486484410945878215065286004660920864899568782809268073809870570781877587303257160190333867266314371460
2625969991431391776234560068347486222805521279464279345172033663654937941567323922328348830183891708774140037960647975144487984299930476437755521536579725196
6666328814854826468313028066108917017079359782028913380823065106691499678004680310449466239010439652283254192434326608423633775736000254902305545143191447708
16923247414392560538727416670674051722326384402934931756196462534135488603631209500247256295709172799913281228972268171159223057237215402071959343670124161994
42961622656619792932901259939787626233703565921604580934181472365289978895202417781397668273971010269654058840701764179658615284649827521263352601819786140472
109063052503746445782865857157053008100706702364485477964281773249122873583225217864719265491523378543342311792440059459932897116602015813303768322230017434712
276869184306802182822392428918442082241247127548339167665356631267246227427597532602188821178580871678449433000773437545288212463765256119892628705902550274088
702864475722250231883441468942088979938826912385375061147110326836293732834871874871268093087975652704188653133995733822284211648672104225938048196295687298650
1784302837707231730778837341346743734392438241060062082630551842074124152253690796998872965824037301948245607525359987994937669276320516586317169761756226416524
4529659310749106005462638619897834272280742754158681430188892848535466188905155496400623740958387544491311967109604628003800234039056745198028946826528744316884
11499064529774977191538461413523420135709955293215076071010025358813839444075546369658646048567479259149187276002711201898195595797175571236708765489881117143604
29191706481355953164327966853091110327135346525012765898283843057386656694288894012992061740491634656088695924307907417636400532768495703922779133305602957386578
74106526238470880431586416634780136115521556369198383160840502977404184051172260569499041062025490043441388073927387971056529458329549576509235073699666886843120
188127995690852818814214482768593486886174637956150827406417534200489468791676371922065537248857678425253105411574773001593269024640796163588639829857306198489072
477584695425710469354484326514088445484831650893887965408958413599827831741195023326803679189350546884360782398391218311924991496200875643586900305992621373034832
1212404036237540768638552752148894702838104811486693585207354732703212889657687163371732412492857105188433695396385114102559862657792740165255389257606124326748146
3077827998183267718789231608423559458989045205218059829580631727182506689265583890122440149928725437338524132840330506796839699717035188867016534541182545889430932
7813422673681048854960814550885324919570811369577881726164473626772272963155828432256803303713321669710447197088223578176542410781894902940958686815449403884777564
19835277966679262079577471140834067796928335177512383906484459656102961357268645341341825761487730550605436051462729160053569487178475578929026564504044272267955532
50354149320591627200136660918740561217858307495231105191343957844088668151975466930324110243037510671143151926817629576969104259144463326171192822814228384853352474
127829837225362948568295866625802167649420707811549274572908519474021219781442151568940705551552564541414805695224600824489102370799123193185537935546829052362491816
324510839832231676232670927358302647060272171628113873441700508950786126115453774748102783369918010993615490338247226060985816696312116783796367074529475733780555080
823808333440685257281237737271562574780597479066376469553014600817540316847109564114780583118353860278379724264771123777065199103112028880550450939028197074847344376
2091332821415699597091362256926866669600756193261113242034957138432699114514217841518209432116476124132303969742405127604092931116394508268493752978835915897384167754
5309090467273669304848154000306055362291583709210300950865450980072927830273189413338715169281376511375551213033082651464833729417187963923681211622216103529264405916
13477740750329598965549227967281021561283757018438189320136487544326959381996049156232390819928915561452566407359680536644708739557253003407045394398577120437383013668
34214805125815822603893277158591983082729766547841130527486977372751916512357151020220573697305985757670007025565487244787964274819204947005016157022942813213373848036
86858243639159204126280064508060765233044635907399151035550985012444595242674239367746708128023525739626348409526575387539771501034934481245254432577443576140369079330
220499706496564524834096381399049508871272874582814485436668400661812032576343871876808497180082568383063129268497846842830887802010960813610131602025834641361984233312
559764030770145411678515565464317603604459244903183201209601304147336381995317969604901654041529132291491507712277550507810098796010633699107785149559247929015341942880
1421025792380917287376557041869204677568104733705038201748924416966159555170332355248147459884482335627526584168063131170990394468792525009950340795038220801687288041760
3607438476948155552568232516377006309835626843958212986079265625915812404421287145320227941619881324811536273633212245059478982426619330272141243117720711754821660581986
9157900183614419381366644366962836276469817540102950458673845878131083187768946933803755992105751624678205829446493498288149444000813403979577729128425203896349197595044
23248389767133460704795155248405593421079138545615433687217975478308808456035121417356574601723830360015922545535562774861086162713291052182645048051774637627982482213420
59018728739980366354563691239852051452994763217225380521374035878014318033935894766928352764303883655392710786865751187350503643043762776790113408919996480340707326494716
149825875123946970908552636758966623505043795289433940485915596582299899008825425646282570689463806106272391279542853172906359705939100180258502698804412539899502882808170
380350328377202172498008989867788999350388657462190725098817159842141900361221344925512453696193470427976564871192576669079703816539957213711519848473693969120804651773976
965563339289471014808791026022212736225954517614414003813935416571163771128256873027089917844430616117728413273274920084132205921583880286542463324767994694987182898388280
2451194313825432799151058449501922275595593522791566957375047995540025862995241479379567954466624444534257884516715038347961603707413237416781074357794548728757676661202888
6222640524599350253832233608071658648447362561177014412666248101120395366533379440608573407919186986554291857117137616698934571330853421159482538366982111449147612698442554
15796893326647826248847011052970525374984391790170525457553538520020656817161949438847615342778955100369619221592348046594607642049905513793153818648491024934957017574288300
40102242414132958421865163449102736231898276174726359829503412667773216412528431673180331510307465900897034801658816169975293425268275275358253028640125170005681090121444212
101804184746188301632910940237505128192466204330231308706156454168886981589309244822218314844801092473958982216784768238089894595682067973400629692201062715711738666655782804
258441708191946217865690418875346336747207539990751300568878904734399477735884833553710635432578393535527087450819610339640095329131728891090940342752375833014073091104319986
656084194374650948402319402380467982790535328082683024348617430991047142642493242844344852876922995317547688953483472862104000641140948692059787831275117782375218352851605456
1665545678054950687692062925485721118922451603661132392252183175780892493990666094824854678439708058659128623176695446097283696174449494494858449992292986969360786644721729488
4228180513221499138090294758219190658124024987836359540769999858243967299383858253053196106612906413356257431575503385477585097568599496565055224653832520553155602479593812720
10733725701995543972625766981524233925259090066820369117916010110802024779199947043621122499783961346931203819048250327765169681532947813626798713972453155313296414634032193490
27248805268698835794450317030895874911711862230073875557216271017521246311828771646543272708791242398574212943847600007153046166495336580086050765099260495576557679290660158900
69174246593000711945663641433887557476616306221776902660976745715939500077280386969047252882364302722957447285817389344978545197093819288790446958828055247642757769534918808828
175606832832629506673066677724737587584262181757897177741324013103561410519202281396992002289356073962557170252808981434210428461681015607064453244563557696365193670862687361196
445798274015858309621185771236982774223592341566020778808084985714761353348507740482613087425642229920812013008605791871837024666091944445164497590557158052176083936847924215738
1131710525779673044491627932086561483574188296434355983334080777222287773892688041467658946374059244719397684895042367929290862027853618106963058517684581497373597355642045695112
2872978180518804406825157692631500897903653218706736071462660245382914933521267388075607315903055104078262502587495746078813461661622913178916652686184418954011733012789483908136
7293387697397867790064266384686896802092760528908039729718636086884444118650097659518298351992300311716253519200673625706745026508450189288494880471187242494783686534029898136216
18515108978289856614416778061700655207068043243926860414502516095804903909905861752735106530468234572071048686794859799584372276950530913166061446869931317955019728319202596914218
47002747516117513039803401439598663706088489404690684128851064651835153963962072089823254079489018804137477091711117726353898545622569996658242407827552864488956961036528067979708
119321915774537808135136983925856345120031197458125745698732549566894142443956939754155731831832961233062807021198103546541865053790924354250534601138778298852397738656191017423556
302912496322128796911111480992195604040196047766687178555880832332733229114676397842006057113699791241974724371429396572329527671434377064773926004663986933267453629281062875114308
768978438139388040627306905018607226115345554884171340666027150591389339099248392765412176262555701913871157288627624584619360636155993757898497842820356053216808542120654246030530
1952140784890075571846366205609491633777109299790156231175201931366292005503897773796348257168334082649703626369428952947167945053221462933502020900518682239752685826527580275422272
4955735369189207439260260243197662856824548811273406532269429048816790373420896477193664484466212947876262925594452465465457421089677083607503720078488881018256479217390534310100544
12580707928201918737869750568569290133012821160125470024113088491516119308765768114291207187857682448466165513721936984228341538684919482630988412277038401342852166632875983554098880
31937583463141489251194596117333529938235866898101611991080658368524624692464782028142459006573678329299320783182548618077881390078906200367878720752837556295928728589598529423584834
81077252829198476671454539091019806062625387793697507197023837553814199261123205104276351677098629742428150368989495226628698960401518661716228846803292835480801517836695537610588612
205823992097465301808819029522765754592521415874620704860252243910462199663065334513448871476095464194398874202494666186421935044680687842513742030636672861886012638804226701270249676
522508030855246497196027695561473351566834694700558670156503934683019667772213283293456735481098513663521573090325162574173846768691520090355172725651294683484623022735523402468605788
1326447123710168133917978968103772130131697312461065347630545340447859961040775607433400969566764374560283914630843215686012047096020284742673250539722186976075597015995707661680118538
3367339577765097135281829807375979260274646570367704133050617899994649057560970317531094018820633477801241377406336919374156616600463752642745591316276910430829216317690704263367537912
8548381333337502845816381189359321832271539792131042325909570855429440901322130617855525377288694141590406312096204611158411568900265722432641080291332278308726393260706003746428351000
21701055605640110191556491752824531276395812794775920892815790764635479663456863939199893588566225003326249122833721792267286123578109900755782014861425298210444648147537524098700146536
55090641846135199938100065237719519826917109345539583518980032780588402975476824086482050863635335708791112029678022183789094198851844025834028258212683519152759247197101354825202037786
139853971814640711702962181409745437802357411266736628304823123279583532532784085133183932168646366618855151058237415649170094123659840160957083976881829988539784220485556454618315204556
355035497443609105744827890978640174538028955427131624187884301446502352590930221178787704264719648790230434242259636692542215966767414294503301520757508697272924032330946574436062542612
901298710429869345210936506054156716303334327491433258840270574655630443959931828390179064728027584403915195664471782108113717906728930760008496493714735631530342659386340872557051565300
2288051113963810678443704496483822425904928852649196092965643538425686931011632752958047724511837068859372069726666028486760773698524853812943456333393512199679724189660563339574799844498
5808482625714782547522588404528423373142825860693732083540882746549213577294052805472062102118936375564968813355993763453834645400632580717854386589583308256414069853917471730009892938928
14745505555941056867255540680894818340026869727130121459520395722085042481282437681258649228070211368831081809078635656357505618351624421836081994379281678346399826800714334968491344978864
37433172845813926817879785683932995290832867797840748159031540435072768699089647295935506276082648935477272301080398564757272698014193228241994345764657684437798687589328827590409927711888
95028442666044212953669180417082602941338752181203471162987750359642882137167697096402234528579684926346142663332746943808648115628894992533387363442105621255248613261911944997357559348146
241240702537548948356109439244769983157432326364521927808538672891810430287243866227630245255303181361549635124025013467870665035983560178596453816244546562949709017954970346968562177101268
612417450271499525851053208636733999955903291222899423084510161354846129931926269737452596243670646073668092781633359350201586525548148307611775662223270677880717714055821263719510962453916
1554692593131822449324866720612775755634826598610276507619153708209100124863094525033296720216870933953220442785731650313284479589819820215591678575816080923588154925087088158971841088125964
3946767124397590266593290160426562147807933879118511476953238143703914531152721554182640376939056482257023943550012739335039450274397711681747388207031715698293575855637790096442937306305370
10019325237053375328490316784049977790131146699376299050784302054008147482455023485184599247079816721634702222232247074064115351713322327358051036057493598450951735151293084330359097041056104
25435216986909785817368533656364262364564411250991967463321283140360769907421227298405338403847675185950679538774689685521942231321348585956025267039641737129195029877743393799379897480924936
64570242792262964207855987280588131769410074741109786581923847809539105842310152983847891268193741784609936077699579690815320745110366223480249508356023320687294533271884464225563955519477304
163919036208636339660061698466231394835494612464569421465874895935487371065705435148319901226862256980108850732034057343881334699711182675838194866883374634429369231852307337485612449224997642
416127449265032411429588620964960506270811698608750780219739223263339561483643745152709507429496463879170916764150141772413541778713722954082889252457006034425889205644189900153952111568156124
1056387702349721359580957197957571801038356883915412797670701825918936423321499281932768373180177633335290342375743928536481053697950427398837694489008356433465122838326968940627381108028277860
2681762473604497826908824228193189956716758014860298099431056154303116333321185336858163850033817422253314752893419605620841842299016301577645027257519998987610580157509587470817005496262349988
6807964489587009889780447308837833897804101012798489655229912409852913761383787182424765332795859440398977207742060842113700043136217194720637859855026073407728996812237040360066481434669941090
17282805970948605125646217299111864613235815986095500694200272699737526904250590219853031126728494922513174153283623180168535205253279860752973274499532437958174797468483507680666163757376182560
43874403676211955736616637957470588909684674851982797297668959736493585087947883412772033592161251514652963558640272761859267865878911935190769908683085381190051551084748890080458660499595825184
111380252788751599771873640123682429206949537665419914772709696207059512794950558237258762622221591415787635761257089805449047898290965504023855673912703490468605283639500302272933691140866483296
282751665477616910655468568872920140904600894075412912407586678897484055718679490042780295508104555456253827540969539616393261160969412351643942476047538940808693071323768409705518857200842192930
717797835151261714507097359377375827016967329763795560459455103435837493755614919954387080203058285637290173640456336500134617592016211701707029757053846538132668405225523151476653939441601884644
1822212899356466006518001214210697666338922047199559913486333131989017658446635586932589259770043750870165694398977845384016929575268229033845003027060449358135563936904331407898936871502751013740
4625898390848973220511133649553989134109526503441305037849112809261801705762092591925650851552216553518191716758186374340965619910921022271840036290046217401387683825251672601613077598627887894204
11743378575585971935699543577647542087767563335829551694159568354527447796624906007850486357746508592958388302574385306066089124949315491559599961596153179383589851785184730125776239918578916239530
29811925969308220013892449385359042938093302913906389197504151167036301181636340945641482979260421076850118823507644006546210248161952781296897019475331741391816611752289665790457415230849708124632
75681025207446903464679719841115889449841601539788831621115546556592912203444944310065226230679469983450796513046663721926684435975962730203158892589937856106173123361349778037140091973104223953656
192125043593187276306256384947208769734444208739172643286769371547465332882674851087638096555938981488203245784718031219154576738288121062152751937228279053630187450482161100005255612169377919571720
487731664238237891449786854383578774580152578065939723114921102228571335605591814911974165972462569382566235251088487175136190977153577513677627582281923516072677775967627154629652817741843787041018
1238163291217264748596619488364702352667603673444553458758654005605923813751279784324735555574704582851487487869027353351274376807093424472551338273315861168585200817929166618985994091107084673442796
3143220848932077630944979635443260604476465687082429908794727019130652545151838440608208476213135811475151751183842282336438666527893724578355586729328949118161555410190615125257922685332205305777844
7979429995415396252489880923795977134862277773661259932163689216563475379477727671129577828186694631376349253388280328244308281453955264136611346777954052594978344354786470279233783529564270303930964
20256706770498656161126268996132649547922432152664212487514445562404979557362164469738075663622714289382593268657279001634081333326664705998508818050216204605182075670063464725641077065320625659573042
51423995125181214313938960057335434509284092151930638480525469525281528597127387184843625586767250801419069029592461448435176273312545915586080494470998477332582930047247806378219869910212465988895120
130545764649461026076095675894787474449164958748949611980547178761376718095175486407512455320619676730325777840906762525986337316898404439474311518215850207803734878135240216774512249577269847994852240
331405536003702564710306614835776495955915515270093335879280094665070009649359145916365588315715121116100856457072170273819172795222526562260377736051219013657249809379635587133415868373887646952279600
841311317826463409106052930342589721339515195886888831246118053364735377852176654747806911762757808379397723805430221704374749010943434878295726337642357692861985590605319459785057573147210683576046482
2135766173486591109794466698624492920201815596967995748770227408062138867409848015698163715102473756331764673872783720352850345251847659917749665605426451474763583973746677466666142253797869431055842804
5421889675268164934456521704157399765619995513918532100254677912284985189320506535466722532419652563920448860283190306092798180252035540907044339932251030515740374388079962895410080166719654783354071612
13764094597860287835000177559714382424920507345269371371436854628629847367405714938750524259834452144861732477158159779756366725781102058455256936136121467608941195351822277391715745563114514708620015468
34941747517110186728430518060837168262016889720326704277088728319070122756484923571785973066066019713280231050942562952697003870573523313767398947263534450992697957122916445100704424525219810805412535034
88703671052891210367742814531412794762836618700323082845312037478892108736550111965837713302064112344774794009507848573073995177457027322548972752540236227646561140147064196660686322097027210892412800584
225184537619550383456802831769228560965485997664679363602182500250949753440579147733213046749011012390307034026867693798122062824750932696629273867267549452576376178224396691634760082284984668761764711912
571657016908523102027230434039322757357531960634620855712248473450173326208694387193280098229852662188464926448024118616754474989049975469276952281224623926069419917848911163781199705276698652406149970392
1451217514467474736961011420615114215382379568918280977215326600763532064581931769493096836419665144181274563981710490636302089143261285000481905739167408752991167868975403762611251355454532031356416298474
3684083658565786121430620860301829618311687682476768021496097185404403383436644129872165489103077700303639706815241679482942997792577682868808141058789202680614984357346900666176068278989519240894015914492
9352472849869025896185606525524470713638556579185535649600533125686473997060342172077177501334791376983205722724723796803103286718328917496655462900731524467649840795171183221646999940619689908450329197060
23742335004843197663337662364461694990493261346122666243474855894104863958038803452105772406266260528399606657564534089916242865724340606199240348721931260716616734484934271414204833433586052888382007596548
60272665906760349613146307479983786387022640054581148720373910269537401207906934758114665673415613554339619910929742905109108398443444966654657246866914573760294349714492511701962781545886979143233058056706
153009139782034828882027347498143850946066377325513326649992563261315985721207436206158686645797243111815681398354348075927438952691490993583292406435017822699137471165858100455217298356696203487223488826880
388431414217772987559857591752856355398830068647129153903383768399183519939211477196412337327227983652494595026163837579043712257539519625574074072060733795953280013586003864707597492878613949392599407771136
986078111190938131320814925906494534906240873182245329909479698676029072863062760741018489005485486948340919684741419589640328489299471911204658811979605350500863004559673178335908852812432400361561684679168
2503273437160112929610436647802397865105031769062303463046115717897330615370040538220658945047248068532379286536031561090622311986738446053045538202077557221270305443674130396878540876214587271677108265303554
6354849408048590975624815311410215940170951524520352604754415859609668322308991079736688880096808386768266903787572634278365295389688287670935538290427875374334914340461457521468921770653507648779364573250052
16132520882253304535388731658365094896138314909447950629685487526061123249571149191629071009604369920357105136303889389137738270031794043251126909433112388286161993572737833344730705080989938989582421715520012
40954271817474503294127035569852320477314710202994244872697055034222950985883262227031220378313345964134326426795602344240602835358787241649238477854905018228954067943609994116978080803670151133730917731612188
103967160020518546637392340481416796731669178944905989258302369119246142441660881216067863960689063063978708605159869759290573931988524440511905236197256619502832599795446870277358269104227752220745058013067850
263932671319528081767886104097218260565862100001424919607382289114425608678254979582676715538892886602280126695090738063065242290020723565490969147528526374265584262673099519620680211424469436378566472631570104
670023639927397554757691549675930568536571452396121278615660693924958723517636346335055789252141577324606122883213900345368165043332715571958398721174868339365087582622610624906851504531044013920743647541571544
1700932574270288683070497662153316385218843457108274662802178282874499330494344151630360502039004147689949408373085139642526269638088616635524163742867181206484632558944136542617324974506241547290861042051759784
4318014245776834858757998555945474183110774797950848032879215744489311033109111917981547015465194739888529517727576473608948958714789741724495091869224302962671104357582742166084350804329860001886821491936590298
10961779031558980055909495440942938260151955705327427753738848955992128888849894426136380172043007507110025733129986163875279368909112009141612682929361758033846882930481635687210328760034584506892444245525127180
27827745046058450017951684219146122684624345544736123526247433529138839906446960731310189160190537775941817807852168896028772281014958984033125620832612627919431797040863093246261560684247449936897553038361486932
70643952237951479113276859870440489908549896361333681157016311764157814854869830630560405135575705234016577454882242312232731652056651119536010587528367347187699783786468110077392402254410590431097212625951807412
179337850750678733009396095853232822849155347199435601891929008419098362778042905789449975262911665745585268576936426562381398087039785930579542142732460737109240500151281877438971619161576771724091464329512924626
455269894916702504265352038449997318406313751737393746799134622264226804341781445803536762648636673914430082181062986121045994285072068141306466901785792670788863856724255424227415250223514408943474692079731617392
1155755331904917966340894233084725425378462750695727458594342071367473544436356002656162854712135806627939364414086509638418093721125364888733122534812384749340240943219001476424250494945608630409835440604946956144
2934018704379834954306977211233420331779792206828704888160111682189361786855058915971059689331297334827584933491308380706398111490371945318456105175259800713227428383370418156502780654269503125689534549336283105232
7448346133486779565774434907589529700353037758773512801802567271004315416677309851436821538052504600827773700025600235009921819939890270062345063759305246320666851439881610294838203417144771466035882060052509812594
18908488906840095611746387809926446531915048181550374209535808385916634122533806975306973507991968931969268620386707198276849669703345769125442559701291117239896941616790309374060882403160846331574637029647423540756
48001388003798998412768585245649837226355050217686091704950870020830649049148471824201633568138488202566854138256084614799164850026853552627396159105485510444012970289822004501216860827017837974251804521332247452380
121857080258684463871788053507206928447613913487754611113528333953675297296864996812114630765487202402244283050725691536838583511070990048699443415270202563439713549316831825317381860280337328805270653531190605466316
309348304844773512911394936793450167984460868806554170019689358448182939863636633173455403189319947946511510837215738141731719202728885934465139093108099159608326007419608651183913880825533412361931524105803368568474
785316483106158052352575197919940964943354512334795753066069453147971810345240123298043774281329293224347148119757397325819125397249390630199815258246923542447950114510027253374218642960866652717475383260970876705576
1993616803388293201197132747658018246186757985524876715649411825305789554873171991142970726978462565739795605950750972476223687027841426584558418031275125787677138115515430162982718187839143310522524312192499527067848
5061027043558039945148414071076225014738917171593991208505112173964832148006415959347232826906431024437506769517310954857460769955794852609285631808098102904473237994528529355663427760229290430561406996226524675876216
12848003032525123700897338178422054759949102158374698512196598450693482724932332287557774962396448541852421965533824798157462382375502663061753608255360709459013177998487473181727768491040667589094843374421910021045450
32616143028495898942049814201600464021945877201222421763170667051853022446476392634822117898930163294324613406320526958403218056004161568803161459322614296694066505869511172002191174769822496070984927500172841216413212
82799854838314258596794609365550605780498882361531134849373718482469135601677789917208290795818824189218852810624832575882663023875580185095817289571028932284890029862455661819493749189106889769559252068928952650232740
210197016712128107621042584848534255099730231980351707409200686341222182794450116488292500291611508907819595272340380427114298164964273034283735913084663141944359953461487250635577738696006726933460079385586292367077220
533609460076418058252472098203390848476515576439695539503004073994370074624235359828915121339396788147280091318823196887344948648046885964214537094921516264529380132907350954087488394721622908853163651283106717622838946
1354629386928959713495489961574349459613439729318254645888832750758099266080491765434820779569309109026086280967398016435556385634275319195608072896192915245071766618882276257809335943226867988105113884699700955895780064
3438883515424813586850633559223962711760949029916728090814645995304963451422231807468095092030007600720312406838386498367456735258591444436173565445630565667598463626518735584341986947694075229819194165263371714953316320
8730003901266838591808345430038376900895476597570926101810150030478607468551426542636294000811451352106056788246263016258450642654604028369417938406888592438226060178448809026763246731094647345075748876745518198819592096
22162125519601802988579450153579371154562487372778494632974930624045313382410568529168051747883696475747845919553326193268046933205887193184181399007574001986034894505077887660679283865845332082432821965901484633377095650
56261121197816615700569814010361920147007469610183639933829702069196014065160018294107322092899589563293266882889803438753638066838074873430459616833856972758396748732898198464010423241718676383483867239466963190382522916
142825369147727973781532471027029791513109909800699145020803611320830403409460552368746254771973676974590424435232119729893925450037307520926619720314715330280009629745573289780194907700632797471501074822509230964833369260
362578733553152411578854015197663057912005260673779506745126915562440815652971430810007344234790591476377747585383456967017483809993594430715213814688885194542969028125236010193815340884106930890179989068894937242497185148
920448088525729342308212794582241229710777889101368518297176580252195723376954498298460605575613054251097656195004872709583589319591541349606929235347061106115198712780900090680678934551887436038827215269775894667273158634
2336664027060124175911638491516110912366353949559081399976829471056808285306090771773550712169759527069063225573202223332167933425933731392221506276276318913514712971054023820652609158712441815298496126271790165080256471960
5931892133213130187063527012828407959843363065774039968078561882813956789469608230892754201793137656662156692800879397879362003321100664143153063114183704980453894941164949092059140412461077438365787779767851475974898260152
15058794877048202452912759434722218342909883513137285206261556462799579518450460439545695961009358850436622271943536953970910178664879302802250494124914810770249787427001381654255956614127370566141093370608626430018260332104
38228494054928146270437508706651272010484563147805856067023754329365651768604910295628259506841087014310529134537433129745792086439684012455971031160991454780493137507005513942005654670303899814455597263479151376493077399226
97047457624586561248485120748606275699468521139897284010390327289759357280477615780335953244284375943239052652933383595006848456992859033622358430619721440054092772956737916829057550902652827699760301834911642826153135414316
246366205738146140319083267053899066693929764614905749710383612195464815850733739503729787782025345870888075723855438939442822732856428150695310998425779873109126141014649047325673638330119791334515399235332187021230803223028
625429133492657313047174517626430359108737328727131640513761926774516622243663350416420658999946628450069820756446315763378668385484085646525647289893934527535701340355764282079707025739064809005781300984137983371799982808340
1587724257267361930505982836570097572216881707552086068494534177689809813396443858575257246582216283769748216789274175345375077409134993539653170746560977375961962554334356339094651881003367445095528394032596206510248378633330
4030621827668332767716633295033864004962847064468521202606215311827482596859224554756232188844559508641098976296663487933628694580518161104589372506677985500831168280307681064526428087727277753233348893397715648547788251851600
10232200108624220910669966495008961502835912651201857010884358737681016391874743865333867340635683673792442820382838133970693029941194566146129102925115836571623985129587195290408419524313280569980707372127679930393704098576208
25975624491543040808808408424571886230272493344963715930505841670411894972918712473446105224796000425777656980536901208881271962610639553068656256660359623920522083051476804313760098487813446565242837043969736728234287926397296
65942129802265219834029466085664065028507999570946189546062504370220667349264907426622737999756465465627749866035425885182047673351766909760045144904155927358591762355846993418378831729802266209075919439431998226670655924877138
167401730198036412232052449325487843516852007593884618133974189917730574457476976624226183956678123943867027028675641408118881906622941954469733969785477414915810888835780885947987449474332142161909447115945825697570267757248052
424968671126141403425216980468169006133010940290936040509946063972759710059521087020139500803912861641226682648731170302810008264669333188468374818983663273279385121409889345395620784956955204181465766394943854322406975610031996
1078832167535368232455288335840557455472982389972712654126221340710951129308385024908931998746465040664709576603279672860374956958491656019424783544390329145593730578831123280164218903890783606833841425186885100314847462811203116
2738740346729211667130935200052141301206790644910474342550448933902181197170123178036313369187156022189766214312705829395314214306427861416606893932081185935273201385166310472642083310476615603915871408371198256106038997252851258
6952609416474913404554065560174547344610376196778386530467422611198475807295451208474437918216094526370365243563184305313877207907123310449596339284761181030090904574010869700769350308295220155298403581442224829894529236665292808
17650003862463655081884641829240431386821379843723232478293246472752171460373899810223778078117483877432070445193952094000442938774788364882025274163887738912820135882102003131890050214719059508942332895648019825693848517823913896
44806578031954081871070832714566232315922913181155001986546661640807883270306840706232737253039309803890048525492140812698386821709459283849454222577525797160869408720724248000198853328966111727483571562624977899279524977283914008
113746685302614858763933753167316374017474624301110170211295419938625339043940701794000468195068554332093273668558523032165219319460676537980373208845385896022470481442797073335281189781256517766170873162032744046263727514137921450
288759128360685484510793953665458897237762691473862265969565092824560577515042736588493292658196855043472868741276607807040203612697818224345200653802809089571130413136849506107949336099302360124722627239461629069593337183861135932
733048475125156177889198390065658509265450185031358100866920948717508238037727095162745825278569683020784258213879932147014515159672859321834264554305226115778283107599946666017953395317904591835762190573386810258848927959254200644
1860928414398407689143188013842168297287399417589375395236927904847694836287965100620710036736435277268217755098688174656477385727529461300247638221102824415814755487308722445581441936600866980116111460864256368463636600235238744260
4724182207628371623807118653652052192647648446594852630479862941419910332665239620183925606908684764823151562811141521025068613868469681333453777452055868780066286844986436284318173181420194941420472921558395843352048109535401539394
11992883422163931754633010508522582858576958049779602115669304887924754439345997987872272929391297573184642988133176134876103172485350384848079502891509743249776648862527273633871272781505617019526367010937992432183264900806633301952
30445322905912947556483080686730592017139864342601516802691400797711448109484272110033722824405663804499937849905138894636403316412254069084405548799230801343834643548009921611233961447967794553497219133837650624402201748172846394816
77288976655295423063761133097044413663425747309161907970998613393280279268618026056064850330512988502991076305553035191631353135785799006498310186698472176042904766618410240367155564032707300243322337907298750794930473679123395059008
196207014485717249355029525204156897836624955650562497946521281547553856210177839976636526057963394233435893897461137423808375173293875062802726242664442337053991809452772212973354678579759150496006852981955213817650869162514617843138
498094219892363381479248165737464021824398635284025380345326293174170129177969185833207580057532735437038707694351243576482753157820190385281341264018877166755900513908872337092423835110502929391190310521770620408541547087736966316612
1264469838351483363097516196375883604012335551593453457444389323454598860348542271617592234394371946139466988422423830511955953707068786952255920188768925456877809757034478541008479860763077353841246870326691817486926086890429224596300
3210003064171554413507230806915425869663644209762994587657387283555710545901285261004391427118395563189130680744180908520892016518976003555967380606945192749202341689599567570622253598620349565716182993640313198950564003310426541198556
8148964379747066039606027200311847801539787207795407827459421909219832410353894533554188688968432942016553816841968128336538809309743075308686645306054924415702493674903119762049973927125607130828485959872424005875547955388752216799626
20687089431026637561510731787440244156206590367213923295690166031816058320991244231715183343442445853569473726021801656267432497401120774210077552712481260582809951728845289920419919165076261614798034476893861395086913290705236033120376
52516571331555781738316572558049215780177802282086126528428790638414959231236249280147553444979338410933260712661601582678114534090844478877849555011950909955498017185332162764703758847926115713661921756578636221510720572457552642039192
133319395829842260933949785097270650139352855092772278580976456805578080829648483217621487626025098208161491924427051129738908460883420359114448305443699684994413292168148233416769661770373889960979123540840460420394735818858499457918440
338446719840489876261117278936071091328187921223084371454889584733573795890140871065661904144092414473067111638975670240635719804456031202873127260792393593149905208924173332284156976833573095250514507600922894499512634156610384350474138
859186178108579348475011714738025295530932538434754970310564667833289893298097454237986859993718794394160159427504041231660459959898334940429529575160765996960450919542824095792865678677118000610461453247263298791880212096727898365827148
2181143575570009709342674989711700689219713011412220252897384382160986175948415933452202106468551559729064818996766922267792657141032736047254266616030870720187383689783030552085209746328560527513655596371270101963506941441417119158804884
5537085463506040624047088636124580436984268112340553982087095387326982627542393516466675612262380977508477225495017637647373703053833499928735786166242185932990272092971510864604606558114584755708184207576061472932143774581927765806234228
14056532441775431846090621101132582752674285091859122900802719788042931616275564862427443621618519900159830881767536707607647520274391833273994173675016974905584314935347607974078058228365627660473271209001059446707053642009844357548898066
35684134837531504870065081209828950296408612924009668230295426254251146029037182345121821114818417430272646735959078887206117592334283529251380916025617346233734857596615000668987775758980421777946061093658964934143261162397437906758481968
90588307207171801893559902339385605913416972818468694550919485692095176211489123315617380354817664265577065603459962836600575476250716461240532873684815141132845184567765226109007664604791489892935951786539195917799849001092126116161096496
229968904669361790459115813532288527351286869413579033742911479703933763876043875113090191308297504568888240140798027670045464799675049814364575018237073210854981726551036748472439370828927152776525667549970264283404256817541367096547595024
583802686519779606811311890424822948689264743707935243027873798071598519733267197029598944718212022708545148898365359946487492887457357325981448125467558986413768421979721555798996577577842069443504387694702049980828742954481954969449317170
1482050702801470695623800684445280690550677893530100832670027010421125360824681079999265332458202143453985293607365928447070882014097664887462361456065251458505544785522601156993844343362935886432134268009925201627009562704259829806430113364
3762357276510948825845553425015015829690728508467382778460898143269675409575297927147165552091050987452861470333326484283626395680010661259399002000276289609261508146470337154749810764828493096091161928095853170566667946683492961474824767516
9551179490254641619775200251603235670455570185992675769949014190942338265209467495346754070970379720965491470225452133238465034412976987456124405679985037373561550746577470260361756432056100978936109284372122908709101789684083039720158722444
24246774814448019106805217874770764567880506345567850674507644445653375147653435882018907525924669152637280442801190738096528589045237324982103540573859710035048796637030134072034442284621158446633778276610803805278349090281114297746556070362
61553244759184894497093530087163249507841373939716388164661547997073201367399891980436257422066197915753806178993998702549805337570504967245120249963202167057203223259797135512286620247060468545389585533784072288468575429267668581790210163944
156260037443267492794092648845676572640223348707050508916901254646838151909263018661363987306132025682304051773472801099099364180085541270801597771714429969046642446446969935802668422964079545122265670980141359540642313406412892641108039791240
396684194266263377988537122367741350830824002788390768584059330587458294523228417014909428475517488611806646489556670260343746891634594813585353367887529889511155296886051344746202958285093811420979065759001378956374181280482976890023546492088
1007028748715139971677877700127280112494292461457017629347105718920099865277836523273693224245091301909351064610872136051883140057344499559265765319851375093036237836783478424145203964288846934442344080687328136222374187605537516196429308309130
2556459055835456608241737877385853030877627605016432166193189137718513217151003735234913588251019727593461124832906009128804850875357611171344162082012152194058704597704916801689763619466782870027504536466160383564680686388482869472479840183900
6489867258011933896656249559136460157722415476077168562829372306749147727720486701648758755347319107464315137681915750939787852262220573104850745839666424764214216721651657697980197673905151531220004773769115641202003698833487710198879243793124
16475279324530764444428756595157807503042325242061556967934970781682580453710536244234867667182012554908657042297455918293762873052101964247443638571541933619984522262032243495795717616451268745031309524854897156044994576513349103839883097827876
41824403802129623437364414253944109372268518687701604358489413620346529793837874944571118892801715171468373174903803456261374888935274351921166209978243787473316306608741447208317507306068121746889963605003032963587009365522245405328994311183330
106176090793132364578515580457316766466054484512388417693383213328278438256806852709549369197523836965418891283871593256359504670325669097298862367502250744852231928895948982813955818116695260791430041248643789340424681172792696467412476170620064
269540297799474381039558725791342596828283771392134098730704684640633922921588869521419999601634398271421529970637797339594021224679903543050020623657571622175341643206968030750935413286529379117797395431352965937135395622436673248002054011744160
684259248905485008805848540584588315347181799675703381099131939478814243222826230817031367479895052685652753201508630197678064885192698541102877200934699092728499053250383376208943165810764305069706255674842341783991129435927597724010954840189664
1737071315625783673971147786091172400791090691798599728631396235202685985569054370202375114660812943154779156951453472018086537768029140325629237124158283727576533841731546295500163029267264968539037183320106069724990697136665394414530059673810850
4409756624256720968053390782226153005086031924676726439693030193410011049997390315705522334275671032103439651648520203008700667527409539744663049770373073141111614432445872264730297381699695049773322128375834680484117543073105334248490397175132772
11194677679753513647476938781256816777888165404991379673181293662908399507608825779703152162514812243416553640767567886997812302045171866601428840010850887174094640085061038398793969903598920805603103507473549782787369617170122935126021058029252076
28418985225674386891924212095368183079713395075414716149584987181710263387297149681229630131739235717416081024130777866174530928494297230582028182515066052267987940404801112112257151677873466078744483160733399128876984055649053347643973745901337660
72144883877968142816666667974888866105822147803257338494777897537619989675386224660656895034617566800613169183451104572345371663792148255203217182635246016329518465956564102788141811428812648637687566262982334532085462956628807291457538873184724778
183148139472034753090281273360226617820380786872038076382056212306253718160146487440072268341959651581328832785277149306052881248009956778112296100049295435987935146985054225267940283787874082871431213960860202436834272333288580742199473519288753496
464942753928410531677524397260751418470867244604752777127679538987235288404079950618702218652190777572468395529962519911445256268660787472068399040349801687273025985158695470286443856981225451666351697633691825462872872085706792307152098351173533304
1180311004270628670794202217387546523450565162422481746179500694693448297164977576477464814050804960423784199287707907156480062634251489220536984098042768266130873272779172297644741810358447237878935173823872785864120346980382184863432039740456461704
2996356121331977041579557350551031514307925388113650232345025940286479724493208303972846423756689739630460693248237660096090246973596788084189391259321795051161446687862191188114632578532409861985398881256391152312403356422229600148226868017867207802
7606596882820425114482751614715879856395627398734796479175750404291639184668358347103290306652567496544881826797243243988302987926384936443428248734078818696026523097950390256213801347607137379267395928854004427864135934967098566151213092333589025900
19310226753691957502213737893019481112976842493456682707810230838756576512397258099816046051369095329075585037045508513767271600800121258086229710831065492649387219011225513763653828088543425458414070970206737414087710760903598755179167939573173077300
49021246034631439821028066531756205433579654170578139655461411300216920242309793862370444682580751132403796540476736102475448746140070302111474120709687800854635464115406597961150735525594753189271071209432574165143007025877317627227740367518246252500
124446107932337921459097662970670644894629663918713702000536809409650194864570595534139247278351247669499460194698240404604924965001210035592740556872670744667153766745225634125296157111594492398820891382827005455045567060049865232659617297533527815602
315920851309375232670306734833530618286860578590405114375551730146512716373634620940490582125778374442200225223056179230614507208608703095679398182236664924440830546796763826901799930444898777638623179172959688840065862585014266775567592543290791007504
802001653167855386118966400437909596608798019170538036149064487350648558504188103324334815494466837287667362791600875579255238455739806916407558947630361229156084917864391239895544532150340459154760069662914977674024555999277227517178106886185318218512
2035974039124416834481379011133295345435637521855037036703620227475239080268814051323742745366368679253140052180394364913005090144834670255099907266698398618714158859947265463305247346492884241978395786115527896283232710074360575747399904631403409073328
5168555789898131897319175016446019292409779588789053618954802778768400039663305662949313204748465531866713839692576362927896567748932758187248876621056860591525980228775011386723280053508246339387886244593793375689428374037296938210680455246129400384274
13120977203018761924033481989116340700760098761537510353394268767932493839229497842837932851366513122106573283385795883753907346084663946147561848062486460886608938888512535047167765666146479022061667101265772277437338918809774839657372098525985773485684
33309119560752809359861522389296038892077279676113591907439967125801958155752167012251341436991686786727961504587556639116852885833263875075829193781320206947997605432544953181067141278474022698097075189150990491361093721544699631758483405167608847811772
84559055986871295607633037735066015946290835219579134320462486457407342990905532435603664912585837433188781948741946684798732418482824796327384237712198013104875287044512219146328501128717395003520107877761466682501241242708715642157750001526333850899692
214662952479108817984241331286937447567625811857099485367971172409322014654519708872983460201170487727487054179579991243251252484211782208698552043483120378924053887405864285947179033535598123698498918175887163168539420464924577806728403071582043250835834
544946755013473370388059175254531189944438833562667565915381652249787292818575646435509500204895789870002322530854558461620171379807350206047776022890482831048472076924175638872048552437829471029905568830261050996796474890986962473912711434407522281333192
1383410422572174594889196460002101282023624900076489425833220643529205887120131812758029932423952567115329151027972762679262235776905879111913716851104130600683298960003600364526865310967894422147865833445924485457030401947950348908725212414094072210350440
3511947506199949590193661645674456064747166678783694147081724733196749673559281033076715609767941575948877620707236606480061041763485719014853265898735184118720309586088335654049798160868968933962065076078358213253076153990734182793976791555365436332595288
8915485299996410447373839192130989761220331302452131499367098621361658550376194107671455544175167194115895952588289612638657464805380278050136965497380784155634326825741385045356408872333665893858549599563930458595159582560319716264306988141686015774060906
22632991522261844255744667930861220277832184995881340007146587074308191966449262302415791943243208195768891167065961471340532712963727586112200805112914158178391146980576416308630731996907310282375403253222989423779207144097194062773029846000322282073944700
57456469054688784820738887414637609230634324139176044144697142568475407573652482566779093687724820194987148148922001717677520507788150169406882726274223647031293627400462531764401550727711908906691641386863047823699611547281509541395445297587379795241171076
145859898060108386848413093952410135559239522343994199452034986776040631653010382556123575783353663969229164347506583759238852553656480673952746397678249226226821204696683461709401545865440075524379055157122571791020394371627501958602313102447397559414705028
370282236485067065274188466064504038785303654277029938678538183161777353070803399748645210599845719131010738611313537623790338161767186792544993603176498214315081697058880539375701138064823014191249136181089190840476757132183954590713764096210596160937923714
940004322503235178859470013135414350505649889959577527978898641812993346266771861778395177334192334006274400786862200802043873128234762180293915354273961745199609695690779354950032998402009671900248503155920419039374287057157088078614293648141550132296860032
2386309790911076499391229657909654116694062367924402578555500818965935542942782240508612717989093598531099098250260311050868237980479086767179207845818645113607034003506415396997066731930497130040928809746637124001360911182708590962846934581396877262881328512
6057923651918597612801435503913538992388056729557894535163757542010343703930511787632848945230234090781954685199124532217482398447549804983809005591510466515209945208973311886852198730400807651024235408600059276191537276586990950860097241369103060027895234688
15378740477137944931940578763440061555938242069322469110159257621488349154283847732474778182370116429744569503936358822556403864761355445933933589769286797981549820730636776397174166065923413232521080566562641153147524558557268862079373528700927370477897330050
39040712998794167269561039232023307213770122751871499661513927330878507976809926420976423996556706177997124582557308288248079923585087090481420690384231200511505073567898125129008629127189457178909022833988047029714776134980259532031861964625408656618119332484
99109369438938105676791594641009313671334678551196551051574355639678962397269306972145319185382270632450577900839345468224871017778264549630269756969833709069296932182629594675658259657354622650852664793647894937342887745083783477465123438495862811399124184204
251600607573107253641625545723098657650721175197049057741021808240148586143521283108926778944367954852188220644119714400050576551651542193339322720761066689713714315248755198701837644167642140845505449530746660904011815919600539245695320990209791255106587607964
638717268503640329029652781027609389772509704062070687372323730719386430282245175052666126448757155043027917428739861982611139156450794750910277164462625194524562168457610112894148715461538025867419263547375658776427379617965395244336538456861418190253082249418
1621457726274413121258534503451420774717562524167717887785056293970590616033804228799871596412042384703528244926597770117121769304233231879720080946891947550849464176615369558969664829070840545303053119402936896515907391719944561557165333981776101924539210678840
4116258143848830498969915072152872327350036784616675585884290788539335882742325548459367207018245440421186461323275180867589534835843233424212340538156845820389920991831078540999610060386827483300786531632779683713988798581702618589078226335351320530770534824792
10449597810812313836039219134876466082240900384641694630335068511821228723131290487522072132907429295015561798286385892404250906518902883299383611361933403043143360315226431172852089992159902146318346224507428503810949437286964109049509364710741799785219914116392
26527513725277102756530852188183444659519258994243375344240929743499334409961868789415801613476021856509467946794866468292048483257476564438662019070859227819892196429341890422658219162413316194499578537021918240794489067915409727407181052585495454973155558774106
67343164510755585308458847005265497603537807712704506665168471227533045116735471685756884675142453806911214812442552129774541479185305660507386660736163517636140735682089855667991063017443622260337329579196071018298806804961286997292389715903547970379749086810252
170958418994289578956870875189297824688982369429229050344032955706961637489874425523760595518440338177231428383225340592192267646683601916717542477428335530646169064584241708376593994435780900100337910315053901194278681669761167849889201033891954571666139997760724
433997737370348436853636959147636221348242736680022057960256062893811925116427347327725429293120969550281912296032438399753772191741764908871917849549213043967978567989205778416705766573782314478669668938963536447376948250901054348598328759130755973930686965710132
1101753497433041963760628826851520541526893855787336578622482024489980369389094471120874081886313729697713719680425320192635045201737598894602809351553629341775905990212057152673275615146652500831840077886664651487508135299317280129797461206823820605407311312095314
2796928796128957228623248668624983373975846253788963679142578734581194359148030257535434715997131175948439621998907388130167640972776829434021756108085177227831571722916132301094765837586751452680681002600344644499511610565875620254305567580028791985723465646899696
7100327531377591090017351947847033212997977115221785449953642348061687244331269188180927332699088210368974287149825880438290095612228928756222837697607522581925167354862209059079265366755024178168040733411145420273564276898344859920898601089335667806066319984330480
18025003397517361146613580538388628312242101763126847158907734179199614393296837296518701362912932282789682291232648335151399154958278083500155486757827353979929644743121774193418216944964028574512432985188614363018512452580707454439411743684212034346695635603979856
45758557762965031979775996462072876844055359104906674438060077609850194926349246925449262041116092364118147632447558975111678264397197964539315946046253028009822386740347759055478708563411255100831425509885494929072638373125670668341807015593861640939484291194916594
116163396054338561301367698773853927260574813759412435973170917616557438509777660325109506858657004049026150895059670247779742288459271068000518946321030896043485299980130780680730086120827270447032316525926272388134684708181942145974945883957504806945950679276031636
294894228370950055359077581342923384797774119317606311954600164442477725329991409096261062406419416471078206759698987655918332891408610826835581648916520662728681251309575740144660420845304018124870658834657451328651185534352155579675580912823644494883544989718267228
748623136722164530507952147847797498740829249707350994138329743077569552220136482288361315810833588594762102335854846192324192985899645944093724785140424415504617973841839297733241813750404095516655532686585071938444976191397561569056851306058787356126718391202744396
1900466495840517081111100057295806789400112469635996414677578057416829873007049709044475004758308094397746464033435886176037245442095169370396890921518081392389450237082916273449823005513172941489819175500517996686995592408261220673856779685443715729068109694484876570
4824554204437801673821316946375215733946910013810894629695786189720400838304167224798260023184101537091886870114243159672665953361631680043310587061805001186374259219210490442757538882957373308210240415230817506981713450838795195472451046041315221987568516871214739112
12247689355483258504208007292989373434010160586796686412424669172561800043512152312205008486669571502260820670383347386968676344527063017766063088045281836989246864216212710577092900570285588326491678774924158314789179319645669864734177529754223945215903361338712009800
31092177264883250724344400511985362255854745511650520249024084352808311569838676138205948326001563478504684255264164167122934297879098702822047293156277937981967964370522408790534474709209981481940855561995500722106239332343805240634600443526249690304934255422086489080
78931091327697932190573281774494846701236104638908620478183512728716251423100372160269868583732374981744982575099972675013926623531155250459996479201027628962070588972132174123189495798589565941934407018878201056514405994709621040466510634163760542795606309473652396106
200375712678633650495240666933356886780108289141335803259261642007645926737157959197339876869312835453069579190075822070009035107128013551075271955685852461095957637472094235116019678757985291502977408027129904434644645465654308028206318141912887797756842923985268489884
508676942838379922427147103684722115884989457123984493389266809939669533224351462751012602740756865414880575690206608542768731210087203215192505371506486141141367388363620711474442300265015340252433597742949367852894803575685917520810634194855021245710933317412380803620
1291335305643514532187973378199153674183578028764473872589713962790006728646656775714371170378676215250915028865629080042650613685247221734437608989138899884532476838097687953725079441158032113108894053064397643184156325425605014257735483848734546691649274119270080283876
3278204162934219540430332911675532653278154498133153745917621774172776921690800930696357661083972865407197033306619705705834546199943978047569681289120094758117843766950561034290193621128713889658634892579312414261327373065982868541146110437517120822002335334868037591330
8322100764157341950877559039313285309933594428688622053495399496053874160963370446516772334313097265939532552154160176481441892457336006684704841769190869464113864070841350788197681202801446616533168103828651283619822435297458238584348238324706180333638195197436742633056
21126616185734473840666984249264050693941331253238588347035881424812958241239380665748530252777544697606509688880508212832020381154152729210866333509850614816539829387752068449000033065809272126418251484430081477246881769451358103256328364021832530173693446143481780684640
53632360879558707034416394132002760375377120396352587181817032256178117689670557138852261022392014411528605444321726447257906068508336737430440596968981678929604176221383404359540120736122041819694463444423238336394909988791271960856796467666777726062307886131371051736608
136151956765205897388841971595582584172047868939938260696632650144047180461583935646864395542796896551798362195402768672922803660610250897960773858708402943322178126843538805074975138819388448548817728542628649474305266018956326519598699297165325272626728609489700217167714
345637503682217603116060321995955873016900910594793141116323001446878553980993594686453024959135829797380448453842133991178820588386205819045401086104258884334598811425181632759228134182203883100721049109072263950526410911889938992982683039945247117364324294152615719072420
877440815321464060781638783168335444321084649529996217609313120094308191747053327054678849211858968572906920098726860646519456742130392688362335029197210912270885353482426135398326337596749851786106879898985431654120415653561345206705500102909421858031183481165371549691692
2227485085356510240052130661269420226707252502766054783239823975050457248222596529327387218278787818048506618158654178376808853408321031956324365110155115385496216252349521330524698786655252614495714864375281330597078031081781187321035764159045465131599866217787945154929404
5654728750756719292824260216479182180194920352342453980162260837539820952438896459038090480605818810199864541802480578737221782784740688549243371965204537770187183715657070471402569118958985614911019118873017646075649337665861513589115861741184605017160179419091102188265066
14355183545265748547305564511156489798179077321751818232701866386438818571809872917308050724304631149148308928178657926926201179490248861453456205178429143371159628040473512965817111270217180638341975255807699353987740317100052650399874934634586543698822048605579967306077976
36442295236653379260937026915900838947654574992186431076857919617950672743799399021092186822475183251172240623743695515219747674475467428781112759096154342423972076361044550348788289542638577129300665900509856770586743663021827298542615564536360789026795907094931620228518968
92512985147681327270888793082425713357984716425957645442034874308749797974563347488051681350626778998289876638398399905194262995770272235326975549728913011435385257624071507016930362174448796919958958939264358287594747315993818058027785039018570920548515418780628915847593160
234854922428894635261864771190819307195115348545126970552544115918063125245544643642709725378200481010827481209729355565712840764295722293858507579258480958746582595604942159271205650012699372436746318286806049054463150661497046925930167199581874936770138733959052239728333370
596206408225110915090938639225844853009070057279548188068144007604163319524427057136646490537008784665038543376946777838300913350671303062262196944960908398887151181776411744844512556559236365093151197906928800496930048946038128021230548282762756680282538539895079038000893100
1513538986249301825424766261584377732640055953789621457434164418044903966334616105603701255951640156606324536520299162512858729912868973670368570708077107034820669115875609344546363978337612458349177780409450839298183648246104541076808476451188482182035119617241936343991785588
3842293929238717537778569052321232270266006041474042995341563493770758119201560385683327723571523699519361074013431569476087867994259381112871495697287981961357860661718229367256272131942747698931124278998411539768895840377285062402245500107757298771643554265136555200376283796
9754107936954711531486658120550349606989099224513359499967711924341060657269043511943474703350510623932121615523297263867004209877209825735814246500066842153329339787239796093187452757454946956811048041288673206194762030016199997841577023751947923483562409418925877252462685938
24761932168113365402771860461800253142239168681675110263818366007737992939796402641182848832477797118355354849409806119498767609267871769418896539923516342558620213847941243976639234378679400759879140277662196613827878493240799166355258643099796236826624226673536071255695261392
62861031337908020618384665321643118690564579683218474994323193294661494922062387640489692880465208242142555318359642790292226632214513401754047152160667512536004055062801230749687193986720812493867305860314367399805673014005532744665988809939162205259121283271892722959555112656
159580005067372066517118304378107276721895304322234494511689258249887612528381053925141461742756513172650938178505734861324067931204610071987130386865522007843947718908723586633534223347833280292801920472374193154646474794837548888761586358681778335976009755318142389125951660016
405112316411288154996948876596450634147430529872069077984355882997963289678563121360840086284838359216808398910434440328102058118179713234380376244705413197795992460034406942906351818669204331010391220151341401087443300661220764931986210074794236532300576033251923958912085708498
1028424512449617767194136891767629837499761677703845305267262261914116807509559977932166559126737125412988918390570870917766566443607491578645815498744051728766492461608599841557036930439312998378530809804464650298396083377346361318518873890173501562861553237269883321412659773108
2610774678924975731966319593293589508541158386190578252474180966619046464241546478376220060218103151156435313563358795559381339893379702883832169865328553349973078460531367626409396245508088910686107524827178083862191491501464687468152984022511081723631360313679222505357142755836
6627753754993982754844133521307644700508874372366943454025863949320287576673467723820234527862760347877882604265496187159415764368819572528182348625599905769731104643119844636753696937904228436401296149432976859300935023230018116598132882034462471844360684790712506124841385300908
16825320159349969594229581322263659377247972691579421880449921191048397756489471569889416144193091106459466397787002663930163133755363280901117782229074227979671373744119631786118464324615213028428136949062721986816904163369493650427520194408394340542561559767495614576483822275770
42713022983287571001408927392323058975931139033215419469270470609413394545352345608599027782802233731774816295368850981978161682905213792669581737477435212527625292315024817434482566964462018106665181957141506174809691473573440520433519058730864962889443321726327679713348789414792
108431953454212091413555069979851736813881633091046374043863236668902055914578245387712638858483232131869235491344073713057199444476894704968866512027147622825104201292580576794104064947854094308070153038369680688513512718927296795993965726232104744898919753719900798835339595535144
275267066311293368396312965621129917525638473237731686719393436123854392983555706576664735522047509862247053382117340249369811751622310006002843283176617120515847344370091369521690032113306027209015692242329906612313535081492505448598062063143613206335963716148178234069250510649240
698797313723785747211147797739580850104425907282704704468422325557734506462052684281446109339650107631142411553972128624827862160143345117505373897681733289606323880439413889548741524518011419849269463596178884238851616817062217098744537655698100317233441856050998320958966455814954
1773977876145021619389220314154041120608296633891995453757175520634787081607412636549395439789231004454815275184859641304259110617482734629748283075139840787121759339348874181987137550331388723607095187557419726500112969832828292023130787043950082520230414958684879192099103531272892
4503448200569240087821665362524835843188049768964983317056272056806236446086397473896066266072150436579290502204772933072491521496484434187470493891317061535249575952128973980822482150420042326802768070860907088941815615855723304142548490999241244007154705950895299356812978548412356
11432524592292245288395788723499722144909479464386279819409443939890432435447070558904695928565510176668173785053438231753215351659269957405429649420726955186045870166446959916043446384580145288330203281886625769018467472824471263582467542838130065626639321823206538689975481758389828
29022787147156713260867615341480614585082891106201240069885503277681498106314163476784179619036509325216440435700675175667723387236686659043809094371490085157953697438893533319306323493855609202901021793976405147159191854511794768502515031242540554544360667486884916030337680006873538
73677704953904458542272697719065042894216938237137068598234525842166175272957085760135014002848969135065462712283540590001153545416427099153284782876939798404621742645771912691041713006362813052464009197561667380971800392793913747907998953206808834847920981677077189919099469964974912
187039383218107093117310714036616706511968749526869041014477442416720718333734754829925061652712087003806749228066328000903814683484172035770798949546722918288308715788565946169431662381696596260872423490163800607166865164818197809798641374221679891538439360632406433875736314975329600
474821126642001922085827381551901991787115072779996018905062373902301223436202424785456488001614603803979716794351825062227705034987094909165978925525072218255999392157335610998377550172987745509201025069384751450977414879025104841990718135210026409310638671468403954218971691625251776
1205388396959565826582598411080387925394816659245657222712496084231393031100274351187277250921991952670658447055969900121928455733346366350610795278761200761437326428039152822272841322590498666638119900517950174501504151156610572576265236143692335486546674768334351312381554753278086466
3060017985720825769644502854910411464234142903234705469804396557276113247678441128045752368544637908076728291956794334956505845715115005547165235292356039921214655951461616886894616133769942444825361013391903918071601202134428872964822624762568172843485669140017774855368679729820992196
7768209895294886441399858482914411502195657728927602388238137977627130829018760863725071324582742600890620793664891148033317007510432726012990902240731059847080274690475434142507591474756603328169432201171102482851422741988846879207992926916322643732981849834399850860938261897922983372
19720500094754294691009353235040772073857083018613297289565139275246003314630057705952549372412391716397360993925782990798016500019389825328256663434176870231971207819953132025257110122045081958222547653159497204294017000812355464035091349205606988589152327083634952762069745440557029980
50062772405616276552112016137169932149032012347858045638710257475425434823041029234451013907822984771093165438323729507871583779362761457938775456043864981077110979545973051384013012248653984349771357582395341712649181232490157513132788538862415254443843690324368408847660209970596128778
127090143195872195373087524633502996905621018178322186549878914103364727864983093281402736279849905681276539569126037036229072389458552120055247669766977622845218481302363115420419677925654868404474307082159376786255152184761761068884596547065967371443514004287224796352952066756281342968
322633040908763240909780233554178725463787552744061472186286202584715449575806890483527472955103740072835308820712858254638596345114280231344523826994062527227796780747241503700858751579284144920215666223961545072072055574867973115172580400361873918329392584890316355738023324470563866904
819041323492792614152520837336064352514610200167664523484474857700555488550127966766910940026673713682434726896956114556790186410439531612250248744868527208223779772827216267499787944634615139908059779100610657495650070055091508805883868166336459059247278124789980439248700107953055192168
2079231214816983595930539108650650094294585481814665663880474549839237855344944557172522367311678080919080157735409601058271004511553280905017825260235089206289827124090162362944467048825142817197373634067220993275583128122885599217476492578127146466710157101110512406115202941305271560986
5278369137997898133719646949498574439596437276654859616907205324013520516503514360193214405046346014738635691192431751757074261543215616691902348025986085397416838713642637368907212161686602492774909800969899588184577437390980030885260157235269430586699599286307577775604711516331807115468
13399751099552941471905110675180499088216612669347782986792696234889121216172468791681179137617804504023397552882483334771748755633773012200684372909699357318193568910558408432404641283333544485048662978096981393001093046492416215708878143694482109906654349110146535840680452023838610835476
34016819368960504633540957869392911219551539128543618403123328875827363243212205156170653290731618589368340899575967085497894211741310227587388040095769234226864940773048983144234560737024623461160458069099930633315824781576112803559207484869585247112534860715477182859588621305683347972084
86355633875848079539383382298800321830638014524287749209898114123245165741107263732489758413917832238225285680267446938083408416175288527097357955219200101501573169064019670778408446766168273724065796126521245869540263909477983575983127435235722999331689378179742794255443926567685574945170
219223773428509183535758105935524042363542319243622028869364698852380336052797514554151679539109638661879093745114293129376182006108867101660025592836526042217905920566663128349383944601405307893130092236018289807894568726514340358552173710056921703661839378856454460324308903215392431279024
556524926970346458355106171405043405037474201948080102339071664434485398317557615052622748462209509125495474604494029298695141176719463814540675388829613176303421866625826040399520302544431460797119523564976191481239108755324838477661065464540601021668642141751586679281008868978627927339696
1412802952414975629336502747952927162360308552463372382400199827203068500501707936904739992465534249687666906238257718065473723745047395005794074092989647468266374177029987979085226161496361613393528097418046401472502651926298503324019430963593184699110119145572073873559336312558352915319184
3586563845789473887851085009143693371899118884859948660949711699693592291274043338538911881191186072540791859875542355407668774247491271964446805733184669306205353415242321453049133485644943806319100853620529852161234647819695986462239772871389451033565533195114154979287516483210862397704882
9104907515896715301200721277318678300807448789994103910891044423776731122969184835336209929928131264867805676763726381478270895637747273413060434467525933238554517371859629911819062633795153225724148947183218414112890950707853642975748450450940991125675859776725738807455996756796567202647764
23113861745512773577785713248423932425729992446729440481220184256968995225800598088993386385769775684567356735406516066939627033457101764557967007604271523329290415086769752811965460218431902298096562930336379921084485001957827090705598650182015115941931189794287226505649362723876781297406620
58677213783655005611607201781150761871636953256190563844723233789307336615493187108486108861478976003476408010827657904085932033439762927018955346770215221991545532263804110520556004894660585048396750145216183367544785261618267997762234086486726496767193151897369694541195022307483325120018188
148958899872331601664235472513655725365018112710711749491054458944692793727923244062825482515832426918892709998816437534502245116765726108292170645547106293470768213372670788294453938444239612047857429110359219601193993273556178877446408345306990694200462497024976519458064293032337940827258970
378149411336844382697314643370083787922657595830339849620006061377839001358200850999972619913011385740471328225238885124775371129134521814919378403893625917504601178471269921917908028874731742822039381597661264509421478017141093211981836013674345141177124778032843713794675901988685536502388840
959976056596554731077671541453601435257807503016451511013894757323417912167062413997617373520499448996342617161861845577322995458378071756943154412945305501296938134247042952195577385067053441941096684055944981407225857060115835274037619195171233793162719436115188303928739708150957085716665864
2437010349905790029833108626401209757502530925528349786130415953302435576210173228978015130696835791639318878787396244239278174974933497854159679689353865472653087730955088282158618955889751730478954023231710235998451468869019767214908327813563902977045956586143480691071897656522092687903609656
6186632890203332358091166521483110535040379778139634644539663757440721767765992828014145251124480136709273045446854846918153843725119821700659082042358196406361617586834393413167030562608386471243880080490347125393705689097545197431374630335428573952263564985476627081869987218401066415063032330
15705483778361979696390521856231521502492863997133405688932375968217317864976408136989058636514644344444969942370017376284993417612485017410670593041427138672940135545556147408178052295736901262385514220929886024479284079830039351956472513921316831413470729049042682651820966235533089571002341084
39870188693915598780374831044080445995319233202505832605697142302034626025231517886047994887405076828026190835220813803505061168183720754271283145201808244714594268937117948030568505189978125448241977240432990809156302457177245399619915252081534238570539394332866846389166851302975083682040193380
101215089514054282267181481384058923683045965768527557086310124978924879821094039619023831676287317863163094343075348909983079659117105397816748992091108239434998661522634492333317672802103032209246176784976769652482213164688498875504934599148408895040539073379009284609307558296736306363862613924
256946221749419135060422747665298806886785049725939602650689446382925097730464291564179681105479980830197903517299145521324448663101802091055382170545336887359667207415226979324583281955296899261449159689450095999712168773168955043768129304952681178347479042311143523775176873946757667364863964770
652287728917477616790849317866786090651516428581056059951537234087848020917630034731300094425239088075114583992677378631889927725682858486612366627910700902833083335547043194662842951430580513307292232688917635710555443041190456391262769817960428501048428171763614606642456128116570869664375111712
1655907910999600537948555999340132393705830258279442043637530253285731103679232091238959882596268578912324977169023164289967654627518831113973282757931667346230098031816389311338785626357526886167232408427214914924727099756519070518671844299610935807281275675724364538005817738836159545012793118496
4203713925849372321625146620467298278624169240037644558963066206960232933553889708431184423508342690177646409631878143711049347039316880416877283422685170962842026981419045545687408264467724032635397139638341678923622961213769642607837904224385775155004988683732680526355501544308681800988471144800
10671614437612409620626129351546587970243751189198000687948807898699157130361447821441868104464224342859911509133747004259578596545407508179531781275957611699837750562792010304051285160744637710252123790442728012275301404631365468514262086717025246100823151417698004439212903184003298620038642267938
27091128633841840425396289263214293800975696770493462466500224938835165941389840911999485385177835996325580467185881345993210505640093973451483930509332931535732442360336376271462658549140250226747869275996627188258949975218422537598119063101560599398142157023176255461767630107068212621693015700196
68773966202209355986743099987927299378896387697587079234609463514433911380074030141259298014863703876928016110544523577373447164919888033542250139483142411891686429915235071370991856517191854694896424262029241958145983937028555797527758335488011076495201915190007523287255881232361818426499166765164
174590674722726945904651666419657308697880835797802726585284827316100073315758736172065015014662973750965016546825193981925207495068465878045281860855720634418004270406977920222493868075642658455419736634804623947182887976444995375831068527969478634740046830274704229145976717855162146657295551539644
443218639019801332552623083640287216521846804638990687394736939682096794639247298624091523393161907605994815889501419430870466905241927384451627920935017841247754266486545240948097417248133163557388707032117205446415145281141622740035677687428883469775036328300768998382142841144914803544242047477162
1125161823714479685366459589407248745482638202248906131957324831906361079091253850221793966171100190956389213118750061016837664976421104431360803215124525059083876656316912555870661516162308184862571908085781802059163048616334547174276094822922262655437904643794107663943494985642498476171769880203480
2856353542225317500015605113243684605992104729877775264768163352059149512209558855488900247114061953499766041033397096508939295938109019909076548689890786943718939734708194824563521987186789234623978181228218009074936595779090904874489166300251346057440990198830352389646578099096864084543931919047160
7251184128562718651563534904440949578603673090773184145246787315882927666638889550345270394798663447451285893072116670171738195513644859790016729829016308957528128519484102199194666040277571170313742501198569835322551886205012653993290235399458929120947763858922086339561837205044057661000215055086600
18407970333166914264977983940195058094748126041443097243509988611753528994153636409848844874876412327595320257863028830758550119855907477919916578528500159525574137462237314176723150439852237603707686255714129290123066012016679646127042291441004908515676735156217431128911983478141761342288996235337722
46730763662723110518418287052191894880202027006925918379934549983060975376257188059632224011293127834050069432922246869859535703839307740033074322550375888137850529150343355658579250502048347263657473059454744034800525653501537337665962815903347245813804922276412437821597980153820408313662328622957804
118631453276879929763681077289135691398685064645069438221163665909922302919753428693760497229855815381887973636459715157401634552301249736235024891189610264355512015920901330096778991790432816628726811809168824988277016154405499564473918910190037796474508777346245917611542830952933088074446151525465012
301159677341434970685806295706706005946881604311877702860423241878342426270352850237433023127343725224136731516109983063176978468082944856486382000251988294893104943737498845356464849745535423747666939727017449301231503477985727166018969104704219196666221692791803934948019492462267527752639182881256788
764528704244350494127116155827494663025477409941485542646814704222161036621851818152971437566689237871544591697157931532196704752945681183296581716310945501747106998478350953766052332507692023829180243209177189799539053969796058431780892689422824403169527830879492260604840670000902176369135007802865714
1940844620280534180616901035542321850027549926223513532952083110364223295321159667452920150939647423261636768586538645745803633041294060347128951973297022952707250381740240293710055631427637609159898215313506372259787608240254109404317848583777358852536286414926512993704232643174293640408318406940272784
4927058747643779337880102868615356705610976528351312183698112811326006114265070699430677627987841687199977231171632903587048353204614843084113328269901570583478016888883086134336065220170021235111549849400501050504467333618534380904633463247181965914553693883374648556333650472378789666124074615249228432
12507909004701361019425581792367073791172979693578558050867185676814479172199109947698685705848943470404275547638137218664487541454009389352377779054027284363769425488027449793916601887925469064632202582736677915230663279255970590920359807387777219924507126627635142513814104383566629788079155211654527792
31752774968373562847504683406707711956538290001354198945873245459774685018907893777505857803360964706556776612143620884543661227987606025362020892417574609490827490988818942222851275285843397404996888676856522376750225063238297783273131736791786478376218596023046048413491885095543153803958957847729832594
80608095071142823238717225696461179934228136259386403159036719760890539449005025719000651913383780402783786625806789044988004465515295203607699638376697669494945049557666852058573679538625328078194981035698904855212629625991722095982034010448540823624880343949539597735648910656636281492236395295210536692
204632980817273829471472757490218992904797869662675400291783671899027496705692689797046325649779444965072552611796178325321404657302398522318798831750391559827484247005799775109352771093256534072230884109037999683968850153566632957574245342952282130067737320573275655826987033209604400682356470477820911420
519484510844787540744796181352311995556148411534993767060761478077101181443778753424780925225453464793003400798556830190195983331114184790481332934473056524026973036637322819684066952580002398555490155518497442240093172711896085131486655040605850170557305263627173552812102221924961686529346971062257758828
1318771568150210656802608109698847329009974579877919727332890105890250962419840728783159055727059223417141110181236059825602428273790182243746885148111075438209851959159730427692543363555110606504049005860529596514449011542180289769430864483010969432376543076524865270220372574051402765242893050337466099706
3347854291426591559390580292818341843256878379759862591362772543897539833764858610540787962518850266892927703361800212425942018360719232227426538140044178474313626547140173796593088769622338270052811535575676982996359297827011205982668582371777615769357102383107065932146624436190156383672003497139016430920
8498915678281303180368257199819973346326206965868252503561586015320406726187533861595378511690691495999203378100755062448018331264092857883702979539114786336820495186330962584312483132288149490074971655944456274225399123468157454198799828971317752192420417712582790954936776609842799325453455623306270455016
21575481313960155706657254947231247716702369943035384502243698384732492376508882240130795762190418543742983343361195260286911826033158000525246597996568835269875512585260134726110124029290756705802958526837704763654711992217872825955561748760774647229359259301957156786538159165888067574294479111277899331288
54771856969779945312072471818164605768553371638165468556217913818200969500282955711153931678451578769115659146381536280443578706146853434606792963939389961702974614408061577455351580147468246458154286300273497706281952647260218438112816855203640536737221692339390628888876995253132823797394755525227772810474
139044699502344187236113519423970102121115947610425063701162824919123650134973466789919485820421461900611805926645753168990886420192556386724099702933732199746372890161121672990891530858564045617817357877909169374418890329846878825721826132357972479317678170240637055373103380054546340476143561523537819804412
352981065994609256863425729789626893692260105576978548013835666720504661243682614383480621985055935747968166837432943440743124931876596499494995117292221438695764479154177194024578457085771220230412342958634380908317661093246606329956962306572994489843501624268723845905821208893424992723941131498281657022212
896083298368307153281590809738096027806347733041511670819804854027587176133255133164623148016242056302671610578755515918867777117877756903749850310569696188748201022399734713846346939623024795485953787599377809916563909543884406261087504916215427512077275463641897701566633346555565086379674354104461307363588
2274811186690924391129878512025670244523537153654295778821173305476137343984211517227522500040204639069171602125466948661683609965270447467648284413795760817098159837193642047215419311847932186655251831660479540607207313261828485968758099036064539581943419527679359613087579346042020301052338603683638061973250
5774871537631588762332200703372248859396365509848082866955447810485563367882541538807249537963202981148361897660224795448607410722735772130530378917080203334047565651039520807065267119628935569439403910480355108605326013754779450625499109423771917687672064904345703992869886347462867129892287214103173244433664
14660179917903021257224402541109273045919369966498712497927468190588731732710678460123778401959387063577691945251305399823589612072133521888352621157904757363490813410821033474893257440793457141447816252041548059500256496038693666996296369393815054004919919561035055654687485902792069681853844058862981655108864
37216563836055678410135040274649799349390744378426510842943290245223902689351272096571634027781012867616436092150882009139894602777075450006219281632948095949628639471733559183332557436771945843949890449322225064913314302607173669567162264479260291733374405339044697770506219154981398107767259692669494982502144
94478555619345146201184362736799317316351034823808576726651794556130279452343029553003848283594598539160703881609392175691437218218216846995731332161341060775241934300223785749536514827720867018571857413427315572223696883044004257844677147934671395683187939519147458477735216766663221620509971678542244848327938
239844750612627195470522201644051936099041183981320833010290681032016464185849787917710657356795651667547257954678162365464091828569053322357726364189849002056807086373312143723016896767027647011587267131896340263878835392979747971456585195464005184510956915498659905179977786385167967222739061838800689595876100
608873664709736347780367450753512181177922318819904510285925838876434413630393769208409521627177861741760743433524650463854858500092522960582829450594388691128331575814425774053334965756746593513866284444044409601878692442871850786464496527232647630926460818918560387429101053896491651152817391708209860578512652
1545696283242092472509545619596179399270615680333260043982072740949865099417152327242804295428538842607911031105337723316394920823663794321895868246878741360769422095246761823236963252828878692857713278774349093651980976208222362669719971414003223131241833995135190366033193466184974191617860223429606105634623772
3923928950297748395839966100148078606015344665167496019242067592144696377175735646620010167681436703903409737049977815005262812208592744767237673998727903160457135103675974692884099158464916145738556449586421641552185363399272935227300442639478402550997863736629329155042368684159258972716387078276572798082848586
9961347888272836236608810739625543584315117237343023938886719669468270590110838197226520540322391021206667307398259938081069840892897085579459151954214360662253258332589933627858471787841124137176394154965348991468454129722226642192568420247961961287137430741190578172472899979280650993585598881834738775873795512
25288034775366720667658829891108397763297614763174424338579354880202638149369236802415862346777755626746092770119324710003730323055744595010184744862721433615010274257852718769064550352711069773628340935998887488339195726269426280286762279474106929044713381784287994310393251448406363200521068865071620797222553304
64196603709925709489364894680767904882465390351033164560430086656002289824025831033287549734265958730706611712040551389475469624303761665966708313883294523594382217068780117231314809217003434222990070561529978770162909961392982337173780485579184198692947731572833677021680758953240484634398421560689179655661624232
162970510144336936236669793764649596728911120418896625939487511325618011143744194923573793249124083376395484086573210137801523025141811095562105487582331096254735601091761779437925874722211675864622591134713456175619488479279636885763249132250136735452045228968491515474244589528891652655384170166128696152103612634
413719506046064686353360527848243751280472909250853756261563205872303596226912416506117481813546963981918673364387133572627594493672553418616717265160022733130468346137968289428210738960849204765145035675454443906354859558528612527493103096958389971487696588255264974543537094046732199172108644605327248796959162636
1050274859736318546868989683755359284017134893400608859619820615964041273242630797595223313003587932881961184247958909351911026112076950291434413622580840045196653734579752622038708159284825962587183453433274730111962071879099960432451905766732791945538301553086133620302595100693173097586709855286605151384024855380
2666244314986018303460725730358674782019858754816165144444222707677456006475623869388821552870287585705675358763586216962949664785519146894944759114200357887739155176320698381289300856263930417198401866509561414455557795878090854485537299948461274561840853556318647835765455969375267772841267081012296587713422434996
6768569847496881264189379566296230226241952598350737121544447746864005378126428695879428561369781192587831223380889195622267715832988898631087016430824681495865416730616727207237522427898026025905503159669476857497949504876604041666755454368721489807234962271267524478523272541572308995167120753553277676753079868114
17182798111539226727915591753647335199769825828783440568999262883027143818945755951852171084286508654805009469157420140039240303506534743887811441110048421409946304690853314222404440988715110165798588181166981527589445317309718483967174800197858334818562725137255342362515803914555539540015464603163265474961914058096
43620522147836497924157480862925140572000974238036633951818796460391427654435752354280779498575592456256291851797405146749027735220085941539341810475926330081341786224878438718744033279983237511598562402087068671375636124495563302729237815002969892073451969257494571630849836074198334622269346406695098279387167837808
110735745138743705079228111830911165873077553691754839942991445900786588196985783089895865595854927422652615553911458399294950310572782720487077229424500497878584503546550749849111204537864573720181696713678708097389821669735446344544851621612674748731400317803283426865450190863738398107076647593622468742905426490576
281115508197578833815129381446674172716859356800366803773166406703165749443077987680528376581657803640795627096483776007631743200405656734908302214011581494595825386891768475898139116086163428157868845028867067339849974458719186368280584727204294101779814086118312836746091718588334695373828179547861880771414440408690
713644260488511308668315616582967731235641698336953460097677375170148963790201792784139096442160785869188911066353078660394571855023241771599886707030359746196082513117734888279417015676804638898702546862084395059317765325227857304159571867825856251694087594465458726323899950670305057257286426072741767944827312181012
1811668569242529372732591253260386616730847977129167481807523468405447677727023747103823994354502916630920137069648197684211757224932317513581565193710807815907988579150783667375633887730190224184377952756632577274931472352918757958519847761837921101558454694818470844039932792864001043670345262460657458226059820036060
4599130388205667400250783088624271516372338191023263116207060319645648372345280887504765294025866725141279457632946459073244122069672587821033376602883672632895075914300050909362934779179527443570605005893378518086188348108590304133342521426531641251676856724134516894100932240755681209214683665564697159541850810107340
11675424902116949762445246832050054976451948296431321079606979232465059922007283671329428760458075515446816994368966932201754358079568983860938412393139822899809789347557967852816442418551989485870429668604720467943454084731281595943686179368291706304862261735093370860380021884487089086629313183453087580417581076333466
29639417702648686888595192951410847483422518718987786888110709542580670197041283416244879216701039433783541540930883465841968017703641750108380334311655735179789835878532205077886903635679458049412015990345017212568739686299134141541177277933796709161655415123284292547205942615427843561604589599186996331411571444990504
75243093002362467874311904642933648503735105625920857184828780379205611171133596147242909360620999364809078292403456075625168264652008609810152305397534578709317087202731027710056456437834030407608059258869350902126942318196569624661561719512951469531240094963304763871009997311182503921708783496611430962800663242469320
191013301993994077401174484613213153537783690287977909102872081698288091264680472671821484927753793291432885135563691677604007970621835339936221831234984654611489343381710580779616770089102525385869896167112673811590644187637434644651448157583444586027743353427125888009772768325002198002582803490255376587131158032360056
484909379489532666536227639441521964092644502686253279878787284302291124399552854476968458903805581960363660768441495506976170793219973383136926017034866819181842978759376774676389088201066184974002308539878735470241147723801021851487351377693490399099518328269386089527533667926000805812003307958812710017458080736011210
1230998594664977239014775631775013785736808693415608450481771880785327879183240745419338948158577791207758476764134345683751989016083241976634371420056289525347820305755244860569785707340348817953940306886589133971978438872782907884495652909461763740353698588589698719879798820495068843347359245504100307614988722496794396
3125032437323394124173969477849578841087074117253688499700202947157867435807359850596214753629880159118187583086427755101873471942014768649480303517109877958545664969468553136643172507342458985491753497777579742163384827136089559807324673978656570576382187221827222606666129437503317406235268283441926713053431953643360420
7933256606991671470706209424979354479000260306254065249709247168980096472446775955748991970697058530022597683299804902234902588300377909825891719671497585984034773936310553025852755023052585762329252888415692955141834880757780326325317399178433132421300478317722196362046561948469773085543831245464683997889056348840647268
20139490278789709378267034181549361032793695962870543877734143755007563182541342976328704011240527377826417240012638118813024313245838846380612229554137215653647080178807099378528672734310458044708134467153245862136723685765974978347780191872949368913757452230188826587193318798882044102675483874763833516672457240710437794
51126427491580950688613323889133287127150572997157449705968147834444912317544758908382301404773989288669413157216164877575858848224487217090681662837106136883620198597053443396046296207381518461045208022469307284202325917648114397616041487054913625257705185240757299405027301440192068407315452919077281910631151994312243680
129790354764081371316522266769256166202975091424801545167686291788102625491086011708520241644264796432064653010944423943409834618281911075940284648956601411065010674648568532634087600344621240472339932700191300124557814272448707659084333233477516294076706505528275081867014246018711996255129479380194789571882537726007428832
329487840560736896724443322378659539073664197224430967241549838904060045724625631236896670046293575215837895539595706306580240894821496803126599884150638250574002360069940306329063202658437187539683265399430416048388667889419474483030506456497394233262608955395409305731743019268513814205082728094481159929571521308059116704
836443025945264344082971564699114197331771127267020669284270109470443080978875111050397924582809292096292688026660568863641457643003680170333017970094404265164432752421717890512737686325664277146664114621458063639625036174206110467345376597712943173076978003596043002974653246492949528208468992985961168698318271320219041506
2123407450975420689670398564506168427532071039130457632422235461007245914742374220065931007374450131048801274267839867331199586687311019012129348073413988346230469074283232771811472873486341966889060102663863666411114105500001868980199141128520555849783466092167111753083791340925694760724159936319572360022645661798853702436
5390515627483977645374375880422502337783331029770896214097597754935360525484333411467384765466196492290576786520753883719931441489268315834611816967672110132706809607918589244624382314651759353464421836471973928129258761842025717588112355772949725873272376786263765982520417382318972945710221881802299527154667361348034683308
13684447945589004878648049082837772675040926080493097321712676051848386764220290672202732366561968237702008641063462070681559381961972806155942894026134026678119694219630148558175298206283311273953318914428189477849884330225062426684962747064012071333220338705065078770990853972771950170656908378366302596887561024961397805180
34739555270140388012787024362207327367916143269534092476060346801023445830903374838258770173890238489983860994659412743004223931170863886127183743810878701194356502258952727952489152981223121598204025411094057542775683009308378661053097300014595425886495476801919509003829613274823406239494409640684020696737483720341376613610
88190382627466251181791793693751363837879547679643044799773085656880190054021038418054166557346470601839386972672081727262903329974447771909158989812095223825769242815611807303891610619195689004274905080764409851403731260882832609280094523739836098542670343533608755337683891071478461689606352210815619892963400429708333173400
223881495531519246277235913826664339399292860767138976122339110567045858766892578579687793494815678200533055439056818682891067199855946019595411496161351906816718911317787362641035313102922758010515644991332529760788318641774323404884570509153788632065163340047190137123565718129378808462597928828068975512781313611524658646968
568349093723279223771129415399254524413553456434988954213816374897653592744240774991169112123105788862479171475202437404981052579281032616910716378351270885574382997968523032543050839688073962107126368236433953616682618116922617132908098212822070680775896752262823845685830845824839677996076651174767452014902021666744628218696
1442819968524804825745934095426542327317849682314503863548825146416661968745128005143864248295040231412329540877833761464222656829495925615321121513211933838325021835200349903712878237324825183824938241705098204594910094004936594518078245696486641854483274974354729963947254959040303455777630865224725635966177353417463283998138
3662765516060595857661446987692016388502100103644350728080377907151419595498973441528745300404007154750390700800630842099888187747816472197182011780615800857991141086517782954533679138439148464847372834981163666753012518221052609101483641324049683904930687116674336100356724064543007112311825527353663844829559523375074840313132
9298354277255762165549739249265272722212085519814870250953112467907901801766613921942568666646698872801015195845581151001150651195918676410780245327114279528300278758817007014048048385254722131140885061890988365223268306859907496378192148124582298789341294017579674574359862073646320588649357411635313033074451023863111650832116
23604948743306385618701633698460748091206225338724423185183146832182972449785159491646068549634437381140631883011958900678613416807759478602192987567387563981507179018237403162280749412426164786433765678570541608379424080268969639056103185717112752360353309072061385267224493204122888168363180798703269935890568409308191042512916
59923894977527908678925786015494551177150271192104389279660587932295571280850727949263648080049298429794842296991652180623974417341219291246903563740984019141957655216273604347303115555808302089279494052665830818294269831820585647183701630731777376344011106920288177446402517385492706745179056231194563884237097173009918990061938
152123744403217660121816807917072069480790922125672235155861622500292703453237520479463041226478081031019308669116690702702762553653936659073814623743130408048320252037905783945605312304398637953992122173671931789653863728680348188824708977972665343734976931066214112378891021096481555762097584763878705418935988640285071603798608
386183735552134128529631659717477017855682021477919272751631239668718506370372791796103810180432583032148053362038349116297397759570711619847830645160568005945841735230700977275303405280816272644816586157425430364360687267323835890282806994099242234226610751846461483690497952629349069266476277804375311767639485831836710753527376
980372118698954145563746996936569820409851570161698660440847695305614249535304328144252475203357168647885671351338734177430985208574617453951676397892816353685915843122903716909491953471239381805492194235433604279819986408636166502903731868397373155595506461056836222513197405884798724735152793472822176540567323007531917777041008
2488788114673269136622049483489444088746635610219995785352895212880375676185729926871050136394672639727823674385512437362675215246324004120698288402361491922308832307847671424825683208451122335081912810491040036527347889726379894055907361399779677468518291670594455365096011192220825183224242029257832129662778737571177032843601490
6318076740043395967434146449334145852082401239933222581240084959534835542154560446917860644061672531718141893418742335550320367944309756568678082933930610948146133083517654112865348825587489526439168959311768352675268241464064797525881281526128282123509351690675874320216312312049031233147934674616436694290349138134029551338028852
16039169207587556045514529531491517258694052581460958685055896193887912443980344883085420420686408588628307846267870426587426593723688998090697220521959141039483940831715544618838383566415561232075995737292175000209952976830940886048052629109120415107090884552273448409288750149399464452540524098607268606592760591227186043562706044
40717287784614319898216999991609007864469487992510069622327019576390358869433655134408714331910174129885137801953539383727574478051924118531305706504949336484328399057893958330665590320575096228671995966461240236995566643545887745538956830339335412679759395605766570951331299944340139729663586281404568518981229306587609041891307820
103365548618990229089216815631022202630908914278295607237638556834367247218704609068023598353464493013318431183990847386892036622908930724227347976588317225073641245920031369098102933331257458203699558299374333805587850647551907562178163717244434768795200148605322745445903486755601971081336593440048632992230060256932708101075571514
262405411132077381851272718631613532325451100618622658931059445393274222830470399085611645173438189640868664172771775023614689382418641445904591008076545451985117541375937219732725628996421475927030286016398566437422196869997773640864017118475427814859246671008307610296108385413134323950067245920308302503527407082720291750146375432
666146513140494138130059598073544971442475106390277351777797861496390134803463050921538478810671425637232222955886036480145729648274985101291963776841785822188344717307864805619164327580623237036191692435915495012238914724838527801054500639870174757056465732568001017990649894598191775056021030256512002560145236657357967662223984296
1691090039091776901682448002139881610138504073453718876564764519686984579699891337012661765593200418659450049691287467617464339293621315764469719323164977434683970424585435270838239636812149605747716836272340695525142088538114675505019664912541671018920783905547738336633040886455788395579166951754947912661866396272878711664480884248
4293027830819377545011686578794648301141965072729042746060644428414568230564472586765200796814331802324945648132794305534882795741864249563941532160448752834848036446954757082547459604123960191917456043683089582005505463433462766892598460585117270691031206082820186234101068278037293664451578065622351858429198511951965483254192557738
10898348124673397998979422684353583412001439180203591200626281618603599573752272144798259812367159780335195613909163248368017500156839801900143166421620434346672441849840592315265795455707394597184992661055428131474239471363475602833991266834052961720650295182608154715783026925202914893899515220161883839565366750217692746263045290812
27666718345942491422747382120090245177452275465348107492022120916158756584037169840023136165987253753638614647657226209051017642858440456500521922294650205315861360461727693059569195173619033603745655429368269530921444607242485916244194625653127297542577900452329206244492758528167032100599873698315087573225542968450917003367737912900
70235167318684800655112684453438242186762003219099030769740280732382560434149830133125052128673363881957179276558477771385769033840453333437916832434808751090055502153812491855413301687217085623774100929753556856305499318883112179876194528716667648163314763009782087788982475237121095055674788657464187021385288809706167244417662176196
178300102910727165702772974357144456205567644081216136868332884488290003119433928243465057761401247512846142268745875769672421148825972225640532708776125796953336877978353942281980862414381409452586983439815886093510914372957707753465394235656601238661515942641826464869485481958207718189201872336857133368520128567830748486298902154306
452635451891612347869255976065338489841756182850137711492728370227631213512845449217932207260541875062664609409203417912382362579772810007055998404254189119801734481190718074470915733311666317542415850541457774969264177640560143637028779544274336140285155905581166847543733424259526477182453089812174349472925115568389690200960698126016
1149067493313251917256579914058179652898575922889857742674664068883236068980296264496567561952526771140745759450438858030389047032375098255017750483485662536645893074492246742854535783251280316346203121532408477943860629996511964337480153128081666759109292070878751655492965620489393232732560220681449679213345453621479459889051614121152
2917040851906958999501238515986185615256290926536657665367859389977537119181565401075194475032008161263085632458351278117583745960484325406304349190362260470078636857563034241942354609984347534495838078197854290495533285847111912621963271402115470969629178830645966164123409600818545078507297664970997977656886170053782970451844482361920
7405245889567924303479897882315198012831788977233971529967923061754573952417466360951124717209387362195179707267919312240853281974999199534172735247963593570798927779707479762933930182262304476051837681817425873033770390779085174398294684207502204415568145934528928409014769076055031386304011464017403748163133144781576228766169698868418
18799073948214875119318368944551746440220764144611680616814965135925381218750316444277435467838279379697703769960866882568478324385989663377974666313934572128265077606747252598514413751302409705945361127507201146140150270899930389002584384507346353392461221294173452682834159537027892941339950906426078442686272837996149168858885832344388
47723625465064932763850636535819697328491100313507846705504721684288072172952731072803298981983843932400341448991308691413884767833384173266703855226557472994616630132275642981866514430412013611348924583785953935300635381660319265895311747753547840435909668866991581510944003645018151731005889631626418105598385079069364314235473711822924
121151947899330726158879453712098677127016441888307769250071386906895295997752727713334413940257480061068816655826863801600603366449233599627315921775419163574244196776193865876836350608888585216980734137149312707309563809409440873621166167508899449795234667283918177733650197812800571650590955813041183577899935714621657479108224172959708
307558244721929491910303340489048454043405345091641842207490209972270547856327751044671679626015476589738088376982530533132872901768255418566262956624047722451990426383151992283310832758258682720820432868673556865973868231118744675426081745717704078092934375648001541532534852917636692266817800540500450229787229056171321477735793803744906
780772208260605445729982684275206614124082137477495210120928715525680924581005811814683024636416504816510830937597038169207661325154199353231724712659753398191501063660887682955075751624772918358849845971581032422105743588635662955306456715453457728296979969424029728193316253707866117314145684350256509846863832221443378454075974362107768
1982080635631473355726663778640132479409433181675166412862199798866400425052114401364843879626332846622760546766496718492893746488779826517608047350243321387133111216667967261704966981978698045336728013989996507096840731402350252780118056335078072553625269024443217765495345821270422627591750947787057971103100636205055449219642561697608856
5031741146239629345251565698564679956107236390010347330801347995746516899551337651983044863213725229760135395310049316059537673190780774504174334134333473289319487904667599770630300152299313147166495588322957278013254777329143782993618028777136551857453863903722410082045904641934104676928748619006669245018254414455276669871073708684903144
12773657391942924002406796926348260096828580213507678909292728368146743347901220234111083116033298619722508310654880523299580389610581058755667576500458130278974186541732510691043693598064735231009567945551419062241953398516835490312285338539240037443657240293131197780228403271910959066679525565427441862778769665933948802751016385844553370
32427408013362765429593380376820821761176848981163214864584681845579400569381892781273251223877798510536277149334463279901656293950318212837699451281756317760512627523125174082893129288395473584037520885740340698738840632475893704006877078678050491223268650314244809921751240438857148349347192157644362783234710720589783425258971040025803084
82320729153763593529223886987848936283205818790996259299014324234825654460515665128167422833021076647620060676125085692776291767229016820695993434646005270887467763537048137268318012450300489381097914499927601473031919238729521075431206833215386026172569322431750413005362823958938428105787689155917328773093552580341966565497469996068515476
208980700696606499258072506575207675851215411507313937839413903420263140263544013002642226744944878306627794424919386214816273016328288724060224952988940390027331896941549201090965196433561768615418230468556003497070867722706302361245215175485529511761815328809450460375817226893703339453839460115275168632117241684450879045881923009184433524
530521701065957578717812823298819840843317342847801643456979819987165531657256790933183879824209611507145664214074897778681397368824555722592705449206836816587548252452676839243823852788998304055966816111037947604969846056436694955651375198584970130865889242147043324699086024099480197487239439792523711106730936754340073174991860316298845202
1346790753230963734322916266149177982583830720109401858859343480190785435489952170396590618696144624842843073075072859881344413529797973464751573386381300189215337399237480980215835202832914640164611785045073039956756429713302846186937644160388277724133539147363731554060832094507347366019929613661407464714743962437487754736011597698855329584
3418984236354393221094537052733429231435071121690775388252833117750201308227845561782431966383839792734341946404581828583195367531817497747264101199844398502438575273034265374005705730827002840591418655875037569602342735332795998638118815200190822712647795443834399249773564607385186876212446875833229343151808867595095864295740540008007998000
8679487277735405252657353497742782422202384409412065145149807459327905564384625895494319637256494490446706504956078967586533040401910119702906163227026664140160060736579688231046399358175400122015545480086701327405329505702030602100055383499473790123592706026911625418646438582479811428944113559519501362151761028240937970759402477790313398288
22033883222783627057575761391952887182950566964834678992543574013761808405902295364693505849712588928183556420785250770355449386176683843693430087530186361723354145473205622088916363625127974948940671517944369661706801468699484204058124484277137640355079813888911629553417428214814782075760501083175170192284382803551432233813254700515230978610
55935563281560241912600071940073658730019591225221339357740440190869810759608103567207377659866631876634685031748568678598918531623350904762895872501118554911366599272739570872129949707785659100894208469357139878976332907850740461227059749313229493256182988091341442998641436474326160623004265147384291887283413890832036435289844874293928087380
141998902689571320656131496721300956212970618682978681798521246608357628510479391634595559711029292421477411841560062791318865122328066755254103694808400903491559943291765274834005533680303470696230087670304653996157952477029184125008376515381977509687987987350517293516598416820707449415853752217913150777983880199880157260983134734045699333404
360480652774431276274968968036586237942281670296142749472586033030259167292755025569713182679623165230303787410002840366711201575951377752350045122785692857499304854919178135465484638884097709818382794723521549754260297338062911366454678944335612515301775029132805839342291288742917467355139146123764046308117583602562460895678852293439106282636
915121867587668337094576547027579958033415962472634862819277252909255778493154922638896235311284240478476584860413919729217745719488871049375935977716136773882350543349613300943636809338359017776378019366882497404590635283182194264530115905085858703822239870672875009273913966393412294371737767471760980589920482626772595676557539006896986035930
2323142798626616827339428108625804138255473619396819200344424518853184445310469216715235094219622858451240605889461963287819082877847714997706650683887976010691557509226791894022361778792092172897955661309555926204362293196282583473179896417392216912128236813001668553197855113105570785245050587902608044127391785949741835057796358006874714057704
5897566929569279096974202871954896672906186441829601309180752724072719741532217619203431853413597159820304218521306148091970119165098483344719186772445240757640766338606219393835033432173010432408131859576138401705543214759832916867519043271666903710985391296433992739775553998332838673939152170719123107596373250147784096938333224174710886955400
14971656373990886450713077835142827944198769867803714042884386013063555983991818852129254607323494720816440266510711223667854114222866032338449848080019852846399251463885974109293001442137584884877801797761145210764890042683929523518792326512282136353884551506658378406741281578832911796980069128423704388575806690544069133534822938642816336236984
38007282877454765777790281743971420915732381342945627166260705689475438338920289431873798968346222284849484343145524736673228046739722472420300704314870371960579271129880416519154983000375365306552334011422337869936732563778141908090793062638199505009305651850854280195911874894513771665720079189952199884679496792110995386507277148628202004305290
96485887442379363090397741522944508512305403157236299000273102475785733608070250546314478538731862550142481388159321587786043166472827757825769381928777944109367070019547134363248263799471971690941963560524245284196521076600759612957312588175021692216537860935159000278953060063133260362767042883216170375445252250964302681265330084199489621231452
244940594821255763931924093735501099640584215706586025556479597028467951667529659871321477652922777388171355148109576349674804317144466879159959663099702167204734945709689372940055524147592514657641123407947014288442270410149776911926145691873545025454903313855143796876022860755961079136953258060208454850694257955210241965413901812544461465554916
621810055146351608939776184864091202418513244909557108823868373642620049857351060823653569053940330027745144652757457625243092987978010361469306529507239331553444740662598155677590611335515826968939307711858988616169007888628718757104122761333016561678155597385555412324869373427994047464980512635368555071495833518671167653878732434874314501199140
1578536807927910785340395355897267008009316496260759297926410442080079974172541229729194935304608712016397521168560949510936936324039021438027294325671197481258204503835361205027950726367648105177829269129985853110766247008133614020236704792701279294842347752461934698039790223136157504144053534814673878978169175237945209262561885475066774695350498
4007298423948392623786892635574658730086796454084697061387871539864249878332795511909368531949984391862085102734576983160796493156217957598499051766086247235323195667596087109894219890910614806669196870428319900161182490049825871343786676312496523354347737932919851627256226531679514205306928621662884128773386753853776572583318762278992745083220896
10172990948281159364306947706951170170995783626578384526537306813631887556963501021501141274054228325089646313648870526442655477301702404229274038787600112937260645807247389691429215536033086684413814787100840543600001728748811310125764662379603117200478763489847605622818317623531316403108956545744587360210814449101311470349417732450914872020299424
25825315183749634014446666158121214988565040413714201688821404196474734972104861668186283310453148339898412935082530577810273161255740691140960898985537564714204718682678829348268560012487622598779304084510208169917004951469635853655733390560129739081646462937996600516394377237577340256008643777820963775083559888952956834994227950944555999317538784
65560552224092712295273837814892719866957371668676537605868089382564825275643675585285307040419393258268345813162209191695201227126489296981499066339774058313542542148495625064635062041587837058225673271495443479822414627345376198895659458047173945150397324742310643721952726881994442411765396938620007892020144343638928674783215727708023027204585122
166433051343070766514614005167700188099140053365709406597692245070679595259902867975850266685586610938016309971926315469286434315317273125384870904841509267416296425715450216552843032926995360751851522008237942112440018190182227356195043048767897657417477786313839128858313799523760446734637096963055652742559166320834924651439370654682321054086869860
422509567715108848955189301355894556126060552867921869556015167327171258683846864807399722105159940037862132013660858692785380239677745866680092183179091634968529144169781414229848285448224237107009597177547195388290857460864746712995702894889486844172936059726153949750562615959886414183896656793453981079202316000143104452806134595342491035968131820
1072589448851923440363505603575525263705051509543623678784500050227046792308316976064115646811107463775118605279932460518563499816992800081307888942347191252856770774156150840784381072679751144200050195913089596211733926998872831594245906361780550851961679505533361470290241754440882177269545357413600215634566235843631157693918806995578134125018371900
2722892482672015757903435637342331983330901389760348821091514034349641736740165621376615511501780979008197200456496216675820092709833034942187719507709321299131549527369459701987407712443547878168642215436293142454991947166456078100988791873851454022584672882633663226086933868636010731849375231426617095834438915389517603665354357600184631241003852842
6912377778960731465138117884291625569918924746237810667237690079569714135989174333242513139101043616428923657417461952472482858889613451439015903438596351101455878740427108473636724032277144931275217150351909028669310051599110553320673033730252933718164310443195580622111539813757773436604684961056582313522164836786846238464373430655522869714195055704
17547871193276756414311285137472759135215609805776993488645423294711789419525892821917425729688594203361866637201712275952264283804585118466471560191096053930429844131450616083909349629530107567594627936927772345213427000994252346367827541379537160621747543700317918705567026471865690396552926326932652368523277348665608473324424097115601224696329205112
44547302427982867683455440372419630707312317834052534348367698730090770429858120043630762361386821145340304793605288484016417599785723870007907377186313358718365117463172680551901712971407160385602455939599866059067224137852686474769269472833657831486616042027293033673473506588415788379886017470538835388056572775969505373940805147337457060464059187848
113088484167269801023160650888543860528548907176943783160642377924815333163529842685987965415450524443554692747235573831668218142111224109012913787385335444393809715235761836026336084849763793922012375667787751893677674121662112613733836752839735570802983223451464406739944920361683421411517892904256427981949809491086052821267065985195255462133390527354
287088208582912556049747730131273089771210155156676458707966996799958342483713314148645117233398546387495185464695762031937225775074339172547715112199701849464945855875394909462293620415558838411315624491271600243732252568640204037591230402317965417053867754000074624037814340770224812226306653056781804316488374673566745682231267501489745465516436075884
728806651837675735193217166432267398320109098804912408529128775284077599854295966403922066304613093574781013473853807035130316918604263941571914604988543924211210751427418745957365334217361051463045716375846744501898832105893512699479422906027623473362217414548809912914138535558850580912429983307931446189286500126032194732439480775810688959067864035892
1850160054934619848123063931722412885832853011403342702501274487048531988778816995776789198606509052182783317176233278954815066702920481880221339236792134017283058901597276319338547452537719352290300386338261051762974045243595894721442902583845364470712819932222133294097489418523199731834323504391452480435706703392995280560748169731547814985365878356692
4696845480546035855556227386935358249292052817280101087805514908990117825462329138750120260770897723183692983118018221747684533835012037407503991246547287628452457309534362147693574417528806924606073332113460143935958923683360519380396026927949780624845322408993201572687572146985334422452411562189460672598959467182007512043179831996932772419968003160754
11923485975868872493021896034582280563380803614913739222263288238309102771257413650394619903378985909970885759105491149366675793013730849864854546868901457292513556775283834351611806692113889289277971628643020502637800526210766006842310243613853008661445717607333124531779660400669591958974916819602745218007247715571507941425208309406829542358048471038992
30269149454798252736103336146022719252000115940385907623664186095785454815736147553139823997391362255518371863568405991354220837210249074725846312362301765731577121117869259105891032648427314774650534865212285934123469641406954775702006158821942473104518657582757195533653624793822303880098439738109438266530287458847072540547719424120239688544369055722000
76841739955176798595261073519061696018010586487442434218745193337257411511841281125345436478605409936793912596287991116901239259480856256246615075206104004808559500068834738938957077298562513630935166709821953637413596533112316421049283653599536766752950925494416370279588915513536322565076213495436898104312858117866141220420243972791820731950264925557168
195071652348758393532241254647939627662551850443109306328097697298457644938102359194931401406006470287866490384619830139525253141189760999622717672645555914123698586132374689534166180927280685157221533224895898281734490220300370899198355164543202243016893053348674084135613331960363403394851884390076642978270755189465419151128690007007394528693139023641106
495211971674142751275819880076539489420505445595245405068620697318168306039672399184668647677820021848254947993784321679511218919934467212151827417847617763693875486941964173086076257846945657316290301767654152472687034750222231095933575562255446081992096360127999642294876905760824436118634233114410950850113899412540483603427637420764780686556118257991540
1257152917590246945161703458556857561382093535042210461979610588654522533747603102061649049207833526654173423427800727395624686440496992985781706342936441111749606267128877506468461755599754972459803871430668480168139326516227525923867300305220165589616595633547271907835456269209125337776918247756210829714673880427126595608819886334080948655142353767872956
3191428213786439404405825241489976542298104846876135555659012370685723801210187565228118027437899566365917674670218428988122543697964254652868247251483109927448125835945768718979700742337402402868680446656675422355597338625411088662254325059464355623936548806147611302269028601532709063566477406456527173277346907418269461342657911468468490357960930930003948
8101809971753845590115658894588528856181937723089310531468102221342613702774338895405128259341832612631538790593089499547997275578243321852618970025789422465131411818397738794258338661107704121181609565864275398383833751003133137879574454769401352506138989212482441219754829261922383333844374726586730747262084532055176565847229010770576711181787471903411834
20567382507574218849995381235119835163616403515441716655363628704065798246513519116327863122821617326534821031664798723960501484591355634251562849286519800325353738261371224186625231553537648760497262583948218833615270560974855632331856534609546531162909981130293560870671680094252758555386502003688505132499629017505179346765561709230693286455768216389077192
52212681448673497016572133234993632516382566318351993724325047698099898829902943995071395758658934272255057718603140316436377119383766395888408850464588666837823654754775266030276200700215655930080187277742306099455153273221382889022220628944187221679841438706804053484150417778493990989105716895393628242683407164711299498149085503399683963214331868492843112
132547936182774179957309536392539854189932169068284935252100160732331890548494435997216379271715337538682597594019917510685885200491721671227573706702121199323540088231443271564265887927628603541660361038309174491728777505011621855611259742628129156297161410055377957572403565823181441484862165751447332429119250207740874019477494315188069567334586156887020888
336488280219500761837888235679415831941578601465479735173591261674074595966542060647324952074447141581437207352509607705871518946146508187581458385786169554137151421268092365610092052809720925543668181030070798913521154185519431362482822128694941046134324724476259341591519436276767731171007136012891641825868141241949164907569265229484697199368087089884985450
854214452414777108407246658909043942393872811946267070058096378120678973616780624415267734297828707022264315487517568524202555539100282560092809333333923973571089447750891966474788711627805395070993972165223553445204827395594196290475579019367312492666199372779960052230216848737163121888913671741579197157107597587462658204560909791776858893432450972947403644
2168522274351680877592222849626833472807421055005275733683500005822943256899559442125824009959779956402292908210617657755212755688893904548781796875300533323607225216329857387071505953720011090076083771591712661833449561425425394483716503439812435986686566813108486925982815856159992814139223000901440641350396384408053197683454446915546657014146235680383579524
5505044829276688628280472082105463020709362700040411072388110405271427159648090447784749963638038381224922630285271154657773469764187079513813869352398696685405866573856757247436671113003819722748479486492040007221995246776011940679029780403597744022734044332879753230815430103063957851199121239011703725792390931714874255980369677270865706983755785283779016324
13975193582646685556768784781325920934187400487664319207200619327621457481828280591637937430674426402791339653369252095483438858774107911192587172174516781625021156106139537701676868763001771761050806752867129030134001115797205709107024231776780676079643148270892819550727577657250342818069868272356021981797227578312878755826095694018755707408307227072315369858
35477646727558163723321314686518144906572557077345176161868555832260561742770403819008994503003198362250203066375328753296201701237902454875331298636563813947210684375083767090558856556198966182517398907700136304490298429691178706895150596500499280724047450954108131763350600657045778832148446692674149329635551848826862286450582758539926373649266004324369016960
90064113236208002181211477621104039112908610784943444327045629515044127386800747367850187950038952724035533087129237045998946936184540477656990999792664331097259173031062952476669614366113847531715536119742163316638058158850170345130006599187176861548599676597350883092508312278624320412177610452938375812631173375257786770276071997491179405161781127906194320512
228638177591515649323808487134697989191296897449289013635815242444637890455133831638227240008373487748213715630555898562281193027060857122193284121861821423524303269173871120978539875431625903629112736035642381189210706192264298626515295708225388676408742002894012143841078100659903470703711498985524710046731386223258414857781487801295565849789235595600274951552
580424481782977661120166084919893687729453302801438882809185251582464369680156630965774804341492910622789430955988865805451315382789098201142474818210360662973724671765840150430978135246083341717672553248235945432850932958643786238607327653600913190546231605345402609891199202220214367385551193763933895041251243077691557439040049774512393470011808665436515880066
1473474739004128780248847503553493420522255736008914080397778284856376827239749834291312707302658089656185430065206383396763324648568732146232867179195599324748748220192380404956255649179389761812656905235972462915337460413807007746880384121778749291536795314238235873042888581860032814186318611285714607880338463700211233339541513915173486202927792270585562039172
3740586199627389586271621680298482277233732893507071343469342217503450740316346014605570731221593977785557823868407938325865840944778486928021106750880941459493598418599761821294057432353808247334148981016874217634593432519223161063074838733495724472897169509976603561278527679119311742148494222581185961562347814484546538611876223774271807051462511808749800255884
9495911091288597060124414684998862009244367550878382095751685743999364286207012267500444508373891801386121361585806810396636893448177098868416282345594181666061547203226475272617209768005855238487379402044863851423370626141037063769211086111572509824184208440632885792701512218178163848602234779191458058849601456437390843882536863631161365418546226423397967781532
24106469585606693393414543808407595419641142719554517600455684604875340768247373526595179868927148289653776941734005596456930134871562805501551518652769408264586519475033553528341001237606630789735415508899767157718104129451550220409418409100179883201635396878087909571765501833095099920514371974737792720104472857521143855748783196755031766004173700588560927876554
61197063693539930514783521129769443723825810489860570785873834547598885455515829393271419999461550316164866388968015320452165699398491567030126255674160896267057684739512914364284562795696745323589948765091486045929100106560535253977989697078292086397381666931726619479419861326167936868122543673981844242663791462648187555378429187139016134945442622677003752843576
155355830575343443282418922186654836545678904210580483924625009034453174615428727319337881451251207586650601762100836151350783722588533034254544090713553187190658912441239747061310765962948849997010118724909652922082260652261319982299468878867294644022562880248339890078246229561289057622217855961637543769399673541948427673101227264300044878113602705493083226133080
394388760457841957867700213701032231708971511512651456315838003698352802891601378639528687671945111027709503780255498561088675467679100690434653937815483532052321702614664691067125864810083784300216683364247607472009883884881647095505291419802386204260802509044590085764502690326901952988254290100954648642767585750588333589344283372999219859528289481586450069981736
1001201524264897634664085773324242844481290353186297256509634040975289524871275926657785478116396684886044255248510644380431517116609847120819695064362521054216432380107816601056645137192278408737009122157031315854044192990616413868062959612282957406973602841600494622298423618957141247405213576751958489059111408517298291269882946097075528971397072829393620014419034
2541665971988332229013517650807009923012991731466597028587567905825977191750412985349223988673642726970371180922298628900790983422799321121029736078603063694423248025301996004489205034874523431404021322357830026853872732553034017216515554003514390020821066607725216255448780020771676222410622565456533032107622432914524581927630433598688424040568961833650977469378956
6452313302166119254902225343047095908116300050491066141487352895240281002075603794054299439687439809244062466543208385591618433866048668137084098501013755620365376318031535576018759380476384961678637641026137123393896343969798887960445913270857217091090296760810581474043648128365120091277381560176711288817332184904417506889439419909829511182989093068409378053765588
16379944260236949656371014654760758205004974369055383283446411523880290140801083084131004588161316813684488288214248238785044475812155384965022932968324080053196705629066094649969764421127343752991516365818119276259459650949314629713302306743979685614136323562915196300152511750686212085553835387863526312374454004353875928683718098195884032363850253626919921087432756
41582384705094370999183530467325931224697855729346002049202027067564477427123823712329945556466624476802403402918826635332175369627419311082974285845832065012494100223699085044055282670650688975269274491129884061453010717722775414782528291634927982775784710273601617659793183335516453156246402341919367627227438921204835998560937115111125767983937842552750263358057810
105561697298318735030318157208886196966186051827287235410909739298234950323449018990162525398554645689456029630102031605951993806569851376942855976704887842585074107094769284240501780457477818964568327754201562455491020781957616330287284924219615292618482540759137681227252873936446766523456334904668898333676743914223113422638062020393049002370166968056172590252828912
267980588788518432001163571385949835879874166425646774494818062579078556221619123030777232173407346514391951956156428390589867834636279274258698757665805410709108379696836084845193356794478713335370809400052791604763040041431953118673467731491984396651352151700458786647830739170919135279575185277626190585876789847052564491920001494526410987163498207032415243100673520
680299747023722541720967410909780961447729699416231398996497961143378348376689719701350628619152052267775644654893514961204417018969578065202183830018046456616573478764878662733249473583739030402331241692067059273861559862282902698069751034897323098602236287934904896730733371294385109379124071068614968897026643684495559760677970897812552475463304918698595061078322000
1727019661732938848382809180641015131947533483758527878210014595916008385976843471196260616344476130662225537364814650127016757463699431236119027507803760114493709602957590011719937382512130538521536721166966460907720168961237254387694395975974312388045996508026053621962415656393231409426732245225063889925680818155854857658480757859002954688497210157902425691210391026
4384239337234604651235544197538578711996964085325512240834298728258851306587277154723830550978996318520674489757205505001214607102635311431067881137016890163387423511146034463456488779060259530141562634672163019609128398346134024264468643482978917472612243829280137145317889450969841533576018596936774234807338087900818819277115516544971241355964200707193383608628907924
11129899092676160347795935505925575600873409905761264214590448788642041244596480935468258309582048140344640716890409708724643762929366608478228148387271013053238227650374327709731546732771780789856907037694177634090737054931608705026860044579603797920763360250443030527746974211308294802526828727464072502257861314591408798841756608506849698125159710099826843720622627420
28254537283379374843018308456556059323293410714072728553425963803113146678790518957693007117052288708673954983220494642158887642155574555411556187862986332660880456595890422985669445732223558593356197144090815444858152128495293852505338335208114129109261451431329132998935629383064194962731354229420180663176063812357241080681460705283448522060716706216934198337160610636
71727413739374799927540208710527127556287246552775488932574242322908681619576288948071130367655157191658067958072212341891650353428311136153551937734284671215956231073195022475608944754382290244664619815392626579587241739122774320923153868585452331502871132213010106384691843943198527872791060965120021751178854896251516978150684352349656912348321641377037742589519051290
182088343197390633496760707519853801269411458807499418783653813403018425414127931095315588901229791838495438938561800055653003072411673477604827835557016871810584343548568269966550176286728395626469382478250691800318442023719052961067732961910904242855350690617072554857078887680878697599567191531089034059001452875935517339257892414797482713923721475695483578020742976936
462252338399448277510361151053575314605683999198165622540194632634269961954423883106855682613247368783303744543717445219496175330298186725171875319243901433784558463702120066622710897350546035345412517336799183504185800323624675563997957035156088688418684103047950087013417178693334355821780625261041822796266349234250995272295988732234231906547812531811001088266825462600
1173481072998307597002181608182360035960909833619851833335974371231872558176741569465893289410696295568956186031634560508673943740718672688657858621996253601419253608950877051212973703498007840047790757143405312894692153344937202260790410592171195328651588774335354203970544074245093246059844865883441850871353958240227232347487854294647563938307141438475828045733259387128
2979017550140105281959104312142690226150651994573811563117604623249156871053651331902937896613082902219187051231652623686925882350638683008603364149100560998002411689282052718213877793878033249778132403819300235776706265028808424048364423199418211879932715505745473578638456574458296336436907660191909300968416564093336937539202585576518283174210786630559728854548202796874
7562580912675319836398610246062803696281167116798494966610422537096537359966065967619266595722293449848174424377701278007860304594530011421783522739262843203084798012610187675574831376337718504587490669730063422134743678123960954451381486474777541283186591044682827946048245827700989150949510993159707692146009799074561866568046794692660713125863952550144595202050016419740
19198487118033683320221427051099843087547502554703075015324300210861913307640375343219478088462607481780114323699156127591720661739198230208629931851978202633120470649584846751774181830786033863981077150148715873537701379939289028041908955199205204357354119655233844728445733834521718838474928200197392107282411159089594138791819040681297096630083008016267993109996745121572
48737582034136103346324047578222273151316945187475368670970210620650460151282321527337506864554332354387159579722044124333984111706897789932278039506277223277824967554776840469483244529989446077628661589262363432686169739413820319150642447541300262849867579162677752395681590249773916552034907932213822847791362746381865367988814353889526617101779489310181546960730376876004
123725994029129038942252833078661315311317213245333709002485781212080829068966913137778374611202375674857386009318650571522614820053770700446852261387085726413723692072785051809579067762753556123822628543181332003954961147487105209530704255730874063728002931052203011934796613087647588815557557938694923826823944776887132217964375785332844284386207876183169618591902413952546
314092758803138237773109517457630294446454478873010500282873805780835289185183784611412073370310494544777036955060778414537616844637470531762784260822032337319941175968564278730151092300251655179527916634320022548341602692047233955730256982620715785724219372163976667150113184833500562209184586334582416826811802527433368760890788991774808322841672667504310940087322107833696
797360828714296030058298032967238516300456996416440756244103052955393229513377127786925360322379683212274641093013925851044215767707885114763346897257659883544800271622729826892268012896817564315424844326626698112758489580180326720262546536819784377562063567762237698106902149177270187783889400882324427718971180274966865360524519887117549076882285116770866016546985034942048
2024192769010746561124633482270637264022505469275710463719952365668945839410470320048455625027529936518775743657234151512452419696290067682090835832891490212179860478591794948095163319398620772819888926424793140746976431988894731252074840974960552461966427596910700459040119032096020238907067766488637664285709438797408069174890680541008552847777279305494196223045539834522400
5138647671872937745761896828639152287064333186883615148364849006899088388546294239585716198570400626047404081599693248469440652058774735230629649200041321243223162840564706044324139547753126920035394336777380964626741598901542753242744965314050116171336546516070125991928612605967227317779102720011454274182561577866770263767013198658035431488021991385704672217602307937214050
13045051983141914791429574073342732364019217798358780211964270445006117286071958648305904999921412253252587405282887726676235328819351306127677060532172335481036387271036106609784220800810111912259244754385414837070260685312561549504844776487002484297206040462601154172873772162605455300013746757570117438325411475305856303923649507615627678840675643816360315788289047581422500
33116374600722507982191972872389733290422548028349810549462437225427912899928942263473256507250945568774706127543707573117491338131379832467195094695901992907704179537640765238918662071226053683264925173802632020012810194030599469711292348189003880390714382331283397109631433622130594945555452823068192524163498409025403862392068571352426664038722996909912449582238616403170348
84069750592993716616843933716457263998777370748925661689843669692738829434319683664435346242231444328478554646111038254161024449480202874410575847888957504503214668414816126556852649967964698123797440109246124925659634992872131263198859159698873049495134180152539551040193305389633666094487261487742349040898406051726387874272300441161046375630530577986630382528896251929279996
213420794093021557360974561859647682137425735144716999203048521953220338484899628798791111697692355914048750818343409449674001569643237536730817413305415645102988084203406276416298322024514406709641635394104065181831110602081881120053358428115799007348621590558513713945830546304284838797837037826492302527655547548758641129248452208453726153145177853546069704863293949439269738
541793392153727446782682619480773158055580333528944480898823779286068627324652699047812307865267121600757786079104367988111304690803472463476073393529114648878033533432199382078248840643316214212607545413480531012026131487159387376586695255738338837203288817222140889925658608306181275193551439739903035527106321858225106586181017664140319408314646513061935591408192217512181272
1375405245908233083035818468120316885678879943877821447373519700318528185650394230627809403148707011941430670630217185940366054960064394084059825012587047571863318077979219829114307687470957899280168406570479574556408024386768873936593681396499533470504266837587513502772223132063795490739357884980374170551890425119540123544706407434218425035697310574152662277067418446447512376
3491625438530871661531896985199341987192846455273023519828433584995491778414614285418096544874794999584757966428067327211767740611929460896020737833510450655779941722830841996109369062147484111690066073288958205698865725536564891649452895607943019650213002308654820908544295693521017520364631835275312156143580804909739565877550246220971082957364089045323686709753529680970127816
8863895378663776152931040229537419111769717866388517971809307534009123011965611262794978392014162135764910452776703699777718983332024002569939796318442182802633440618959131162707154139974766000224895504286018563668326347474430637538973121925524227574376582248598900756727550980861548310618713598858058884864385363890867806801399724190552103322638684066374896495688805769250187578
22502024534726556909636920112713661584622949089096384569427266616658241836784315334218343375345767368417233283228212050086352642658581611227277491672260286421978162061053706041482679869945900639482193887422474920633594228735612697880251367529673766345373924256554557214924905692943721955681526538045896776439257809220359604854668143618749841896925571588153777448158026225057787308
57123994195627155885107945182223794304078520944301579490189800831662274326321018853818259848118976021136202209783914031244973825717416699886452925326971084709526639992343210245275237583017322955314215043409550131762517725733725761476136869091009482009579275230584787628988545092632300982610574488237661180872015161522515815101741650610880149560097643792562636745254023073123206516
145015872141910744945159547115999415541056350789291915695443953413618278080694060135901346207775957507161808046898912090318982710699878077983601979195088827313522664591706412244210895688124399300833092926380971183154436939526380535284283124998261061211366236785735709082916095302949966775711406690126310301037356018613754792187570386299126859226133151674006722105200016738831740308
368139578984286463994192184600556515632793563155382739204222282791253744152427138573797503753112494455526464399685931842732926770849450335855494622018041434004775725664950964058714060942366409233555123669022111352235047220523417835299310375044717781325519757768130779750687020386138639915899622879494208295804612105722689811670687510773066437101249131823206059300280832943044506610
934564938395866663018124493181377935324165735089842535388380137363077737650384675045979523600884719251521373756830071853700223954322405039132564843444578639639521662589682038156782117964892871797630196991409539727887527097367757916095164629433612487399987362903117959624154046885856333373682436700811611608379163734848217182367700636541376135431494850997454066768611679442563868112
2372501284672111920019422206514093865135884415856168297284506734313088681770556525821569622140561488420908262429018097243473309854661371293895367897862033577371076087318196390187845804021287086416018670511510909925698792482463316193696520628051147897037861043001610848212838489030722314010351880268596680387164854805436820218803377172641511576173319306085869444672639014366676475344
6022869160309294983031868577305829985195569526370548102632773131183443628617722184723404630184443383940968151619223386599200196786968530072328478217772230393325166713077561340816038617775751497261020580594177647785856981658141693084269032889878346267436023533058931765255527126363829981711980794869954477700516168887738449971188350983118769408233263202194241626387139738471223414000
15289750592155366944060524765877648345647369977429130468262021739058162889628215209571786961201352800676236544982508755820679492145464442990038057166397412096118218001277102349752918668606657832992373231897580147319571541306997920559040088152036481135473314184082980087439110157403530564613200099754973301254408332022376795826918742549210876135051424446388520067882614979733716549074
38814801873980966677164066766520146866738275910976863082608956409220113410601146411993223462091354111644114242102258162206512982109865608576074899816059796463784138916662616638919005082687137359472380480951903310087346988062720352815320365457160971499142940711183719968587751636359132798003340465413473808743898455944205068340975133355917644069654231535991238565962843087119090843572
98535867896326189196404868116698024319516037139927059193760916768502754024993835399504781208357088545179673533360105160099457864791384414281464325427231989910525456497042511685899616071057374476823484935022122529167821887905616476773879362066689360631398323767417147429755507823828389075819471420865581944982746092963123648612214427016661013169118104866456903459589275671129844432636
250144707516612872842048688811986875666409455673320131718848476008512852720551255388575840048678623096236070612578932519569782906298539689807330814371560978949707921537933613290947443588051459503868004948747069031657051650980819511144588311633506048257571924122094706387063825731931812600131204367918119382644988602657642292223729986629854331615675087114313485541726147295501660868268
635021297670071557666639505090207154584021803781969786128262894474649149559516103961746582551090067860219496352656067790746135070105581434015478537131863756889016696237904119025609027821450051075430592037532156648794624642954429190765334704638105355915127928540739247783902273996205668320507870746495428339022080811375498540816857303130406277565329345335946820938587774738758545463738
1612075076454697449301730718337512158728568720541702580389309863838538609920748194313628506244914558934195901105852048462639433205335339027658764951968445288320182461474253057900232715759575409564422604583466109612655055800121984803087407673867005058581745998502017333451008935444977316487642547852509405362112545098084239437197720858843116836093426886703598044607412135813379814642312
4092439201112638457449047937348162899611878174440631528791209481377852567544419921173103278703009095941538327225218472627731028603076145958015289674884728122429507928845489638955688216057005376748793868279524516988753079472096805442190187495809898093110002329608740897125450275242330733491857899883039010581962020706567315020193910777703998577255280394716919663468136802184403242908200
10389130667311141571010326990002922683179259638074048777823361377491996908531855278438546244842345797127265534569407839118818436382910346793124482993814180286671055309701610768951571251578312929979439766599664008936884072909509541620169109241711101639810812723262132671972177699114136575918116358346024094592749958589209754125373278653463272603182430959283455259815648473813550685041816
26374010881608236715981927923117354002709159987727925238578784884537270881870570114557788617151970736129435417730204594358566198631407888880977493970592789998449778250383598819039662531572935845403052652628976989274758817805923153709309112831946094704593266037278451719077140351819185654165171291499602827964220949206761157957555794447778714966253898279929500578291334055107906772079146
66953479772068177108388144669881739731281651623264387555611183425141369055636759137960091672827529433564521151254639970161946646027819518459832139531012929613702833723953692955971323849948062206831819706481699072058434678286793764577663476829561601561169898860365704321298744486826960309670502047777685229312130319276891433562668045505919094820455524575695670393885103589287488243067836
169969159173843182964168539143340505001234982120277159561524423345751138625495367869331771368977317841074920396056091923431119845155710267053385590690467806773392621258116851651074518475942375621259659053301548621781371925838511558775797148335403087345014706678372787633932864554306349509326971861745566935949164640495452989809895033378173072944309264187400351088189715143348091903118532
431486386795917388284159838770212704142794207149701292534937005150202470507054969063906695094148098874147277793730462437587819021487154140057604955495590073063962408773075502344963930840213316895356291980908205418066979645548273880908472133907748290042993491726182213144281115077742384905582721594393322769186897979720376284955387847526090178200204211925616497067382617828868897433256260
1095378143276993024995862394410460292828204235281156054320279275026161751035697725705114538197747745299444789494794033376072550639861497666183294307280682690445754170864860920899173913463988196464971315308085086924854592604005906503922520723659125646358269865125657044632907610642262733864643554108222011779612085551084636840362785465244467027614369801354571856101665792820966908958693058
2780744221570202637740095532744546723670808572244424762142994897086367534890151412937339015518664582098598814936191447750620446278413702596834859483702622843086350750483592836142097975506466337684967716177865186514338835325718131416688054895292503299673667199207298644607810466818224498831469109729517220455011768099896011704579224604290687360560985022761271674555602494602262917220729408
7059241115276399731867764715912929129713672182872036207418198757270404769463083707026425488613505774888867573670566129301641475638731802512974483261665898727709677646408873361043690434736424810130425138063385684664034268494190039638180004118423164399322901851891919739826806789319796045090386856348437385866823075983015997509783139477396301492894610488567854418267961054332069949395450944
17920700773935136077508155547264243825255347246820311123016765763811423577142129757581206626962993322250190476017657549789966561576055169027309701831671267833764510860828286054918192924398019219596199369847239773925104002077352802982799548714020832395319591863673304892747700406069258005020007545533858511853632415043375121032954545080411133829882655631874724970511178130055600812748230848
45493773478559659368267511855275712755424625950177001190904218523017083374465821829045700738313416775380363258998858496058047732512608035553081945526549770127221429684371994080538744680719943580548284898773605631074453463095655328912505516597962112636295922897841509020566301067783921836422494138413779366310499531404074850516679705372277962952046931996717187284548739172391782598804597826
115491210496006994065555900905998601625603410600494976975148565956202571899179887172138302768844473227581971137628091280843366083178276506731669187676812901309638876548066406384968592316269542317713085977292784627185385228683354315930938177282412064564258893018453086991582199835884992091535698764927918205049629509028763959784281446554876277938630939302809387348139514990832889841535484868
293187807516539434444498279143933070241259050790575370293490236188086868162470242194232019249003299136313155414889150583524535983868390549027857346005048705933901268389629102182221978579919358167460768150501686653333503647897503723359468294451129854009793349957134501978628407784519107890966757571964115504879816326761943376045796353170882515614485041823871553742622113120670213204579154636
744291189841908674361081491936576162048131018128607003278485933006356136951510744832230449186031704499279717063054424286409675230644173209440198878142294942066401941367475315028221845355335933028847337827888971072813974829047758223738601458985180444270832232019165464792036313511309614297179931942490367199091525023816640091659750733787372795032020753891802232582936956008278241707368314204
1889469347203441888848315252204296974082997942587551794384559424999497949804068021537694032070694477591402165939629825674239737995181182539025856018467611263508550096102448015731489207918691441337738324900969351828998639959619470591246768668905758580069029300813535268578731343987671382029644475637466908364153923214503713866359210986179036028367796644822445985239387847448622912739628565770
4796636669553629251595352830899878733405343230451661831714258809591737009085396935523523226784290239136319426313218290035093120567092206905608064288886527900591740414708654863539946741704485574715962875134006057124143607510222804499182741844162030405224395258769585549775860699264808768963250998780914238321780893332145585123730612180145928893509295653083562715507544895663294772326370935544
12176817461346864366609671461479132161121679360611788615934154839357844512038378666652205638586909323593196905794476533429370902647126823019415300204428737150001678407276884230668650187115601524217168492564674562413990048929486537456741286402616346936054978005085045209103739867266860181282397842523745674478566399372427261172905941218246066769304628129852284490070613687327949099921841528856
30912260757236012133074499572286004002936180315080404309806194380906523279590925906108300115787041874775508049399184419866858245668719867981435215827837602516236139393133657471982437287158127248219633423423311506491084007789227500953093120614730417966691520158101356445393774758599304750729188663276876376071478264003954904952214435558213292063924275030118604673260478427093520160724536111464
78474352445261936385025951657934811835388030833068613982436740246344759514891883296011659087250016396056173223700515152196511793492690150729510759505227234794800704867506221693953770673057177836779416406608929375390859538376601938412550099015275227575113235109647167478022039197190383708126315489676882532820681463302976875869138740178805895907807011658597098880886482284964971889379641975322
199216228151855797554576912368383246087810406805526121184331818385378613573974258006459030355684588133613288160923664367303091393595658598288669414546158728222662072121434644734075062287903892696279725550069138696060050601982908608316986608298940627616723949784096542978400008876310465324109463619640940707148967549201154624420625081217692171298362612770810400843660238945124380672691044051404
505733457141110307979666400369543240001646194007640450329858883340991544130588809459376984292882034633381103576244466732694860785486384585092905216651525458152454953598891302142761441534721488093896185559074187692333642314070052629009628459801587221386346307476369753231160286497069948744295578734605639402274907896372780451848004712894815617053795326928430074592643099293319613902614141359380
1283862926452644350431509221732269352511073320275276319373314117340957319658933294245757011238420254616651945076334416315469739016847425933285562959212751505676868781098773107837747903586294533155012622828492105532496750763141946098781223058785235660822605564459739613908470287110979365471286642392416271529277866228545871305751196543425617076952626131111405357784094190334051565532575622982388
3259234663329059658098223371124793504685206245787849911020119104839485259945987574693361589438485418628895694207010952513919528610968993990909108282141463706008124030019965752186822336339281434942037582081603238432931544488834782177360279919591039736759569079413672815800483168660668081491071830504438822981628294614737971142226291090384286941323924702196647161947040583649458569414377082556050
8273944493433043198654709297343422480477077150916497681311480496064280684522638376965942263123731865357946359575125468560691905078255729276492201463951538235287737787161129760497692659069612852702587764252111451242249356477796259902580735645448316980008380622578181895933986347425465461760235251944139850924411473443023278616679590923047868973743873625530055291120643588325505422761368172409520
21004365917760027320622513293841436505304066346865782996246429850466608793749974124286470666940476093373761320987848476250978250130240979253324398790412026329390441025763536111836295625179920997073121632569519355977701942721048244591329213472309829333277034582540599948883158744447378304304336458846930444155798711554803537358157375652907893293284139720159024265159823062575144467188953405325744
53322014422180666072789507661852400314702947824264137852448896600723765756312183147363859692489865334822275917788260400910970992211902855011100546903656953223016978346908173348132079799406799362822356252308547243106536260183161390731880561455119448813874297815869957671941794133535330734618286402965679215726441646994723560970972547514568567728360803418096270146450946324836434206604464613340816
135364106356344360047612846687825622183745080286214696245787811015091672991025025364062137782051704544305077452608977769716434203138745203966774596742376346340247487201041125151128187867373496449327817823333513534116909237341661533018618358483552962071045472631078424265582416229775155235815847050241378440897286064827745610567126955579241471037126063727647125402927292181821605071478476775070130
343637454214963040798214391409016594466765000678142599885292036026761940591697107151244995878325919436865130458393904857313545795519069888725593691175194084703035786831532654535345636742270362482856692650397194293733736466085345618220920148578173480083293852351393745873216089585151680794019829240664394275860269473978354546976563845804852159918149328476698797859557474476491295044549344138579924
872363458216013496866697974163821069176918332627052099553508330732726304446569872860173018602715993386069625307417092928488996263022065454615859880818238981969923032397094748788519785245654040135797430075413840525465920829208739765606645104685523816014207088915745024882596582107230388894739116234727117446218026495177556730503593883391958019747113317292658330497227463729528076286035666005944220
2214595626571445021307388545431876483234579453862224144238474008089516909850796092442075613090470281892081632544192300433083186703016683133760458497405770393888439642402080729693606548040508611701474966057263589813272032376088009092349774351015408116866785235087990650652402305058749159640504483253265945778088461455651054894797034094749705984984633967501516276054166238373231966724817531352248844
5622007367501335314799357103061187538073210651908481984059168416606054220402362741666069409411772416226877332239039954778233708544178102603268223970840006928650901263136326773044689580955158075158159224787893985624125342715764468012489616972729069867666442415935762283589148011391430890718263387544898716337789723018528259767215255220252865160664321976362598742786599747434359101004086183214296410
14272116525928496719278309740067502498728508546965450657373560223952451592204875029647189003677379328902643809410024229422969343763864510453551238866030270765841871533114158162434898324242295655930530214189884664117596644991372820296686412586696081817121334976567409564591123558271051003722077338367539483615180585431981870409993954709026078411721834581619612174546634518632617277930285441259781992
36231419991932787522407254569557448176311197822650469093942017595670704109959453230602538618600078919860948643517160860464728727473073925300733868559747253583178589340093903160360482499559544278910226375916443960382365831491307298199259155521505010951856191403746107419938335111314695858494411601553071625795981720484895707295327945552450433194550158498254047613055363519117016900705143852249603336
91977653927291342875079802958559402757167570889277099678751292814123719873374727129609392038821841946965511873920482570652011912088537349435794225407280805234627558862545549829194989033733872331066669696694132867564946299909919310059261676621959453919488953163843500052533023621447381102636955588004690731924833627252349690771010324177196998876199976174523638365684962819003782121987503751942426680
233495922154092602671216852679159884407573730981832718214698668788289999002660973402795552716900855492074510748294278358165776300139671631169221934172835583032579454602186916427285835999057399983250890941629278313283556315535472043936158456086265835976114061597980158099349618360373482805536843089925344464549059247629055315079903885261495572478720922158678746351173983386410722590528810509078792458
592756428704830812767057111876391180475588716643884148256389448237438481124357369633252001277922616367260791766805224366129088313274134621062115820906768540133898719782391284354675583390705751726745198739003819105049870212899540931889008366960136639704614981692722511028479737299283387103080851491121466624971002894225000467521166482481510354732463314251516286382153799891227592901552626258803013596
1504780813855196932648795577763540772428300951295530002678615666018880224617246685043478862530603338744600529925875201167750434130123611730891820927904393889446879820384159205065893343211618103036769066343794373061919326288541494629731069448370391054474336371657464445570530999187733673470455889587637312340986438749688307890955448032684068289864518678969596836348341004436386083640893009884128362084
3820060294739161628364351476880103539749799444804439965119364183750181133351260889677480014222072041186539133762692776922079504198604686791005223854683934498331025729991272695815761170240266781891593417979031960574936226671721046345427100395110483170325163536668257097051855259874734536638636751565671559734741598419820855777564431583985363143112722118299392391124326604701409690025821155019647593124
9697665281933148099163396738213666147812597089894004357297879471851535752690961383578209303666406382619832254591819785805567476331047999432839079857535955278320593115788268149481243696121415666386485462109274307376894921810261472130474481409127741006165883914863978221287162661886743128817560422414300155366063127798197381717077330153637337728968275888193624628532201601879547084120851887799024675682
24618645954339056402524962386536849010743779883449712787733645427403111803974308546057672911993672786490802508624079947485922181112332283606967081389537760314543376770573154564816898629690834442209364826228027608884873514599781588624230033078695802883738037141442264256565453582446771371074563420275790272144607577830884859674893793892358775519165421969298356652998528204180368973913112692127890827040
62497282696921282679296810873504364010041456008374084362502937097027813071245264764960283265406617594592791788832289113906570740619674804228493695712683956078512768133124459242030655654355584756445282807060334284435583745765185523448285897633796512493631851410933435207172052968105293599977430071836475047892844653168211079119768832956705568499906470157354774617161147407153398819657179859698664181280
158656587033393543593681104520535197285695077048664025550996770288908959378408484744556973761689840038114063219491791328095930395000522863596248618344055456727802129305809964010548382346090273846427917760337207132462060903781132326229509999001839631912733172811691699581952543037205378221107502890961601889077519804821617969932735024974839375723319954595218405674379274623609851108924702483074708258400
402768112833884687840069302753219090717798103437070798608830003388918857044049843310497377533871976075051937253991820774838725385346778767868389545191939260261863634452510805525005522437631463987714156944448301923402437191703333994237606208523008424051419858077229719286405447507614544028838299507458873485017576888116085760472297458232009675137090281454743271905615989255045308993458391189089987900962
1022473480295052953911432155187036696997647228838171192382381318589003118506400435126245808972304069823637219877926725925542092260567585938079256017036159282136849368020965775151863396888423140597602948621678377151742702214038343182661890652860798889824780396097418231578937328735876028671011308073443790924549111657369870162245421094392645740240172953754512162578666761147183891539364940317059954783204
2595667294888009478994937517712945544869541966461530015242932040475053845415328852149332708754379029315742979613685799858476345242447358488931287583480770127420334514468457692574671729614284246234223658418639278169801740749686275224788259622397731876420566014136845937773952519380675682557461639451718600088871182134496886984689735888256337647807793031385428832236968098964392097667454437905849133032812
6589401911731749033726281844814061499584477260773924843583963481639185173133767372674719254147312086166770587694733201346455354630336854181880556728994035755318442625379635288413607590476242119534652817952075913928746072447823701152654598132472884316300586277125760599714921344255079712620376798926368636945882953612322960742858454073808786801545071361965613851494417016336671211535646676550712908088508
16727959565483295805459643717433159785630542100231638131497858410439390657129441422706109685392646067392804632114976371333617940609780032233333566136069232461465719178106765217197837368841837914330261212442521931817012659158646600383799540412542643029844163648407606331106278517307373277042492560116745765705427625067016040891077835193576967093362473160647804314211052697562804144320930739468094160577194
42465861844949123674293408244255588177688602017926237112060161021796047088202160321589238270543462318311301700269974271568735992255906641790644926580201155460864503946056851401225409856296014715858983692573595512303656683927606395805993648498096389829273148218890460217673432013099430642881826747256235396049427904747054099460738527852651478234439675936210490829515669991017350407917610896542975826048984
107804506292289350371048477751462318472338875681229430815191043941667558989810997595390590112331971628390414468994120682970273501713146998173127159558033474461443895512036420352593950998937505267543407832546722338553648282026544865299065441178730028962054017194481457835903530891684124097165346656344943649706816334537991246202605553833095654700321948501170791416701579443451358779073244356826563290108152)"""};

#define ONLINE_JUDGE

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
#ifdef ONLINE_JUDGE
	std::freopen("vans.in", "r", stdin);
	std::freopen("vans.out", "w", stdout);
#endif

	LL N;
	cin >> N;

	stringstream ss;
	ss << S;
	string Z;
	RF(i, 0, N) {
		ss >> Z;
	}
	cout << Z << '\n';
	return 0;

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
	// RF(i, 0, B.size()) {
	// 	cout << B[i].high.high.high << ' ' <<
	// B[i].high.high.low
	// 			 << ' ' << B[i].high.low.high << ' '
	// 			 << B[i].high.low.low << ' ' << B[i].low.high.high
	// 			 << ' ' << B[i].low.high.low << ' '
	// 			 << B[i].low.low.high << ' ' << B[i].low.low.low
	// 			 << '\n';
	// }
	RF(i, 1, 1001) {
		stringstream ss;
		ss << B[i] - B[i - 1];
		string s{ss.str()};
		reverse(s.begin(), s.end());
		while (s.back() == '0' && s.length() > 1) {
			s.pop_back();
		}
		reverse(s.begin(), s.end());
		cout << s << '\n';
	}

	return 0;
}
