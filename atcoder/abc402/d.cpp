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

	vector<LL> C(N);
	RF(i, 0, M) {
		LL A, B;
		cin >> A >> B;
		C[(A + B - 2) % N]++;
	}

	LL Z{M * M};
	RF(i, 0, N) {
		Z -= C[i] * C[i];
	}
	cout << Z / 2 << '\n';

	return 0;
}
