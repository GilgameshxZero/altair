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

LL solve(array<array<bool, 9>, 9> &V, string &S, LL r, LL c, LL x) {
	static array<pair<LL, LL>, 4> const D{
		pair<LL, LL>{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

	if (r == 7 && c == 1) {
		return x == 48 ? 1 : 0;
	}

	LL Z{0}, P{0};
	P = 0;
	P += ((S[x] == '?' || S[x] == 'U') && !V[r - 1][c]);
	P += ((S[x] == '?' || S[x] == 'R') && !V[r][c + 1]) * 2;
	P += ((S[x] == '?' || S[x] == 'D') && !V[r + 1][c]) * 4;
	P += ((S[x] == '?' || S[x] == 'L') && !V[r][c - 1]) * 8;

	if (P == 5 || P == 10) {
		return 0;
	}

	V[r][c] = true;
	RF(i, 0, 4) {
		if ((P >> i) & 1) {
			Z += solve(V, S, r + D[i].first, c + D[i].second, x + 1);
		}
	}
	V[r][c] = false;

	return Z;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	string S;
	cin >> S;

	array<array<bool, 9>, 9> V;
	V.fill({false});
	RF(i, 0, 9) {
		V[0][i] = V[i][0] = V[8][i] = V[i][8] = true;
	}
	cout << solve(V, S, 1, 1, 0);

	return 0;
}
