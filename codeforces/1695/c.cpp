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
		vector<vector<LL>> A(N, vector<LL>(M)), B(A), C(A);
		RF(i, 0, N) {
			RF(j, 0, M) {
				cin >> A[i][j];
			}
		}
		B[0][0] = C[0][0] = A[0][0];
		RF(i, 1, M) {
			B[0][i] = C[0][i] = A[0][i] + B[0][i - 1];
		}
		RF(i, 1, N) {
			B[i][0] = C[i][0] = A[i][0] + B[i - 1][0];
		}
		RF(i, 1, N) {
			RF(j, 1, M) {
				B[i][j] = min(B[i - 1][j], B[i][j - 1]) + A[i][j];
				C[i][j] = max(C[i - 1][j], C[i][j - 1]) + A[i][j];
			}
		}
		// cout << B.back().back() << ' ' << C.back().back() << '\n';
		cout << ((N + M) % 2 == 1 && B.back().back() <= 0 && C.back().back() >= 0
							 ? "YES"
							 : "NO")
				 << '\n';
	}

	return 0;
}
