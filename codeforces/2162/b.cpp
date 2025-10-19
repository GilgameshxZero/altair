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
		LL N;
		string S, W, X, Y;
		cin >> N >> S;
		bool fail{true};
		RF(i, 0, 1LL << N) {
			X.clear();
			Y.clear();
			RF(j, 0, N) {
				if ((i >> j) & 1) {
					X += S[j];
				} else {
					Y += S[j];
				}
			}
			W = X;
			sort(W.begin(), W.end());
			if (W == X) {
				W = Y;
				reverse(W.begin(), W.end());
				if (W == Y) {
					cout << X.length() << '\n';
					RF(j, 0, N) {
						if ((i >> j) & 1) {
							cout << j + 1 << ' ';
						}
					}
					cout << '\n';
					fail = false;
					break;
				}
			}
		}
		if (fail) {
			cout << -1 << '\n';
		}
	}

	return 0;
}
