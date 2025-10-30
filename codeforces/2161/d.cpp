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

	LL T;
	cin >> T;
	while (T--) {
		LL N;
		cin >> N;
		vector<vector<LL>> P(N + 1);
		RF(i, 1, N + 1) {
			P[i].push_back(0);
		}
		RF(i, 0, N) {
			LL x;
			cin >> x;
			P[x].push_back(i + 1);
			if (P[x].size() == 2) {
				P[x][0] = P[x][1] - 1;
			}
		}

		vector<vector<LL>> Y(N + 1), Z(N + 1);
		Y[N].push_back(0);
		RF(i, 1, P[N].size()) {
			Y[N].push_back(1 + Y[N].back());
		}
		Z[N] = vector<LL>(P[N].size(), 0);
		RF(i, N - 1, 0) {
			Y[i].resize(P[i].size());
			RF(j, 0, Y[i].size()) {
				auto ui{
					upper_bound(P[i + 1].begin() + 1, P[i + 1].end(), P[i][j]) -
					P[i + 1].begin()};
				Y[i][j] = j + (P[i + 1].size() - ui) + Z[i + 1][ui - 1];
			}
			Z[i] = Y[i];
			Z[i][0] = min(
				Z[i][0], (LL)(P[i + 1].size() - 1) + (i + 2 < N ? Z[i + 2].back() : 0));
			RF(j, 1, Z[i].size()) {
				Z[i][j] = min(Z[i][j], Z[i][j - 1]);
			}
		}
		cout << min(Z[1].back(), (LL)P[1].size() + (N >= 2 ? Z[2].back() : 0))
				 << '\n';
	}

	return 0;
}
