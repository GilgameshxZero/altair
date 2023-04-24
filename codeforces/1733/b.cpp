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

int main(int, char const *[]) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL T;
	cin >> T;
	while (T--) {
		LL N, X, Y;
		cin >> N >> X >> Y;
		if (X > Y) {
			swap(X, Y);
		}
		if (X != 0) {
			cout << -1 << '\n';
			continue;
		}
		if (Y == 0) {
			cout << -1 << '\n';
			continue;
		}
		if ((N - 1) % Y != 0) {
			cout << -1 << '\n';
			continue;
		}
		for (LL c{2}; c <= N; c += Y) {
			RF(i, 0, Y) {
				cout << c << ' ';
			}
		}
		cout << '\n';
	}

	return 0;
}
