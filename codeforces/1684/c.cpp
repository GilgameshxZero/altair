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
		array<LL, 2> Y;
		Y[0] = Y[1] = -1;
		vector<vector<LL>> X(N, vector<LL>(M));
		bool fail{false};
		RF(i, 0, N) {
			RF(j, 0, M) {
				cin >> X[i][j];
			}
			RF(j, 1, M) {
				if (X[i][j] < X[i][j - 1]) {
					if (Y[0] == -1) {
						RF(k, j - 1, -1) {
							if (X[i][k] >= X[i][j - 1]) {
								Y[0] = k;
							}
						}
						RF(k, j, M) {
							if (X[i][k] <= X[i][j]) {
								Y[1] = k;
							}
						}
					}
				}
			}
		}
		if (Y[0] != -1) {
			RF(i, 0, N) {
				swap(X[i][Y[0]], X[i][Y[1]]);
				RF(j, 1, M) {
					if (X[i][j] < X[i][j - 1]) {
						fail = true;
						break;
					}
				}
				if (fail) {
					break;
				}
			}
		}
		if (fail) {
			cout << "-1\n";
		} else {
			if (Y[0] == -1) {
				Y[0]++;
				Y[1]++;
			}
			cout << Y[0] + 1 << ' ' << Y[1] + 1 << '\n';
		}
	}

	return 0;
}
