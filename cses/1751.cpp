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

void CY_(vector<LL> &T,
	vector<bool> &V,
	vector<LL> &CID,
	vector<LL> &P,
	vector<vector<LL>> &C,
	LL i) {
	V[i] = true;
	if (V[T[i]]) {
		if (P[T[i]] != -1) {
			C.push_back({});
			LL target{T[i]};
			while (i != target) {
				C.back().push_back(i);
				CID[i] = C.size() - 1;
				i = P[i];
			}
			C.back().push_back(i);
			reverse(C.back().begin(), C.back().end());
			CID[i] = C.size() - 1;
		}
		return;
	}
	P[T[i]] = i;
	CY_(T, V, CID, P, C, T[i]);
	P[T[i]] = -1;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL N;
	cin >> N;

	vector<LL> T(N), P(N, -1), CID(N, -1), H(N, -1), L(N, -1), CR(N, -1);
	vector<vector<LL>> R(N), C, E(N);
	vector<array<LL, 30>> A(N);
	vector<bool> V(N, false);
	RF(i, 0, N) {
		cin >> T[i];
		T[i]--;
		R[T[i]].push_back(i);
	}
	RF(i, 0, N) {
		if (!V[i]) {
			P[i] = -2;
			CY_(T, V, CID, P, C, i);
			P[i] = -1;
		}
	}
	RF(i, 0, C.size()) {
		RF(j, 0, C[i].size()) {
			CR[C[i][j]] = j;
			for (auto &k : R[C[i][j]]) {
				if (k == C[i][(j - 1 + C[i].size()) % C[i].size()]) {
					continue;
				}
				E[C[i][j]].push_back(k);
			}
			queue<LL> Q;
			A[C[i][j]][0] = C[i][j];
			L[C[i][j]] = 0;
			H[C[i][j]] = C[i][j];
			Q.push(C[i][j]);
			while (!Q.empty()) {
				LL k{Q.front()};
				Q.pop();
				for (auto &l : E[k]) {
					A[l][0] = k;
					E[l] = R[l];
					L[l] = L[k] + 1;
					H[l] = C[i][j];
					Q.push(l);
				}
			}
		}
	}
	RF(i, 1, 30) {
		RF(j, 0, N) {
			A[j][i] = A[A[j][i - 1]][i - 1];
		}
	}

	RF(i, 0, N) {
		if (CID[i] == -1) {
			cout << L[i] + C[CID[H[i]]].size() << '\n';
		} else {
			cout << C[CID[i]].size() << '\n';
		}
	}

	return 0;
}
