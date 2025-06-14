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

	map<LL, set<LL>> Y;
	LL N, Q;
	cin >> N >> Q;
	vector<LL> M(N);
	RF(i, 0, N) {
		Y[0].insert(i);
	}
	RF(i, 0, Q) {
		LL X;
		cin >> X;
		while (Y.begin()->second.empty()) {
			Y.erase(Y.begin());
		}
		if (X == 0) {
			LL Z{*Y.begin()->second.begin()}, j{Y.begin()->first};
			cout << Z + 1 << '\n';
			Y.begin()->second.erase(Z);
			Y[j + 1].insert(Z);
			M[Z]++;
		} else {
			LL Z{X - 1}, j{M[Z]};
			cout << Z + 1 << '\n';
			Y[j].erase(Z);
			Y[j + 1].insert(Z);
			M[Z]++;
		}
	}

	return 0;
}
