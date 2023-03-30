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
		LL L, R;
		cin >> L >> R;

		if (R - L + 1 >= 100) {
			LL cand{L / 100 * 100 + 90};
			while (cand < L) {
				cand += 100;
			}
			while (cand > R) {
				cand -= 100;
			}
			cout << cand << '\n';
		} else {
			LL argans{-1}, ans;
			RF(i, L, R + 1) {
				auto S{to_string(i)};
				char maxc{'0'}, minc{'9'};
				for (auto &j : S) {
					maxc = max(maxc, j);
					minc = min(minc, j);
				}
				if (maxc - minc > argans) {
					argans = maxc - minc;
					ans = i;
				}
			}
			cout << ans << '\n';
		}
	}

	return 0;
}
