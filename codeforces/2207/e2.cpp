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

LL const MOD{1000000007};

LL expMod(LL base, LL exp) {
	if (exp == 0) {
		return 1;
	}
	LL half{expMod(base, exp / 2)};
	return half * half % MOD * (exp % 2 == 1 ? base : 1) %
		MOD;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	vector<LL> FMOD(200001);
	FMOD[0] = 1;
	RF(i, 1, FMOD.size()) {
		FMOD[i] = i * FMOD[i - 1] % MOD;
	}

	LL _T;
	cin >> _T;
	while (_T--) {
		LL N;
		cin >> N;
		vector<LL> A(N + 1);
		bool F{false};
		A[0] = N;
		RF(i, 1, N + 1) {
			cin >> A[i];
		}
		vector<LL> C(A);
		sort(C.begin(), C.end());
		reverse(C.begin(), C.end());
		vector<LL> B(N + 1), D, DD;
		vector<bool> E(N + 1, true);
		if (A != C) {
			F = true;
		} else {
			RF(i, 0, N + 1) {
				E[A[i]] = false;
			}
			RF(i, 0, N + 1) {
				if (E[i]) {
					D.push_back(i);
				}
			}

			DD = D;
			B[1] = N;
			RF(i, 1, N + 1) {
				if (A[i] == A[i - 1]) {
					B[i] = D.back();
					D.pop_back();
					if (B[i] > A[i]) {
						F = true;
					}
				} else {
					B[i] = B[1];
				}
			}
		}

		if (F) {
			cout << "0\n";
			continue;
		}
		A.push_back(-1);
		D = DD;
		vector<vector<LL>> X(N + 2);
		RF(i, 1, N + 2) {
			if (A[i] < A[i - 1] - 1) {
				RF(j, A[i] + 1, A[i - 1]) {
					X[i].push_back(j);
				}
			}
		}

		vector<LL> C2F(N + 2), C2G(N + 2);
		C2F[0] = C2G[0] = 0;
		LL C1{1}, C2{1};
		RF(i, 1, N + 2) {
			if (A[i] == A[i - 1]) {
				C2F[i] = C2F[i - 1] + 1;
				C2G[i] = C2G[i - 1] + 1;
			} else {
				if (!X[i].empty()) {
					C2 = C2 * FMOD[X[i].size()] % MOD *
						FMOD[C2F[i - 1]] % MOD *
						expMod(FMOD[X[i].size()], MOD - 2) % MOD *
						expMod(
								 FMOD[C2F[i - 1] - X[i].size()], MOD - 2) %
						MOD;
					C2F[i] = C2F[i - 1] - X[i].size();
				} else {
					C2F[i] = C2F[i - 1];
				}

				C2G[i] = C2G[i - 1] - (A[i - 1] - A[i] - 1);
				if (i != N + 1) {
					C1 = C1 * (N - A[i] + C2G[i]) % MOD;
				}
			}
		}
		// cout << C1 << ' ' << C2 << '\n';
		cout << C1 * C2 % MOD << '\n';
	}

	return 0;
}
