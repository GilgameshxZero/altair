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

	string S;
	cin >> S;

	vector<LL> A[2];
	RF(i, 0, S.length()) {
		A[S[i] - '0'].push_back(i);
	}
	if (A[0].empty() || A[1].empty()) {
		cout << 0;
		return 0;
	}

	LL Y{0}, C[2]{A[0].size(), A[1].size()};
	RF(i, 0, S.length()) {
		if (S[i] == '0') {
			C[0]--;
			Y += C[1] - (A[1].size() - C[1]);
		} else {
			C[1]--;
			Y -= C[0] - (A[0].size() - C[0]);
		}
	}
	Y /= 2;

	LL B{2 * (A[0][0] - A[1][0])};
	RF(i, 0, 2) {
		RF(j, 1, A[i].size()) {
			A[i][j] -= A[i][0];
			A[i][j] *= 2 * (-2 * i + 1);
		}
		A[i][0] = 0;
	}

	if (Y == 0) {
		cout << 0;
		return 0;
	}
	LL const O{2500};
	vector<bitset<O * 2 + 1>> P[2];
	RF(i, 0, 2) {
		P[i].resize(A[i].size());
		RF(j, 0, A[i].size()) {
			P[i][j][O] = true;
		}
	}
	RF(i, 1, min(A[0].size(), A[1].size())) {
		Y += B;
		vector<bitset<O * 2 + 1>> Q[2];
		bitset<O * 2 + 1> R[2];
		RF(j, 0, 2) {
			Q[j].resize(A[j].size());
			LL m{0};
			RF(k, 0, i) {
				m += A[j][k];
			}
			if (m + O < 2 * O + 1 && m + O >= 0) {
				Q[j][i - 1][m + O] = true;
			}
			RF(k, i, A[j].size()) {
				Q[j][k] = Q[j][k - 1];
				RF(l, 0, O * 2 + 1) {
					if (P[j][k - 1][l] && l + A[j][k] >= 0 && l + A[j][k] <= O * 2) {
						Q[j][k][l + A[j][k]] = true;
					}
				}
			}
			R[j] = Q[j][A[j].size() - 1];
		}
		swap(P, Q);

		RF(j, 0, O * 2 + 1) {
			if (
				R[0][j] && -Y - (j - O) + O >= 0 && -Y - (j - O) + O <= O * 2 &&
				R[1][-Y - (j - O) + O]) {
				cout << i;
				return 0;
			}
		}
	}

	return 0;
}
