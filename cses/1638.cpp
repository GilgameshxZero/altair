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

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL N;
	cin >> N;
	vector<string> G;
	G.push_back(string(N + 2, '*'));
	string S;
	RF(i, 0, N) {
		cin >> S;
		G.push_back('*' + S + '*');
	}
	G.push_back(string(N + 2, '*'));

	LL const M{1000000007};
	vector<vector<LL>> Z(N + 2, vector<LL>(N + 2, 0));
	Z[1][1] = G[1][1] == '*' ? 0 : 1;
	RF(i, 1, N + 1) {
		RF(j, 1, N + 1) {
			Z[i][j] = (Z[i][j] + Z[i - 1][j] + Z[i][j - 1]) % M;
			if (G[i][j] == '*') {
				Z[i][j] = 0;
			}
		}
	}
	cout << Z[N][N];

	return 0;
}
