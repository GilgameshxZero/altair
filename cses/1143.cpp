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

namespace Rain::Algorithm {
	template <typename = void>
	class SegmentTreeLazy;

	template <>
	class SegmentTreeLazy<void> {
		private:
		// SFINAE base class which conditionally defines DEFAULT_VALUE.
		template <typename Value, typename = void>
		class PolicyBaseDefaultValue {};

		template <typename Value>
		class PolicyBaseDefaultValue<Value,
			typename std::enable_if<
				std::is_default_constructible<Value>::value>::type> {
			protected:
			inline Value defaultValue() { return {}; }
		};

		// SFINAE base class which conditionally defines DEFAULT_UPDATE.
		template <typename Update, typename = void>
		class PolicyBaseDefaultUpdate {};

		template <typename Update>
		class PolicyBaseDefaultUpdate<Update,
			typename std::enable_if<
				std::is_default_constructible<Update>::value>::type> {
			protected:
			inline Update defaultUpdate() { return {}; }
		};

		// SFINAE base class which conditionally defines combine. While MSVC allows
		// placing this function with SFINAE directly in the policy class, other
		// compilers do not, and so we compromise and place it outside, and inherit
		// it.
		template <typename Update, typename = void>
		class PolicyBaseCombine {};

		template <typename Update>
		class PolicyBaseCombine<Update,
			typename std::void_t<decltype(std::declval<Update &>() +=
				std::declval<Update const &>())>> {
			protected:
			// Stack an update atop an existing, potentially non-empty update, which
			// will be used lazily later. Must be associative but may not be
			// commutative.
			inline void combine(Update &current, Update const &update, std::size_t) {
				current += update;
			}
		};

		// SFINAE base class which conditionally defines retrace.
		template <typename Value, typename = void>
		class PolicyBaseRetrace {};

		template <typename Value>
		class PolicyBaseRetrace<Value,
			typename std::void_t<decltype(std::declval<Value &>() =
																			std::declval<Value const &>() +
					std::declval<Value const &>())>> {
			protected:
			// Aggregate values from two children while retracing an update.
			// Aggregating with a default Value should do nothing. Must be associative
			// but may not be commutative.
			inline void retrace(Value &value,
				Value const &left,
				Value const &right,
				std::size_t) {
				value = left + right;
			}
		};

		// SFINAE base class which conditionally defines apply.
		template <typename Value, typename Update, typename = void>
		class PolicyBaseApply {};

		template <typename Value, typename Update>
		class PolicyBaseApply<Value,
			Update,
			typename std::void_t<decltype(std::declval<Value &>() +=
				std::declval<Update const &>() * std::declval<std::size_t>())>> {
			protected:
			// Fully apply an update to a node. The node may not be a leaf.
			inline void apply(Value &value, Update const &update, std::size_t range) {
				value += update * range;
			}
		};

		// SFINAE base class which conditionally defines aggregate.
		template <typename Result, typename Query, typename = void>
		class PolicyBaseAggregate {};

		template <typename Result, typename Query>
		class PolicyBaseAggregate<Result,
			Query,
			typename std::enable_if<std::is_constructible<Result,
				decltype(std::declval<Result const &>() +
					std::declval<Result const &>())>::value>::type> {
			protected:
			// Aggregate two results from queries on children. Aggregating with a
			// Result converted from a default Value should do nothing. Must be
			// associative but may not be commutative.
			inline Result aggregate(Result const &left,
				Result const &right,
				Query const &) {
				return {left + right};
			}
		};

