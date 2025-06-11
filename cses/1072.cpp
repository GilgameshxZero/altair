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
	if (N <= 4) {
		array<LL, 4> Z{0, 6, 28, 96};
		RF(i, 0, N) {
			cout << Z[i] << '\n';
		}
		return 0;
	}
	cout << "0\n6\n28\n96\n";
	RF(i, 5, N + 1) {
		LL Z{i * i * (i * i - 1)};
		Z -= 4 * 2;
		Z -= 8 * 3;
		Z -= 4 * (i - 4) * 4;
		Z -= 4 * 4;
		Z -= 4 * (i - 4) * 6;
		Z -= (i - 4) * (i - 4) * 8;
		cout << Z / 2 << '\n';
	}

	return 0;
}
