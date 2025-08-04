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

	Rain::Algorithm::FenwickTree<LL> F(N + 1);
	RF(i, 1, N + 1) {
		LL X;
		cin >> X;
		F.modify(i, X);
	}
	RF(i, 0, Q) {
		LL A, B, C;
		cin>> A >> B >> C;
		if (A == 1) {
			F.modify(B, -(F.sum(B) - F.sum(B - 1)) + C);
		} else {
			cout << F.sum(C) - F.sum(B - 1) << '\n';
		}
	}

	return 0;
}
