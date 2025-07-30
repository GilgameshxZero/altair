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

	string S, T;
	cin >> S >> T;

	vector<vector<LL>> Z(S.length() + 1, vector<LL>(T.length() + 1));
	RF(i, 0, S.length() + 1) {
		Z[i].back() = S.length() - i;
	}
	RF(i, 0, T.length() + 1) {
		Z.back()[i] = T.length() - i;
	}
	RF(i, S.length() - 1, -1) {
		RF(j, T.length() - 1, -1) {
			Z[i][j] = min({1 + Z[i + 1][j],
				1 + Z[i][j + 1],
				(S[i] == T[j] ? 0 : 1) + Z[i + 1][j + 1]});
		}
	}
	cout << Z[0][0];

	return 0;
}
