#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC target("avx2", "bmi", "bmi2", "popcnt", "lzcnt")
#pragma GCC optimize("Ofast", "unroll-loops")
#endif

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <algorithm>
#include <array>
#include <atomic>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cinttypes>
#include <climits>
#include <cmath>
#include <complex>
#include <condition_variable>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <mutex>
#include <numeric>
#include <queue>
#include <random>
#include <regex>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <system_error>
#include <thread>
#include <tuple>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#if __has_include(<ext/pb_ds/assoc_container.hpp>)
#include <ext/pb_ds/assoc_container.hpp>
template <typename Key, typename Value, typename Hasher = std::hash<Key>>
using UnorderedMap = __gnu_pbds::gp_hash_table<Key, Value, Hasher>;
#else
template <typename Key, typename Value, typename Hasher = std::hash<Key>>
using UnorderedMap = std::unordered_map<Key, Value, Hasher>;
#endif

#define RF(x, from, to)                                                      \
	for (long long x = from, _to = to, _delta{x < _to ? 1LL : -1LL}; x != _to; \
			 x += _delta)

using LL = long long;
using LD = long double;
using namespace std;

#pragma hdrstop	 // ------------------------------------------------------------

namespace Rain::Algorithm {
	// Union-Find/Disjoint-Set-Union implementation. Near-constant time amortized
	// union and find.
	//
	// Implements path compression and union by rank.
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
		std::size_t rank(std::size_t const i) const {
			return this->parent[this->find(i)];
		}
		bool connected(std::size_t const i, std::size_t const j) const {
			auto rI{this->find(i)}, rJ{this->find(j)};
			return rI == rJ;
		}
		std::size_t parityToRoot(std::size_t const i) const {
			this->find(i);
			return this->parity[i];
		}
		std::size_t distanceToRoot(std::size_t const i) const {
			this->find(i);
			return this->distance[i];
		}
		void
		join(std::size_t const i, std::size_t const j, std::size_t length = 0) {
			std::size_t rI{this->find(i)}, rJ{this->find(j)};
			if (rI == rJ) {
				return;
			}
			if (this->parent[rI] > this->parent[rJ]) {
				std::swap(rI, rJ);
			}
			this->parent[rJ] += this->parent[rI];
			this->isRoot[rI] = false;
			this->parent[rI] = rJ;
			this->parity[rI] = this->parity[i] ^ this->parity[j] ^ (length % 2);
			this->distance[rI] = length;
		}
	};
}

using namespace Rain::Algorithm;

void dfsColor(
	vector<vector<LL>> &E,
	vector<bool> &color,
	vector<bool> &vis,
	LL cur) {
	vis[cur] = true;
	for (auto const &j : E[cur]) {
		if (vis[j]) {
			continue;
		}
		color[j] = !color[cur];
		dfsColor(E, color, vis, j);
	}
}

int main(int, char const *[]) {
#if !defined(ONLINEJUDGE) && (defined(__APPLE__) || defined(__MACH__))
	std::freopen("../build/i.default.txt", "r", stdin);
	std::freopen("../build/o.default.txt", "w", stdout);
#endif

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	LL T;
	cin >> T;
	while (T--) {
		LL N;
		cin >> N;
		vector<vector<LL>> A(N, vector<LL>(N));
		RF(i, 0, N) {
			RF(j, 0, N) {
				cin >> A[i][j];
			}
		}
		DisjointSetUnion dsu(N), d2(N);
		vector<vector<LL>> E(N);
		RF(i, 0, N) {
			RF(j, i + 1, N) {
				if (A[i][j] < A[j][i]) {
					if (
						dsu.connected(i, j) && dsu.parityToRoot(i) != dsu.parityToRoot(j)) {
						continue;
					}
					dsu.join(i, j, 0);
					E.push_back({});
					E[i].push_back(E.size() - 1);
					E.back().push_back(i);
					E[j].push_back(E.size() - 1);
					E.back().push_back(j);
				} else if (A[i][j] > A[j][i]) {
					if (
						dsu.connected(i, j) && dsu.parityToRoot(i) == dsu.parityToRoot(j)) {
						continue;
					}
					dsu.join(i, j, 1);
					E[i].push_back(j);
					E[j].push_back(i);
				}
			}
		}

		vector<bool> flip(E.size()), vis(E.size());
		RF(i, 0, E.size()) {
			if (vis[i]) {
				continue;
			}
			dfsColor(E, flip, vis, i);
		}
		RF(i, 0, N) {
			if (!flip[i]) {
				continue;
			}
			RF(j, 0, N) {
				swap(A[i][j], A[j][i]);
			}
		}
		RF(i, 0, N) {
			RF(j, 0, N) {
				cout << A[i][j] << ' ';
			}
			cout << '\n';
		}
	}

	return 0;
}
