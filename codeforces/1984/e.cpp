#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC target( \
	"avx", "avx2", "fma", "bmi", "bmi2", "popcnt", "lzcnt")
#pragma GCC optimize("Ofast", "unroll-loops")
#endif

#include <bits/stdc++.h>

using LL = long long;
using LD = long double;
using namespace std;

#define RF(x, f, t)                                      \
	for (LL x(f), _t(t), _d{x < _t ? 1LL : -1LL}; x != _t; \
			 x += _d)

void dfsSelect(
	vector<vector<LL>> &E,
	vector<array<array<LL, 2>, 2>> &minSelect,
	LL u,
	LL p) {
	if (E[u].size() == 1 && p != -1) {
		minSelect[u][0][0] = 0;
		minSelect[u][0][1] = 999999;
		minSelect[u][1][0] = 999999;
		minSelect[u][1][1] = 1;
		return;
	}

	bool ms01Done{false}, ms11Done{false};
	LL ms01ExchangeDelta{999999},
		ms11ExchangeDelta{999999};
	minSelect[u][0][0] = minSelect[u][0][1] =
		minSelect[u][1][0] = minSelect[u][1][1] = 0;
	for (LL v : E[u]) {
		if (v == p) {
			continue;
		}
		dfsSelect(E, minSelect, v, u);
		minSelect[u][0][0] += minSelect[v][1][0];
		if (minSelect[v][1][0] < minSelect[v][1][1]) {
			minSelect[u][0][1] += minSelect[v][1][0];
			ms01ExchangeDelta = min(
				ms01ExchangeDelta,
				minSelect[v][1][1] - minSelect[v][1][0]);
		} else {
			minSelect[u][0][1] += minSelect[v][1][1];
			ms01Done = true;
		}
		minSelect[u][1][0] +=
			min(minSelect[v][0][0], minSelect[v][1][0]);
		if (
			min(minSelect[v][0][0], minSelect[v][1][0]) <
			min(minSelect[v][0][1], minSelect[v][1][1])) {
			minSelect[u][1][1] +=
				min(minSelect[v][0][0], minSelect[v][1][0]);
			ms11ExchangeDelta = min(
				ms11ExchangeDelta,
				min(minSelect[v][0][1], minSelect[v][1][1]) -
					min(minSelect[v][0][0], minSelect[v][1][0]));
		} else {
			minSelect[u][1][1] +=
				min(minSelect[v][0][1], minSelect[v][1][1]);
			ms11Done = true;
		}
	}
	if (!ms01Done) {
		minSelect[u][0][1] += ms01ExchangeDelta;
	}
	minSelect[u][1][0]++;
	if (!ms11Done) {
		minSelect[u][1][1] += ms11ExchangeDelta;
	}
	minSelect[u][1][1]++;

	if (E[u].size() == 1) {
		minSelect[u][1][0] = minSelect[u][1][1] =
			min(minSelect[u][1][0], minSelect[u][1][1]);
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL T;
	cin >> T;
	while (T--) {
		LL N;
		cin >> N;
		vector<vector<LL>> E(N);
		RF(i, 0, N - 1) {
			LL u, v;
			cin >> u >> v;
			u--;
			v--;
			E[u].push_back(v);
			E[v].push_back(u);
		}

		vector<array<array<LL, 2>, 2>> minSelect(N);
		dfsSelect(E, minSelect, 0, -1);
		cout << N -
				min(
							{minSelect[0][0][0],
							 minSelect[0][0][1] - 1,
							 minSelect[0][1][0],
							 minSelect[0][1][1] - 1})
				 << '\n';
	}

	return 0;
}
