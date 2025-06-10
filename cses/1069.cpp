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

	string S;
	cin >> S;

	char R{'\0'};
	LL C{0}, Z{0};
	RF(i, 0, S.length()) {
		if (S[i] != R) {
			R = S[i];
			C = 1;
		} else {
			C++;
		}
		Z = max(Z, C);
	}
	cout << Z << '\n';

	return 0;
}
