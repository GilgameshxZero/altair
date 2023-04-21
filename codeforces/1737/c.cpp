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
		map<LL, LL> RF, CF;
		RF(i, 0, 3) {
			LL R, C;
			cin >> R >> C;
			RF[R]++;
			CF[C]++;
		}
		LL X, Y, R, C;
		cin >> X >> Y;
		if (RF.begin()->second > RF.rbegin()->second) {
			R = RF.begin()->first;
		} else {
			R = RF.rbegin()->first;
		}
		if (CF.begin()->second > CF.rbegin()->second) {
			C = CF.begin()->first;
		} else {
			C = CF.rbegin()->first;
		}
		if ((R == 1 || R == N) && (C == 1 || C == N)) {
			cout << (X == R || Y == C ? "YES" : "NO") << '\n';
			continue;
		}
		cout << (X % 2 == R % 2 || Y % 2 == C % 2 ? "YES" : "NO") << '\n';
	}

	return 0;
}
