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
		LL N, K;
		cin >> N >> K;

		vector<LL> S(K), A(N);
		RF(i, 0, K) {
			cin >> S[i];
		}
		RF(i, 0, N) {
			if (i <= N - K) {
				A[i] =
					S[0] < 0 ? S[0] / (N - K + 1) : (S[0] + N - K + 1 - 1) / (N - K + 1);
			} else {
				A[i] = S[i - (N - K)] - S[i - (N - K) - 1];
			}
		}

		bool fail{false};
		RF(i, 0, N - 1) {
			if (A[i] > A[i + 1]) {
				fail = true;
				break;
			}
		}
		cout << (fail ? "NO" : "YES") << '\n';
	}

	return 0;
}
