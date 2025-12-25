#if defined(__GNUC__) && !defined(__clang__) && !defined(__MINGW32__)
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
		vector<LL> A(N), B(N), C(N);
		RF(i, 0, N) {
			cin >> A[i];
		}
		B[0] = 0;
		RF(i, 1, N) {
			B[i] = B[i - 1] + abs(A[i] - A[i - 1]);
		}
		C[N - 1] = 0;
		RF(i, N - 2, -1) {
			C[i] = C[i + 1] + abs(A[i] - A[i + 1]);
		}
		LL Z{min(B[N - 2], C[1])};
		RF(i, 1, N - 1) {
			Z = min(Z, B[i - 1] + C[i + 1] + abs(A[i - 1] - A[i + 1]));
		}
		cout << Z << '\n';
	}

	return 0;
}
