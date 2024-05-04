#if defined(__GNUC__) && !defined(__clang__)
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

	LL N;
	cin >> N;
	LL Z{0}, mY{0};
	RF(i, 0, N) {
		LL x, y;
		cin >> x >> y;
		Z += x;
		mY = max(mY, y - x);
	}
	cout << Z + mY << '\n';

	return 0;
}
