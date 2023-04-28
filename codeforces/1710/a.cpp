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
		LL N, M, K;
		cin >> N >> M >> K;

		vector<LL> A(K);
		RF(i, 0, K) {
			cin >> A[i];
		}

		bool fail{true};
		LL R{0}, li{0};
		RF(i, 0, K) {
			if (A[i] >= 2 * M) {
				R += A[i] / M;
				li = max(li, A[i] / M);
			}
		}
		if (N % 2 == 1) {
			if (R == N + 1) {
				if (li > 2) {
					fail = false;
				}
			} else if (R >= N) {
				fail = false;
			}
		} else if (R >= N) {
			fail = false;
		}
		if (!fail) {
			cout << "Yes\n";
			continue;
		}

		R = li = 0;
		RF(i, 0, K) {
			if (A[i] >= 2 * N) {
				R += A[i] / N;
				li = max(li, A[i] / N);
			}
		}
		if (M % 2 == 1) {
			if (R == M + 1) {
				if (li > 2) {
					fail = false;
				}
			} else if (R >= M) {
				fail = false;
			}
		} else if (R >= M) {
			fail = false;
		}
		cout << (!fail ? "Yes" : "No") << '\n';
	}

	return 0;
}
