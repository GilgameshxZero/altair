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

	LL N, X;
	cin >> N >> X;
	vector<LL> C(N);
	RF(i, 0, N) {
		cin >> C[i];
	}
	sort(C.begin(), C.end());

	vector<LL> Z(X + 1, LLONG_MAX / 2);
	Z[0] = 0;
	RF(i, 1, X + 1) {
		RF(j, 0, N) {
			if (C[j] > i) {
				break;
			}
			Z[i] = min(Z[i], Z[i - C[j]] + 1);
		}
	}
	cout << (Z[X] >= LLONG_MAX / 2 ? -1 : Z[X]);

	return 0;
}
