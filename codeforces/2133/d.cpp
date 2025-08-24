#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC target("avx", "avx2", "fma", "bmi", "bmi2", "popcnt", "lzcnt")
#pragma GCC optimize("Ofast", "unroll-loops")
#endif

#include <bits/stdc++.h>

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

namespace Rain::Algorithm {
	// Fixed-size Fenwick/Binary-Indexed Tree implementation. O(ln N) point
	// updates and range queries. Not thread-safe.
	//
	// Value must support commutative addition. In addition, default
	// initialization should be equivalent to "empty".
	template <typename Value = long long>
	class FenwickTree {
		private:
		std::vector<Value> tree;

		public:
		// Creates a Fenwick tree, which may be resized by operations.
		FenwickTree(std::size_t const size) : tree(size) {}

		// Computes prefix sum up to and including idx.
		Value sum(std::size_t const idx) const {
			Value aggregate{};
			for (std::size_t i{idx}; i != SIZE_MAX; i &= i + 1, i--) {
				aggregate += this->tree[i];
			}
			return aggregate;
		}

		// Modify index by a delta.
		void modify(std::size_t const idx, Value const &delta) {
			for (std::size_t i{idx}; i < this->tree.size(); i |= i + 1) {
				this->tree[i] += delta;
			}
		}
	};
}

namespace Rain::Algorithm {
	template <typename = std::nullptr_t>
	class SegmentTreeLazy;

	template <>
	class SegmentTreeLazy<std::nullptr_t> {
		public:
		// Exceptions are defined on the default template.
		enum Error { NONE, NOT_IMPLEMENTED_POLICY, ITERATOR_INVALID };
		class ErrorCategory : public std::error_category {
			public:
			char const *name() const noexcept {
				return "Rain::Algorithm::SegmentTreeLazy";
			}
			std::string message(int error) const noexcept {
				switch (error) {
					case Error::NONE:
						return "None.";
					case Error::NOT_IMPLEMENTED_POLICY:
						return "An unimplemented Policy function was called.";
					case Error::ITERATOR_INVALID:
						return "The requested iterator is invalid.";
					default:
						return "Generic.";
				}
			}
		};
		typedef Rain::Error::Exception<Error, ErrorCategory> Exception;

		private:
		// SFINAE base class which conditionally defines defaultValue() and
		// defaultResult().
		template <typename Value, typename Result, typename = void>
		class PolicyBaseDefaultValueResult {};

		template <typename Value, typename Result>
		class PolicyBaseDefaultValueResult<
			Value,
			Result,
			typename std::enable_if<
				std::is_default_constructible<Value>::value>::type> {
			public:
			static inline Value defaultValue() { return {}; }

			template <
				bool isConstructible = std::is_constructible<Result, Value>::value,
				typename std::enable_if<isConstructible>::type * = nullptr>
			static inline Result defaultResult() {
				return {defaultValue()};
			}
		};

		// SFINAE base class which conditionally defines defaultUpdate().
		template <typename Update, typename = void>
		class PolicyBaseDefaultUpdate {};

		template <typename Update>
		class PolicyBaseDefaultUpdate<
			Update,
			typename std::enable_if<
				std::is_default_constructible<Update>::value>::type> {
			public:
			static inline Update defaultUpdate() { return {}; }
		};

		public:
		// Default policy for SegmentTreeLazy, which has functions disabled by
		// SFINAE if they do not support expected operations. In that case, the
		// client should inherit the enabled parts of this disabled policy and
		// re-implement the disabled functions.
		template <
			typename ValueType,
			typename UpdateType = ValueType,
			typename ResultType = ValueType,
			typename QueryType = std::nullptr_t>
		class PolicyBase
				: public PolicyBaseDefaultValueResult<ValueType, ResultType>,
					public PolicyBaseDefaultUpdate<UpdateType> {
			public:
			// Expose typenames to subclasses (SegmentTreeLazy).
			using Value = ValueType;
			using Update = UpdateType;
			using Result = ResultType;
			using Query = QueryType;

			// Convert the value at a node to a result. The node may not be a leaf.
			template <
				bool isConstructible = std::is_constructible<Result, Value>::value,
				typename std::enable_if<isConstructible>::type * = nullptr>
			static inline Result
			convert(Value const &value, Query const &, std::size_t) {
				return {value};
			}

			// Some functions do not need to be provided by the policy if the segtree
			// does not use them.
			//
			// `combine` is used iff range updates are used.
			static inline void combine(Update &, Update const &) {
				throw Exception(Error::NOT_IMPLEMENTED_POLICY);
			}
			// `build` is used iff the segtree is moved from an array in the
			// constructor.
			static inline void build(Value &, Value const &, Value const &) {
				throw Exception(Error::NOT_IMPLEMENTED_POLICY);
			}
			// `retrace` is used iff the segtree is updated.
			static inline void
			retrace(Value &, Value const &, Value const &, Update const &) {
				throw Exception(Error::NOT_IMPLEMENTED_POLICY);
			}
			// `apply` is used iff the segtree is updated.
			static inline void apply(Value &, Update const &, std::size_t) {
				throw Exception(Error::NOT_IMPLEMENTED_POLICY);
			}
		};

