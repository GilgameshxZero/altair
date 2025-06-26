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

	array<vector<pair<LL, LL>>, 16> Z;
	Z[0].push_back({0, 2});
	RF(i, 1, 16) {
		array<LL, 3> M;
		M[0] = 0;
		M[1] = 2;
		M[2] = 1;
		RF(j, 0, Z[i - 1].size()) {
			Z[i].push_back({M[Z[i - 1][j].first], M[Z[i - 1][j].second]});
		}
		Z[i].push_back({0, 2});
		M[0] = 1;
		M[1] = 0;
		M[2] = 2;
		RF(j, 0, Z[i - 1].size()) {
			Z[i].push_back({M[Z[i - 1][j].first], M[Z[i - 1][j].second]});
		}
	}

	LL N;
	cin >> N;
	cout << Z[N - 1].size() << '\n';
	RF(i, 0, Z[N - 1].size()) {
		cout << Z[N - 1][i].first + 1 << ' ' << Z[N - 1][i].second + 1 << '\n';
	}

	return 0;
}
