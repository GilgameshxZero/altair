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
	vector<string> G(N);
	RF(i, 0, N) {
		cin >> G[i];
	}
	auto Z{G};
	RF(i, 1, N) {
		Z[0][i] = G[0][i - 1];
		Z[i].back() = G[i - 1].back();
		Z.back()[N - 1 - i] = G.back()[N - i];
		Z[N - 1 - i][0] = G[N - i][0];
	}
	RF(i, 0, N) {
		cout << Z[i] << '\n';
	}

	return 0;
}
