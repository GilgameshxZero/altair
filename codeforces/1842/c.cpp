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
		cin >> N;
		vector<LL> A(N), mbl(N), mblX(N + 1, LLONG_MAX / 2);
		RF(i, 0, N) {
			cin >> A[i];
		}
		RF(i, N - 1, -1) {
			mbl[i] = min(i == N - 1 ? 1 : 1 + mbl[i + 1], mblX[A[i]]);
			mblX[A[i]] = min(mblX[A[i]], i == N - 1 ? 0 : mbl[i + 1]);
		}
		cout << N - mbl[0] << '\n';
	}

	return 0;
}
