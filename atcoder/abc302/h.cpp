#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC target("avx2", "bmi", "bmi2", "popcnt", "lzcnt")
#pragma GCC optimize("Ofast", "unroll-loops")
#endif

#include <bits/stdc++.h>

using LL = long long;
using LD = long double;
using namespace std;

#define RF(x, from, to) \
	for (LL x(from), _to(to), _delta{x < _to ? 1LL : -1LL}; x != _to; x += _delta)

namespace Rain::Algorithm {
	// Union-Find/Disjoint-Set-Union implementation. Near-constant time amortized
	// union and find. A constant-time amortized Union-Find exists for offline
	// unions and online finds, but this does not implement it.
	//
	// Implements path compression and union by rank. Stores additional parity and
	// distance extensions:
	// <https://cp-algorithms.com/data_structures/disjoint_set_union.html>.
	class DisjointSetUnion {
		private:
		mutable std::vector<bool> isRoot;
		// If a node is root, parent[node] stores the size of the component instead.
		mutable std::vector<std::size_t> parent;
		// Parity of the path weight from a node to its parent. Joining i and j
		// preserves the parity as if an edge had been added between i and j.
		mutable std::vector<bool> parity;
		// Length of the path wieght from node to its parent. Joining i and j
		// preserves the length as if an edge had been added between the roots of i
		// and j.
		mutable std::vector<std::size_t> distance;

		public:
		DisjointSetUnion(std::size_t const size)
				: isRoot(size, true),
					parent(size, 1),
					parity(size, false),
					distance(size, 0) {}

		std::size_t find(std::size_t const i) const {
			if (this->isRoot[i]) {
				return i;
			}
			auto rI{this->find(this->parent[i])};
			this->parity[i] = this->parity[i] ^ this->parity[this->parent[i]];
			this->distance[i] += this->distance[this->parent[i]];
			return this->parent[i] = rI;
		}
		inline std::size_t rank(std::size_t const i) const {
			return this->parent[this->find(i)];
		}
		inline bool connected(std::size_t const i, std::size_t const j) const {
			auto rI{this->find(i)}, rJ{this->find(j)};
			return rI == rJ;
		}
		inline std::size_t parityToRoot(std::size_t const i) const {
			this->find(i);
			return this->parity[i];
		}
		inline std::size_t distanceToRoot(std::size_t const i) const {
			this->find(i);
			return this->distance[i];
		}
		// Returns false if no join happened; otherwise true.
		inline bool
		join(std::size_t const i, std::size_t const j, std::size_t length = 0) {
			std::size_t rI{this->find(i)}, rJ{this->find(j)};
			if (rI == rJ) {
				return false;
			}
			if (this->parent[rI] > this->parent[rJ]) {
				std::swap(rI, rJ);
			}
			this->parent[rJ] += this->parent[rI];
			this->isRoot[rI] = false;
			this->parent[rI] = rJ;
			// i and j may be swapped here but it is okay.
			this->parity[rI] = this->parity[i] ^ this->parity[j] ^ (length % 2);
			this->distance[rI] = length;
			return true;
		}
	};

	// Persistent DSU based on
	// <https://codeforces.com/blog/entry/22031?#comment-266919>. Does not store
	// additional distance and parity extensions, and does not do path
	// compression. Overall runtime is hence O(N\ln N).
	//
	// Stores an additional extension to track the number of edges per connected
	// component.
	class DisjointSetUnionPersistent {
		private:
		mutable std::vector<bool> isRoot;
		// If a node is root, parent[node] stores the size of the component instead.
		mutable std::vector<std::size_t> parent;
		// cEdges[root] stores the number of edges in a connected component,
		// including those added via ineffective `join`s.
		mutable std::vector<std::size_t> cEdges;

		// History of changes for persistence.
		mutable std::stack<std::size_t> actions, actionParams;

		public:
		DisjointSetUnionPersistent(std::size_t const size)
				: isRoot(size, true), parent(size, 1), cEdges(size, 0) {}

