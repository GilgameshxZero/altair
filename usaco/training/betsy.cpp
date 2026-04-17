/*
ID: yangchess1
LANG: C++
PROB: betsy
*/

#include <bits/stdc++.h>

using LL = long long;
using LD = long double;
using namespace std;

#define RF(x, from, to)                                   \
	for (LL x(from), _to(to), _delta{x < _to ? 1LL : -1LL}; \
			 x != _to;                                          \
			 x += _delta)

array<pair<int, int>, 4> const D{
	{{-1, 0}, {0, 1}, {1, 0}, {0, -1}}};
int N, Z, NV;
array<array<bool, 9>, 9> V;

void count(LL I, LL J) {
	if (I == N && J == 1) {
		if (NV == N * N - 1) {
			Z++;
		}
		return;
	}
	V[I][J] = true;
	NV++;
	int YC{0}, YS{0};
	RF(i, 0, D.size()) {
		if (!V[I + D[i].first][J + D[i].second]) {
			YC++;
			YS += i;
		}
	}
	if (YC == 2 && YS % 2 == 0) {
		V[I][J] = false;
		NV--;
		return;
	}
	RF(i, 0, D.size()) {
		if (!V[I + D[i].first][J + D[i].second]) {
			count(I + D[i].first, J + D[i].second);
		}
	}
	V[I][J] = false;
	NV--;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
#ifndef _DEBUG
	std::freopen("betsy.in", "r", stdin);
	std::freopen("betsy.out", "w", stdout);
#endif

	cin >> N;
	RF(i, 0, N + 2) {
		V[0][i] = V[i][0] = V[N + 1][i] = V[i][N + 1] = true;
	}
	count(1, 1);
	cout << Z << '\n';

	return 0;
}
