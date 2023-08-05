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

bitset<10000> P;

void dfs(vector<vector<LL>> &E, vector<LL> &S, LL &Z, LL x, LL par) {
	S[x] = 1;
	for (auto &i : E[x]) {
		if (i == par) {
			continue;
		}
		dfs(E, S, Z, i, x);
		S[x] += S[i];
	}
	P.reset();
	P[0] = true;
	for (auto &i : E[x]) {
		if (i == par) {
			continue;
		}
		RF(j, S[x] / 2, -1) {
			P[j + S[i]] = P[j + S[i]] | P[j];
		}
	}
	LL Y{0};
	RF(j, 0, S[x] / 2 + 1) {
		if (P[j]) {
			Y = max(Y, j * (S[x] - 1 - j));
		}
	}
	Z += Y;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL N;
	cin >> N;
	vector<LL> P(N), S(N);
	vector<vector<LL>> E(N);
	P[0] = -1;
	RF(i, 1, N) {
		cin >> P[i];
		P[i]--;
		E[i].push_back(P[i]);
		E[P[i]].push_back(i);
	}
	LL Z{0};
	dfs(E, S, Z, 0, -1);
	cout << Z << '\n';

	return 0;
}