		// Wraps a policy to implement a persistent segment tree via the fat-node
		// technique. Range updates are somewhat dangerous because lazy propagation
		// may cause some updates to not be stored in the history. I do not believe
		// lazy propagation is possible in a persistent manner, because lazy
		// propagation works via the combining of updates, which necessarily
		// destroys time information, or otherwise is no longer constant-time.
		//
		// Updates should typically be applied in non-decreasing order of time. One
		// may choose to apply an out-of-order update to operate on a previous
		// "version" of the tree, however, this invalidates later "version"s of the
		// tree. In this method, it is recommended to compute offline the number of
		// versions to be able to revert to.
		//
		// A query for time `t` is evaluated after all requested updates at time `t`
		// have been applied.
		template <typename Policy, typename TimeType = std::size_t>
		class PolicyPersistentWrapper {
			public:
			using Value = std::map<TimeType, typename Policy::Value>;
			using Update = std::pair<TimeType, typename Policy::Update>;
			using Result = typename Policy::Result;
			using Query = std::pair<TimeType, typename Policy::Query>;

			static inline Value defaultValue() {
				return {{std::numeric_limits<TimeType>::min(), Policy::defaultValue()}};
			}
			static inline Update defaultUpdate() {
				return {std::numeric_limits<TimeType>::min(), Policy::defaultUpdate()};
			}
			static inline Result defaultResult() { return Policy::defaultResult(); }
			static inline Result
			convert(Value const &value, Query const &query, std::size_t size) {
				return Policy::convert(
					std::prev(value.upper_bound(query.first))->second,
					query.second,
					size);
			}
			static inline void combine(Update &current, Update const &update) {
				current.first = update.first;
				Policy::combine(current.second, update.second);
			}
			// TODO: Persistent retrace performs redundant work in binary searching
			// left/right each time, so this is slower than necessary by a
			// constant factor.
			static inline void retrace(
				Value &value,
				Value const &left,
				Value const &right,
				Update const &update) {
				auto hint{std::prev(value.upper_bound(update.first))};
				auto it{value.insert_or_assign(hint, update.first, hint->second)};
				Policy::retrace(
					it->second,
					std::prev(left.upper_bound(update.first))->second,
					std::prev(right.upper_bound(update.first))->second,
					update.second);
			}
			static inline void
			build(Value &value, Value const &left, Value const &right) {
				auto t{std::max(left.rbegin()->first, right.rbegin()->first)};
				auto hint{std::prev(value.upper_bound(t))};
				auto it{value.insert_or_assign(hint, t, hint->second)};
				Policy::build(
					it->second, left.rbegin()->second, right.rbegin()->second);
			}
			static inline void
			apply(Value &value, Update const &update, std::size_t size) {
				auto hint{std::prev(value.upper_bound(update.first))};
				auto it{value.insert_or_assign(hint, update.first, hint->second)};
				Policy::apply(it->second, update.second, size);
			}
			static inline Result
			aggregate(Result const &left, Result const &right, Query const &query) {
				return Policy::aggregate(left, right, query.second);
			}
		};

		template <typename ValueType>
		class PolicySum : public PolicyBase<ValueType> {
			public:
			using SuperPolicy = PolicyBase<ValueType>;
			using typename SuperPolicy::Value;
			using typename SuperPolicy::Update;
			using typename SuperPolicy::Result;
			using typename SuperPolicy::Query;

