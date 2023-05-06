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

	cout << setprecision(9) << fixed;

	LL T;
	cin >> T;
	while (T--) {
		LL N;
		cin >> N;
		cout << "? 0 1 0\n"
				 << "? 1 0 0\n"
				 << "? " << -sqrt(99) << " 1 0" << endl;

		vector<pair<LD, LD>> P[3];
		RF(i, 0, 3) {
			P[i].resize(N);
			RF(j, 0, N) {
				cin >> P[i][j].first >> P[i][j].second;
			}
		}
	}

	return 0;
}
