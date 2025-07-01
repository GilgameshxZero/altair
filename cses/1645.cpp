#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC target("avx", "avx2", "fma", "bmi", "bmi2", "popcnt", "lzcnt")
#pragma GCC optimize("Ofast", "unroll-loops")
#endif

#include <bits/stdc++.h>

namespace Rain::Algorithm {
	// Segment tree without lazy propagation nor range updates.
	//
	// Implements the policy pattern. Policy must implement the following
	// interface (omitted from being an actual interface, as static virtual
	// functions are not supported):
	//
	// static constexpr Value DEFAULT_VALUE: Identity values at creation and
	// aggregation.
	//
	// static void apply(Value &value, Update const &update): Fully apply
	// an update to a leaf node.
	//
	// static Result aggregate(Result const &left, Result const &right):
	// Aggregate two results from queries on children. Aggregating with a Result
	// converted from a default Value should do nothing.
	//
	// static void retrace(Value &value, Value const &left, Value const &right):
	// Aggregate values from two children while retracing an update. Aggregating
	// with a default Value should do nothing.
	template <typename Policy>
	class SegmentTree {
		public:
		using Value = typename Policy::Value;
		using Update = typename Policy::Update;
		using Result = typename Policy::Result;

		protected:
		// Aggregate values at each node.
		std::vector<Value> values;

		public:
		// Segment tree for a segment array of size size.
		SegmentTree(std::size_t const size)
				: values(2 * size, Policy::DEFAULT_VALUE) {}

		// Queries an inclusive range.
		Result query(std::size_t left, std::size_t right) {
			Value resLeft{Policy::DEFAULT_VALUE}, resRight{Policy::DEFAULT_VALUE};
			for (left += this->values.size() / 2,
				right += this->values.size() / 2 + 1;
				left < right;
				left /= 2, right /= 2) {
				// Order of aggregation matters for non-commutative operations.
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
		void update(std::size_t idx, Update const &update) {
			idx += this->values.size() / 2;
			Policy::apply(this->values[idx], update);
			for (idx /= 2; idx >= 1; idx /= 2) {
				Policy::retrace(
					this->values[idx], this->values[idx * 2], this->values[idx * 2 + 1]);
			}
		}
	};
}

using LL = long long;
using LD = long double;
using namespace std;

class SegmentTreePolicy {
	public:
	using Value = LL;
	using Update = LL;
	using Result = LL;

	static constexpr Value DEFAULT_VALUE{0};

	static void apply(Value &value, Update const &update) { value = update; }

	static Result aggregate(Result const &left, Result const &right) {
		return max(left, right);
	}

	static void retrace(Value &value, Value const &left, Value const &right) {
		value = max(left, right);
	}
};

using ST = Rain::Algorithm::SegmentTree<SegmentTreePolicy>;

#define RF(x, from, to) \
	for (LL x(from), _to(to), _delta{x < _to ? 1LL : -1LL}; x != _to; x += _delta)

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	unordered_map<LL, LL> Dr;
	LL N;
	cin >> N;

	vector<LL> X(N);
	RF(i, 0, N) {
		cin >> X[i];
		Dr[X[i]] = 0;
	}

	vector<LL> D;
	D.push_back(0);
	for (auto &i : Dr) {
		D.push_back(i.first);
	}
	sort(D.begin(), D.end());
	RF(i, 0, D.size()) {
		Dr[D[i]] = i;
	}

	ST S(D.size());
	RF(i, 0, N) {
		cout << S.query(0, Dr[X[i]] - 1) << ' ';
		S.update(Dr[X[i]], i + 1);
	}

	return 0;
}
