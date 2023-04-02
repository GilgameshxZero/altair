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

	LL N, M, Q;
	cin >> N >> M >> Q;

	vector<unordered_set<LL>> E(N);
	RF(i, 0, M) {
		LL U, V;
		cin >> U >> V;
		E[U].insert(V);
		E[V].insert(U);
	}

	vector<pair<LL, pair<LL, LL>>> Q_(Q);
	RF(i, 0, Q) {
		LL T, U, V;
		cin >> T >> U >> V;
		Q_[i] = {T, {U, V}};
		if (T == 0) {
			E[U].erase(V);
			E[V].erase(U);
		}
	}

	DisjointSetUnion dsu(N);
	RF(i, 0, N) {
		for (auto &j : E[i]) {
			dsu.join(i, j);
		}
	}

	vector<string> ans;
	RF(i, Q - 1, -1) {
		auto &q = Q_[i];
		if (q.first == 0) {
			E[q.second.first].insert(q.second.second);
			E[q.second.second].insert(q.second.first);
			dsu.join(q.second.first, q.second.second);
		} else {
			ans.push_back(
				dsu.find(q.second.first) == dsu.find(q.second.second) ? "safe"
																															: "unsafe");
		}
	}

	RF(i, ans.size() - 1, -1) {
		cout << ans[i] << '\n';
	}

	return 0;
}
