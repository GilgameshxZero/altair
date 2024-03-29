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
	vector<LL> C(S.length()), P(26, -1);
	LL Z{0};
	RF(i, 0, S.length()) {
		if (P[S[i] - 'a'] == -1) {
			C[i] = 1;
		} else {
			C[i] = C[P[S[i] - 'a']] + 1;
			Z = 1;
		}
		P[S[i] - 'a'] = i;
	}
	RF(i, 1, S.length()) {
		Z += i + 1 - C[i];
	}
	cout << Z;
	return 0;
}
