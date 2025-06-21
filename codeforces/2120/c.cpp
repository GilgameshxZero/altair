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
		LL N, M;
		cin >> N >> M;
		if (M < N || M > N * (N + 1) / 2) {
			cout << "-1\n";
			continue;
		}

		LL L{M - N};
		vector<LL> X, Y;
		RF(i, N, 1) {
			if (i - 1 <= L) {
				L -= i - 1;
				X.push_back(i);
			} else {
				Y.push_back(i);
			}
		}
		X.push_back(1);

		cout << X[0] << '\n';
		RF(i, 1, X.size()) {
			cout << X[i - 1] << ' ' << X[i] << '\n';
		}
		if (!Y.empty()) {
			cout << X.back() << ' ' << Y[0] << '\n';
			RF(i, 1, Y.size()) {
				cout << Y[i - 1] << ' ' << Y[i] << '\n';
			}
		}
	}

	return 0;
}
