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
		vector<vector<LL>> H(N, vector<LL>(N));
		vector<LL> A(N), B(N);
		RF(i, 0, N) {
			RF(j, 0, N) {
				cin >> H[i][j];
			}
		}
		RF(i, 0, N) {
			cin >> A[i];
		}
		RF(i, 0, N) {
			cin >> B[i];
		}

		LL const INF{LLONG_MAX / 10000};
		LL Z{0};
		RF(z, 0, 2) {
			vector<array<bool, 3>> R(N);
			RF(i, 0, N - 1) {
				R[i].fill(false);
				RF(j, 0, N) {
					if (H[i][j] == H[i + 1][j] - 1) {
						R[i][0] = true;
					}
					if (H[i][j] == H[i + 1][j]) {
						R[i][1] = true;
					}
					if (H[i][j] == H[i + 1][j] + 1) {
						R[i][2] = true;
					}
				}
			}

			vector<LL> C;
			C.push_back(-1);
			for (LL i{0}; i < N; i++) {
				LL j;
				for (j = i; j < N && R[j][1]; j++);
				C.push_back(j);
				i = j;
			}

			vector<array<LL, 2>> X(C.size());
			X[0][0] = 0;
			X[0][1] = INF;
			RF(i, 1, C.size()) {
				X[i].fill(0);
				RF(k, C[i] - 1, C[i] + 1) {
					LL Y{0};
					array<bool, 2> fp;
					fp.fill(false);
					for (LL l{k}; l > C[i - 1]; l -= 2) {
						if (l != C[i] && R[l][0]) {
							fp.fill(true);
							break;
						}
						if (l > 0 && l != C[i - 1] + 1 && R[l - 1][2]) {
							fp.fill(true);
							break;
						}
						if (l > 0 && l == C[i - 1] + 1 && R[l - 1][2]) {
							fp[0] = true;
						}
						if (l > 1 && l == C[i - 1] + 2 && R[l - 2][0]) {
							fp[1] = true;
						}
						X[i][k - (C[i] - 1)] += A[l];
					}
					if (fp[1] && fp[0]) {
						X[i][k - (C[i] - 1)] = INF;
					} else if (fp[1]) {
						X[i][k - (C[i] - 1)] += X[i - 1][0];
					} else if (fp[0]) {
						X[i][k - (C[i] - 1)] += X[i - 1][1];
					} else {
						X[i][k - (C[i] - 1)] += min(X[i - 1][0], X[i - 1][1]);
					}
				}
			}

			Z += min(X.back()[0], X.back()[1]);

			swap(A, B);
			RF(i, 0, N) {
				RF(j, i + 1, N) {
					swap(H[i][j], H[j][i]);
				}
			}
		}
		cout << (Z >= INF ? -1 : Z) << '\n';
	}

	return 0;
}
