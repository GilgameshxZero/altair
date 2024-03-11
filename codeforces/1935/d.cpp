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
		LL N, C;
		cin >> N >> C;
		vector<LL> S(N);
		LL cS[2]{0};
		RF(i, 0, N) {
			cin >> S[i];
		}
		LL Z{(C + 1) * (C + 2) / 2};
		RF(i, 0, N) {
			Z -= C - S[i] + 1;
			Z -= S[i] / 2 + 1;
			cS[S[i] % 2]++;
			Z += cS[S[i] % 2];
		}
		cout << Z << '\n';
	}

	return 0;
}