		std::size_t find(std::size_t const i) const {
			if (this->isRoot[i]) {
				return i;
			}
			return this->find(this->parent[i]);
		}
		inline std::size_t rank(std::size_t const i) const {
			return this->parent[this->find(i)];
		}
		inline bool connected(std::size_t const i, std::size_t const j) const {
			auto rI{this->find(i)}, rJ{this->find(j)};
			return rI == rJ;
		}
		inline std::size_t countEdges(std::size_t const i) const {
			return this->cEdges[this->find(i)];
		}
		// Returns false if no join happened; otherwise true.
		inline bool join(std::size_t const i, std::size_t const j) {
			std::size_t rI{this->find(i)}, rJ{this->find(j)};
			if (rI == rJ) {
				this->actions.push(1);
				this->actionParams.push(rI);
				this->cEdges[rI]++;
				return false;
			}
			if (this->parent[rI] > this->parent[rJ]) {
				std::swap(rI, rJ);
			}
			this->actions.push(0);
			this->actionParams.push(this->parent[rI]);
			this->actionParams.push(rJ);
			this->actionParams.push(rI);
			this->parent[rJ] += this->parent[rI];
			this->cEdges[rJ] += this->cEdges[rI] + 1;
			this->isRoot[rI] = false;
			this->parent[rI] = rJ;
			return true;
		}

		// Returns the size of the history at the current time. Rewinds should
		// rewind until the history is some previous size.
		inline std::size_t countActions() const { return this->actions.size(); }
		// Rewinds the last action in the history.
		inline void rewind() {
			auto type{this->actions.top()};
			this->actions.pop();
			if (type == 0) {
				// Join.
				std::size_t rI{this->actionParams.top()};
				this->actionParams.pop();
				std::size_t rJ{this->actionParams.top()};
				this->actionParams.pop();
				std::size_t rankI{this->actionParams.top()};
				this->actionParams.pop();
				this->parent[rI] = rankI;
				this->isRoot[rI] = true;
				this->cEdges[rJ] -= this->cEdges[rI] + 1;
				this->parent[rJ] -= rankI;
			} else if (type == 1) {
				// Ineffective join.
				std::size_t rI{this->actionParams.top()};
				this->actionParams.pop();
				this->cEdges[rI]--;
			}
		}
	};
}

using namespace Rain::Algorithm;

LL N, Y;
vector<LL> A, B, Z;
vector<vector<LL>> E;
DisjointSetUnionPersistent *dsu;

void dfs(LL X, LL P) {
	LL rewindSize(dsu->countActions()), rA(dsu->find(A[X])), rB(dsu->find(B[X]));
	Y -= dsu->rank(rA) - 1 + (dsu->countEdges(rA) >= dsu->rank(rA));
	if (rA != rB) {
		Y -= dsu->rank(rB) - 1 + (dsu->countEdges(rB) >= dsu->rank(rB));
	}
	dsu->join(rA, rB);
	LL rC(dsu->find(rA));
	Y += dsu->rank(rC) - 1 + (dsu->countEdges(rC) >= dsu->rank(rC));
	Z[X] = Y;

	for (auto &i : E[X]) {
		if (i == P) {
			continue;
		}
		dfs(i, X);
	}

	Y -= dsu->rank(rC) - 1 + (dsu->countEdges(rC) >= dsu->rank(rC));
	while (dsu->countActions() > rewindSize) {
		dsu->rewind();
	}
	if (rA != rB) {
		Y += dsu->rank(rB) - 1 + (dsu->countEdges(rB) >= dsu->rank(rB));
	}
	Y += dsu->rank(rA) - 1 + (dsu->countEdges(rA) >= dsu->rank(rA));
}

int main(int, char const *[]) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> N;
	dsu = new DisjointSetUnionPersistent(N);
	A.resize(N);
	B.resize(N);
	Z.resize(N);
	E.resize(N);
	RF(i, 0, N) {
		cin >> A[i] >> B[i];
		A[i]--;
		B[i]--;
	}
	RF(i, 0, N) {
		LL U, V;
		cin >> U >> V;
		E[U - 1].push_back(V - 1);
		E[V - 1].push_back(U - 1);
	}

	dfs(0, -1);
	delete dsu;
	RF(i, 1, N) {
		cout << Z[i] << ' ';
	}
	return 0;
}
