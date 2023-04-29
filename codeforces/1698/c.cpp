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
		LL N;
		cin >> N;

		array<LL, 3> C;
		C.fill(0);
		multiset<LL> S;
		RF(i, 0, N) {
			LL X;
			cin >> X;
			if (X < 0) {
				C[0]++;
			} else if (X == 0) {
				C[1]++;
			} else {
				C[2]++;
			}
			if (X != 0) {
				S.insert(X);
			}
		}
		if (C[0] > 2 || C[2] > 2) {
			cout << "No\n";
			continue;
		}
		bool fail{false};
		if (C[1] >= 1) {
			S.insert(0);
			S.insert(0);
			S.insert(0);
		}
		for (auto i{S.begin()}; i != S.end(); i++) {
			for (auto j{next(i)}; j != S.end(); j++) {
				for (auto k{next(j)}; k != S.end(); k++) {
					if (S.count(*i + *j + *k) == 0) {
						fail = true;
					}
				}
			}
		}
		cout << (fail ? "No" : "Yes") << '\n';
	}

	return 0;
}