			static inline void combine(Update &current, Update const &update) {
				current += update;
			}
			static inline void retrace(
				Value &value,
				Value const &left,
				Value const &right,
				Update const &) {
				value = left + right;
			}
			static inline void
			build(Value &value, Value const &left, Value const &right) {
				value = left + right;
			}
			static inline void
			apply(Value &value, Update const &update, std::size_t size) {
				value += update * static_cast<Update>(size);
			}
			static inline Result
			aggregate(Result const &left, Result const &right, Query const &) {
				return left + right;
			}
		};

		template <typename ValueType>
		class PolicyMin : public PolicyBase<ValueType> {
			public:
			using SuperPolicy = PolicyBase<ValueType>;
			using typename SuperPolicy::Value;
			using typename SuperPolicy::Update;
			using typename SuperPolicy::Result;
			using typename SuperPolicy::Query;

			static inline Result defaultResult() {
				return std::numeric_limits<Result>::max();
			}
			static inline void combine(Update &current, Update const &update) {
				current += update;
			}
			static inline void retrace(
				Value &value,
				Value const &left,
				Value const &right,
				Update const &) {
				value = std::min(left, right);
			}
			static inline void
			build(Value &value, Value const &left, Value const &right) {
				value = std::min(left, right);
			}
			static inline void
			apply(Value &value, Update const &update, std::size_t) {
				value += update;
			}
			static inline Result
			aggregate(Result const &left, Result const &right, Query const &) {
				return std::min(left, right);
			}
		};

		template <typename ValueType>
		class PolicyMax : public PolicyBase<ValueType> {
			public:
			using SuperPolicy = PolicyBase<ValueType>;
			using typename SuperPolicy::Value;
			using typename SuperPolicy::Update;
			using typename SuperPolicy::Result;
			using typename SuperPolicy::Query;

			static inline Result defaultResult() {
				return std::numeric_limits<Result>::min();
			}
			static inline void combine(Update &current, Update const &update) {
				current += update;
			}
			static inline void retrace(
				Value &value,
				Value const &left,
				Value const &right,
				Update const &) {
				value = std::max(left, right);
			}
			static inline void
			build(Value &value, Value const &left, Value const &right) {
				value = std::max(left, right);
			}
			static inline void
			apply(Value &value, Update const &update, std::size_t) {
				value += update;
			}
			static inline Result
			aggregate(Result const &left, Result const &right, Query const &) {
				return std::max(left, right);
			}
		};

		// 2D segtree for point updates and range queries.
		template <typename ValueType, std::size_t INNER_DIMENSION>
		class PolicySum2DPoint : public PolicyBase<
															 FenwickTree<ValueType>,
															 std::pair<std::size_t, ValueType>,
															 ValueType,
															 std::size_t> {
			public:
			using SuperPolicy = PolicyBase<
				FenwickTree<ValueType>,
				std::pair<std::size_t, ValueType>,
				ValueType,
				std::size_t>;
			using typename SuperPolicy::Value;
			using typename SuperPolicy::Update;
			using typename SuperPolicy::Result;
			using typename SuperPolicy::Query;

			static inline Value defaultValue() { return {INNER_DIMENSION}; }
			static inline Result defaultResult() { return {}; }
			static inline Result
			convert(Value const &value, Query const &query, std::size_t) {
				return value.sum(query);
			}
			// combine is omitted because we only support point updates.
			static inline void retrace(
				Value &value,
				Value const &left,
				Value const &right,
				Update const &update) {
				// We can directly apply the update to this vertex.
				value.modify(update.first, update.second);
			}
			// build is omitted because there is no easy way to combine two Fenwicks.
			static inline void
			apply(Value &value, Update const &update, std::size_t) {
				value.modify(update.first, update.second);
			}
			static inline Result
			aggregate(Result const &left, Result const &right, Query const &) {
				return left + right;
			}
		};
	};

