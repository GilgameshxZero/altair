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
		LL N, K;
		cin >> N >> K;
		unordered_set<LL> S;
		RF(i, 0, N) {
			LL x;
			cin >> x;
			S.insert(x);
		}
		LL Z{K - 1};
		RF(i, 0, K - 1) {
			if (S.count(i) == 0) {
				Z = i;
				break;
			}
		}
		cout << Z << '\n';
	}

	return 0;
}
