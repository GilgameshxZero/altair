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

bitset<250000> G;
array<LL, 250000> Z, D;
array<pair<pair<short, short>, int> *, 250000> C;
array<array<LL, 500>, 500> Y;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL T;
	cin >> T;
	while (T--) {
		LL N, M;
		cin >> N >> M;
		bool TP{N > M};
		RF(i, 0, N) {
			string s;
			cin >> s;
			RF(j, 0, M) {
				G[TP ? i + j * N : j + i * M] = s[j] == '1';
			}
		}
		if (TP) {
			swap(N, M);
		}

		RF(i, 0, M) {
			D[i] = 0;
		}
		RF(i, 0, N) {
			RF(j, i + 1, N) {
				RF(k, 0, M) {
					if (!G[i * M + k] || !G[j * M + k]) {
						continue;
					}
					RF(l, k + 1, M) {
						if (G[i * M + l] && G[j * M + l]) {
							RF(m, k, l + 1) {
								D[m]++;
							}
							k = l - 1;
							break;
						}
					}
				}
			}
		}
		RF(i, 0, M) {
			C[i] = new pair<pair<short, short>, int>[D[i]];
			D[i] = 0;
		}
		RF(i, 0, N) {
			RF(j, i + 1, N) {
				RF(k, 0, M) {
					if (!G[i * M + k] || !G[j * M + k]) {
						continue;
					}
					RF(l, k + 1, M) {
						if (G[i * M + l] && G[j * M + l]) {
							RF(m, k, l + 1) {
								C[m][D[m]++] = {{i, j}, (int)(l - k + 1) * (int)(j - i + 1)};
							}
							k = l - 1;
							break;
						}
					}
				}
			}
		}

		RF(i, 0, M) {
			RF(j, 0, N) {
				RF(k, 0, N) {
					Y[j][k] = LLONG_MAX;
				}
			}
			RF(k, 0, D[i]) {
				auto &j = C[i][k];
				Y[j.first.first][j.first.second] =
					min(Y[j.first.first][j.first.second], (LL)j.second);
			}
			delete C[i];
			RF(j, N, 0) {
				RF(k, 0, N + 1 - j) {
					if (k > 0) {
						Y[k][k + j - 1] = min(Y[k][k + j - 1], Y[k - 1][k + j - 1]);
					}
					if (k + j < N) {
						Y[k][k + j - 1] = min(Y[k][k + j - 1], Y[k][k + j]);
					}
				}
			}
			RF(j, 0, N) {
				Z[j * M + i] = (Y[j][j] == LLONG_MAX ? 0 : Y[j][j]);
			}
		}

		if (TP) {
			RF(i, 0, M) {
				RF(j, 0, N) {
					cout << Z[j * M + i] << ' ';
				}
				cout << '\n';
			}
		} else {
			RF(i, 0, N) {
				RF(j, 0, M) {
					cout << Z[i * M + j] << ' ';
				}
				cout << '\n';
			}
		}
	}

	return 0;
}
