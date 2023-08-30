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
		LL N, M;
		cin >> N >> M;
		vector<string> G(N);
		RF(i, 0, N) {
			cin >> G[i];
		}
		bool fail{false};
		RF(i, 0, N) {
			LL free{0};
			RF(j, 0, M) {
				if (G[i][j] == 'U' || G[i][j] == 'D') {
					G[i][j] = free % 2 ? 'B' : 'W';
					G[i + 1][j] = 'W' - G[i][j] + 'B';
					free++;
				}
			}
			if (free % 2 != 0) {
				fail = true;
				break;
			}
		}
		if (fail) {
			cout << "-1\n";
			continue;
		}
		RF(j, 0, M) {
			LL free{0};
			RF(i, 0, N) {
				if (G[i][j] == 'L' || G[i][j] == 'R') {
					G[i][j] = free % 2 ? 'B' : 'W';
					G[i][j + 1] = 'W' - G[i][j] + 'B';
					free++;
				}
			}
			if (free % 2 != 0) {
				fail = true;
				break;
			}
		}
		if (fail) {
			cout << "-1\n";
			continue;
		}
		RF(i, 0, N) {
			cout << G[i] << '\n';
		}
	}

	return 0;
}
