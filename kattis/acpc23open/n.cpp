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
	vector<LL> rating(N, 0), matches(N, 0);
	LL starting{1500};
	RF(i, 0, M) {
		LL x, y;
		cin >> x >> y;
		x--;
		y--;
		if (matches[x] == 0) {
			rating[x] = starting;
		}
		if (matches[y] == 0) {
			rating[y] = starting;
		}
		LL rx{rating[x]}, ry{rating[y]},
			ux{max(rx, (LL)floor((3 * ry + rx) / 2.0)) - rx},
			uy{ry - min(ry, (LL)floor((rx / 3.0 + ry) / 2.0))},
			tux(floor((LD)(matches[y] + 1) * ux / (matches[x] + matches[y] + 2))),
			tuy(floor((LD)(matches[x] + 1) * uy / (matches[x] + matches[y] + 2))),
			mtux(min(1000LL, tux)), mtuy(min(1000LL, tuy));

		rating[x] += mtux;
		rating[y] -= mtuy;
		cout << rating[x] << ' ' << rating[y] << '\n';
		if (matches[x] == 0 && matches[y] != 0) {
			starting = rating[x];
		}
		if (matches[y] == 0 && matches[x] != 0) {
			starting = rating[y];
		}
		matches[x]++;
		matches[y]++;
	}

	return 0;
}
