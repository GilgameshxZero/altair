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

	LL const M{1000000007};
	LL N, X;
	cin >> N >> X;
	vector<LL> C(N);
	RF(i, 0, N) {
		cin >> C[i];
	}

	vector<LL> Z(X + 1);
	Z[0] = 1;
	RF(i, 0, N) {
		RF(j, 1, X + 1) {
			if (j < C[i]) {
				continue;
			}
			Z[j] = (Z[j] + Z[j - C[i]]) % M;
		}
	}
	cout << Z[X];

	return 0;
}
