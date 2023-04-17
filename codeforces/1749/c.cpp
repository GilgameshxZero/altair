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
		LL N;
		cin >> N;
		array<LL, 102> C;
		C.fill(0);
		RF(i, 0, N) {
			LL X;
			cin >> X;
			C[X]++;
		}
		C[101] = 1000;
		LL ans;
		RF(i, 100, -1) {
			LL low{1}, high{i};
			auto R{C};
			bool possible{true};
			RF(j, i, 0) {
				high = min(high, j);
				while (high >= low && R[high] == 0) {
					high--;
				}
				if (high < low) {
					possible = false;
					break;
				}
				R[high]--;
				while (R[low] == 0) {
					low++;
				}
				R[low]--;
			}
			if (possible) {
				ans = i;
				break;
			}
		}
		cout << ans << '\n';
	}

	return 0;
}
