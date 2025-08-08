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
 
		inline std::size_t size() { return this->tree.size(); }
	};
}
 
using namespace Rain::Algorithm;
 
using LL = long long;
using LD = long double;
using namespace std;
 
#define RF(x, from, to) \
	for (LL x(from), _to(to), _delta{x < _to ? 1LL : -1LL}; x != _to; x += _delta)
 
struct Vertex {
	vector<LL> E;
	LL S, D;
	bool CV{false};
};
 
LL N, K1, K2, Z{0};
array<Vertex, 200001> V;
 
void CV(LL i, LL p) {
	V[i].S = 1;
	for (auto &j : V[i].E) {
		if (j == p || V[j].CV) {
			continue;
		}
		V[j].D = V[i].D + 1;
		CV(j, i);
		V[i].S += V[j].S;
	}
}
 
LL CC(LL i, LL p, LL t) {
	for (auto &j : V[i].E) {
		if (j == p || V[j].CV) {
			continue;
		}
		if (V[j].S > t / 2) {
			return CC(j, i, t);
		}
	}
	return i;
}
 
void CCZ1(LL i, LL p, FenwickTree<LL> &F) {
	if (V[i].D >= K1) {
		return;
	}
	for (auto &j : V[i].E) {
		if (j == p || V[j].CV) {
			continue;
		}
		V[j].D = V[i].D + 1;
		Z += F.sum(K1 - V[j].D) - F.sum(K1 - V[j].D - 1);
		CCZ1(j, i, F);
	}
}
 
void CCZ2(LL i, LL p, FenwickTree<LL> &F) {
	if (V[i].D >= K1) {
		return;
	}
	F.modify(V[i].D, 1);
	for (auto &j : V[i].E) {
		if (j == p || V[j].CV) {
			continue;
		}
		CCZ2(j, i, F);
	}
}
 
void CCZ(LL i, LL p) {
	V[i].CV = true;
	CV(i, p);
 
	if (K1 <= V[i].S - 1) {
		for (auto &j : V[i].E) {
			if (j == p || V[j].CV) {
				continue;
			}
			LL c{CC(j, 0, V[j].S)};
			CCZ(c, 0);
		}
 
		FenwickTree<LL> F(K1);
		F.modify(0, 1);
		for (auto &j : V[i].E) {
			if (V[j].CV) {
				continue;
			}
			V[j].D = 1;
			Z += F.sum(K1 - 1) - (K1 > 1 ? F.sum(K1 - 2) : 0);
			CCZ1(j, i, F);
			CCZ2(j, i, F);
		}
	}
 
	V[i].CV = false;
}
 
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
 
	cin >> N >> K1;
	RF(i, 0, N - 1) {
		LL a, b;
		cin >> a >> b;
		V[a].E.push_back(b);
		V[b].E.push_back(a);
	}
	CV(1, 0);
	LL c{CC(1, 0, N)};
	CCZ(c, 0);
	cout << Z;
 
	return 0;
}