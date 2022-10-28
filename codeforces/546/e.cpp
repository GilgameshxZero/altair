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

#define RF(x, from, to) \
	for (long long x = from, rfDir = from < to ? 1 : -1; x != to; x += rfDir)

using namespace std;

// Computes the maximum flow on a graph using Edmonds-Karp in O(VE^2). The
// provided graph must be simple (no self-loops, no multi-edges, connected).
// Returns the residual graph after the max flow is computed.
std::
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
					parent[edge.first] == SIZE_MAX && residual[current][edge.first] > 0) {
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
			pathFlow = min(pathFlow, residual[parent[current]][current]);
		}
		flow += pathFlow;
		for (std::size_t current{sink}; current != source;
				 current = parent[current]) {
			residual[parent[current]][current] -= pathFlow;
			residual[current][parent[current]] += pathFlow;
		}
	}

	return {flow, residual};
}

/* ---------------------------- End of template. ---------------------------- */

int main(int, char const *[]) {
#if !defined(ONLINEJUDGE) && (defined(__APPLE__) || defined(__MACH__))
	std::freopen("../build/i.default.txt", "r", stdin);
	std::freopen("../build/o.default.txt", "w", stdout);
#endif

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	LL N, M;
	cin >> N >> M;

	vector<LL> A(N), B(N);
	vector<unordered_map<size_t, size_t>> edges(N * 2 + 2);
	RF(i, 0, N) {
		cin >> A[i];
	}
	RF(i, 0, N) {
		cin >> B[i];
	}
	RF(i, 0, N) {
		edges[i * 2 + 2][i * 2 + 3] = A[i];
	}
	size_t inFlow{0}, outFlow{0};
	RF(i, 0, N) {
		if (B[i] > A[i]) {
			edges[i * 2 + 2][1] = B[i] - A[i];
			inFlow += edges[i * 2 + 2][1];
		} else if (A[i] > B[i]) {
			edges[0][i * 2 + 2] = A[i] - B[i];
			outFlow += edges[0][i * 2 + 2];
		}
	}
	if (outFlow != inFlow) {
		cout << "NO";
		return 0;
	}
	RF(i, 0, M) {
		LL P, Q;
		cin >> P >> Q;
		edges[P * 2 + 1][Q * 2] = SIZE_MAX;
		edges[Q * 2 + 1][P * 2] = SIZE_MAX;
	}

	auto flowResidual{maxFlowEdmondsKarp(edges, 0, 1)};
	if (outFlow != flowResidual.first) {
		cout << "NO";
		return 0;
	}

	cout << "YES\n";
	RF(i, 0, N) {
		RF(j, 0, N) {
			cout << (i == j ? flowResidual.second[i * 2 + 2][i * 2 + 3]
											: edges[i * 2 + 3][j * 2 + 2] -
									 flowResidual.second[i * 2 + 3][j * 2 + 2])
					 << ' ';
		}
		cout << '\n';
	}
	return 0;
}
