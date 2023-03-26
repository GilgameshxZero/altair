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
		LL N;
		cin >> N;
		vector<LL> A(N);
		RF(i, 0, N) {
			cin >> A[i];
		}
		if (N == 1) {
			cout << 0;
		} else if (N == 2) {
			cout << max(A[0], A[1]) - min(A[0], A[1]);
		} else {
			LL ans{A.back() - A[0]};
			RF(i, 1, N) {
				ans = max(ans, A[i] - A[0]);
			}
			RF(i, 0, N - 1) {
				ans = max(ans, A.back() - A[i]);
			}
			RF(i, 0, N - 1) {
				ans = max(ans, A[i] - A[i + 1]);
			}
			cout << ans;
		}
		cout << '\n';
	}

	return 0;
}
