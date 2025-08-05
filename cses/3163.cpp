#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC target("avx", "avx2", "fma", "bmi", "bmi2", "popcnt", "lzcnt")
#pragma GCC optimize("Ofast", "unroll-loops")
#endif

#include <bits/stdc++.h>

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

using namespace Rain::Algorithm;

using LL = long long;
using LD = long double;
using namespace std;

#define RF(x, from, to) \
	for (LL x(from), _to(to), _delta{x < _to ? 1LL : -1LL}; x != _to; x += _delta)

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL N, Q;
	cin >> N >> Q;
	vector<pair<LL, LL>> X(N + 1);
	RF(i, 1, N + 1) {
		cin >> X[i].first;
		X[i].second = i;
	}
	X[0].second = 0;
	sort(X.begin(), X.end());
	vector<LL> Z(Q);
	vector<pair<pair<LL, LL>, pair<LL, LL>>> Y;
	RF(i, 0, Q) {
		LL a, b, c, d;
		cin >> a >> b >> c >> d;
		Y.push_back({{d, b}, {1, i}});
		Y.push_back({{d, a - 1}, {-1, i}});
		Y.push_back({{c - 1, b}, {-1, i}});
		Y.push_back({{c - 1, a - 1}, {1, i}});
	}
	sort(Y.begin(), Y.end());

	LL x{0};
	FenwickTree<LL> F(N + 1);
	RF(i, 0, Y.size()) {
		for (; x < X.size() && X[x].first <= Y[i].first.first; x++) {
			F.modify(X[x].second, 1);
		}
		Z[Y[i].second.second] += Y[i].second.first * F.sum(Y[i].first.second);
	}
	RF(i, 0, Q) {
		cout << Z[i] << '\n';
	}

	return 0;
}
