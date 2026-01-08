#if defined(__GNUC__) && !defined(__clang__) && !defined(__MINGW32__)
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
		LL F{-1};
		vector<string> G(N);
		vector<LL> Z;
		RF(i, 0, N) {
			cin >> G[i];
			if (count(G[i].begin(), G[i].end(), 'H') == 0) {
				F = i;
			} else {
				RF(j, 0, N) {
					if (G[i][j] == 'H') {
						Z.push_back(j);
						break;
					}
				}
			}
		}
		if (F == -1) {
			cout << N << '\n';
			RF(i, 0, N) {
				cout << i + 1 << ' ' << Z[i] + 1 << '\n';
			}
		} else {
			cout << N << '\n';
			RF(i, 0, N) {
				cout << F + 1 << ' ' << i + 1 << '\n';
			}
		}
	}

	return 0;
}
