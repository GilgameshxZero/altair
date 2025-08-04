#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC target("avx", "avx2", "fma", "bmi", "bmi2", "popcnt", "lzcnt")
#pragma GCC optimize("Ofast", "unroll-loops")
#endif

#include <bits/stdc++.h>

namespace Rain::Algorithm {
	// Computes the maximum flow on a graph using Edmonds-Karp in O(VE^2). The
	// provided graph must be simple (no self-loops, no multi-edges, connected).
	//
	// Returns the residual graph after the max flow is computed.
	template <typename WeightType>
	inline std::pair<std::size_t,
		std::vector<std::unordered_map<std::size_t, WeightType>>>
	maxFlowEdmondsKarp(
		std::vector<std::unordered_map<std::size_t, WeightType>> const &edges,
		std::size_t const source,
		std::size_t const sink) {
		std::vector<std::unordered_map<std::size_t, WeightType>> residual(edges);
		WeightType flow{0};

		while (true) {
			// BFS for the shortest source-sink path.
			std::queue<std::size_t> bfsQueue;
			std::vector<std::size_t> parent(
				edges.size(), std::numeric_limits<std::size_t>::max());
			bfsQueue.push(source);
			while (!bfsQueue.empty()) {
				std::size_t current{bfsQueue.front()};
				bfsQueue.pop();
				for (auto const &edge : residual[current]) {
					if (parent[edge.first] == std::numeric_limits<std::size_t>::max() &&
						residual[current][edge.first] > 0) {
						parent[edge.first] = current;
						bfsQueue.push(edge.first);
					}
				}
				if (parent[sink] != std::numeric_limits<std::size_t>::max()) {
					break;
				}
			}

			// Exit if no path found, otherwise update residuals.
			if (parent[sink] == std::numeric_limits<std::size_t>::max()) {
				break;
			}

			WeightType pathFlow{std::numeric_limits<WeightType>::max()};
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
	vector<unordered_map<size_t, LL>> E(N);
	RF(i, 0, M) {
		LL A, B, C;
		cin >> A >> B >> C;
		A--;
		B--;
		E[A][B] += C;
	}

	auto [F, R]{maxFlowEdmondsKarp(E, 0, N - 1)};
	cout << F;

	return 0;
}
