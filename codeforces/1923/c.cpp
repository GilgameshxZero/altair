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
		LL N, Q;
		cin >> N >> Q;
		vector<LL> A(N), B(N), C(N);
		RF(i, 0, N) {
			cin >> A[i];
			A[i]--;
		}
		B[0] = A[0];
		C[0] = A[0] == 0;
		RF(i, 1, N) {
			B[i] = A[i] + B[i - 1];
			C[i] = (A[i] == 0) + C[i - 1];
		}
		RF(i, 0, Q) {
			LL L, R;
			cin >> L >> R;
			LL b{B[R - 1] - (L > 1 ? B[L - 2] : 0)},
				c{C[R - 1] - (L > 1 ? C[L - 2] : 0)};
			if (L == R) {
				cout << "NO\n";
			} else {
				cout << (b >= c ? "YES\n" : "NO\n");
			}
		}
	}

	return 0;
}
