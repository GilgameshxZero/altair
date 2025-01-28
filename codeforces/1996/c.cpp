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
		LL N, Q;
		cin >> N >> Q;
		string S[2];
		cin >> S[0] >> S[1];
		vector<array<LL, 26>> C[2];
		RF(i, 0, 2) {
			C[i].resize(N + 1);
			C[i][0].fill(0);
			RF(j, 1, N + 1) {
				C[i][j] = C[i][j - 1];
				C[i][j][S[i][j - 1] - 'a']++;
			}
		}

		RF(i, 0, Q) {
			LL L, R;
			cin >> L >> R;
			array<LL, 26> X[2];
			X[0] = C[0][R];
			X[1] = C[1][R];
			LL Z{0};
			RF(j, 0, 26) {
				X[0][j] -= C[0][L - 1][j];
				X[1][j] -= C[1][L - 1][j];
				Z += abs(X[0][j] - X[1][j]);
			}
			cout << Z / 2 << '\n';
		}
	}

	return 0;
}
