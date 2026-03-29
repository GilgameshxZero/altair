/*
ID: yangchess1
PROG: twofive
LANG: C++
*/

// #define ONLINE_JUDGE

#if defined(__GNUC__) && !defined(__clang__) && \
	!defined(__MINGW32__) && !defined(ONLINE_JUDGE)
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
#ifdef ONLINE_JUDGE
	std::freopen("twofive.in", "r", stdin);
	std::freopen("twofive.out", "w", stdout);
#endif

	char C;
	cin >> C;
	if (C == 'N') {
		LL N;
		cin >> N;
	} else {
		string W;
		cin >> W;
	}

	return 0;
}