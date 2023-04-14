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

	LL N, M;
	cin >> N >> M;

	vector<vector<LL>> E(N), EE(N);
	RF(i, 0, M) {
		LL U, V;
		cin >> U >> V;
		if (U == N) {
			continue;
		}
		E[U - 1].push_back(V - 1);
		EE[V - 1].push_back(U - 1);
	}

	vector<LL> D(N, LLONG_MAX / 2);
	D.back() = 0;
	priority_queue<pair<LL, LL>> PQ;
	vector<bool> V(N);
	PQ.push({0, N - 1});
	while (!PQ.empty()) {
		auto cur{PQ.top().second};
		PQ.pop();
		if (V[cur]) {
			continue;
		}
		V[cur] = true;

		for (auto &i : EE[cur]) {
			if (!V[i] && D[cur] + 1 < D[i]) {
				D[i] = D[cur] + 1;
				PQ.push({-D[i], i});
			}
		}
	}

	while (!PQ.empty()) {
		PQ.pop();
	}
	vector<LL> od(N);
	queue<LL> Q;
	RF(i, 0, N) {
		od[i] = E[i].size();
		if (od[i] == 0) {
			Q.push(i);
		} else {
			PQ.push({-D[i], i});
		}
	}

	vector<LL> C(N, LLONG_MAX / 2);
	fill(V.begin(), V.end(), false);
	while (!(Q.empty() && PQ.empty())) {
		if (Q.empty()) {
			LL cur;
			while (!PQ.empty()) {
				cur = PQ.top().second;
				PQ.pop();
				if (!V[cur]) {
					break;
				}
			}
			if (V[cur]) {
				break;
			}
			Q.push(cur);
		}
		LL cur{Q.front()};
		Q.pop();
		V[cur] = true;

		vector<LL> CB;
		for (auto &i : E[cur]) {
			CB.push_back(C[i]);
		}
		sort(CB.begin(), CB.end());
		LL vmin{LLONG_MAX / 2};
		RF(i, 0, CB.size()) {
			CB[i] += CB.size() - 1 - i;
			vmin = min(vmin, CB[i]);
		}
		vmin++;
		C[cur] = cur == N - 1 ? 0LL : vmin;

		for (auto &i : EE[cur]) {
			od[i]--;
			if (od[i] == 0) {
				Q.push(i);
			}
		}
	}

	cout << C[0];
	return 0;
}
