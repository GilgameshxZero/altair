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
		vector<LL> A(N);

		RF(i, 0, N) {
			A[i] = i + 1;
		}
		// LL Z{0};
		// vector<LL> Y;
		// do {
		// 	LL z{0}, m{0};
		// 	RF(i, 0, N) {
		// 		z += (i + 1) * A[i];
		// 		m = max(m, (i + 1) * A[i]);
		// 	}
		// 	if (z - m > Z) {
		// 		Z = z - m;
		// 		Y = A;
		// 	}
		// } while (next_permutation(A.begin(), A.end()));
		// cout << Z << '\n';
		// RF(i, 0, N) {
		// 	cout << Y[i] << ' ';
		// }
		// cout << '\n';

		LL Z{0};
		RF(i, 0, N) {
			reverse(A.begin() + i, A.end());
			LL z{0}, m{0};
			RF(i, 0, N) {
				z += (i + 1) * A[i];
				m = max(m, (i + 1) * A[i]);
			}
			Z = max(Z, z - m);
			reverse(A.begin() + i, A.end());
		}
		cout << Z << '\n';
	}

	return 0;
}
