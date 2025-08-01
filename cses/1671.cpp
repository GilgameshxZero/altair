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
	// Returns a list of distances to each node.
	template <typename IndexType, typename WeightType>
	std::vector<WeightType> ssspDijkstra(
		std::vector<std::unordered_map<IndexType, WeightType>> const &edges,
		IndexType const source,
		IndexType const sink = std::numeric_limits<IndexType>::max()) {
		std::vector<WeightType> distances(
			edges.size(), std::numeric_limits<WeightType>::max());
		distances[source] = 0;

		std::priority_queue<std::pair<WeightType, IndexType>,
			std::vector<std::pair<WeightType, IndexType>>,
			std::greater<std::pair<WeightType, IndexType>>>
			queue;
		queue.push({0, source});

		std::vector<bool> visited(edges.size(), false);
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
					queue.push({distances[j.first], j.first});
				}
			}
		}

		return distances;
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

	vector<unordered_map<LL, LL>> E(N);
	RF(i, 0, M) {
		LL A, B, C;
		cin >> A >> B >> C;
		if (E[A - 1].count(B - 1)) {
			E[A - 1][B - 1] = min(E[A - 1][B - 1], C);
		} else {
			E[A - 1][B - 1] = C;
		}
	}
	auto D{ssspDijkstra(E, 0LL)};
	RF(i, 0, N) {
		cout << D[i] << ' ';
	}

	return 0;
}