		public:
		// Default policy for SegmentTreeLazy, which has functions disabled by
		// SFINAE if they do not support expected operations. In that case, the
		// client should inherit the enabled parts of this disabled policy and
		// re-implement the disabled functions.
		//
		// This default policy represents a sum tree.
		template <typename ValueType,
			typename UpdateType = ValueType,
			typename ResultType = ValueType,
			typename QueryType = std::nullptr_t>
		class Policy : protected PolicyBaseDefaultValue<ValueType>,
									 protected PolicyBaseDefaultUpdate<UpdateType>,
									 protected PolicyBaseCombine<UpdateType>,
									 protected PolicyBaseRetrace<ValueType>,
									 protected PolicyBaseApply<ValueType, UpdateType>,
									 protected PolicyBaseAggregate<ResultType, QueryType> {
			protected:
			// Expose typenames to subclasses (SegmentTreeLazy).
			using Value = ValueType;
			using Update = UpdateType;
			using Result = ResultType;
			using Query = QueryType;

			// Convert the value at a node to a result. The node may not be a leaf.
			template <
				bool isConstructible = std::is_constructible<Result, Value>::value,
				typename std::enable_if<isConstructible>::type * = nullptr>
			inline Result convert(Value const &value, Query const &, std::size_t) {
				return {value};
			}
		};
	};

	// Segment tree with lazy propagation, supporting range queries and range
	// updates in O(ln N) and O(N) memory.
	//
	// Loosely based on <https://codeforces.com/blog/entry/18051>. Earlier
	// iterations of this data structure have higher constant factor but enable
	// more intuitive modifications. Inherit and modify the provided default
	// policy to implement custom behavior.
	template <typename Policy>
	class SegmentTreeLazy : protected Policy {
		public:
		using Value = typename Policy::Value;
		using Update = typename Policy::Update;
		using Result = typename Policy::Result;
		using Query = typename Policy::Query;

		protected:
		// Aggregate values at each node. Index 0 is unused.
		std::vector<Value> values;

		// True iff node has a pending lazy update to propagate to its children. The
		// update has already been applied to the node itself.
		std::vector<bool> lazy;

		// Lazily-stored updates.
		std::vector<Update> updates;

		// Height of the highest node in the tree.
		std::size_t const HEIGHT;

		public:
		// Segment tree for a segment array of size size.
		SegmentTreeLazy(std::size_t const size)
				: values(2 * size, this->defaultValue()),
					lazy(this->values.size(), false),
					updates(this->values.size(), this->defaultUpdate()),
					HEIGHT{mostSignificant1BitIdx(this->values.size())} {}

		// Segment tree with all values pre-initialized, to minimize build time.
		SegmentTreeLazy(std::vector<Value> &&values)
				: values(values.size(), this->defaultValue()),
					lazy(2 * this->values.size(), false),
					updates(2 * this->values.size(), this->defaultUpdate()),
					HEIGHT{mostSignificant1BitIdx(2 * this->values.size())} {
			this->values.insert(this->values.end(),
				std::make_move_iterator(values.begin()),
				std::make_move_iterator(values.end()));
			for (std::size_t level{1}, range{2_zu}; level < this->HEIGHT;
				level++, range *= 2) {
				for (std::size_t i{values.size() >> level};
					i < (values.size() >> (level - 1));
					i++) {
					this->retrace(this->values[i],
						this->values[i * 2],
						this->values[i * 2 + 1],
						range);
				}
			}
		}

		protected:
		// Propagate all ancestors of nodes in a given inclusive underlying range.
		// After this, no ancestor of any node in this range should have a queued
		// update.
		void propagate(std::size_t left, std::size_t right) {
			std::size_t level{this->HEIGHT}, range{1_zu << (this->HEIGHT - 1)};
			for (left += this->values.size() / 2, right += this->values.size() / 2;
				level > 0;
				--level, range /= 2) {
				for (std::size_t i{left >> level}; i <= (right >> level); ++i) {
					if (this->lazy[i]) {
						this->apply(this->values[i * 2], this->updates[i], range);
						this->apply(this->values[i * 2 + 1], this->updates[i], range);
						this->combine(this->updates[i * 2], this->updates[i], range);
						this->combine(this->updates[i * 2 + 1], this->updates[i], range);
						this->lazy[i * 2] = this->lazy[i * 2 + 1] = true;

						this->updates[i] = this->defaultUpdate();
						this->lazy[i] = false;
					}
				}
			}
		}

