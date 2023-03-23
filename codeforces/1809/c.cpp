#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC target("avx2", "bmi", "bmi2", "popcnt", "lzcnt")
#pragma GCC optimize("Ofast", "unroll-loops")
#endif

#include <bits/stdc++.h>

using LL = long long;
using LD = long double;
using namespace std;

#define RF(x, from, to) \
	for (LL x(from), _to(to), _delta{x < _to ? 1LL : -1LL}; x != _to; x += _delta)

#pragma hdrstop	 // ------------------------------------------------------------

int main(int, char const *[]) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL T;
	cin >> T;
	while (T--) {
		LL N, K;
		cin >> N >> K;
		vector<LL> A(N);
		LL cur{1};
		for (LL i{0}; i < N; i++) {
			if (K == 0) {
				RF(j, i, N) {
					A[j] = -1000;
				}
				break;
			} else if (K >= cur) {
				A[i] = 2;
				K -= cur;
				cur++;
			} else if (K < cur) {
				A[i] = -2 * cur + 1 + 2 * K;
				K = 0;
			}
		}
		RF(i, 0, N) {
			cout << A[i] << ' ';
		}
		cout << '\n';
	}

	return 0;
}
