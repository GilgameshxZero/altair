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
	vector<LL> W(N);
	RF(i, 0, N) {
		cin >> W[i];
	}

	vector<pair<LL, LL>> Z(1 << N);
	Z[0] = {0, X};
	RF(i, 1, 1 << N) {
		Z[i] = {LLONG_MAX, 0};
		RF(j, 0, N) {
			if (((i >> j) & 1) == 0) {
				continue;
			}
			pair<LL, LL> k{Z[i ^ (1 << j)]};
			k.second += W[j];
			if (k.second > X) {
				k.second = W[j];
				k.first++;
			}
			Z[i] = min(Z[i], k);
		}
	}
	cout << Z.back().first;

	return 0;
}
