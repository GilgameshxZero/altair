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
	FenwickTree<LL> F(N + 1);
	vector<array<LL, 20>> H(N + 1);
	H[0][0] = LLONG_MAX;
	RF(i, 1, N + 1) {
		cin >> H[i][0];
	}
	RF(i, 1, H[0].size()) {
		RF(j, 0, N + 1) {
			if (j + (1LL << (i - 1)) < N + 1) {
				H[j][i] = max(H[j][i - 1], H[j + (1LL << (i - 1))][i - 1]);
			} else {
				H[j][i] = H[j][i - 1];
			}
		}
	}
	vector<pair<pair<LL, LL>, LL>> X(Q);
	RF(i, 0, Q) {
		cin >> X[i].first.second >> X[i].first.first;
		X[i].second = i;
	}
	sort(X.begin(), X.end());

	LL i{1};
	vector<LL> Z(Q);
	RF(j, 0, Q) {
		for (; i <= X[j].first.first; i++) {
			LL low{0}, high{i}, mid;
			while (low + 1 < high) {
				mid = (low + high) / 2;
				LL l{0};
				while ((1LL << l) <= i - mid) {
					l++;
				}
				l--;
				LL k{max(H[mid][l], H[i - (1LL << l)][l])};
				if (k >= H[i][0]) {
					low = mid;
				} else {
					high = mid;
				}
			}
			F.modify(low, 1);
		}
		Z[X[j].second] = X[j].first.first - X[j].first.second + 1 -
			(F.sum(X[j].first.first) - F.sum(X[j].first.second - 1));
	}
	RF(i, 0, Q) {
		cout << Z[i] << '\n';
	}

	return 0;
}
