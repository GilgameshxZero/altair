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

	string S, T;
	cin >> S >> T;
	RF(i, 0, 3) {
		T[i] += 'a' - 'A';
	}
	bool fail{true};
	LL cur{0};
	RF(i, 0, S.length()) {
		if (S[i] == T[cur]) {
			cur++;
			if (cur == 3) {
				fail = false;
				break;
			}
		}
	}
	if (fail && T[2] == 'x') {
		cur = 0;
		RF(i, 0, S.length()) {
			if (S[i] == T[cur]) {
				cur++;
				if (cur == 2) {
					fail = false;
					break;
				}
			}
		}
	}
	cout << (fail ? "No" : "Yes") << '\n';

	return 0;
}
