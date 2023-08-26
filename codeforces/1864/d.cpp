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

array<array<int, 6000>, 6000> P[2];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL T;
	cin >> T;
	while (T--) {
		LL N;
		cin >> N;
		vector<string> G(N);
		RF(i, 0, N) {
			cin >> G[i];
		}
		RF(i, 0, 2) {
			RF(j, 0, 2 * N) {
				fill(P[i][j].begin(), P[i][j].begin() + 2 * N, 0);
			}
		}
		LL Z{0};
		RF(i, 0, N) {
			RF(j, 0, N) {
				LL r{i - j + N}, c{i + j + 1};
				RF(k, 0, 2) {
					P[k][r][c] = (i >= 1 && j < N - 1 ? P[k][r - 2][c] : 0) +
						(i >= 1 && j >= 1 ? P[k][r][c - 2] : 0) -
						(i >= 2 && j >= 1 && j < N - 1 ? P[k][r - 2][c - 2] : 0);
				}
				LL x{
					G[i][j] - '0' + P[(i + j) % 2][r][c] +
					(i > 0 ? P[(i + j + 1) % 2][(i - 1) - j + N][(i - 1) + j + 1] : 0LL)};
				if (x % 2 == 1) {
					P[(i + j) % 2][r][c]++;
					Z++;
				}
			}
		}
		cout << Z << '\n';
	}

	return 0;
}
