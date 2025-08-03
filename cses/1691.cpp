#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC target("avx", "avx2", "fma", "bmi", "bmi2", "popcnt", "lzcnt")
#pragma GCC optimize("Ofast", "unroll-loops")
#endif

#include <bits/stdc++.h>

namespace Rain::Algorithm {
	// Constructs an Eulerian cycle/circuit with Hierholzer's in O(E). The
	// provided graph must be unweighted, undirected, simple, and all edges must
	// be connected.
	//
	// Returns a list of points on the cycle. If the cycle is not constructable,
	// returns an empty list.
	std::vector<std::size_t> eulerCycleHeirholzer(
		std::vector<std::unordered_set<std::size_t>> const &edges) {
		std::size_t target{0};
		for (auto const &i : edges) {
			if (i.size() % 2 != 0) {
				return {};
			}
			target += i.size();
		}
		if (target == 0) {
			return {};
		}

		std::deque<std::size_t> cycle;
		std::size_t current;

		// Verify the connectivity of all edges via BFS.
		std::queue<std::size_t> queue;
		std::vector<bool> visited(edges.size(), false);
		std::size_t total{0};
		queue.push(0);
		while (edges[queue.front()].empty()) {
			queue.front()++;
		}
		cycle.push_back(queue.front());
		while (!queue.empty()) {
			current = queue.front();
			queue.pop();
			if (visited[current]) {
				continue;
			}
			visited[current] = true;
			total += edges[current].size();
			for (auto const &i : edges[current]) {
				queue.push(i);
			}
		}
		if (total != target) {
			return {};
		}
		target /= 2;

		auto residual{edges};
		while (cycle.size() < target) {
			while (residual[cycle.back()].empty()) {
				cycle.push_front(cycle.back());
				cycle.pop_back();
			}
			do {
				current = *residual[cycle.back()].begin();
				residual[cycle.back()].erase(current);
				residual[current].erase(cycle.back());
				cycle.push_back(current);
			} while (!residual[cycle.back()].empty());
			if (cycle.front() == cycle.back()) {
				cycle.pop_back();
			}
		}

		return {cycle.begin(), cycle.end()};
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
	vector<unordered_set<size_t>> E(N);
	RF(i, 0, M) {
		LL A, B;
		cin >> A >> B;
		A--;
		B--;
		E[A].insert(B);
		E[B].insert(A);
	}

	auto T{eulerCycleHeirholzer(E)};
	if (T.empty()) {
		cout << "IMPOSSIBLE";
		return 0;
	}
	LL start{0};
	for (; start < T.size(); start++) {
		if (T[start] == 0) {
			break;
		}
	}
	if (start == T.size()) {
		cout << "IMPOSSIBLE";
		return 0;
	}
	RF(i, 0, T.size()) {
		cout << T[(start + i) % T.size()] + 1 << ' ';
	}
	cout << T[start] + 1;

	return 0;
}
