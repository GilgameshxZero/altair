#include <string>
#if defined(__GNUC__) && !defined(__clang__) && \
	!defined(__MINGW32__)
#pragma GCC target( \
	"avx", "avx2", "fma", "bmi", "bmi2", "popcnt", "lzcnt")
#pragma GCC optimize("Ofast", "unroll-loops")
#endif

#include <bits/stdc++.h>

using LL = long long;
using LD = long double;
using namespace std;

#define RF(x, from, to)                                   \
	for (LL x(from), _to(to), _delta{x < _to ? 1LL : -1LL}; \
			 x != _to;                                          \
			 x += _delta)

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL _T;
	cin >> _T;
	while (_T--) {
		LL X, Z{0};
		cin >> X;
		RF(i, X, X + 100) {
			string s{to_string(i)};
			LL sum{0};
			for (auto &j : s) {
				sum += j - '0';
			}
			if (X + sum == i) {
				Z++;
			}
		}
		cout << Z << '\n';
	}

	return 0;
}
