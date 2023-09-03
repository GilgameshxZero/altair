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
		vector<LL> A(N), B(N), C(N);
		RF(i, 0, N) {
			cin >> A[i];
		}
		RF(i, 1, N) {
			B[i] = B[i - 1] + (A[i] <= A[i - 1]);
			C[i] = C[i - 1] + (A[i] >= A[i - 1]);
		}
		LL Z{min(B[N - 1], 1 + C[N - 1])};
		RF(i, 0, N - 1) {
			Z = min(Z, 1 + C[i] - C[0] + B[N - 1] - B[i + 1]);
		}
		cout << Z << '\n';
	}

	return 0;
}
