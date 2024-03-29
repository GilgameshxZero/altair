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
		LL N;
		cin >> N;

		vector<LL> A(N), B, C;
		LL sB{0}, sC{0};
		RF(i, 0, N) {
			cin >> A[i];
		}
		RF(i, 0, N) {
			LL X;
			cin >> X;
			if (A[i] == 0) {
				B.push_back(X);
				sB += X;
			} else {
				C.push_back(X);
				sC += X;
			}
		}

		sort(B.begin(), B.end());
		sort(C.begin(), C.end());
		if (B.size() == C.size()) {
			cout << 2 * (sB + sC) - min(B[0], C[0]) << '\n';
		} else {
			if (B.size() > C.size()) {
				swap(B, C);
				swap(sB, sC);
			}
			RF(i, C.size() - 1, C.size() - 1 - B.size()) {
				sC += C[i];
			}
			cout << 2 * sB + sC << '\n';
		}
	}

	return 0;
}
