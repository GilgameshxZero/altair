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
		LL A, B;
		cin >> A >> B;
		vector<LL> Z;
		RF(i, 31, -1) {
			if (((A >> i) & 1) != ((B >> i) & 1)) {
				Z.push_back(1LL << i);
			}
		}
		if (!Z.empty() && Z[0] > A) {
			cout << -1 << '\n';
		} else {
			cout << Z.size() << '\n';
			RF(i, (LL) Z.size() - 1, -1) {
				cout << Z[i] << ' ';
			}
			cout << '\n';
		}
	}

	return 0;
}
