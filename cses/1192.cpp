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

void flood(vector<string> &G, LL I, LL J) {
	array<pair<LL, LL>, 4> D{{{0, 1}, {1, 0}, {0, -1}, {-1, 0}}};
	G[I][J] = 'V';
	RF(i, 0, D.size()) {
		if (G[I + D[i].first][J + D[i].second] == '.') {
			flood(G, I + D[i].first, J + D[i].second);
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL N, M;
	cin >> N >> M;
	vector<string> G(N + 2);
	G[0] = string(M + 2, '#');
	RF(i, 1, N + 1) {
		cin >> G[i];
		G[i] = '#' + G[i] + '#';
	}
	G.back() = string(M + 2, '#');

	LL Z{0};
	RF(i, 1, N + 1) {
		RF(j, 1, M + 1) {
			if (G[i][j] == '.') {
				Z++;
				flood(G, i, j);
			}
		}
	}
	cout << Z;

	return 0;
}
