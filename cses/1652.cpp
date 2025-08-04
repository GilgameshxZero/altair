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

	// 2D segtree is hard because we can't easily `retrace`.
	LL N, Q;
	cin >> N >> Q;

	vector<vector<LL>> G(N + 1, vector<LL>(N + 1));
	RF(i, 1, N + 1) {
		string S;
		cin >> S;
		RF(j, 0, S.size()) {
			G[i][j + 1] = S[j] == '*';
		}
	}

	auto H{G};
	RF(i, 1, N + 1) {
		RF(j, 1, N + 1) {
			H[i][j] += H[i - 1][j] + H[i][j - 1] - H[i - 1][j - 1];
		}
	}

	RF(i, 0, Q) {
		LL A, B, C, D;
		cin >> A >> B >> C >> D;
		cout << H[C][D] - H[C][B - 1] - H[A - 1][D] + H[A - 1][B - 1] << '\n';
	}

	return 0;
}
