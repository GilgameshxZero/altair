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
		LL x;
		cin >> x;
		vector<LL> Z;
		Z.push_back(x);
		RF(i, 1, N) {
			LL y;
			cin >> y;
			if (y >= x) {
				Z.push_back(y);
			} else {
				Z.push_back(y);
				Z.push_back(y);
			}
			x = y;
		}
		cout << Z.size() << '\n';
		RF(i, 0, Z.size()) {
			cout << Z[i] << ' ';
		}
		cout << '\n';
	}

	return 0;
}
