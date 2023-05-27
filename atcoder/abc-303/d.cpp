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

array<array<LL, 2>, 300001> A;

int main(int, char const *[]) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL X, Y, Z;
	string S;
	cin >> X >> Y >> Z >> S;

	A[0][0] = 0;
	A[0][1] = Z;
	RF(i, 1, S.length() + 1) {
		if (S[i - 1] == 'a') {
			A[i][0] = min(X + A[i - 1][0], Z + X + A[i - 1][1]);
			A[i][1] = min(Z + Y + A[i - 1][0], Y + A[i - 1][1]);
		} else {
			A[i][0] = min(Y + A[i - 1][0], Z + Y + A[i - 1][1]);
			A[i][1] = min(Z + X + A[i - 1][0], X + A[i - 1][1]);
		}
		A[i][0] = min(A[i][0], A[i][1] + Z);
		A[i][1] = min(A[i][1], A[i][0] + Z);
	}
	cout << min(A[S.length()][0], A[S.length()][1]);
	return 0;
}
