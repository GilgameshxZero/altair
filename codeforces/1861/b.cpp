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
		string S[2];
		cin >> S[0] >> S[1];
		bool fail{true};
		RF(i, 0, S[0].size() - 1) {
			if (
				S[0][i] == '0' && S[1][i] == '0' && S[0][i + 1] == '1' &&
				S[1][i + 1] == '1') {
				fail = false;
				break;
			}
		}
		cout << (fail ? "NO" : "YES") << '\n';
	}

	return 0;
}
