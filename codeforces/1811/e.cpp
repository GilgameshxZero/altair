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
		LL K;
		cin >> K;
		string S;
		while (K != 0) {
			S += '0' + K % 9;
			K /= 9;
		}
		RF(i, 0, S.length()) {
			if (S[i] >= '4') {
				S[i]++;
			}
		}
		reverse(S.begin(), S.end());
		cout << S << '\n';
		// K--;
		// LL low{0}, high{K * 10}, mid;
		// while (low + 1 < high) {
		// 	mid = (low + high) / 2;
		// 	array<LL, 2> c{1, 0};
		// 	LL div{100000000000000};
		// 	RF(i, 14, -1) {
		// 		LL dig{(mid / div) % 10};
		// 		div /= 10;
		// 		array<LL, 2> nc{0, 0};
		// 		if (dig == 4) {
		// 			nc[1] += 4 * c[0] + 9 * c[1];
		// 		} else if (dig > 4) {
		// 			nc[0] += c[0];
		// 			nc[1] += (dig - 1) * c[0] + 9 * c[1];
		// 		} else {
		// 			nc[0] += c[0];
		// 			nc[1] += dig * c[0] + 9 * c[1];
		// 		}
		// 		c.swap(nc);
		// 	}
		// 	c[1]--;
		// 	if (c[0] + c[1] <= K) {
		// 		low = mid;
		// 	} else {
		// 		high = mid;
		// 	}
		// }
		// cout << low + 1 << '\n';
	}

	return 0;
}
