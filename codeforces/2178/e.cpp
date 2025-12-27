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
		LL N;
		cin >> N;
		LL L{1}, R{N + 1}, S;
		cout << "? 1 " << N << endl;
		cin >> S;
		while (L + 1 < R) {
			LL l{L}, r{R}, m, s;
			while (l + 1 < r) {
				m = (l + r) / 2;
				cout << "? " << L << ' ' << m - 1 << endl;
				cin >> s;
				if (s <= S / 2) {
					l = m;
				} else if (s > S / 2) {
					r = m;
				}
			}
			// cout << "l: " << l << endl;
			if (l - L >= R - l) {
				L = l;
			} else {
				R = l;
			}
			S /= 2;
		}
		cout << "! " << S << endl;
	}

	return 0;
}
