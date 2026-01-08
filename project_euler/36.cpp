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

	LL Z{0};
	char b2[128], b10[128];
	RF(i, 1, 1000001) {
		char *b2e{to_chars(b2, b2 + 100, i, 2).ptr},
			*b10e{to_chars(b10, b10 + 100, i, 10).ptr};
		string s2(b2, b2e), s10(b10, b10e);
		reverse(b2, b2e);
		reverse(b10, b10e);
		string s2r(b2, b2e), s10r(b10, b10e);
		if (s2 == s2r && s10 == s10r) {
			Z += i;
			cout << i << '\n';
		}
	}
	cout << Z;

	return 0;
}
