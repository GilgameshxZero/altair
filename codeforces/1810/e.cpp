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
}

using namespace Rain::Algorithm;

int main(int, char const *[]) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL T;
	cin >> T;
	while (T--) {
		LL N, M;
		cin >> N >> M;

		vector<LL> A(N);
		RF(i, 0, N) {
			cin >> A[i];
		}

		vector<vector<pair<LL, LL>>> E(N + 1);
		RF(i, 0, M) {
			LL U, V;
			cin >> U >> V;
			E[max(A[U - 1], A[V - 1])].push_back({U - 1, V - 1});
		}

		set<pair<LL, LL>> alive;
		DisjointSetUnion dsu(N);
		RF(i, 0, N) {
			if (A[i] == 0) {
				alive.insert({dsu.rank(i), dsu.find(i)});
			}
		}

		RF(i, 0, E.size()) {
			RF(j, 0, E[i].size()) {
				LL U{E[i][j].first}, V{E[i][j].second}, repU(dsu.find(U)),
					repV(dsu.find(V)), rankU(dsu.rank(U)), rankV(dsu.rank(V));
				dsu.join(U, V);
				LL repNew(dsu.find(U)), rankNew(dsu.rank(U));
				if (alive.count({rankU, repU}) || alive.count({rankV, repV})) {
					alive.erase({rankU, repU});
					alive.erase({rankV, repV});
					alive.insert({rankNew, repNew});
				}
			}
			if (!alive.empty() && alive.begin()->first == N) {
				break;
			}
			while (!alive.empty() && alive.begin()->first < i + 1) {
				alive.erase(alive.begin());
			}
		}

		cout << (alive.empty() ? "NO" : "YES") << '\n';
	}

	return 0;
}
