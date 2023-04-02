#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC target("avx2", "bmi", "bmi2", "popcnt", "lzcnt")
#pragma GCC optimize("Ofast", "unroll-loops")
#endif

#include <bits/stdc++.h>

using LL = long long;
using LD = long double;
using namespace std;

#define RF(x, from, to) \
	for (LL x(from), _to(to), _delta{x < _to ? 1LL : -1LL}; x != _to; x += _delta)

int main(int, char const *[]) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL N, M, S, T;
	cin >> N >> M >> S >> T;

	vector<vector<LL>> E(N);
	RF(i, 0, M) {
		LL U, V;
		cin >> U >> V;
		E[U].push_back(V);
		E[V].push_back(U);
	}

	priority_queue<pair<LL, LL>> pq;
	vector<bool> vis(N, false);
	vector<LL> dist(N, LLONG_MAX / 2);
	pq.push({0, S});
	dist[S] = 0;
	while (!pq.empty()) {
		LL cur{pq.top().second};
		pq.pop();
		if (vis[cur]) {
			continue;
		}
		vis[cur] = true;
		RF(i, 0, E[cur].size()) {
			if (vis[E[cur][i]]) {
				continue;
			}
			dist[E[cur][i]] = min(dist[E[cur][i]], dist[cur] + 1);
			pq.push({-dist[E[cur][i]], E[cur][i]});
		}
	}

	cout << (dist[T] + 1) / 2;
	return 0;
}
