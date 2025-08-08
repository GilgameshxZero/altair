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

class Vertex {
	public:
	LL V;
	vector<LL> E;
	LL S{0}, D;
	bool H{false};
	LL P, PI;
};

class Path {
	public:
	LL P;
	vector<LL> V;
	unique_ptr<FenwickTree<LL>> F;
};

LL N, Q;
array<Vertex, 200001> V;
vector<Path> P;

void CH(LL i, LL p) {
	V[i].S = 1;
	for (auto &j : V[i].E) {
		if (j == p) {
			continue;
		}
		V[j].D = V[i].D + 1;
		CH(j, i);
		V[i].S += V[j].S;
	}
	for (auto &j : V[i].E) {
		if (j == p) {
			continue;
		}
		if (V[j].S > V[i].S / 2) {
			V[j].H = true;
		}
	}
}

void CP(LL i, LL p) {
	for (auto &j : V[i].E) {
		if (j == p) {
			continue;
		}
		if (V[j].H) {
			V[j].P = V[i].P;
			V[j].PI = V[i].PI + 1;
			P[V[i].P].V.push_back(j);
		} else {
			V[j].P = P.size();
			V[j].PI = 0;
			P.push_back({i, {j}, {}});
		}
		CP(j, i);
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> N >> Q;
	RF(i, 1, N + 1) {
		cin >> V[i].V;
	}
	RF(i, 0, N - 1) {
		LL a, b;
		cin >> a >> b;
		V[a].E.push_back(b);
		V[b].E.push_back(a);
	}
	V[1].D = 0;
	CH(1, 0);
	V[1].P = 0;
	V[1].PI = 0;
	P.push_back({0, {1}, {}});
	CP(1, 0);
	RF(i, 0, P.size()) {
		P[i].F.reset(new FenwickTree<LL>(P[i].V.size()));
		RF(j, 0, P[i].V.size()) {
			P[i].F->modify(j, V[P[i].V[j]].V);
		}
	}
	RF(i, 0, Q) {
		LL a, b;
		cin >> a;
		if (a == 1) {
			cin >> a >> b;
			LL d{b - V[a].V};
			V[a].V = b;
			P[V[a].P].F->modify(V[a].PI, d);
		} else {
			cin >> a;
			LL z{0};
			while (a != 0) {
				z += P[V[a].P].F->sum(V[a].PI);
				a = P[V[a].P].P;
			}
			cout << z << '\n';
		}
	}

	return 0;
}
