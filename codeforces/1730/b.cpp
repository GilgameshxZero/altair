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
	cout << setprecision(10) << fixed;
	while (T--) {
		LL N;
		cin >> N;
		vector<LL> X(N), T(N);
		RF(i, 0, N) {
			cin >> X[i];
		}
		RF(i, 0, N) {
			cin >> T[i];
		}
		LD low{0}, high{1000000000}, mid, last;
		while (low + 1e-8 < high) {
			mid = (low + high) / 2;
			LD l(-LLONG_MAX / 2), h(LLONG_MAX / 2);
			RF(i, 0, N) {
				l = max(l, X[i] - (mid - T[i]));
				h = min(h, X[i] + (mid - T[i]));
			}
			if (h < l) {
				low = mid;
			} else {
				high = mid;
				last = l;
			}
		}
		cout << last << '\n';
	}

	return 0;
}
