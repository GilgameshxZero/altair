#if defined(__GNUC__) && !defined(__clang__) && \
	!defined(__MINGW32__)
	// <https://codeforces.com/blog/entry/135127>.
	#include <string>
	#pragma GCC target("arch=core-avx2")
	#pragma GCC optimize("Ofast", "unroll-loops")
#endif

#include <bits/stdc++.h>

using LL = long long;
using LD = long double;
using namespace std;

#define RF(x, from, to) \
	for ( \
		LL x(from), _to(to), _delta{x < _to ? 1LL : -1LL}; \
		x != _to; \
		x += _delta)

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL _T;
	cin >> _T;
	while (_T--) {
		LL N;
		cin >> N;
		LL Z{}, M{LLONG_MAX};
		RF(i, 0, N) {
			LL a;
			cin >> a;
			M = min(a, M);
			Z += M;
		}
		cout << Z << '\n';
	}

	return 0;
}
