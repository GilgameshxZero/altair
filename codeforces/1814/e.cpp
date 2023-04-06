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
	// Segment tree without lazy propagation nor range updates.
	template <
		typename Value,
		typename Update,
		typename Result,
		// Aggregate values from two children while retracing an update. Aggregating
		// with a default Value should do nothing.
		void (*retrace)(
			typename std::vector<Value>::reference,
			Value const &,
			Value const &),
		// Aggregate two results from queries on children. Aggregating with a
		// Result converted from a default Value should do nothing.
		Result (*aggregate)(Result const &, Result const &),
		// Apply an update fully to a node.
		void (*apply)(typename std::vector<Value>::reference, Update const &)>
	class SegmentTree {
		public:
		// Aggregate values at each node.
		std::vector<Value> values;

		// Segment tree for a segment array of size size.
		SegmentTree(std::size_t const size)
				: values(1LL << (mostSignificant1BitIdx(size - 1) + 2)) {
			RF(i, 0, values.size()) {
				values[i].fill(-LLONG_MAX / 2);
			}
		}

		// Queries an inclusive range.
		Result query(std::size_t left, std::size_t right) {
			Value resLeft, resRight;
			resLeft.fill(-LLONG_MAX / 2);
			resRight.fill(-LLONG_MAX / 2);
			for (left += this->values.size() / 2,
					 right += this->values.size() / 2 + 1;
					 left < right;
					 left /= 2, right /= 2) {
				if (left % 2 == 1) {
					resLeft = aggregate(this->values[left++], resLeft);
				}
				if (right % 2 == 1) {
					resRight = aggregate(this->values[--right], resRight);
				}
			}
			return aggregate(resLeft, resRight);
		}

		// Point update an index.
		void update(std::size_t idx, Update const &update) {
			idx += this->values.size() / 2;
			apply(this->values[idx], update);
			for (idx /= 2; idx >= 1; idx /= 2) {
				retrace(
					this->values[idx], this->values[idx * 2], this->values[idx * 2 + 1]);
			}
		}
	};
}

using namespace Rain::Algorithm;

namespace namespaceST {
	using Value = array<LL, 4>;
	using Result = array<LL, 4>;
	using Update = LL;

	// Aggregate values from two children while retracing an update. Aggregating
	// with a default Value should do nothing.
	void retrace(
		typename std::vector<Value>::reference node,
		Value const &left,
		Value const &right) {
		static Value const DEFAULT{
			-LLONG_MAX / 2, -LLONG_MAX / 2, -LLONG_MAX / 2, -LLONG_MAX / 2};
		if (left == DEFAULT) {
			node = right;
		} else if (right == DEFAULT) {
			node = left;
		} else {
			node[0] =
				max({left[0] + right[0], left[0] + right[2], left[1] + right[0]});
			node[1] =
				max({left[0] + right[1], left[0] + right[3], left[1] + right[1]});
			node[2] =
				max({left[2] + right[0], left[2] + right[2], left[3] + right[0]});
			node[3] =
				max({left[2] + right[1], left[2] + right[3], left[3] + right[1]});
		}
	}

	// Aggregate two results from queries on children. Aggregating with a
	// Result converted from a default Value should do nothing.
	Result aggregate(Result const &left, Result const &right) {
		static Value const DEFAULT{
			-LLONG_MAX / 2, -LLONG_MAX / 2, -LLONG_MAX / 2, -LLONG_MAX / 2};
		if (left == DEFAULT) {
			return right;
		} else if (right == DEFAULT) {
			return left;
		}

		Result node;
		node[0] = max({left[0] + right[0], left[0] + right[2], left[1] + right[0]});
		node[1] = max({left[0] + right[1], left[0] + right[3], left[1] + right[1]});
		node[2] = max({left[2] + right[0], left[2] + right[2], left[3] + right[0]});
		node[3] = max({left[2] + right[1], left[2] + right[3], left[3] + right[1]});
		return node;
	}

	// Apply an update fully to a node.
	void apply(
		typename std::vector<Value>::reference node,
		Update const &update) {
		node[0] = 0;
		node[1] = node[2] = -LLONG_MAX / 3;
		node[3] = update;
	}
}

using ST = SegmentTree<
	array<LL, 4>,
	LL,
	array<LL, 4>,
	namespaceST::retrace,
	namespaceST::aggregate,
	namespaceST::apply>;

int main(int, char const *[]) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL N, Q;
	cin >> N;

	vector<LL> A(N - 1);
	LL S{0};
	RF(i, 0, N - 1) {
		cin >> A[i];
		S += A[i];
	}

	ST st(N - 1);
	RF(i, 0, N - 1) {
		st.update(i, A[i]);
	}

	cin >> Q;
	RF(i, 0, Q) {
		LL K, X;
		cin >> K >> X;
		S -= A[K - 1];
		S += X;
		A[K - 1] = X;
		st.update(K - 1, X);
		cout << 2 * (S - st.query(0, N - 2)[0]) << '\n';
	}

	return 0;
}
