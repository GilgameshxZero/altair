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

LL solve(vector<string> &G,
	bitset<8> &C,
	bitset<16> &D1,
	bitset<16> &D2,
	LL r) {
	if (r == 8) {
		return 1;
	}
	LL Z{0};
	RF(i, 0, 8) {
		if (C[i] || D1[7 - i + r] || D2[i + r] || G[r][i] == '*') {
			continue;
		}
		C[i] = D1[7 - i + r] = D2[i + r] = true;
		Z += solve(G, C, D1, D2, r + 1);
		C[i] = D1[7 - i + r] = D2[i + r] = false;
	}
	return Z;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	vector<string> G(8);
	RF(i, 0, 8) {
		cin >> G[i];
	}

	bitset<8> C;
	bitset<16> D1, D2;
	cout << solve(G, C, D1, D2, 0);

	return 0;
}
