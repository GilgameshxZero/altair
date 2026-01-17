#if defined(__GNUC__) && !defined(__clang__) && \
	!defined(__MINGW32__)
#pragma GCC target( \
	"avx", "avx2", "fma", "bmi", "bmi2", "popcnt", "lzcnt")
#pragma GCC optimize("Ofast", "unroll-loops")
#endif

#include <bits/stdc++.h>

using LL = long long;
using LD = long double;
using namespace std;

#define RF(x, from, to)                                   \
	for (LL x(from), _to(to), _delta{x < _to ? 1LL : -1LL}; \
			 x != _to;                                          \
			 x += _delta)

LL const MOD{998244353};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	vector<vector<LL>> F(3001);
	LL Y{0};
	RF(i, 1, 3001) {
		RF(j, 1, i + 1) {
			if (i % j == 0) {
				F[i].push_back(j);
			}
		}
		Y = max(Y, (LL)F[i].size());
	}
	// cout << Y << '\n';

	LL _T;
	cin >> _T;
	while (_T--) {
		LL N, M;
		cin >> N >> M;
		vector<LL> A(N);
		RF(i, 0, N) {
			cin >> A[i];
		}

		vector<LL> B(M + 1);
		B[1] = 1;
		if (A[0] != 0 && A[0] != 1) {
			cout << "0\n";
			continue;
		}
		RF(i, 1, N) {
			vector<LL> C(M + 1);
			RF(j, 1, M + 1) {
				for (auto &k : F[j]) {
					if (j + k > M) {
						break;
					}
					C[j + k] = (C[j + k] + B[j]) % MOD;
				}
			}
			if (A[i] != 0) {
				RF(j, 1, M + 1) {
					if (j == A[i]) {
						continue;
					}
					C[j] = 0;
				}
			}
			swap(B, C);
		}
		LL Z{0};
		RF(i, 1, M + 1) {
			Z += B[i];
			// cout << B[i] << ',';
		}
		// cout << '\n';
		cout << Z % MOD << '\n';
	}

	return 0;
}
