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
		LL N, K;
		cin >> N >> K;
		bool fail{true};
		RF(i, 0, N + 1) {
			if (i * (i - 1) / 2 + (N - i) * (N - i - 1) / 2 == K) {
				fail = false;
				cout << "YES\n";
				RF(j, 0, i) {
					cout << 1 << ' ';
				}
				RF(j, 0, N - i) {
					cout << -1 << ' ';
				}
				cout << '\n';
				break;
			}
		}
		if (fail) {
			cout << "NO\n";
		}
	}

	return 0;
}
