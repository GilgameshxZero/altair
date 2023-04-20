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
		string M;
		cin >> M;
		if (M[0] == '0') {
			cout << "0\n";
			continue;
		}
		LL ans{1};
		RF(i, 0, M.size()) {
			if (M[i] == '?') {
				ans *= 10;
			}
		}
		if (M[0] == '?') {
			ans = ans * 9 / 10;
		}
		cout << ans << '\n';
	}

	return 0;
}
