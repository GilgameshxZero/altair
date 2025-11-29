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
		LL N, K, S{0};
		cin >> N >> K;
		vector<LL> A(N + 2), B(N + 2), APRE(N + 2), ASUF(N + 2), AMP(N + 2),
			AMS(N + 2);
		RF(i, 1, N + 1) {
			cin >> A[i];
			S += A[i];
		}
		RF(i, 1, N + 1) {
			cin >> B[i];
		}
		APRE[0] = ASUF[N + 1] = AMP[0] = AMS[N + 1] = 0;
		RF(i, 1, N + 1) {
			APRE[i] = APRE[i - 1] + A[i];
		}
		RF(i, N, 0) {
			ASUF[i] = ASUF[i + 1] + A[i];
		}
		RF(i, 1, N + 1) {
			AMP[i] = min(AMP[i - 1], APRE[i]);
		}
		RF(i, N, 0) {
			AMS[i] = min(AMS[i + 1], ASUF[i]);
		}
		LL Z{LLONG_MIN};
		RF(i, 1, N + 1) {
			Z = max(Z, S - AMP[i - 1] - AMS[i + 1]);
			if (K % 2 == 1) {
				Z = max(Z, S + B[i] - AMP[i - 1] - AMS[i + 1]);
			}
		}
		cout << Z << '\n';
	}

	return 0;
}
