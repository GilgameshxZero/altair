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

	set<pair<LL, LL>> S;
	LL N, M;
	cin >> N >> M;
	RF(i, 0, M) {
		LL X;
		cin >> X;
		RF(j, 1, N) {
			LL Y;
			cin >> Y;
			S.insert({min(X, Y), max(X, Y)});
			X = Y;
		}
	}
	cout << N * (N - 1) / 2 - S.size();
	return 0;
}
