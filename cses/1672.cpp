#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC target("avx", "avx2", "fma", "bmi", "bmi2", "popcnt", "lzcnt")
#pragma GCC optimize("Ofast", "unroll-loops")
#endif

#include <bits/stdc++.h>

namespace Rain::Algorithm {
	// Computes APSP on directed weighted graph in $O(N^3)$. The provided graph
	// must be simple.
	//
	// Returns a matrix A, where A[i][j] is the shortest distance from node `i` to
	// node `j`.
	template <typename IndexType, typename WeightType>
	std::vector<std::vector<WeightType>> apspFloydWarshall(
		std::vector<std::unordered_map<IndexType, WeightType>> const &edges) {
		std::vector<std::vector<WeightType>> distances(edges.size(),
			std::vector<WeightType>(
				edges.size(), std::numeric_limits<WeightType>::max()));

		for (std::size_t i{0}; i < edges.size(); i++) {
			for (auto const &j : edges[i]) {
				distances[i][j.first] = j.second;
			}
			distances[i][i] = 0;
		}

		for (std::size_t k{0}; k < edges.size(); k++) {
			for (std::size_t i{0}; i < edges.size(); i++) {
				for (std::size_t j{0}; j < edges.size(); j++) {
					if (distances[i][k] == std::numeric_limits<WeightType>::max() ||
						distances[k][j] == std::numeric_limits<WeightType>::max()) {
						continue;
					}
					distances[i][j] =
						std::min(distances[i][j], distances[i][k] + distances[k][j]);
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

	LL N, M, Q;
	cin >> N >> M >> Q;

	vector<unordered_map<LL, LL>> E(N);
	RF(i, 0, M) {
		LL A, B, C;
		cin >> A >> B >> C;
		A--;
		B--;
		if (E[A].count(B)) {
			E[A][B] = min(E[A][B], C);
		} else {
			E[A][B] = C;
		}
		if (E[B].count(A)) {
			E[B][A] = min(E[B][A], C);
		} else {
			E[B][A] = C;
		}
	}

	auto D{apspFloydWarshall(E)};
	RF(i, 0, Q) {
		LL A, B;
		cin >> A >> B;
		A--;
		B--;
		cout << (D[A][B] == LLONG_MAX ? -1 : D[A][B]) << '\n';
	}

	return 0;
}
