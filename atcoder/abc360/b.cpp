#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC target("avx", "avx2", "fma", "bmi", "bmi2", "popcnt", "lzcnt")
#pragma GCC optimize("Ofast", "unroll-loops")
#endif

#include <bits/stdc++.h>

using LL = long long;
using LD = long double;
using namespace std;

#define RF(x, y, z) \
	for (LL x(y), _c(z), d{x < _c ? 1LL : -1LL}; x != _c; x += d)

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	string S, T;
	cin >> S >> T;
	bool fail{true};
	RF(w, 1, S.size()) {
		RF(c, 0, w) {
			string U;
			for (LL i{c}; i < S.size(); i += w) {
				U.push_back(S[i]);
			}
			if (U == T) {
				fail = false;
				break;
			}
		}
	}
	cout << (fail ? "No" : "Yes") << '\n';

	return 0;
}
