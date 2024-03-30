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
		unordered_set<LL> S;
		vector<LL> Z(N);
		LL m{0};
		RF(i, 0, N) {
			LL x;
			cin >> x;
			if (x > 0) {
				Z[i] = m;
				S.insert(m);
				while (S.count(++m))
					;
			} else {
				Z[i] = m - x;
				S.insert(m - x);
			}
			cout << Z[i] << ' ';
		}
		cout << '\n';
	}

	return 0;
}
