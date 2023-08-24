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

	LL T;
	cin >> T;
	while (T--) {
		LL N, M, D;
		cin >> N >> M >> D;
		vector<LL> S(M);
		RF(i, 0, M) {
			cin >> S[i];
		}
		vector<LL> Y(M);
		if (S[0] == 1) {
			Y[0] = 1;
		} else {
			Y[0] = 1 + (S[0] - 1 + D - 1) / D;
		}
		RF(i, 1, M) {
			Y[i] = Y[i - 1] + (S[i] - S[i - 1] + D - 1) / D;
		}
		LL X{Y.back() + (N - S.back()) / D};
		map<LL, LL> Z;
		Z[X - Y[1] + 1 + (S[1] - 1 + D - 1) / D]++;
		Z[Y[M - 2] + (N - S[M - 2]) / D]++;
		RF(i, 1, M - 1) {
			Z[Y[i - 1] + X - Y[i + 1] + (S[i + 1] - S[i - 1] + D - 1) / D]++;
		}
		cout << Z.begin()->first << ' ' << Z.begin()->second << '\n';
	}

	return 0;
}
