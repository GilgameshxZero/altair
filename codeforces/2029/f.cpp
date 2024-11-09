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

	LL T;
	cin >> T;
	while (T--) {
		LL N;
		cin >> N;
		string S;
		cin >> S;

		bool rr{false}, bb{false};
		RF(i, 0, N) {
			rr |= S[i] == 'R' && S[(i + 1) % N] == 'R';
			bb |= S[i] == 'B' && S[(i + 1) % N] == 'B';
		}
		if (rr && bb) {
			cout << "NO\n";
			continue;
		}
		if (N % 2 == 0 && !rr && !bb) {
			cout << "NO\n";
			continue;
		}
		if (N % 2 == 1) {
			cout << "YES\n";
			continue;
		}
		LL cR{0}, cB{0};
		RF(i, 0, N) {
			cR += S[i] == 'R';
			cB += S[i] == 'B';
		}
		if (cR <= 1 || cB <= 1) {
			cout << "YES\n";
		} else {
			cout << "NO\n";
		}
	}

	return 0;
}
