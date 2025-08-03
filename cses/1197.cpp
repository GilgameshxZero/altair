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
	// distance is INF. If there exists any negative-weight cycle reachable from a
	// source, each negative-weight cycle will contain at least one vertex with
	// distance -INF.
	template <typename WeightType>
	std::pair<std::vector<WeightType>, std::vector<std::size_t>> ssspSpfa(
		std::vector<std::unordered_map<std::size_t, WeightType>> const &edges,
		std::vector<std::size_t> const &sources) {
		std::vector<WeightType> distances(
			edges.size(), std::numeric_limits<WeightType>::max());
		std::vector<std::size_t> predecessors(
			edges.size(), std::numeric_limits<std::size_t>::max());
		std::queue<std::pair<std::size_t, std::size_t>> queue;
		std::vector<std::size_t> enqueues(edges.size(), 0);
		for (auto const &i : sources) {
			distances[i] = 0;
			enqueues[i]++;
			queue.push({i, 0});
		}
		while (!queue.empty()) {
			auto [i, j]{queue.front()};
			queue.pop();
			enqueues[i]--;
			if (enqueues[i] > 0) {
				continue;
			}
			if (j == edges.size()) {
				distances[i] = std::numeric_limits<WeightType>::min();
				continue;
			}
			for (auto const &k : edges[i]) {
				if (distances[i] + k.second < distances[k.first]) {
					distances[k.first] = distances[i] + k.second;
					predecessors[k.first] = i;
					enqueues[k.first]++;
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

	vector<unordered_map<size_t, LL>> E(N);
	RF(i, 0, M) {
		LL A, B, C;
		cin >> A >> B >> C;
		A--;
		B--;
		if (A == B) {
			if (C < 0) {
				cout << "YES\n" << A + 1 << ' ' << A + 1;
				return 0;
			}
		} else {
			if (E[A].count(B)) {
				E[A][B] = min(E[A][B], C);
			} else {
				E[A][B] = C;
			}
		}
	}

	vector<size_t> sources;
	RF(i, 0, N) {
		sources.push_back(i);
	}
	auto [D, P]{ssspSpfa(E, sources)};
	vector<LL> Z;
	RF(i, 0, N) {
		if (D[i] == LLONG_MIN) {
			vector<bool> V(N, false);
			while (!V[i]) {
				V[i] = true;
				Z.push_back(i);
				i = P[i];
			}
			reverse(Z.begin(), Z.end());
			while (Z.back() != i) {
				Z.pop_back();
			}
			Z.push_back(Z[0]);
			break;
		}
	}
	if (Z.empty()) {
		cout << "NO";
	} else {
		cout << "YES\n";
		RF(i, 0, Z.size()) {
			cout << Z[i] + 1 << ' ';
		}
	}

	return 0;
}
