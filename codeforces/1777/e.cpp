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
#include <regex>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <system_error>
#include <thread>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using LL = long long;
using LD = long double;

#define RF(x, from, to)                                                      \
	for (long long x = from, _to = to, _delta{x < _to ? 1LL : -1LL}; x != _to; \
			 x += _delta)

using namespace std;

// namespace Rain::Algorithm {
// 	// Union-Find/Disjoint-Set-Union implementation. Near-constant time
// amortized
// 	// union and find.
// 	//
// 	// Implements path compression and union by rank.
// 	class DisjointSetUnion {
// 		private:
// 		// A pair of (is_root, X). If node is root, X stores the size of the
// 		// cluster. Otherwise, X stores the index of the node’s parent.
// 		mutable std::vector<std::pair<bool, std::size_t>> nodes;

// 		public:
// 		DisjointSetUnion(std::size_t const size) : nodes(size, {true, 1}) {}

// 		std::size_t find(std::size_t const i) const {
// 			if (this->nodes[i].first) {
// 				return i;
// 			}
// 			return this->nodes[i].second = this->find(this->nodes[i].second);
// 		}
// 		std::size_t rank(std::size_t const i) const {
// 			return this->nodes[this->find(i)].second;
// 		}
// 		void join(std::size_t const i, std::size_t const j) {
// 			std::size_t pI{this->find(i)}, pJ{this->find(j)};
// 			if (pI == pJ) {
// 				return;
// 			}
// 			if (this->nodes[pI].second > this->nodes[pJ].second) {
// 				std::swap(pI, pJ);
// 			}
// 			this->nodes[pJ].second += this->nodes[pI].second;
// 			this->nodes[pI] = {false, pJ};
// 		}
// 	};
// }

namespace Rain::Algorithm {
	// Computes strongly connected components (SCCs) for a simple graph G in
	// O(V+E). The SCCs form an acyclic condensation graph of G. Typically,
	// Tarjan’s is more efficient than Kosarju’s algorithm for SCCs, though
	// Kosarju’s algorithm provides the SCCs in topologically sorted order.
	//
	// Returns the number of CCs, and the 0-indexed index of the
	// SCC that each vertex belongs to.
	std::pair<std::size_t, std::vector<std::size_t>> stronglyConnectedTarjans(
		std::vector<std::vector<std::size_t>> const &edges) {
		std::size_t cScc{0}, cPreOrderId{0};
		std::vector<std::size_t> scc(edges.size()),
			preOrderId(edges.size(), SIZE_MAX), lowLink(edges.size());
		std::vector<bool> onStack(edges.size(), false);
		std::stack<std::size_t> s;

		// Tarjan’s requires a subroutine for its inner DFS, which we implement via
		// recursive lambda with an explicit return type.
		auto subroutine{[&](std::size_t _i) {
			auto subroutineInner{[&](std::size_t i, auto &subroutineRef) -> void {
				lowLink[i] = preOrderId[i] = cPreOrderId++;
				onStack[i] = true;
				s.push(i);

				for (auto const &j : edges[i]) {
					if (preOrderId[j] == SIZE_MAX) {
						subroutineRef(j, subroutineRef);
						lowLink[i] = min(lowLink[i], lowLink[j]);
					} else if (onStack[j]) {
						lowLink[i] = min(lowLink[i], preOrderId[j]);
					}
				}

				if (lowLink[i] == preOrderId[i]) {
					std::size_t j;
					do {
						j = s.top();
						s.pop();
						onStack[j] = false;
						scc[j] = cScc;
					} while (j != i);
					cScc++;
				}
			}};
			subroutineInner(_i, subroutineInner);
		}};

		for (std::size_t i{0}; i < edges.size(); i++) {
			if (preOrderId[i] == SIZE_MAX) {
				subroutine(i);
			}
		}

		return {cScc, scc};
	}
}

using namespace Rain::Algorithm;

/* ---------------------------- End of template. ---------------------------- */

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
		LL N, M;
		cin >> N >> M;
		vector<vector<size_t>> E(N);
		vector<unordered_map<LL, LL>> W(N);
		RF(i, 0, M) {
			LL j, k, w;
			cin >> j >> k >> w;
			E[j - 1].push_back(k - 1);
			W[j - 1][k - 1] = w;
		}

		LL low{1000000001}, high{-1}, mid;
		while (low - 1 != high) {
			mid = (low + high) / 2;
			vector<vector<size_t>> EE(E);
			RF(i, 0, N) {
				for (auto const &j : E[i]) {
					if (W[i][j] <= mid) {
						EE[j].push_back(i);
					}
				}
			}

			auto [cScc, scc]{stronglyConnectedTarjans(EE)};
			vector<bool> cSccIn(cScc);
			RF(i, 0, N) {
				for (auto const &j : E[i]) {
					if (scc[i] == scc[j]) {
						continue;
					}
					cSccIn[scc[j]] = true;
				}
			}

			LL cSccIn0{0};
			RF(i, 0, cScc) {
				cSccIn0 += !cSccIn[i];
			}

			if (cSccIn0 == 1) {
				low = mid;
			} else {
				high = mid;
			}
		}
		cout << (low == 1000000001 ? -1 : low) << '\n';

		// LL ans{0};
		// DisjointSetUnion dsu(cScc);
		// RF(i, 0, E2S.size()) {
		// 	if (cSccIn0 == 1) {
		// 		break;
		// 	}
		// 	LL iS = dsu.find(E2S[i].second.first),
		// 		 jS = dsu.find(E2S[i].second.second);
		// 	if (iS == jS) {
		// 		continue;
		// 	}

		// 	ans = E2S[i].first;

		// 	while (true) {
		// 		cSccIn0 -= E2R[iS].empty() + E2R[jS].empty();
		// 		dsu.join(iS, jS);
		// 		LL cur = dsu.find(iS), other{cur == iS ? jS : iS};

		// 		for (auto const &j : E2[other]) {
		// 			E2[cur][j.first] = j.second;
		// 			E2R[j.first].erase(other);
		// 			E2R[j.first][cur] = j.second;
		// 		}
		// 		for (auto const &j : E2R[other]) {
		// 			E2R[cur][j.first] = j.second;
		// 			E2[j.first].erase(other);
		// 			E2[j.first][cur] = j.second;
		// 		}
		// 		E2[cur].erase(cur);
		// 		E2[cur].erase(other);
		// 		E2R[cur].erase(cur);
		// 		E2R[cur].erase(other);

		// 		cSccIn0 += E2R[cur].empty();

		// 		bool again{false};
		// 		for (auto const &j : E2[cur]) {
		// 			if (E2[j.first].count(cur)) {
		// 				iS = cur;
		// 				jS = j.first;
		// 				again = true;
		// 				break;
		// 			}
		// 		}
		// 		for (auto const &j : E2R[cur]) {
		// 			if (E2R[j.first].count(cur)) {
		// 				iS = cur;
		// 				jS = j.first;
		// 				again = true;
		// 				break;
		// 			}
		// 		}
		// 		if (!again) {
		// 			break;
		// 		}
		// 	}
		// }
		// cout << (cSccIn0 == 1 ? ans : -1) << '\n';
	}

	return 0;
}
