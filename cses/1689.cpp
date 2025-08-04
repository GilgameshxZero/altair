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

array<pair<LL, LL>, 8> const D{
	{{-2, 1}, {-1, 2}, {1, 2}, {2, 1}, {2, -1}, {1, -2}, {-1, -2}, {-2, -1}}};

array<array<bool, 12>, 12> V;
array<array<LL, 8>, 8> Z;
vector<pair<LL, LL>> P;

bool dfs(LL r, LL c) {
	P.push_back({r, c});
	V[r][c] = true;
	if (P.size() == 64) {
		return true;
	}

	vector<pair<LL, LL>> O;
	RF(i, 0, D.size()) {
		LL rr{r + D[i].first}, cc{c + D[i].second};
		if (!V[rr][cc]) {
			O.push_back({0, i});
			RF(j, 0, D.size()) {
				O.back().first += !V[rr + D[j].first][cc + D[j].second];
			}
		}
	}
	sort(O.begin(), O.end());
	RF(i, 0, O.size()) {
		if (dfs(r + D[O[i].second].first, c + D[O[i].second].second)) {
			return true;
		}
	}
	P.pop_back();
	V[r][c] = false;
	return false;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	RF(i, 0, V.size()) {
		V[0][i] = V.back()[i] = V[i][0] = V[i].back() = true;
		V[1][i] = V[V.size() - 2][i] = V[i][1] = V[i][V.size() - 2] = true;
	}

	LL X, Y;
	cin >> X >> Y;

	dfs(Y - 1 + 2, X - 1 + 2);
	RF(i, 0, P.size()) {
		if (Z[P[i].first - 2][P[i].second - 2] != 0) {
			cout << P[i].first << ',' << P[i].second << '\n';
		}
		Z[P[i].first - 2][P[i].second - 2] = i + 1;
	}
	RF(i, 0, Z.size()) {
		RF(j, 0, Z[i].size()) {
			cout << Z[i][j] << ' ';
		}
		cout << '\n';
	}

	return 0;
}
