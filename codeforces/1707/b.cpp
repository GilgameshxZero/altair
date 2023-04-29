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

		map<LL, LL> CU;
		RF(i, 0, N) {
			LL X;
			cin >> X;
			CU[X]++;
		}

		while (CU.size() > 1) {
			map<LL, LL> R;
			for (auto i{CU.begin()}; next(i) != CU.end(); i++) {
				if (i->second > 1) {
					R[0] += i->second - 1;
				}
				R[next(i)->first - i->first]++;
			}
			if (CU.rbegin()->second > 1) {
				R[0] += CU.rbegin()->second - 1;
			}
			swap(R, CU);
		}

		if (CU.begin()->second == 1) {
			cout << CU.begin()->first << '\n';
		} else {
			cout << 0 << '\n';
		}
	}

	return 0;
}