	// Segment tree with lazy propagation, supporting range queries and range
	// updates in O(ln N) and O(N) memory.
	//
	// Loosely based on <https://codeforces.com/blog/entry/18051>. Earlier
	// iterations of this data structure have higher constant factor but enable
	// more intuitive modifications. Due to the memory layout, some vertices are
	// "bridge" vertices, and aggregate a prefix and suffix of the underlying
	// together. Bridges do not have a uniform height or size.
	//
	// Inherit and modify the provided default policy to implement custom
	// behavior.
	//
	// Updates must be combinable. If updates are not combinable, consider using
	// the non-lazy version of this segtree, or otherwise using a
	// higher-dimensional structure (e.g. quad-tree). Otherwise, using only point
	// updates will guarantee that combine is never called.
	//
	// build is only required when using the building version of the constructor.
	// retrace receives information about the update that caused it to be called,
	// and may know which child was updated, but this is not yet implemented.
	template <typename Policy>
	class SegmentTreeLazy {
		public:
		using Value = typename Policy::Value;
		using Update = typename Policy::Update;
		using Result = typename Policy::Result;
		using Query = typename Policy::Query;

		using Error = SegmentTreeLazy<>::Error;
		using Exception = SegmentTreeLazy<>::Exception;

		private:
		class Vertex {
			public:
			Value value{Policy::defaultValue()};

			// True iff node has a pending lazy update to propagate to its children.
			// The update has already been applied to the node itself.
			bool lazy{false};

			// Lazily-stored updates. Will be the default update if lazy is false.
			Update update{Policy::defaultUpdate()};
		};

		// Depth of the deepest node in the tree.
		std::size_t const DEPTH;

		// Number of underlying nodes.
		std::size_t const SIZE_UNDERLYING;

		// All vertices in the tree. Vertex 0 is unused.
		mutable std::vector<Vertex> vertices;

		// Propagate a single non-leaf vertex in the tree. It is guaranteed that
		// propagate will never be called on a leaf. propagate may be called on a
		// bridge, but bridges (and ancestors of them) will never be lazy.
		//
		// `size` is only valid for non-bridge-ancestors. It is always the number of
		// leaf nodes contained in this subtree.
		inline void propagate(std::size_t idx, std::size_t size) const {
			if (!this->vertices[idx].lazy) {
				return;
			}

			Policy::apply(
				this->vertices[idx * 2].value, this->vertices[idx].update, size / 2);
			Policy::apply(
				this->vertices[idx * 2 + 1].value,
				this->vertices[idx].update,
				size / 2);

			// Avoid unnecessarily setting lazy on a leaf node.
			if (idx * 2 < this->SIZE_UNDERLYING) {
				Policy::combine(
					this->vertices[idx * 2].update, this->vertices[idx].update);
				Policy::combine(
					this->vertices[idx * 2 + 1].update, this->vertices[idx].update);
				this->vertices[idx * 2].lazy = this->vertices[idx * 2 + 1].lazy = true;
			}

			this->vertices[idx].update = Policy::defaultUpdate();
			this->vertices[idx].lazy = false;
		}

		// Propagate all ancestors of a single vertex, optionally beginning at a
		// specific ancestor depth.
		inline void propagateTo(std::size_t idx) const {
			for (std::size_t level{this->DEPTH}, size{1_zu << level}; level > 0;
					 level--, size /= 2) {
				if ((idx >> level) == 0) {
					continue;
				}
				this->propagate(idx >> level, size);
			}
		}

		public:
		// Publicly accessible way to traverse the tree while abstracting away the
		// lazy propagation. It is assumed that the tree has been propagated to the
		// iterator already.
		//
		// Iterators remain valid as long as no operations are performed between
		// accesses. Operations may invalidate the values of iterators as they will
		// no longer be up-to-date with lazy updates. This can be resolved with
		// `revalidate`.
		//
		// TODO: Implement a constant version of this.
		class Iterator {
			private:
			SegmentTreeLazy<Policy> const *TREE;

			std::size_t IDX, SIZE;

			public:
			// Size is the number of leaf nodes in this subtree. It is only valid if
			// this is not an ancestor of a bridge.
			Iterator(
				SegmentTreeLazy<Policy> const *tree,
				std::size_t idx,
				std::size_t size)
					: TREE{tree}, IDX{idx}, SIZE{size} {}
			Iterator(Iterator const &other)
					: TREE{other.TREE}, IDX{other.IDX}, SIZE{other.SIZE} {}

			Iterator &operator=(Iterator const &other) {
				this->TREE = other.TREE;
				this->IDX = other.IDX;
				this->SIZE = other.SIZE;
				return *this;
			}

