#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC target("avx", "avx2", "fma", "bmi", "bmi2", "popcnt", "lzcnt")
#pragma GCC optimize("Ofast", "unroll-loops")
#endif

#include <bits/stdc++.h>

using LL = long long;
using LD = long double;
using namespace std;

#define RF(x, from, to) \
	for (LL x(from), _to(to), _delta{x < _to ? 1LL : -1LL}; x != _to; x += _delta)

void solve(vector<vector<LL>> &E,
	vector<LL> &cycle,
	vector<LL> &P,
	vector<bool> &V,
	LL cur) {
	V[cur] = true;
	RF(i, 0, E[cur].size()) {
		if (!cycle.empty()) {
			break;
		}
		if (P[E[cur][i]] != -1) {
			LL target{E[cur][i]};
			while (cur != target) {
				cycle.push_back(cur);
				cur = P[cur];
			}
			cycle.push_back(cur);
			reverse(cycle.begin(), cycle.end());
			break;
		}
		if (V[E[cur][i]]) {
			continue;
		}
		P[E[cur][i]] = cur;
		solve(E, cycle, P, V, E[cur][i]);
		P[E[cur][i]] = -1;
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL N, M;
	cin >> N >> M;
	vector<vector<LL>> E(N);
	RF(i, 0, M) {
		LL X, Y;
		cin >> X >> Y;
		E[X - 1].push_back(Y - 1);
	}

	vector<LL> cycle, P(N, -1);
	vector<bool> V(N, false);
	RF(i, 0, N) {
		if (V[i]) {
			continue;
		}
		P[i] = -2;
		solve(E, cycle, P, V, i);
		P[i] = -1;
	}

	if (cycle.empty()) {
		cout << "IMPOSSIBLE";
	} else {
		cycle.push_back(cycle[0]);
		cout << cycle.size() << '\n';
		RF(i, 0, cycle.size()) {
			cout << cycle[i] + 1 << ' ';
		}
	}

	return 0;
}
