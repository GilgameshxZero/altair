/*
ID: yangchess1
PROG: vans
LANG: C++
*/

// #define ONLINE_JUDGE

#if defined(__GNUC__) && !defined(__clang__) && \
	!defined(__MINGW32__) && !defined(ONLINE_JUDGE)
#pragma GCC target( \
	"avx", "avx2", "fma", "bmi", "bmi2", "popcnt", "lzcnt")
#pragma GCC optimize("Ofast", "unroll-loops")
#endif

#include <bits/stdc++.h>

using LL = long long;
using LD = long double;
using namespace std;

#define RF(x, from, to)                                   \
	for (LL x(from), _to(to), _delta{x < _to ? 1LL : -1LL}; \
			 x != _to;                                          \
			 x += _delta)

// LL N, Y, Z;
// array<pair<LL, LL>, 4> D{
// 	{{-1, 0}, {0, 1}, {1, 0}, {0, -1}}};

// void count(
// 	array<vector<bool>, 6> &V,
// 	LL I,
// 	LL J,
// 	LL C,
// 	bool EP1) {
// 	if (I == 1 && J == 1) {
// 		if (C == N * 4 - 1) {
// 			if (EP1) {
// 				Y++;
// 			} else {
// 				Z++;
// 			}
// 		}
// 		return;
// 	}
// 	V[I][J] = true;
// 	C++;
// 	vector<LL> Y;
// 	RF(i, 0, 4) {
// 		if (!V[I + D[i].first][J + D[i].second]) {
// 			Y.push_back(i);
// 		}
// 	}
// 	if (Y.empty()) {
// 		V[I][J] = false;
// 		return;
// 	} else if (Y.size() == 1) {
// 		if (I == 2 && J == N) {
// 			EP1 |= Y[0] == 3;
// 		}
// 		if (I == 3 && J == N) {
// 			EP1 |= Y[0] == 3;
// 		}
// 		count(V, I + D[Y[0]].first, J + D[Y[0]].second, C, EP1);
// 	} else {
// 		if (Y.size() == 2 && Y[0] % 2 == Y[1] % 2) {
// 			V[I][J] = false;
// 			return;
// 		}
// 		RF(i, 0, Y.size()) {
// 			if (I == 2 && J == N) {
// 				EP1 |= Y[i] == 3;
// 			}
// 			if (I == 3 && J == N) {
// 				EP1 |= Y[i] == 3;
// 			}
// 			count(
// 				V, I + D[Y[i]].first, J + D[Y[i]].second, C, EP1);
// 		}
// 	}
// 	V[I][J] = false;
// }

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
#ifdef ONLINE_JUDGE
	std::freopen("vans.in", "r", stdin);
	std::freopen("vans.out", "w", stdout);
#endif

	// RF(i, 2, 14) {
	// 	N = i;
	// 	Y = Z = 0;
	// 	array<vector<bool>, 6> V;
	// 	V[0].resize(N + 2, true);
	// 	RF(i, 1, 5) {
	// 		V[i].resize(N + 2, false);
	// 		V[i][0] = V[i][N + 1] = true;
	// 	}
	// 	V[5].resize(N + 2, true);
	// 	count(V, 1, 2, 0, false);
	// 	count(V, 2, 1, 0, false);
	// 	cout << Z << ' ' << Y << '\n';
	// }

	LL N;
	cin >> N;

	return 0;
}
