#include <type_traits>
#if defined(__GNUC__) && !defined(__clang__) && !defined(__MINGW32__)
#pragma GCC target("avx", "avx2", "fma", "bmi", "bmi2", "popcnt", "lzcnt")
#pragma GCC optimize("Ofast", "unroll-loops")
#endif

#include <bits/stdc++.h>

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

using LL = long long;
using LD = long double;
using namespace std;

#define RF(x, from, to) \
	for (LL x(from), _to(to), _delta{x < _to ? 1LL : -1LL}; x != _to; x += _delta)

array<pair<LL, LL>, 4> D;

using namespace Rain::Algorithm;

void flood(vector<vector<LL>> &G, vector<vector<LL>> &CCX, LL I, LL J) {
	CCX[I][J] = -1;
	RF(i, 0, 4) {
		if (CCX[I + D[i].first][J + D[i].second] != -1) {
			flood(G, CCX, I + D[i].first, J + D[i].second);
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	D[0] = {-1, 0};
	D[1] = {0, 1};
	D[2] = {1, 0};
	D[3] = {0, -1};

	LL T;
	cin >> T;
	while (T--) {
		LL N, M, Q;
		cin >> N >> M;
		vector<vector<LL>> G(N + 2, vector<LL>(M + 2, LLONG_MAX));
		RF(i, 1, N + 1) {
			RF(j, 1, M + 1) {
				cin >> G[i][j];
			}
		}
		cin >> Q;
		vector<vector<array<bool, 4>>> F(N + 2, vector<array<bool, 4>>(M + 2));
		vector<vector<LL>> CCX(N + 2, vector<LL>(M + 2, -1));
		DisjointSetUnion DSU(N * M + Q);
		vector<LL> CCY(N * M + Q, LLONG_MAX);
		LL CCXC{0}, Z{0};
		RF(i, 1, N + 1) {
			RF(j, 1, M + 1) {
				RF(k, 0, 4) {
					F[i][j][k] = G[i][j] > G[i + D[k].first][j + D[k].second];
				}
				CCX[i][j] = CCXC++;
				RF(k, 0, 4) {
					if (
						G[i][j] == G[i + D[k].first][j + D[k].second] &&
						CCX[i + D[k].first][j + D[k].second] != -1) {
						DSU.join(CCX[i][j], CCX[i + D[k].first][j + D[k].second]);
					}
				}
			}
		}
		RF(i, 1, N + 1) {
			RF(j, 1, M + 1) {
				RF(k, 0, 4) {
					CCY[DSU.find(CCX[i][j])] =
						min(CCY[DSU.find(CCX[i][j])], G[i + D[k].first][j + D[k].second]);
				}
			}
		}
		// RF(i, 1, N + 1) {
		// 	RF(j, 1, M + 1) {
		// 		if (CCX[i][j] != -1) {
		// 			cout << DSU.find(CCX[i][j]) << ' ';
		// 		} else {
		// 			cout << "-1 ";
		// 		}
		// 	}
		// 	cout << '\n';
		// }
		cout << Z << '\n';
		// RF(i, 1, N + 1) {
		// 	RF(j, 1, M + 1) {
		// 		if (CCX[i][j] != -1) {
		// 			CCX[i][j] = DSU.find(CCX[i][j]);
		// 		}
		// 	}
		// }
		RF(i, 0, Q) {
			LL I, J, X;
			cin >> I >> J >> X;
			continue;
			if (CCX[I][J] != -1) {
				if (CCY[DSU.find(CCX[I][J])] == G[I][J]) {
					Z--;
				}
				flood(G, CCX, I, J);
			}
			G[I][J] -= X;
			RF(k, 0, 4) {
				F[I][J][k] = G[I][J] > G[I + D[k].first][J + D[k].second];
				F[I - D[k].first][J - D[k].second][k] =
					G[I - D[k].first][J - D[k].second] > G[I][J];
			}
			RF(k, 0, 4) {
				if (
					count(
						F[I - D[k].first][J - D[k].second].begin(),
						F[I - D[k].first][J - D[k].second].end(),
						true) > 0 &&
					CCX[I - D[k].first][J - D[k].second] != -1) {
					Z--;
					flood(G, CCX, I - D[k].first, J - D[k].second);
				}
			}
			if (count(F[I][J].begin(), F[I][J].end(), true) == 0) {
				CCX[I][J] = CCXC++;
				Z++;
				RF(k, 0, 4) {
					if (CCX[I + D[k].first][J + D[k].second] != -1) {
						Z -= DSU.join(CCX[I][J], CCX[I + D[k].first][J + D[k].second]);
					}
				}
			}
			// RF(i, 1, N + 1) {
			// 	RF(j, 1, M + 1) {
			// 		if (CCX[i][j] != -1) {
			// 			cout << DSU.find(CCX[i][j]) << ' ';
			// 		} else {
			// 			cout << "-1 ";
			// 		}
			// 	}
			// 	cout << '\n';
			// }
			cout << Z << '\n';
		}
	}

	return 0;
}
