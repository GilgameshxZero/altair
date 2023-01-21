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

// Union-Find/Disjoint-Set-Union implementation. Near-constant time amortized
// union and find.
//
// Implements path compression and union by rank.
class DisjointSetUnion {
	private:
	// A pair of (is_root, X). If node is root, X stores the size of the
	// cluster. Otherwise, X stores the index of the node’s parent.
	mutable std::vector<std::pair<bool, std::size_t>> nodes;

	public:
	DisjointSetUnion(std::size_t const size) : nodes(size, {true, 1}) {}

	std::size_t find(std::size_t const i) const {
		if (this->nodes[i].first) {
			return i;
		}
		return this->nodes[i].second = this->find(this->nodes[i].second);
	}
	std::size_t rank(std::size_t const i) const {
		return this->nodes[this->find(i)].second;
	}
	void join(std::size_t const i, std::size_t const j) {
		std::size_t pI = this->find(i), pJ = this->find(j);
		if (pI == pJ) {
			return;
		}
		if (this->nodes[pI].second > this->nodes[pJ].second) {
			std::swap(pI, pJ);
		}
		this->nodes[pJ].second += this->nodes[pI].second;
		this->nodes[pI] = {false, pJ};
	}
};

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
		vector<unordered_set<LL>> E(N);
		vector<pair<LL, pair<LL, LL>>> E2;
		RF(i, 0, M) {
			LL j, k, w;
			cin >> j >> k >> w;
			E2.push_back({w, {k - 1, j - 1}});
			E[j - 1].insert(k - 1);
		}
		sort(E2.begin(), E2.end());

		vector<LL> C(N, -1), S, I(N, -1);
		LL ccc{0}, i{0};
		function<void(LL)> dfs = [&](LL u) {
			I[u] = i;
			S.push_back(u);
			i++;
			LL m{I[u]};
			for (auto &v : E[u]) {
				if (I[v] == -1) {
					dfs(v);
				}
				m = min(m, I[v]);
			}
			if (m < I[u]) {
				I[u] = m;
				return;
			}
			LL v;
			do {
				v = S.back();
				S.pop_back();
				I[v] = N;
				C[v] = ccc;
			} while (v != u);
			ccc++;
		};
		RF(u, 0, N) {
			if (I[u] == -1) {
				dfs(u);
			}
		}

		// Edges between connected components.
		vector<unordered_set<LL>> CE(ccc), CEr(ccc);
		RF(i, 0, N) {
			for (auto &e : E[i]) {
				LL u{C[i]}, v{C[e]};
				if (u != v) {
					CE[u].insert(v);
					CEr[v].insert(u);
				}
			}
		}

		LL cinc{0};
		RF(i, 0, ccc) {
			if (CEr[i].size() == 0) {
				cinc++;
			}
		}

		if (cinc == 0) {
			cout << "0\n";
			continue;
		}

		DisjointSetUnion dsu(ccc);
		bool done{false};
		RF(i, 0, M) {
			LL u = dsu.find(C[E2[i].second.first]),
				 v = dsu.find(C[E2[i].second.second]);
			if (u != v) {
				dsu.join(u, v);
				LL j = dsu.find(u), other(j == u ? v : u);
				for (auto &k : CE[other]) {
					CE[j].insert(k);
				}
				for (auto &k : CEr[other]) {
					CEr[j].insert(k);
				}
				CE[j].erase(other);
				CEr[j].erase(other);
				if (CEr[other].size() == 0) {
					cinc--;
				}
				CE[other].clear();
				CEr[other].clear();

				if (cinc == 0) {
					cout << E2[i].first << "\n";
					done = true;
					break;
				}
			}
		}

		if (!done) {
			cout << "-1\n";
		}
	}

	return 0;
}