		public:
		// Queries an inclusive range, propagating if necessary then aggregating.
		// Take an optional query parameter `query` which will be used in convert
		// and aggregate of the results and values.
		Result query(std::size_t left, std::size_t right, Query const &query = {}) {
			this->propagate(left, left);
			this->propagate(right, right);
			Result resLeft{this->convert(this->defaultValue(), query, 1)},
				resRight{this->convert(this->defaultValue(), query, 1)};
			std::size_t range{1};
			for (left += this->values.size() / 2,
				right += this->values.size() / 2 + 1;
				left < right;
				left /= 2, right /= 2, range *= 2) {
				if (left % 2 == 1) {
					resLeft = this->aggregate(
						resLeft, this->convert(this->values[left++], query, range), query);
				}
				if (right % 2 == 1) {
					resRight =
						this->aggregate(this->convert(this->values[--right], query, range),
							resRight,
							query);
				}
			}
			return this->aggregate(resLeft, resRight, query);
		}

		// Lazy update an inclusive range. The updated will be applied identically
		// to all nodes in the range, save for differences based on the depth of the
		// node (which will be expressed via the std::size_t range parameter).
		void update(std::size_t left, std::size_t right, Update const &update) {
			// We must propagate here because retrace expects non-lazy nodes to store
			// the value.
			this->propagate(left, left);
			this->propagate(right, right);
			// Only retrace updates once left or right node has been changed.
			bool changedLeft{false}, changedRight{false};
			std::size_t range{1};
			for (left += this->values.size() / 2,
				right += this->values.size() / 2 + 1;
				left < right;
				left /= 2, right /= 2, range *= 2) {
				if (changedLeft) {
					this->retrace(this->values[left - 1],
						this->values[left * 2 - 2],
						this->values[left * 2 - 1],
						range);
				}
				if (changedRight) {
					this->retrace(this->values[right],
						this->values[right * 2],
						this->values[right * 2 + 1],
						range);
				}
				if (left % 2 == 1) {
					this->apply(this->values[left++], update, range);
					this->combine(this->updates[left - 1], update, range);
					this->lazy[left - 1] = true;
					changedLeft = true;
				}
				if (right % 2 == 1) {
					this->apply(this->values[--right], update, range);
					this->combine(this->updates[right], update, range);
					this->lazy[right] = true;
					changedRight = true;
				}
			}
			for (left--; right > 0; left /= 2, right /= 2, range *= 2) {
				if (changedLeft) {
					this->retrace(this->values[left],
						this->values[left * 2],
						this->values[left * 2 + 1],
						range);
				}
				if (changedRight && (!changedLeft || left != right)) {
					this->retrace(this->values[right],
						this->values[right * 2],
						this->values[right * 2 + 1],
						range);
				}
			}
		}
	};
}

using namespace Rain::Algorithm;

using LL = long long;
using LD = long double;
using namespace std;

#define RF(x, from, to) \
	for (LL x(from), _to(to), _delta{x < _to ? 1LL : -1LL}; x != _to; x += _delta)

class Policy : protected SegmentTreeLazy<>::Policy<LL, LL, LL, LL> {
	protected:
	inline void retrace(Value &value,
		Value const &left,
		Value const &right,
		std::size_t) {
		value = max(left, right);
	}

	inline void apply(Value &value, Update const &update, std::size_t) {
		value += update;
	}

	inline void combine(Update &current, Update const &update, std::size_t) {
		current += update;
	}

	inline Result aggregate(Result const &left,
		Result const &right,
		Query const &) {
		return max(left, right);
	}

	inline Result convert(Value const &value, Query const &, std::size_t) {
		return value;
	}
};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL N, M;
	cin >> N >> M;

	SegmentTreeLazy<Policy> tree(N);
	RF(i, 0, N) {
		LL A;
		cin >> A;
		tree.update(i, i, A);
	}
	RF(i, 0, M) {
		LL A;
		cin >> A;

		if (tree.query(0, N - 1) < A) {
			cout << "0 ";
			continue;
		}

		LL low{0}, high{N}, mid;
		while (low + 1 < high) {
			mid = (low + high) / 2;
			if (tree.query(low, mid - 1) >= A) {
				high = mid;
			} else {
				low = mid;
			}
		}
		tree.update(low, low, -A);
		cout << low + 1 << ' ';
	}

	return 0;
}
