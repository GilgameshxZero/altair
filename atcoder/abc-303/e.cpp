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

vector<LL> S;
vector<vector<LL>> E;

void dfs(LL X, LL P) {
	S[X] = 2;
	RF(i, 0, E[X].size()) {
		if (E[X][i] == P) {
			continue;
		}
		dfs(E[X][i], X);
		if (S[E[X][i]] == -1) {
			S[X] = 1;
		} else if (S[E[X][i]] == 1) {
			S[X] = 2;
		} else {
			S[X] = -1;
		}
	}
}

int main(int, char const *[]) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL N;
	cin >> N;
	S.resize(N);
	E.resize(N);
	RF(i, 0, N - 1) {
		LL U, V;
		cin >> U >> V;
		E[U - 1].push_back(V - 1);
		E[V - 1].push_back(U - 1);
	}
	dfs(0, -1);

	vector<LL> Z;
	RF(i, 0, N) {
		if (S[i] == -1) {
			Z.push_back(E[i].size());
		}
	}
	sort(Z.begin(), Z.end());
	RF(i, 0, Z.size()) {
		cout << Z[i] << ' ';
	}
	return 0;
}
