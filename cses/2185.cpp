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

	LL N, K;
	cin >> N >> K;
	vector<LL> A(K);
	RF(i, 0, K) {
		cin >> A[i];
	}
	LL Z{0};
	RF(i, 1, (1LL << K)) {
		LL pc{-1}, pl{1};
		LD p{1};
		RF(j, 0, K) {
			if (i & (1LL << j)) {
				pc *= -1;
				pl *= A[j];
				p *= A[j];
			}
		}
		if (p <= N) {
			Z += pc * (N / pl);
		}
	}
	cout << Z;

	return 0;
}
