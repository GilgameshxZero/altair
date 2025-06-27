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

	LL N;
	cin >> N;
	multiset<LL> T;
	T.insert(LLONG_MAX);
	RF(i, 0, N) {
		LL x;
		cin >> x;
		auto j{T.upper_bound(x)};
		if (j == T.end()) {
			T.insert(x);
		} else {
			T.erase(j);
			T.insert(x);
		}
	}
	cout << T.size();

	return 0;
}
