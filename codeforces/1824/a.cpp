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

	LL T;
	cin >> T;
	while (T--) {
		LL N, M;
		cin >> N >> M;

		vector<LL> A;
		LL CL{0}, CR{0};
		RF(i, 0, N) {
			A.resize(A.size() + 1);
			cin >> A.back();
			if (A.back() == -1) {
				CL++;
				A.pop_back();
			} else if (A.back() == -2) {
				CR++;
				A.pop_back();
			} else {
				A.back()--;
			}
		}
		sort(A.begin(), A.end());
		vector<LL> B(M, 1), C(M), D(M);
		RF(i, 0, A.size()) {
			B[A[i]] = 0;
		}
		A.clear();
		RF(i, 0, M) {
			if (B[i] == 0) {
				A.push_back(i);
			}
		}
		C[0] = B[0];
		D[M - 1] = B[M - 1];
		RF(i, 1, M) {
			C[i] = C[i - 1] + B[i];
		}
		RF(i, M - 2, -1) {
			D[i] = D[i + 1] + B[i];
		}
		// reverse(D.begin(), D.end());
		LL Z;
		// Z = upper_bound(C.begin(), C.end(), CR) - C.begin();
		// Z = max(Z, upper_bound(D.begin(), D.end(), CL) - D.begin());
		Z = min(C[M - 1], CR) + A.size();
		Z = max(Z, min(D[0], CL) + (LL)A.size());
		RF(i, 0, A.size()) {
			// Z = max(
			// 	Z,
			// 	(upper_bound(C.begin() + A[i] + 1, C.end(), CR + C[A[i]]) -
			// 	 (C.begin() + A[i] + 1)) +
			// 		(upper_bound(
			// 			 D.begin() + (M - 1 - A[i]) + 1, D.end(), CL + D[M - 1 - A[i]]) -
			// 		 (D.begin() + (M - 1 - A[i] + 1))) +
			// 		1);
			Z = max(
				Z, min(C[M - 1] - C[A[i]], CR) + min(D[0] - D[A[i]], CL) + (LL)A.size());
		}
		cout << Z << '\n';
	}

	return 0;
}