			inline bool isRoot() { return this->IDX == 1; }
			inline bool isLeaf() { return this->IDX >= this->TREE->SIZE_UNDERLYING; }
			inline bool isFrontUnderlying() {
				return this->IDX == this->TREE->SIZE_UNDERLYING;
			}
			inline bool isBackUnderlying() {
				return this->IDX == this->TREE->SIZE_UNDERLYING * 2 - 1;
			}

			inline Iterator parent() {
				if (this->isRoot()) {
					throw Exception(Error::ITERATOR_INVALID);
				}
				return {this->TREE, this->IDX / 2, this->SIZE * 2};
			}
			// Children access.
			inline Iterator left() {
				if (this->isLeaf()) {
					throw Exception(Error::ITERATOR_INVALID);
				}
				this->TREE->propagate(this->IDX, this->SIZE);
				return {this->TREE, this->IDX * 2, this->SIZE / 2};
			}
			inline Iterator right() {
				if (this->isLeaf()) {
					throw Exception(Error::ITERATOR_INVALID);
				}
				this->TREE->propagate(this->IDX, this->SIZE);
				return {this->TREE, this->IDX * 2 + 1, this->SIZE / 2};
			}
			// Underlying access. Throws if at the ends of the underlying array, or if
			// this is not leaf. Because of the need to propagate, these are O(\lg N)
			// amortized.
			//
			// TODO: Can this be implemented faster?
			inline Iterator nextUnderlying() {
				if (!this->isLeaf() || this->isBackUnderlying()) {
					throw Exception(Error::ITERATOR_INVALID);
				}
				this->TREE->propagateTo(this->IDX + 1);
				return {this->TREE, this->IDX + 1, this->SIZE};
			}
			inline Iterator prevUnderlying() {
				if (!this->isLeaf() || this->isFrontUnderlying()) {
					throw Exception(Error::ITERATOR_INVALID);
				}
				this->TREE->propagateTo(this->IDX - 1);
				return {this->TREE, this->IDX - 1, this->SIZE};
			}

			// If updates have changed the tree, re-validate this iterator by
			// propagating to it.
			inline void revalidate() { this->TREE->propagateTo(this->IDX); }

			// Access to iterator value.
			Value &operator*() { return this->TREE->vertices[this->IDX].value; }
		};

		friend Iterator;

		// Segment tree for a segment array of size size.
		SegmentTreeLazy(std::size_t size)
				: DEPTH{mostSignificant1BitIdx(size * 2)},
					SIZE_UNDERLYING{size},
					vertices(size * 2) {}

		// Segment tree with all leaf nodes moved in, and the others constructed in
		// order. This minimizes build time by a constant factor.
		SegmentTreeLazy(std::vector<Value> &&values)
				: SegmentTreeLazy(values.size()) {
			for (std::size_t i{0}; i < this->SIZE_UNDERLYING; i++) {
				std::swap(values[i], this->vertices[this->SIZE_UNDERLYING + i].value);
			}
			for (std::size_t i{this->SIZE_UNDERLYING - 1}; i > 0; i--) {
				Policy::build(
					this->vertices[i].value,
					this->vertices[i * 2].value,
					this->vertices[i * 2 + 1].value);
			}
		}

		// Queries an inclusive range, propagating if necessary then aggregating.
		Result query(std::size_t left, std::size_t right, Query const &query = {}) {
			this->propagateTo(left + this->SIZE_UNDERLYING);
			this->propagateTo(right + this->SIZE_UNDERLYING);
			Result resLeft{Policy::defaultResult()},
				resRight{Policy::defaultResult()};
			std::size_t size{1};
			for (left += this->SIZE_UNDERLYING, right += this->SIZE_UNDERLYING + 1;
					 left < right;
					 left /= 2, right /= 2, size *= 2) {
				if (left % 2 == 1) {
					resLeft = Policy::aggregate(
						resLeft,
						Policy::convert(this->vertices[left++].value, query, size),
						query);
				}
				if (right % 2 == 1) {
					resRight = Policy::aggregate(
						Policy::convert(this->vertices[--right].value, query, size),
						resRight,
						query);
				}
			}
			return Policy::aggregate(resLeft, resRight, query);
		}

