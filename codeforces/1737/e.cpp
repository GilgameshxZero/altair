#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC target("avx2", "bmi", "bmi2", "popcnt", "lzcnt")
#pragma GCC optimize("Ofast", "unroll-loops")
#endif

#include <bits/stdc++.h>

using LL = long long;
using LD = long double;
using namespace std;

#define RF(x, from, to) \
	for (LL x(from), _to(to), _delta{x < _to ? 1LL : -1LL}; x != _to; x += _delta)

int main(int, char const *[]) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	// cout << setprecision(10);
	RF(N, 4, 16) {
		vector<LL> S(N), P(N), M(2 * N), W(N);
		vector<bool> D(N);

		RF(i, 0, (1LL << N)) {
			LL kill{0};
			RF(j, 0, N) {
				S[j] = 1;
				D[j] = (i >> j) & 1;
				M[2 * j] = j;
				M[2 * j + 1] = -1;
				P[j] = 2 * j;
			}

			while (true) {
				RF(j, 0, N) {
					if (P[j] == -1) {
						continue;
					}
					if (P[j] == 0) {
						D[j] = true;
					}
					if (P[j] == 2 * (N - 1)) {
						D[j] = false;
					}
					M[P[j]] = -1;
					P[j] += 2 * D[j] - 1;
					if (M[P[j]] != -1) {
						if (S[j] > S[M[P[j]]] || S[j] == S[M[P[j]]] && D[j] == false) {
							S[j] += S[M[P[j]]];
							P[M[P[j]]] = -1;
							M[P[j]] = j;
						} else {
							S[M[P[j]]] += S[j];
							P[j] = -1;
						}
						kill++;
					} else {
						M[P[j]] = j;
					}
				}

				if (kill == N - 1) {
					RF(j, 0, N) {
						if (P[j] == -1) {
							continue;
						}
						W[j]++;
					}
					break;
				}
			}
		}

		cout << N << ": ";
		RF(i, 0, N) {
			cout << W[i] << ' ';
		}
		cout << '\n';

		LL acc{0};
		cout << N << ": ";
		vector<LL> Z;
		RF(i, N - 1, -1) {
			LL C{(i + 1) / 2 + 1 + (N - 1 - i)}, X{(1LL << C) - acc};
			acc += X;
			Z.push_back(X);
		}
		reverse(Z.begin(), Z.end());
		RF(i, 0, N) {
			cout << Z[i] << ' ';
		}
		cout << '\n';
	}

	// return 0;

	// LL T;
	// cin >> T;
	// while (T--) {
	// }

	return 0;
}
