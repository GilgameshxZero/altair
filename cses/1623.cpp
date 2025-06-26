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

	LL N;
	cin >> N;
	vector<LL> P(N);
	RF(i, 0, N) {
		cin >> P[i];
	}
	LL Z{LLONG_MAX};
	RF(i, 0, 1LL << N) {
		LL X{0};
		RF(j, 0, N) {
			if ((i >> j) & 1) {
				X += P[j];
			} else {
				X -= P[j];
			}
		}
		Z = min(Z, abs(X));
	}
	cout << Z;

	return 0;
}