		// Lazy update an inclusive range. The updated will be applied identically
		// to all nodes in the range, save for differences based on the depth of the
		// node (which will be expressed via the std::size_t range parameter).
		void update(std::size_t left, std::size_t right, Update const &update) {
			this->propagateTo(left + this->SIZE_UNDERLYING);
			this->propagateTo(right + this->SIZE_UNDERLYING);
			// Only retrace updates once left or right node has been changed.
			bool changedLeft{false}, changedRight{false};
			std::size_t size{1};
			for (left += this->SIZE_UNDERLYING, right += this->SIZE_UNDERLYING + 1;
					 left < right;
					 left /= 2, right /= 2, size *= 2) {
				if (changedLeft) {
					Policy::retrace(
						this->vertices[left - 1].value,
						this->vertices[left * 2 - 2].value,
						this->vertices[left * 2 - 1].value,
						update);
				}
				if (changedRight) {
					Policy::retrace(
						this->vertices[right].value,
						this->vertices[right * 2].value,
						this->vertices[right * 2 + 1].value,
						update);
				}
				if (left % 2 == 1) {
					changedLeft = true;
					Policy::apply(this->vertices[left].value, update, size);
					// Avoid unnecessarily setting the lazy update on a leaf node.
					if (left < this->SIZE_UNDERLYING) {
						Policy::combine(this->vertices[left].update, update);
						this->vertices[left].lazy = true;
					}
					left++;
				}
				if (right % 2 == 1) {
					right--;
					changedRight = true;
					Policy::apply(this->vertices[right].value, update, size);
					if (right < this->SIZE_UNDERLYING) {
						Policy::combine(this->vertices[right].update, update);
						this->vertices[right].lazy = true;
					}
				}
			}
			for (left--; right > 0; left /= 2, right /= 2) {
				if (changedLeft && left > 0) {
					Policy::retrace(
						this->vertices[left].value,
						this->vertices[left * 2].value,
						this->vertices[left * 2 + 1].value,
						update);
				}
				if (changedRight && (!changedLeft || left != right)) {
					Policy::retrace(
						this->vertices[right].value,
						this->vertices[right * 2].value,
						this->vertices[right * 2 + 1].value,
						update);
				}
			}
		}

		Iterator root() {
			this->propagateTo(1);
			return Iterator(this, 1, 1_zu << this->DEPTH);
		}
		Iterator frontUnderlying() {
			this->propagateTo(this->SIZE_UNDERLYING);
			return Iterator(this, this->SIZE_UNDERLYING, 1);
		}
		Iterator backUnderlying() {
			this->propagateTo(this->SIZE_UNDERLYING * 2 - 1);
			return Iterator(this, this->SIZE_UNDERLYING * 2 - 1, 1);
		}
	};

	template <typename Policy>
	using SegmentTreeLazyPersistent =
		SegmentTreeLazy<SegmentTreeLazy<>::PolicyPersistentWrapper<Policy>>;
}

using namespace Rain::Algorithm;

using LL = long long;
using LD = long double;
using namespace std;

#define RF(x, from, to) \
	for (LL x(from), _to(to), _delta{x < _to ? 1LL : -1LL}; x != _to; x += _delta)

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL const INF{10000000000000};

	LL T;
	cin >> T;
	while (T--) {
		LL N;
		cin >> N;
		SegmentTreeLazy<SegmentTreeLazy<>::PolicyMax<LL>> S(N);
		vector<LL> HH(N), C(N);
		RF(i, 0, N) {
			LL h;
			cin >> h;
			HH[i] = i;
			C[i] = h;
			S.update(i, i, h - i);
		}
		SegmentTreeLazy<SegmentTreeLazy<>::PolicyMax<LL>> H(move(HH));

		LL Z{0};
		RF(i, 0, N) {
			LL low{0}, high{N}, mid;
			while (low + 1 < high) {
				mid = (low + high) / 2;
				LL q{S.query(mid, N - 1)};
				if (q >= 0) {
					low = mid;
				} else {
					high = mid;
				}
			}

			if (low < N - 1) {
				S.update(low + 1, N - 1, low);
			}
			LL h{H.query(low, low)};
			C[low] -= h;
			H.update(low, N - 1, -h);
			if (low > 0 && S.query(low - 1, low - 1) >= -INF / 2) {
				Z += C[low - 1];
				S.update(low - 1, low - 1, -INF);
			} else {
				Z += C[low];
				S.update(low, low, -INF);
			}
		}
		cout << Z << '\n';
	}

	return 0;
}
