#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC target("avx", "avx2", "fma", "bmi", "bmi2", "popcnt", "lzcnt")
#pragma GCC optimize("Ofast", "unroll-loops")
#endif

#include <bits/stdc++.h>

namespace Rain::Algorithm {
	// Computes SSSP on a weighted, directed graph with SPFA in O(NM). The
	// provided graph must be simple and may contain negative weights.
	//
	// SPFA is a variation of Bellman-Ford which tracks vertices which need to be
	// considered for relaxation. Any vertices which are relaxed after the
	// `N-1`-th iteration must be reachable via a negative-weight cycle.
	//
	// Returns a list of minimal distances to each vertex, and the penultimate
	// vertex on the shortest path to each vertex. If a vertex is unreachable, the
	// distance is INF. If a vertex is reachable via a negative-weight cycle, the
	// distance is -INF.
	template <typename IndexType, typename WeightType>
	std::pair<std::vector<WeightType>, std::vector<IndexType>> ssspSpfa(
		std::vector<std::unordered_map<IndexType, WeightType>> const &edges,
		IndexType const source) {
		std::vector<WeightType> distances(
			edges.size(), std::numeric_limits<WeightType>::max());
		distances[source] = 0;
		std::vector<IndexType> predecessors(
			edges.size(), std::numeric_limits<IndexType>::max());
		std::queue<std::pair<IndexType, IndexType>> queue;
		std::vector<bool> visited(edges.size(), true);
		queue.push({source, 0});
		visited[source] = false;
		while (!queue.empty()) {
			auto [i, j]{queue.front()};
			queue.pop();
			if (static_cast<std::size_t>(j) >= 2 * edges.size()) {
				break;
			}
			if (static_cast<std::size_t>(j) >= edges.size()) {
				distances[i] = std::numeric_limits<WeightType>::min();
			}
			if (visited[i]) {
				continue;
			}
			visited[i] = true;
			for (auto const &k : edges[i]) {
				if (distances[i] == std::numeric_limits<WeightType>::min() ||
					distances[i] + k.second < distances[k.first]) {
					if (distances[i] == std::numeric_limits<WeightType>::min()) {
						distances[k.first] = std::numeric_limits<WeightType>::min();
					} else {
						distances[k.first] = distances[i] + k.second;
					}
					predecessors[k.first] = i;
					visited[k.first] = false;
					queue.push({k.first, j + 1});
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

	vector<unordered_map<LL, LL>> E(N);
	RF(i, 0, M) {
		LL A, B, C;
		cin >> A >> B >> C;
		A--;
		B--;
		C = -C;
		if (E[A].count(B)) {
			E[A][B] = min(E[A][B], C);
		} else {
			E[A][B] = C;
		}
	}

	auto [D, P]{ssspSpfa(E, 0LL)};
	// RF(i, 0, N) {
	// 	cout << D[i] << ' ';
	// }
	// cout << '\n';
	cout << (D[N - 1] == std::numeric_limits<LL>::min() ? -1 : -D[N - 1]);

	return 0;
}
