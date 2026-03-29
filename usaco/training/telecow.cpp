/*
ID: yangchess1
PROG: telecow
LANG: C++
*/

#define ONLINE_JUDGE

#if defined(__GNUC__) && !defined(__clang__) && \
	!defined(__MINGW32__) && !defined(ONLINE_JUDGE)
#pragma GCC target( \
	"avx", "avx2", "fma", "bmi", "bmi2", "popcnt", "lzcnt")
#pragma GCC optimize("Ofast", "unroll-loops")
#endif

#include <bits/stdc++.h>

namespace Rain::Algorithm {
	// Computes the maximum flow on a graph using Edmonds-Karp
	// in O(VE^2). The provided graph must be simple (no
	// self-loops, no multi-edges, connected).
	//
	// Returns the residual graph after the max flow is
	// computed.
	template <typename WeightType>
	inline std::pair<
		std::size_t,
		std::vector<
			std::unordered_map<std::size_t, WeightType>>>
	maxFlowEdmondsKarp(
		std::vector<
			std::unordered_map<std::size_t, WeightType>> const
			&edges,
		std::size_t const source,
		std::size_t const sink) {
		std::vector<std::unordered_map<std::size_t, WeightType>>
			residual(edges);
		WeightType flow{0};

		while (true) {
			// BFS for the shortest source-sink path.
			std::queue<std::size_t> bfsQueue;
			std::vector<std::size_t> parent(
				edges.size(),
				std::numeric_limits<std::size_t>::max());
			bfsQueue.push(source);
			while (!bfsQueue.empty()) {
				std::size_t current{bfsQueue.front()};
				bfsQueue.pop();
				for (auto const &edge : residual[current]) {
					if (
						parent[edge.first] ==
							std::numeric_limits<std::size_t>::max() &&
						residual[current][edge.first] > 0) {
						parent[edge.first] = current;
						bfsQueue.push(edge.first);
					}
				}
				if (
					parent[sink] !=
					std::numeric_limits<std::size_t>::max()) {
					break;
				}
			}

			// Exit if no path found, otherwise update residuals.
			if (
				parent[sink] ==
				std::numeric_limits<std::size_t>::max()) {
				break;
			}

			WeightType pathFlow{
				std::numeric_limits<WeightType>::max()};
			for (std::size_t current{sink}; current != source;
					 current = parent[current]) {
				pathFlow = std::min(
					pathFlow, residual[parent[current]][current]);
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

#define RF(x, from, to)                                   \
	for (LL x(from), _to(to), _delta{x < _to ? 1LL : -1LL}; \
			 x != _to;                                          \
			 x += _delta)

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
#ifdef ONLINE_JUDGE
	std::freopen("telecow.in", "r", stdin);
	std::freopen("telecow.out", "w", stdout);
#endif

	LL N, M, S, T;
	cin >> N >> M >> S >> T;
	S--;
	T--;
	vector<unordered_map<size_t, size_t>> G(2 * N);
	RF(i, 0, M) {
		LL u, v;
		cin >> u >> v;
		u--;
		v--;
		G[u][v + N] = G[v][u + N] = SIZE_MAX / 2;
	}
	RF(i, 0, N) {
		G[i + N][i] = 1;
	}
	G[S + N][S] = G[T + N][T] = SIZE_MAX / 2;

	auto Y{maxFlowEdmondsKarp(G, S, T)};
	cout << Y.first << '\n';
	unordered_set<LL> W;
	W.insert(S);
	W.insert(T);
	LL i{0};
	while (Y.first > 0) {
		for (; i < N; i++) {
			if (W.count(i)) {
				continue;
			}
			G[i + N][i] = 0;
			auto X{maxFlowEdmondsKarp(G, S, T)};
			if (X.first == Y.first - 1) {
				// swap(G, X.second);
				Y.first--;
				W.insert(i);
				cout << i + 1 << (Y.first > 0 ? ' ' : '\n');
				break;
			}
			G[i + N][i] = 1;
		}
	}

	return 0;
}