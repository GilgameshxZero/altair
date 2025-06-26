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

	pair<LL, LL> Y[]{
		{-2, 1}, {-1, 2}, {1, 2}, {2, 1}, {2, -1}, {1, -2}, {-1, -2}, {-2, -1}};

	LL N;
	cin >> N;

	vector<vector<LL>> Z(N, vector<LL>(N, LLONG_MAX));
	Z[0][0] = 0;
	queue<pair<LL, LL>> Q;
	Q.push({0, 0});
	while (!Q.empty()) {
		auto [R, C] = Q.front();
		Q.pop();
		RF(i, 0, 8) {
			LL r{R + Y[i].first}, c{C + Y[i].second};
			if (r < 0 || c < 0 || r >= N || c >= N) {
				continue;
			}
			if (Z[r][c] == LLONG_MAX) {
				Z[r][c] = Z[R][C] + 1;
				Q.push({r, c});
			}
		}
	}

	RF(i, 0, N) {
		RF(j, 0, N) {
			cout << Z[i][j] << ' ';
		}
		cout << '\n';
	}

	return 0;
}
