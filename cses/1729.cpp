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

	LL N, K;
	cin >> N >> K;
	vector<LL> P(K);
	RF(i, 0, K) {
		cin >> P[i];
	}
	vector<bool> Z(N + 1);
	Z[0] = false;
	RF(i, 1, N + 1) {
		bool fail{true};
		RF(j, 0, K) {
			if (i - P[j] >= 0 && !Z[i - P[j]]) {
				fail = false;
				break;
			}
		}
		Z[i] = !fail;
		cout << (fail ? 'L' : 'W');
	}

	return 0;
}
