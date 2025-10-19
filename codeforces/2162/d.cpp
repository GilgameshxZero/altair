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
		LL N;
		cin >> N;
		LL L;
		cout << "2 1 " << N << endl;
		cin >> L;
		L -= N * (N + 1) / 2;
		LL low{0}, high{N}, mid;
		while(low + 1 < high) {
			mid = (low + high) / 2;
			LL x, y;
			cout << "1 " << low + 1 << ' ' << mid << endl;
			cin >> x;
			cout << "2 " << low + 1 << ' ' << mid << endl;
			cin >> y;
			if (x == y) {
				low = mid;
			} else {
				high = mid;
			}
		}
		cout << "! " << low + 1 << ' ' << low + L << endl;
	}

	return 0;
}
