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
	// static void retrace(Value &value, Value const &left, Value const &right,
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

class SetSumPolicy {
	public:
	using Value = LL;
	using Update = LL;
	using Result = LL;

	static constexpr Value DEFAULT_VALUE{0};
	static constexpr Update DEFAULT_UPDATE{-1};

	static void apply(Value &value, Update const &update, std::size_t range) {
		if (update == DEFAULT_UPDATE) {
			return;
		}
		value = update * range;
	}
	static Result aggregate(Result const &left, Result const &right) {
		return left + right;
	}
	static void retrace(
		Value &value,
		Value const &left,
		Value const &right,
		std::size_t range) {
		value = left + right;
	}
	static void
	split(Update const &update, Update &left, Update &right, std::size_t range) {
		left = right = update;
	}
};

using namespace Rain::Algorithm;

int main(int, char const *[]) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL T;
	cin >> T;
	while (T--) {
		LL N;
		cin >> N;
		vector<LL> A(N);
		RF(i, 0, N) {
			cin >> A[i];
		}

		LL lnN(mostSignificant1BitIdx(N));
		vector<vector<LL>> rangeSmall(lnN + 1);
		rangeSmall[0].resize(N);
		RF(i, 0, N) {
			rangeSmall[0][i] = A[i];
		}
		RF(i, 1, lnN + 1) {
			rangeSmall[i].resize(N + 1 - (1LL << i));
			RF(j, 0, rangeSmall[i].size()) {
				rangeSmall[i][j] =
					min(rangeSmall[i - 1][j], rangeSmall[i - 1][j + (1LL << (i - 1))]);
			}
		}

		SegmentTreeLazy<SetSumPolicy> T(N);
		LL C0B{0}, Z{0}, scan{0};
		RF(i, 1, N + 1) {
			Z += (i - 1) * (N - i + 1);
		}

		RF(i, 1, N) {
			LL low{i - 1}, high{N}, mid;
			while (low + 1 < high) {
				mid = (low + high) / 2;
				LL ln(mostSignificant1BitIdx(mid - i + 1)),
					small{min(rangeSmall[ln][i], rangeSmall[ln][mid + 1 - (1LL << ln)])};
				if (small < A[i - 1]) {
					high = mid;
				} else {
					low = mid;
				}
			}
			T.update(i - 1, i - 1, low);

			for (; C0B < i; C0B++) {
				if (T.query(C0B, C0B) >= i) {
					break;
				}
			}
			for (; scan < i - 1; scan++) {
				if (T.query(scan, scan) > low) {
					break;
				}
			}
			T.update(scan, i - 1, low);
			for (; C0B < i; C0B++) {
				if (T.query(C0B, C0B) >= i) {
					break;
				}
			}
			if (C0B <= i - 1) {
				Z -= T.query(C0B, i - 1) - (i - 1 - C0B + 1) * (i - 1);
			}
		}

		cout << Z << '\n';
	}

	return 0;
}
