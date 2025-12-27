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
		string R;
		cin >> R;
		LL Z{0};
		if (R[0] == 'u') {
			R[0] = 's';
			Z++;
		}
		if (R.back() == 'u') {
			R.back() = 's';
			Z++;
		}
		RF(i, 1, R.size()) {
			if (R[i] == 'u' && R[i - 1] == 'u') {
				R[i] = 's';
				Z++;
			}
		}
		cout << Z << '\n';
	}

	return 0;
}
