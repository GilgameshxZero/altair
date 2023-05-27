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

	LL N;
	string S, T;
	cin >> N >> S >> T;

	bool fail{false};
	RF(i, 0, N) {
		if (!(S[i] == T[i] || S[i] == '1' && T[i] == 'l' ||
					S[i] == 'l' && T[i] == '1' || S[i] == '0' && T[i] == 'o' ||
					S[i] == 'o' && T[i] == '0')) {
			fail = true;
			break;
		}
	}
	cout << (fail ? "No" : "Yes") << '\n';
	return 0;
}
