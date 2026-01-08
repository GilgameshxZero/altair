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
	cout << fixed << setprecision(9);
	RF(_T, 1, T + 1) {
		LL N;
		cin >> N;
		vector<LL> X(N);
		RF(i, 0, N) {
			cin >> X[i];
		}
		sort(X.begin(), X.end());
		cout << "Case #" << _T << ": ";

		if (N == 5) {
			cout << max(
								(X[3] + X[4]) / 2.0 - (X[0] + X[2]) / 2.0,
								(X[2] + X[4]) / 2.0 - (X[0] + X[1]) / 2.0)
					 << '\n';
		} else {
			cout << (X[N - 2] + X[N - 1]) / 2.0 - (X[0] + X[1]) / 2.0 << '\n';
		}
	}

	return 0;
}
