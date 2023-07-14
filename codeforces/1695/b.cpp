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
		LL N;
		cin >> N;

		LL A[2];
		A[0] = A[1] = LLONG_MAX / 2;
		vector<LL> B(N);
		RF(i, 0, N) {
			cin >> B[i];
		}

		if (N % 2 == 1) {
			cout << "Mike\n";
			continue;
		}

		RF(i, 0, N) {
			A[i % 2] = min(A[i % 2], B[i]);
		}
		LL C[2];
		C[0] = C[1] = -1;
		RF(i, 0, N) {
			if (B[i] == A[i % 2] && C[i % 2] == -1) {
				C[i % 2] = i;
			}
		}
		// cout << A[0] << ' ' << A[1] << ' ' << C[0] << ' ' << C[1] << '\n';
		if (A[0] < A[1] || A[0] == A[1] && C[0] < C[1]) {
			cout << "Joe\n";
		} else {
			cout << "Mike\n";
		}
	}

	return 0;
}
