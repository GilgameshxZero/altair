#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC target("avx", "avx2", "fma", "bmi", "bmi2", "popcnt", "lzcnt")
#pragma GCC optimize("Ofast", "unroll-loops")
#endif

#include <bits/stdc++.h>

using LL = long long;
using LD = long double;
using namespace std;

#define RF(x, y, z) for (LL x(y), c(z), d{x < c ? 1LL : -1LL}; x != c; x += d)

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	string S;
	cin >> S;
	bool seenR{false}, fail{true};
	RF(i, 0, 3) {
		if (S[i] == 'R') {
			seenR = true;
		} else if (S[i] == 'M') {
			fail = !seenR;
		}
	}
	cout << (fail ? "No" : "Yes") << '\n';

	return 0;
}
