#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC target("avx", "avx2", "fma", "bmi", "bmi2", "popcnt", "lzcnt")
#pragma GCC optimize("Ofast", "unroll-loops")
#endif

#include <bits/stdc++.h>

using LL = long long;
using LD = long double;
using namespace std;

#define RF(x, from, to) \
	for (LL x(from), _to(to), _delta{x < _to ? 1LL : -1LL}; x != _to; x += _delta)

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

class Policy {
	public:
	using Value = LL;
	using Update = LL;
	using Result = LL;

	static constexpr Value DEFAULT_VALUE{1000000000};

	static void apply(Value &value, Update const &update) { value = update; }

	static Result aggregate(Result const &left, Result const &right) {
		return min(left, right);
	}

	static void retrace(Value &value, Value const &left, Value const &right) {
		value = min(left, right);
	}
};

using ST = Rain::Algorithm::SegmentTree<Policy>;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL N, M;
	cin >> N >> M;
	vector<LL> A(N);
	RF(i, 0, N) {
		cin >> A[i];
	}
	
	vector<vector<LL>> C(200001);
	RF(i, N - 1, -1) {
		C[A[i]].push_back(i);
	}

	ST S(200001);
	RF(i, 0, C.size()) {
		if (!C[i].empty()) {
			S.update(i, C[i].back());
		}
	}

	RF(i, 0, M) {
		LL b;
		cin >> b;
		LL z{S.query(0, b)};
		if (z == 1000000000) {
			cout << -1 << '\n';
		} else {
			cout << z + 1 << '\n';
			// C[A[z]].pop_back();
			// if (C[A[z]].empty()) {
			// 	S.update(A[z], 1000000000);
			// } else {
			// 	S.update(A[z], C[A[z]].back());
			// }
		}
	}

	return 0;
}
