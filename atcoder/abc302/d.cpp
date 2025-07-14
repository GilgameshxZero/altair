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

	LL N, M, D;
	cin >> N >> M >> D;
	set<LL> A;
	RF(i, 0, N) {
		LL X;
		cin >> X;
		A.insert(X);
	}
	A.insert(-LLONG_MAX / 2);
	LL Z{-1};
	RF(i, 0, M) {
		LL B;
		cin >> B;
		LL X{*prev(A.upper_bound(B + D))};
		if (X >= B - D) {
			Z = max(Z, B + X);
		}
	}
	cout << Z;
	return 0;
}
