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

	array<LL, 2001> Y;
	Y[1] = Y[2] = 0;
	RF(i, 3, Y.size()) {
		set<LL> S;
		RF(i, 0, 200) {
			S.insert(i);
		}
		RF(j, 1, (i + 1) / 2) {
			S.erase(Y[j] ^ Y[i - j]);
		}
		Y[i] = *S.begin();
	}

	LL T;
	cin >> T;
	while (T--) {
		LL N;
		cin >> N;
		cout << (N >= Y.size() ? "first" : (Y[N] == 0 ? "second" : "first"))
				 << '\n';
	}

	return 0;
}
