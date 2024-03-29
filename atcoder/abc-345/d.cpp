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

	LL N, H, W;
	cin >> N >> H >> W;
	vector<pair<LL, LL>> A(N);
	RF(i, 0, N) {
		cin >> A[i].first >> A[i].second;
	}
	vector<LL> P(N);
	RF(i, 0, N) {
		P[i] = i;
	}
	vector<vector<LL>> G(H, vector<LL>(W, 0));
	RF(i, 0, 1LL << N) {
		RF(j, 0, N) {
			if ((i >> j) & 1) {
				swap(A[j].first, A[j].second);
			}
		}
		do {
			RF(j, 0, H) {
				RF(k, 0, W) {
					G[j][k] = -1;
				}
			}
			LL r{0}, c{0};
			bool fail{false};
			RF(j, 0, N) {
				RF(k, 0, A[P[j]].first) {
					RF(l, 0, A[P[j]].second) {
						if (r + k >= H || c + l >= W || G[r + k][c + l] != -1) {
							fail = true;
							break;
						}
						G[r + k][c + l] = P[j];
					}
					if (fail) {
						break;
					}
				}
				if (fail) {
					break;
				}
				for (; r < H; r++) {
					for (; c < W; c++) {
						if (G[r][c] == -1) {
							break;
						}
					}
					if (c < W) {
						break;
					}
					c = 0;
				}
				if (r >= H) {
					cout << "Yes";
					return 0;
				}
			}
			for (; r < H; r++) {
				for (; c < W; c++) {
					if (G[r][c] == -1) {
						break;
					}
				}
			}
			if (fail) {
				continue;
			}
		} while (next_permutation(P.begin(), P.end()));
		RF(j, 0, N) {
			if ((i >> j) & 1) {
				swap(A[j].first, A[j].second);
			}
		}
	}
	cout << "No";
	return 0;
}
