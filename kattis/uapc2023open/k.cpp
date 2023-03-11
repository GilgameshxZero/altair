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
	// Computes the maximum flow on a graph using Edmonds-Karp in O(VE^2). The
	// provided graph must be simple (no self-loops, no multi-edges, connected).
	//
	// Returns the residual graph after the max flow is computed.
	inline std::
		pair<std::size_t, std::vector<std::unordered_map<std::size_t, std::size_t>>>
		maxFlowEdmondsKarp(
			std::vector<std::unordered_map<std::size_t, std::size_t>> const &edges,
			std::size_t const source,
			std::size_t const sink) {
		std::vector<std::unordered_map<std::size_t, std::size_t>> residual(edges);
		std::size_t flow{0};

		while (true) {
			// BFS for the shortest source-sink path.
			std::queue<std::size_t> bfsQueue;
			std::vector<std::size_t> parent(edges.size(), SIZE_MAX);
			bfsQueue.push(source);
			while (!bfsQueue.empty()) {
				std::size_t current{bfsQueue.front()};
				bfsQueue.pop();
				for (auto const &edge : residual[current]) {
					if (
						parent[edge.first] == SIZE_MAX &&
						residual[current][edge.first] > 0) {
						parent[edge.first] = current;
						bfsQueue.push(edge.first);
					}
				}
				if (parent[sink] != SIZE_MAX) {
					break;
				}
			}

			// Exit if no path found, otherwise update residuals.
			if (parent[sink] == SIZE_MAX) {
				break;
			}

			std::size_t pathFlow{SIZE_MAX};
			for (std::size_t current{sink}; current != source;
					 current = parent[current]) {
				pathFlow = std::min(pathFlow, residual[parent[current]][current]);
			}
			flow += pathFlow;
			for (std::size_t current{sink}; current != source;
					 current = parent[current]) {
				residual[parent[current]][current] -= pathFlow;
				residual[current][parent[current]] += pathFlow;
			}
		}

		// C++17: guaranteed either NRVO or move.
		return {flow, residual};
	}
}

using namespace Rain::Algorithm;

int main(int, char const *[]) {
#if !defined(ONLINEJUDGE) && (defined(__APPLE__) || defined(__MACH__))
	std::freopen("../build/i.default.txt", "r", stdin);
	std::freopen("../build/o.default.txt", "w", stdout);
#endif

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	LL N, L, D;
	cin >> N >> L >> D;

	vector<unordered_map<char, vector<LL>>> b0s(L);
	RF(i, 0, N) {
		string S;
		cin >> S;
		RF(j, 0, L) {
			b0s[i][S[j]].push_back(i);
		}
	}

	vector<LL> bi;
	RF(i, 0, L) {
		if (b0s.size() > 1) {
			bi.push_back(i);
		}
	}
	if (bi.size() > N * D) {
		cout << "-1";
		return 0;
	}

	vector<unordered_map<size_t, size_t>> E(2);
	RF(i, 0, bi.size()) {
		E.push_back({});
		E.back()[0] = 1;
	}
	E.resize(E.size() + 26);
	RF(i, 0, bi.size()) {
		for (auto const &j : b0s[bi[i]]) {
			E[2 + i][j.first] = 1;
		}
	}
	E.resize(E.size() + N);
	RF(i, 0, bi.size()) {
		for (auto const &j : b0s[bi[i]]) {
			E[2 + bi.size() + (int)(j.first - 'a')][j.second] = 1;
		}
	}
	E.resize(E.size() + 1);
	LL sink{E.size() - 1};
	RF(i, 0, N) {
		E[2 + 26 + bi.size() + i][sink] = 1;
	}

	auto res{maxFlowEdmondsKarp(E, 0, sink)};

	return 0;
}
