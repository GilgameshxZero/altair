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

	LL T;
	cin >> T;
	while (T--) {
		LL N, X, C{0};
		cin >> N >> X;
		vector<LL> S[3];
		RF(i, 0, 3) {
			S[i].resize(N);
			RF(j, 0, N) {
				cin >> S[i][j];
			}
		}
		RF(i, 0, 3) {
			RF(j, 0, N) {
				if ((S[i][j] | X) == X) {
					C |= S[i][j];
				} else {
					break;
				}
			}
		}
		cout << (C == X ? "Yes" : "No") << '\n';
	}

	return 0;
}
