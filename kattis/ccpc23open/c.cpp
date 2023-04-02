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

	LL R, C, N;
	cin >> R >> C >> N;

	vector<vector<LL>> S(R);
	vector<string> G(R, string(C, ' '));
	LL ans{0};
	RF(i, 0, R) {
		string s;
		cin >> s;
		RF(j, 0, s.length()) {
			if (s[j] == '*') {
				S[i].push_back(j);
				G[i][j] = '*';
			}
		}
		ans += !S[i].empty();
	}

	if (ans <= N) {
		RF(i, 0, R) {
			if (S[i].empty()) {
				continue;
			}
			RF(j, 1, S[i].size()) {
				if (ans < N) {
					ans++;
					continue;
				}

				RF(k, S[i][j - 1] + 1, S[i][j]) {
					G[i][k] = '-';
				}
			}
		}
	} else {
		RF(i, 0, R) {
			if (S[i].empty()) {
				continue;
			}
			RF(j, 1, S[i].size()) {
				RF(k, S[i][j - 1] + 1, S[i][j]) {
					G[i][k] = '-';
				}
			}
		}

		DisjointSetUnion dsu(R);
		RF(i, 0, R) {
			RF(j, i + 1, R) {
				if (dsu.find(i) == dsu.find(j)) {
					continue;
				}

				unordered_set<LL> coll;
				RF(k, 0, S[i].size()) {
					coll.insert(S[i][k]);
				}
				LL found{-1};
				RF(k, 0, S[j].size()) {
					if (coll.count(S[j][k])) {
						found = S[j][k];
						break;
					}
				}
				if (found == -1) {
					continue;
				}

				dsu.join(i, j);
				RF(k, i + 1, j) {
					if (G[k][found] == '-') {
						G[k][found] = '+';
					} else if (G[k][found] == ' ') {
						G[k][found] = '|';
					}
				}
				ans--;

				if (ans == N) {
					break;
				}
			}
			if (ans == N) {
				break;
			}
		}
	}

	RF(i, 0, R) {
		cout << G[i] << '\n';
	}

	return 0;
}
