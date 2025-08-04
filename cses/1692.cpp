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

	vector<bool> V(1LL << N, false);
	cout << string(N, '0');
	LL C{0};
	V[0] = true;
	RF(i, 1, 1LL << N) {
		C = (C * 2 + 1) & ((1LL << N) - 1);
		if (V[C]) {
			C--;
		}
		V[C] = true;
		cout << C % 2;
	}

	return 0;
}
