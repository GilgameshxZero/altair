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

	LL N, M;
	cin >> N >> M;

	vector<vector<LL>> A(N, vector<LL>(N));
	RF(i, 0, N) {
		RF(j, 0, N) {
			cin >> A[i][j];
		}
	}

	vector<LL> P(45);
	P[0] = 1;
	RF(i, 1, 45) {
		P[i] = P[i - 1] * 10 % M;
	}

	vector<vector<LL>> C(2 * N + 1);
	vector<vector<vector<LL>>> X(N, vector<vector<LL>>(N)), Y{X};
	X[0][0].push_back(A[0][0] * P[2 * N - 2] % M);
	Y[N - 1][N - 1].push_back(A[N - 1][N - 1] % M);
	RF(i, 1, N) {
		RF(j, max(0LL, i - N + 1), min(i + 1, N)) {
			if (j > 0) {
				RF(k, 0, X[j - 1][i - j].size()) {
					X[j][i - j].push_back(
						(X[j - 1][i - j][k] + A[j][i - j] * P[2 * N - 2 - i]) % M);
				}
			}
			if (i - j > 0) {
				RF(k, 0, X[j][i - j - 1].size()) {
					X[j][i - j].push_back(
						(X[j][i - j - 1][k] + A[j][i - j] * P[2 * N - 2 - i]) % M);
				}
			}
		}
	}
	RF(i, 2 * N - 3, N - 2) {
		RF(j, max(0LL, i - N + 1), min(i + 1, N)) {
			if (j < N - 1) {
				RF(k, 0, Y[j + 1][i - j].size()) {
					Y[j][i - j].push_back(
						(Y[j + 1][i - j][k] + A[j][i - j] * P[2 * N - 2 - i]) % M);
				}
			}
			if (i - j < N - 1) {
				RF(k, 0, Y[j][i - j + 1].size()) {
					Y[j][i - j].push_back(
						(Y[j][i - j + 1][k] + A[j][i - j] * P[2 * N - 2 - i]) % M);
				}
			}
		}
	}

	LL Z{0};
	RF(i, 0, N) {
		unordered_set<LL> S;
		for (auto &j : X[i][N - 1 - i]) {
			S.insert(j);
		}
		set<LL> T;
		for (auto &j : Y[i][N - 1 - i]) {
			T.insert(j);
		}
		LL U{A[i][N - 1 - i] * P[N - 1] % M};
		for(auto &j : S) {
			auto k{T.upper_bound((M + M - 1 + U - j) % M)};
			if (k == T.begin()) {
				k = T.end();
			}
			k--;
			Z = max(Z, (M - U + j + *k) % M);
		}
	}
	cout << Z;

	return 0;
}
