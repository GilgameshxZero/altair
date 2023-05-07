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
		LL N, K, S{0};
		cin >> N >> K;

		vector<LL> A(N), P(N);
		RF(i, 0, N) {
			cin >> A[i];
			S += A[i];
			if (i == 0) {
				P[i] = A[i];
			} else {
				P[i] = P[i - 1] + A[i];
			}
		}
		if (K >= N) {
			cout << S + N * K - N * (N + 1) / 2 << '\n';
			continue;
		}

		LL Z{0};
		RF(i, 0, N - K + 1) {
			Z = max(Z, P[i + K - 1] - (i == 0 ? 0 : P[i - 1]));
		}
		cout << Z + K * (K - 1) / 2 << '\n';
	}

	return 0;
}
