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
		string S;
		cin >> N >> S;
		vector<LL> Y;
		LL C{S[0] == '1'};
		RF(i, 1, N) {
			if (S[i] == '0' && S[i - 1] == '0') {
				if (C != 0) {
					Y.push_back(C - 1);
				}
				C = 0;
			} else {
				C++;
			}
		}

		if (C != 0) {
			Y.push_back(C - (S.back() == '0'));
		}
		LL Z[2]{};
		RF(i, 0, Y.size()) {
			Z[0] += 1 + Y[i] / 2;
			Z[1] += Y[i];
		}
		cout << Z[0] << ' ' << Z[1] << '\n';
	}

	return 0;
}
