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

	LL N, T;
	cin >> N >> T;
	vector<LL> K(N);
	RF(i, 0, N) {
		cin >> K[i];
	}

	LL low{2000000000000000000}, high{0}, mid;
	while (high + 1 < low) {
		mid = (low + high) / 2;
		LL y{0};
		RF(i, 0, N) {
			y += mid / K[i];
			if (y >= T) {
				break;
			}
		}
		if (y >= T) {
			low = mid;
		} else {
			high = mid;
		}
	}
	cout << low;

	return 0;
}
