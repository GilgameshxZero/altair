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

namespace Rain {
	// Inline namespaces are implicitly accessible by the parent namespace.
	inline namespace Literal {
		// Inject std literals into the Rain namespace.
		using namespace std::literals;

		// User-defined literals.
		inline constexpr std::size_t operator"" _zu(unsigned long long value) {
			return static_cast<std::size_t>(value);
		}
		inline std::regex operator"" _re(char const *value, std::size_t) {
			return std::regex(value);
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
	// Segment tree with lazy propagation, supporting range queries and range
	// updates in O(ln N) and O(N) memory.
	//
	// Based on <https://codeforces.com/blog/entry/18051>. Earlier iterations of
	// this data structure have higher constant factor but enable more intuitive
	// modifications. This policy-based structure requires a policy of the
	// following interface:
	//
	// static constexpr Value DEFAULT_VALUE: Identity values at creation and
	// aggregation.
	//
	// static constexpr Update DEFAULT_UPDATE: Identify value of an update.
	//
	// static void apply(Value &value, Update const &update, std::size_t range):
	// Fully apply an update to a leaf node.
	//
	// static Result aggregate(Result const &left, Result const &right):
	// Aggregate two results from queries on children. Aggregating with a Result
	// converted from a default Value should do nothing.
	//
	// static void retrace( Value &value, Value const &left, Value const &right,
	// std::size_t range): Aggregate values from two children while retracing an
	// update. Aggregating with a default Value should do nothing.
	//
	// static void split(Update const &update, Update &left, Update &right,
	// std::size_t range): Split a lazy update into its children updates.
	template <typename Policy>
	class SegmentTreeLazy {
		public:
		using Value = typename Policy::Value;
		using Update = typename Policy::Update;
		using Result = typename Policy::Result;

		protected:
		// Aggregate values at each node.
		std::vector<Value> values;

		// True iff node has a pending lazy update to propagate.
		std::vector<bool> lazy;

		// Lazily-stored updates.
		std::vector<Update> updates;

		// Height of the highest node in the tree.
		std::size_t const HEIGHT;

		public:
		// Segment tree for a segment array of size size.
		SegmentTreeLazy(std::size_t const size)
				: values(2 * size, Policy::DEFAULT_VALUE),
					lazy(values.size(), false),
					updates(values.size(), Policy::DEFAULT_UPDATE),
					HEIGHT{mostSignificant1BitIdx(values.size())} {}

		protected:
		// Propagate all ancestors of nodes in a given inclusive underlying range.
		void propagate(std::size_t left, std::size_t right) {
			std::size_t level{this->HEIGHT}, range{1_zu << (this->HEIGHT - 1)};
			for (left += this->values.size() / 2, right += this->values.size() / 2;
					 level > 0;
					 --level, range >>= 1) {
				for (std::size_t i{left >> level}; i <= (right >> level); ++i) {
					if (this->lazy[i]) {
						Policy::apply(this->values[i * 2], this->updates[i], range);
						Policy::apply(this->values[i * 2 + 1], this->updates[i], range);
						Policy::split(
							this->updates[i],
							this->updates[i * 2],
							this->updates[i * 2 + 1],
							range);
						this->lazy[i * 2] = this->lazy[i * 2 + 1] = true;

						this->updates[i] = Policy::DEFAULT_UPDATE;
						this->lazy[i] = false;
					}
				}
			}
		}

		public:
		// Queries an inclusive range, propagating if necessary then aggregating.
		Result query(std::size_t left, std::size_t right) {
			this->propagate(left, left);
			this->propagate(right, right);
			Value resLeft{Policy::DEFAULT_VALUE}, resRight{Policy::DEFAULT_VALUE};
			for (left += this->values.size() / 2,
					 right += this->values.size() / 2 + 1;
					 left < right;
					 left /= 2, right /= 2) {
				if (left % 2 == 1) {
					resLeft = Policy::aggregate(resLeft, this->values[left++]);
				}
				if (right % 2 == 1) {
					resRight = Policy::aggregate(this->values[--right], resRight);
				}
			}
			return Policy::aggregate(resLeft, resRight);
		}

		// Lazy update an inclusive range.
		void update(std::size_t left, std::size_t right, Update const &update) {
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
					Policy::retrace(
						this->values[left - 1],
						this->values[left * 2 - 2],
						this->values[left * 2 - 1],
						range);
				}
				if (changedRight) {
					Policy::retrace(
						this->values[right],
						this->values[right * 2],
						this->values[right * 2 + 1],
						range);
				}
				if (left % 2 == 1) {
					Policy::apply(this->values[left++], update, range);
					this->lazy[left - 1] = true;
					this->updates[left - 1] = update;
					changedLeft = true;
				}
				if (right % 2 == 1) {
					Policy::apply(this->values[--right], update, range);
					this->lazy[right] = true;
					this->updates[right] = update;
					changedRight = true;
				}
			}
			for (left--; right > 0; left /= 2, right /= 2, range *= 2) {
				if (changedLeft) {
					Policy::retrace(
						this->values[left],
						this->values[left * 2],
						this->values[left * 2 + 1],
						range);
				}
				if (changedRight && (!changedLeft || left != right)) {
					Policy::retrace(
						this->values[right],
						this->values[right * 2],
						this->values[right * 2 + 1],
						range);
				}
			}
		}
	};
}

class Policy {
	public:
	using Value = array<LL, 4>;
	using Update = LL;
	using Result = array<LL, 4>;

	static constexpr Value DEFAULT_VALUE{
		-LLONG_MAX / 2,
		-LLONG_MAX / 2,
		-LLONG_MAX / 2,
		-LLONG_MAX / 2};
	static constexpr Update DEFAULT_UPDATE{0};
	static void apply(Value &value, Update const &update, std::size_t) {
		value[0] = 0;
		value[1] = value[2] = -LLONG_MAX / 2;
		value[3] = update;
	}
	static Result aggregate(Result const &left, Result const &right) {
		if (left[0] < 0) {
			return right;
		} else if (right[0] < 0) {
			return left;
		} else {
			return {
				max({left[0] + right[0], left[0] + right[2], left[1] + right[0]}),
				max({left[0] + right[1], left[0] + right[3], left[1] + right[1]}),
				max({left[2] + right[0], left[2] + right[2], left[3] + right[0]}),
				max({left[2] + right[1], left[2] + right[3], left[3] + right[1]})};
		}
	}
	static void
	retrace(Value &value, Value const &left, Value const &right, std::size_t) {
		value = aggregate(left, right);
	}
	static void
	split(Update const &update, Update &left, Update &right, std::size_t) {
		left = right = update;
	}
};

using namespace Rain::Algorithm;

int main(int, char const *[]) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL N, Q;
	cin >> N;

	vector<LL> A(N - 1);
	SegmentTreeLazy<Policy> st(N - 1);
	LL S{0};
	RF(i, 0, N - 1) {
		cin >> A[i];
		S += A[i];
		st.update(i, i, A[i]);
	}

	cin >> Q;
	RF(i, 0, Q) {
		LL K, X;
		cin >> K >> X;
		S -= A[K - 1];
		S += X;
		A[K - 1] = X;
		st.update(K - 1, K - 1, X);
		cout << 2 * (S - st.query(0, N - 2)[0]) << '\n';
	}

	return 0;
}
