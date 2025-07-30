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

array<string, 3000> G;
array<array<int, 3000>, 3000> R;
array<array<bool, 3000>, 3000> Z;
array<vector<pair<int, int>>, 26> S;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL N;
	cin >> N;
	RF(i, 0, N) {
		cin >> G[i];
	}

	R.back().back() = 0;
	RF(i, 2 * N - 3, -1) {
		RF(j, i, -1) {
			if (j >= N || i - j >= N) {
				continue;
			}
			if (i - j + 1 >= N) {
				Z[i - j][j] = true;
			} else if (j + 1 >= N) {
				Z[i - j][j] = false;
			} else {
				Z[i - j][j] = R[i - j + 1][j] > R[i - j][j + 1];
			}
			S[G[i - j][j] - 'A'].push_back(
				{Z[i - j][j] ? R[i - j][j + 1] : R[i - j + 1][j], j});
		}
		int r{0}, p{-1};
		RF(j, 0, 26) {
			if (!S[j].empty()) {
				sort(S[j].begin(), S[j].end());
				RF(k, 0, S[j].size()) {
					R[i - S[j][k].second][S[j][k].second] = r;
					if (S[j][k].second != p) {
						p = S[j][k].second;
						r++;
					}
				}
				p = -1;
				S[j].clear();
			}
		}
	}

	pair<LL, LL> C{0, 0};
	while (C.first != N - 1 || C.second != N - 1) {
		cout << G[C.first][C.second];
		if (Z[C.first][C.second]) {
			C.second++;
		} else {
			C.first++;
		}
	}
	cout << G[N - 1][N - 1];

	return 0;
}
