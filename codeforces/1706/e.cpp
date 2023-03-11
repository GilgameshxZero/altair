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

#define RF(x, from, to)                                                      \
	for (long long x = from, _to = to, _delta{x < _to ? 1LL : -1LL}; x != _to; \
			 x += _delta)

using LL = long long;
using namespace std;

#pragma hdrstop	 // ------------------------------------------------------------

namespace Rain::Algorithm {
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
			std::size_t pI{this->find(i)}, pJ{this->find(j)};
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
}

using namespace Rain::Algorithm;

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
		LL N, M, Q;
		cin >> N >> M >> Q;
		DisjointSetUnion dsu(N);
		RF(i, 0, M) {
			LL U, V;
			cin >> U >> V;
			dsu.join(U - 1, V - 1);
		}
	}

	return 0;
}
