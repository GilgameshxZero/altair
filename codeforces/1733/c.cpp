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
		LL N;
		cin >> N;

		vector<LL> P[2];
		RF(i, 0, N) {
			LL X;
			cin >> X;
			P[X % 2].push_back(i);
		}

		LL pp;
		if (!P[0].empty() && P[0][0] == 0) {
			pp = 0;
		} else {
			pp = 1;
		}
		cout << N - 1 << '\n';
		RF(i, 0, P[pp].size() - 1) {
			cout << P[pp][i] + 1 << ' ' << P[pp].back() + 1 << '\n';
		}
		RF(i, 0, P[1 - pp].size()) {
			cout << 1 << ' ' << P[1 - pp][i] + 1 << '\n';
		}
	}

	return 0;
}
