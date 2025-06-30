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

	LL N;
	cin >> N;

	vector<pair<pair<LL, LL>, LL>> X(N);
	unordered_set<LL> d;
	RF(i, 0, N) {
		cin >> X[i].first.first >> X[i].first.second;
		d.insert(X[i].first.first);
		d.insert(X[i].first.second);
		X[i].second = i;
	}

	vector<LL> D;
	for (auto &i : d) {
		D.push_back(i);
	}
	sort(D.begin(), D.end());
	map<LL, LL> Dr;
	RF(i, 0, D.size()) {
		Dr[D[i]] = i;
	}

	vector<LL> Z[2];
	Z[0].resize(N, 0);
	Z[1].resize(N, 0);

	sort(X.begin(),
		X.end(),
		[](pair<pair<LL, LL>, LL> &X, pair<pair<LL, LL>, LL> &Y) {
			if (X.first.first == Y.first.first) {
				return X.first.second > Y.first.second;
			}
			return X.first.first < Y.first.first;
		});

	{
		Rain::Algorithm::FenwickTree<LL> F(D.size());
		RF(i, N - 1, -1) {
			Z[0][i] = F.sum(Dr[X[i].first.second]);
			F.modify(Dr[X[i].first.second], 1);
		}
	}

	{
		Rain::Algorithm::FenwickTree<LL> F(D.size());
		RF(i, 0, N) {
			Z[1][i] = F.sum(D.size() - 1) -
				(X[i].first.second == D[0] ? 0 : F.sum(Dr[X[i].first.second] - 1));
			F.modify(Dr[X[i].first.second], 1);
		}
	}

	vector<LL> R(N);
	RF(i, 0, N) {
		R[X[i].second] = i;
	}

	RF(i, 0, N) {
		cout << Z[0][R[i]] << ' ';
	}
	cout << '\n';
	RF(i, 0, N) {
		cout << Z[1][R[i]] << ' ';
	}

	return 0;
}
