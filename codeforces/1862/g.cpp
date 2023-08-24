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

using namespace Rain::Algorithm;

class AddSumPolicy {
	public:
	using Value = LL;
	using Update = LL;
	using Result = LL;

	static constexpr Value DEFAULT_VALUE{0};

	static void apply(Value &value, Update const &update) { value += update; }

	static Result aggregate(Result const &left, Result const &right) {
		return left + right;
	}

	static void retrace(Value &value, Value const &left, Value const &right) {
		value = left + right;
	}
};

LL const INF{100000000000};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL T;
	cin >> T;
	while (T--) {
		LL N;
		cin >> N;
		map<pair<LL, LL>, LL> X;
		vector<LL> A(N);
		A.push_back(0);
		RF(i, 1, N + 1) {
			cin >> A[i];
			X[{A[i], i}] = 0;
		}
		A.push_back(INF);
		LL Q;
		cin >> Q;
		vector<pair<LL, LL>> R(Q);
		RF(i, 0, Q) {
			cin >> R[i].first >> R[i].second;
			X[{R[i].second, R[i].first}] = 0;
		}

		if (N == 1) {
			RF(i, 0, Q) {
				cout << R[i].second << ' ';
			}
			cout << '\n';
			continue;
		}

		LL r{0};
		for (auto &i : X) {
			i.second = r++;
		}
		SegmentTree<AddSumPolicy> ST(X.size());
		RF(i, 1, N + 1) {
			ST.update(X[{A[i], i}], 1);
		}

		set<pair<LL, LL>> B;
		RF(i, 0, A.size()) {
			B.insert({A[i], i});
		}
		map<pair<LL, LL>, LL> C;
		vector<LL> D(A.size());
		for (auto i{B.begin()}; next(i) != B.end(); i++) {
			D[i->second] = next(i)->first - i->first;
			C.insert({{D[i->second], i->second}, 0});
		}

		vector<pair<LL, LL>> a(A.size());
		RF(i, 0, A.size()) {
			a[i] = {A[i], i};
		}
		sort(a.begin(), a.end());
		C[{INF, N + 1}] = 0;
		D[N + 1] = INF;
		RF(i, D.size() - 2, -1) {
			C[{D[a[i].second], a[i].second}] +=
				D[a[i].second] + C[{D[a[i + 1].second], a[i + 1].second}];
		}

		RF(i, 0, Q) {
			LL x{R[i].second}, y{R[i].first};
			ST.update(X[{A[y], y}], -1);
			auto v{B.find({A[y], y})}, u{prev(v)}, w{next(v)};
			auto z{C[{D[u->second], u->second}]};
			C.erase({D[u->second], u->second});
			D[u->second] += D[v->second];
			C.insert({{D[u->second], u->second}, z});
			C.erase({D[v->second], v->second});
			B.erase(v);
			A[y] = x;
			ST.update(X[{A[y], y}], 1);
			v = B.insert({A[y], y}).first;
			u = prev(v);
			w = next(v);
			z = C[{D[u->second], u->second}];
			C.erase({D[u->second], u->second});
			D[v->second] = A[w->second] - A[v->second];
			D[u->second] -= D[v->second];
			C.insert({{D[u->second], u->second}, z});
			C.insert(
				{{D[v->second], v->second},
				 C[{D[w->second], w->second}] + D[v->second]});

			auto e{prev(prev(C.end()))};
			auto g{e->first.first};
			while (e->first.second == 0 || e->first.first >= INF / 10) {
				e--;
			}
			LL f{
				A[e->first.second] +
				e->first.first * (ST.query(X[{A[y], y}], X.size() - 1) + 1) -
				(e->first.first * ST.query(X[{A[y], y}], X.size() - 1) -
				 (e->second - g))};
			cout << f << ' ';
		}
		cout << '\n';
	}

	return 0;
}
