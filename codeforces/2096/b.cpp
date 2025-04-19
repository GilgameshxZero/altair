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
		LL N, K;
		cin >> N >> K;
		vector<LL> A(N), B(N);
		LL sA{0}, sB{0};
		RF(i, 0, N) {
			cin >> A[i];
		}
		RF(i, 0, N) {
			cin >> B[i];
			if (B[i] > A[i]) {
				swap(B[i], A[i]);
			}
			sA += A[i];
			sB += B[i];
		}
		if (sA < sB) {
			swap(sA, sB);
			swap(A, B);
		}
		LL Z{sA};
		K--;
		sort(B.begin(), B.end());
		RF(i, N - 1, N - 1 - K) {
			Z += B[i];
		}
		cout << Z + 1 << '\n';
	}

	return 0;
}
