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

	LL N, M;
	cin >> N >> M;
	multiset<LL> H;
	RF(i, 0, N) {
		LL X;
		cin >> X;
		H.insert(X);
	}
	RF(i, 0, M) {
		LL X;
		cin >> X;
		auto j{H.upper_bound(X)};
		if (j == H.begin()) {
			cout << -1 << '\n';
		} else {
			j--;
			cout << *j << '\n';
			H.erase(j);
		}
	}

	return 0;
}
