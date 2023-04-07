#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC target("avx2", "bmi", "bmi2", "popcnt", "lzcnt")
#pragma GCC optimize("O0", "unroll-loops", "rename-registers")
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
	//
	// Implements the policy pattern. Value must implement the following interface
	// (omitted from being an implemented as an actual interface, which is fairly
	// difficult and provides little):
	//
	// Value &retrace(Value const &, Value const &): Aggregate values from two
	// children while retracing an update. Aggregating with a default Value should
	// do nothing.
	// Result &aggregate(Result const &, Result const &): Aggregate two results
	// from queries on children. Aggregating with a Result converted from a
	// default Value should do nothing.
	// void apply(Update const &): Fully apply an update to a leaf node.
	template <typename Policy>
	class SegmentTree {
		public:
		using Value = typename Policy::Value;
		using Update = typename Policy::Update;
		using Result = typename Policy::Result;

		protected:
		// Aggregate values at each node.
		std::vector<Value> values;
		LL N;

		public:
		// Segment tree for a segment array of size size.
		SegmentTree(LL const size)
				: values(2 * size, Policy::initialize), N(size) {}

		// Queries an inclusive range.
		Result query(LL left, LL right) {
			Value resLeft{Policy::initialize}, resRight{Policy::initialize};
			for (left += N, right += N + 1; left < right; left /= 2, right /= 2) {
				// Order of aggregation may matter.
				if (left % 2 == 1) {
					resLeft = Policy::aggregate(resLeft, this->values[left++]);
				}
				if (right % 2 == 1) {
					resRight = Policy::aggregate(this->values[--right], resRight);
				}
			}
			return Policy::aggregate(resLeft, resRight);
		}

		// Point update an index.
		void update(LL idx, LL const &update) {
			idx += N;
			Policy::apply(this->values[idx], update);
			for (idx /= 2; idx >= 1; idx /= 2) {
				Policy::retrace(
					this->values[idx], this->values[idx * 2], this->values[idx * 2 + 1]);
			}
		}
	};
}

class Policy {
	public:
	using Value = array<LL, 4>;
	using Update = LL;
	using Result = array<LL, 4>;

	static constexpr Value initialize{
		-LLONG_MAX / 2,
		-LLONG_MAX / 2,
		-LLONG_MAX / 2,
		-LLONG_MAX / 2};

	inline static void apply(Value &value, Update const &update) {
		value[0] = 0;
		value[1] = value[2] = -LLONG_MAX / 2;
		value[3] = update;
	}
	inline static Result aggregate(Result const &left, Result const &right) {
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
	inline static void
	retrace(Value &value, Value const &left, Value const &right) {
		value = aggregate(left, right);
	}
};

using namespace Rain::Algorithm;

template <class P>
struct segtree {
	typedef typename P::T T;

	vector<T> s;
	int n;

	segtree(int N = 0) : s(2 * N, P::unit), n(N) {}

	void update(int i, const T &val) {
		for (s[i += n] = val; i /= 2;) s[i] = P::f(s[i * 2], s[i * 2 + 1]);
	}

	T query(int b, int e) {
		T ra = P::unit, rb = P::unit;
		for (b += n, e += n; b < e; b /= 2, e /= 2) {
			if (b % 2) ra = P::f(ra, s[b++]);
			if (e % 2) rb = P::f(s[--e], rb);
		}
		return P::f(ra, rb);
	}
};

struct pol {
	typedef array<LL, 4> T;

	constexpr static T unit{-1, -1, -1, -1};

	static T f(const T &l, const T &r) {
		if (l[0] < 0) return r;
		if (r[0] < 0) return l;
		return {
			min({l[0] + r[1], l[2] + r[0], l[2] + r[1]}),
			min({l[1] + r[1], l[3] + r[0], l[3] + r[1]}),
			min({l[0] + r[3], l[2] + r[2], l[2] + r[3]}),
			min({l[1] + r[3], l[3] + r[2], l[3] + r[3]})};

		// if (l[0] < 0) {
		// 	return r;
		// } else if (r[0] < 0) {
		// 	return l;
		// } else {
		// 	return {
		// 		max({l[0] + r[0], l[0] + r[2], l[1] + r[0]}),
		// 		max({l[0] + r[1], l[0] + r[3], l[1] + r[1]}),
		// 		max({l[2] + r[0], l[2] + r[2], l[3] + r[0]}),
		// 		max({l[2] + r[1], l[2] + r[3], l[3] + r[1]})};
		// }
	}
};

// array<LL, 199999> A;

int main(int, char const *[]) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL N, Q;
	cin >> N;

	// SegmentTree<Policy> st(N - 1);
	segtree<pol> st(N - 1);
	// LL S{0};
	RF(i, 0, N - 1) {
		LL X;
		// cin >> A[i];
		cin >> X;
		// S += A[i];
		// st.update(i, A[i]);
		st.update(i, {0, X, X, X});
	}

	cin >> Q;
	RF(i, 0, Q) {
		LL K, X;
		cin >> K >> X;
		// S -= A[K - 1];
		// S += X;
		// A[K - 1] = X;
		st.update(K - 1, {0, X, X, X});
		// cout << 2 * (S - st.query(0, N - 2)[0]) << '\n';
		cout << 2 * st.query(0, N - 1)[3] << '\n';
	}

	return 0;
}
