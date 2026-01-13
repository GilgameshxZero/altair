#if defined(__GNUC__) && !defined(__clang__) && !defined(__MINGW32__)
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
		LL N, K;
		string S, Z;
		cin >> N >> K >> S;
		RF(i, 0, N) {
			LL C{(S[i] == '-' ? -1 : 1) * (1LL << i)};
			if (K % (1LL << (i + 1)) != 0) {
				K -= C;
				Z += '#';
			} else {
				Z += '.';
			}
		}
		if (K == 0) {
			cout << Z << '\n';
		} else {
			cout << -1 << '\n';
		}
	}

	return 0;
}
