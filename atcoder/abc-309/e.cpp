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

LL N, M, Z;
vector<LL> P;
vector<vector<LL>> E;
vector<LL> I;
multiset<LL> J;

void dfs(LL x, LL d) {
	J.insert(I[x] + d);
	Z += *J.rbegin() >= d;
	RF(i, 0, E[x].size()) {
		dfs(E[x][i], d + 1);
	}
	J.erase(J.find(I[x] + d));
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> N >> M;
	P.resize(N);
	E.resize(N);
	I.resize(N, -1);
	RF(i, 1, N) {
		cin >> P[i];
		P[i]--;
		E[P[i]].push_back(i);
	}
	RF(i, 0, M) {
		LL x, y;
		cin >> x >> y;
		x--;
		I[x] = max(I[x], y);
	}

	dfs(0, 0);
	cout << Z;

	return 0;
}
