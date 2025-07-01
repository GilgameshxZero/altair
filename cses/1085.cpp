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

	LL N, K;
	cin >> N >> K;
	vector<LL> X(N);
	RF(i, 0, N) {
		cin >> X[i];
	}

	LL low{1000000000000000}, high{0}, mid;
	while (low - 1 > high) {
		mid = (low + high) / 2;
		LL C{0}, Y{1};
		RF(i, 0, N) {
			if (X[i] > mid) {
				Y = K + 1;
				break;
			}
			if (C + X[i] > mid) {
				C = 0;
				Y++;
			}
			C += X[i];
		}
		if (Y > K) {
			high = mid;
		} else {
			low = mid;
		}
	}
	cout << low;

	return 0;
}
