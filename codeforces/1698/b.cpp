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

		vector<LL> A(N);
		RF(i, 0, N) {
			cin >> A[i];
		}

		if (K == 1) {
			cout << (N - 2 + 1) / 2 << '\n';
		} else {
			LL Z{0};
			RF(i, 1, N - 1) {
				Z += A[i] > A[i - 1] + A[i + 1];
			}
			cout << Z << '\n';
		}
	}

	return 0;
}
