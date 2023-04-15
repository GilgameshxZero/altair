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

LL const MM{1000000007};

int main(int, char const *[]) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL T;
	cin >> T;
	while (T--) {
		LL N;
		cin >> N;
		vector<LL> A(N), B(N);
		LL L, R;
		RF(i, 0, N) {
			cin >> A[i];
			B[A[i]] = i;
			if (A[i] == 0) {
				L = R = i;
			}
		}
		LL ans{1};
		RF(i, 1, N) {
			if (B[i] >= L && B[i] <= R) {
				ans = ans * (R - L + 1 - i) % MM;
			} else {
				L = min(L, B[i]);
				R = max(R, B[i]);
			}
		}
		cout << ans << '\n';
	}

	return 0;
}
