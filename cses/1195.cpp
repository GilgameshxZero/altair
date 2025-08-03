#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC target("avx", "avx2", "fma", "bmi", "bmi2", "popcnt", "lzcnt")
#pragma GCC optimize("Ofast", "unroll-loops")
#endif

#include <bits/stdc++.h>

namespace Rain::Algorithm {
	// Computes SSSP on directed weighted graph via Dijkstra's in $O(N + M\log
	// M)$, or until a target vertex is reached. The provided graph must be simple
	// and connected, and edge weights must be non-negative.
	//
	// Returns a list of distances to each node, and the penultimate node on the
	// shortest path to each node.
	template <typename IndexType, typename WeightType>
	std::pair<std::vector<WeightType>, std::vector<IndexType>> ssspDijkstra(
		std::vector<std::unordered_map<IndexType, WeightType>> const &edges,
		IndexType const source,
		IndexType const sink = std::numeric_limits<IndexType>::max()) {
		std::vector<WeightType> distances(
			edges.size(), std::numeric_limits<WeightType>::max());
		std::vector<IndexType> predecessors(
			edges.size(), std::numeric_limits<IndexType>::max());
		std::priority_queue<std::pair<WeightType, IndexType>,
			std::vector<std::pair<WeightType, IndexType>>,
			std::greater<std::pair<WeightType, IndexType>>>
			queue;
		std::vector<bool> visited(edges.size(), false);

		distances[source] = 0;
		queue.push({0, source});
		while (!queue.empty()) {
			auto i{queue.top().second};
			queue.pop();
			if (sink == i) {
				break;
			}
			if (visited[i]) {
				continue;
			}
			visited[i] = true;
			for (auto const &j : edges[i]) {
				if (visited[j.first]) {
					continue;
				}
				if (distances[i] + j.second < distances[j.first]) {
					distances[j.first] = distances[i] + j.second;
					predecessors[j.first] = i;
					queue.push({distances[j.first], j.first});
				}
			}
		}
		return {distances, predecessors};
	}
}

using namespace Rain::Algorithm;

using LL = long long;
using LD = long double;
using namespace std;

#define RF(x, from, to) \
	for (LL x(from), _to(to), _delta{x < _to ? 1LL : -1LL}; x != _to; x += _delta)

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL N, M;
	cin >> N >> M;

	vector<unordered_map<LL, LL>> E(2 * N);
	RF(i, 0, M) {
		LL A, B, C;
		cin >> A >> B >> C;
		A--;
		B--;
		if (E[A].count(B)) {
			E[A][B] = min(E[A][B], C);
			E[A][N + B] = min(E[A][N + B], C / 2);
			E[N + A][N + B] = min(E[N + A][N + B], C);
		} else {
			E[A][B] = C;
			E[A][N + B] = C / 2;
			E[N + A][N + B] = C;
		}
	}

	auto [D, P]{ssspDijkstra(E, 0LL, 2 * N - 1)};
	cout << D.back();
	return 0;
}
