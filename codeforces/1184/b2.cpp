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

// Computes the maximum flow on a graph using Edmonds-Karp in O(VE^2). The
// provided graph must be simple (no self-loops, no multi-edges, connected).
// Returns the residual graph after the max flow is computed.
std::size_t
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

	return flow;
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

	vector<unordered_set<LL>> E(N);
	RF(i, 0, M) {
		LL U, V;
		cin >> U >> V;
		if (U == V) {
			continue;
		}
		E[U - 1].insert(V - 1);
		E[V - 1].insert(U - 1);
	}

	LL S, B, K, H;
	cin >> S >> B >> K >> H;
	vector<vector<pair<pair<LL, LL>, LL>>> s(N);
	RF(i, 0, S) {
		LL X, A, F;
		cin >> X >> A >> F;
		s[X - 1].push_back({{A, F}, i});
	}
	vector<vector<pair<LL, LL>>> b(N);
	RF(i, 0, B) {
		LL X, D;
		cin >> X >> D;
		b[X - 1].push_back({D, i});
	}

	vector<unordered_map<size_t, size_t>> e(S + B + 2);
	RF(i, 0, S) {
		e[0][i + 2] = 1;
	}
	RF(i, 0, B) {
		e[i + 2 + S][1] = 1;
	}

	vector<vector<LL>> d(N, vector<LL>(N, 1000000000));
	RF(i, 0, N) {
		d[i][i] = 0;
	}
	RF(i, 0, N) {
		for (auto &j : E[i]) {
			d[i][j] = 1;
		}
	}
	RF(i, 0, N) {
		RF(j, 0, N) {
			RF(k, 0, N) {
				d[j][k] = min(d[j][k], d[j][i] + d[i][k]);
			}
		}
	}

	RF(i, 0, N) {
		RF(j, 0, s[i].size()) {
			RF(k, 0, N) {
				RF(l, 0, b[k].size()) {
					if (
						d[i][k] < s[i][j].first.second &&
						b[k][l].first <= s[i][j].first.first) {
						e[2 + s[i][j].second][2 + S + b[k][l].second] = 1;
					}
				}
			}
		}
	}

	auto res{maxFlowEdmondsKarp(e, 0, 1)};
	cout << min((LL)res * K, S * H);

	return 0;
}
