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

array<pair<LL, LL>, 4> D{{{0, 1}, {1, 0}, {0, -1}, {-1, 0}}};
array<char, 4> L{{'R', 'D', 'L', 'U'}};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL N, M;
	cin >> N >> M;
	vector<string> G(N + 2);
	G[0] = string(M + 2, '#');
	RF(i, 1, N + 1) {
		cin >> G[i];
		G[i] = '#' + G[i] + '#';
	}
	G.back() = string(M + 2, '#');

	queue<pair<LL, LL>> Q;
	vector<vector<LL>> Y(N + 2, vector<LL>(M + 2));
	RF(i, 1, N + 1) {
		RF(j, 1, M + 1) {
			if (G[i][j] == 'A') {
				Y[i][j] = 4;
				Q.push({i, j});
				bool fail{true};
				while (!Q.empty()) {
					LL I{Q.front().first}, J{Q.front().second};
					Q.pop();
					if (G[I][J] == ' ') {
						continue;
					}
					if (G[I][J] == 'B') {
						i = I;
						j = J;
						fail = false;
						break;
					}
					G[I][J] = ' ';
					RF(k, 0, D.size()) {
						if (G[I + D[k].first][J + D[k].second] == '.' ||
							G[I + D[k].first][J + D[k].second] == 'B') {
							Y[I + D[k].first][J + D[k].second] = k;
							Q.push({I + D[k].first, J + D[k].second});
						}
					}
				}
				if (!fail) {
					cout << "YES\n";
					string Z;
					while (Y[i][j] < 4) {
						Z += L[Y[i][j]];
						auto d{D[Y[i][j]]};
						i -= d.first;
						j -= d.second;
					}
					reverse(Z.begin(), Z.end());
					cout << Z.size() << '\n';
					cout << Z;
					return 0;
				} else {
					cout << "NO";
					return 0;
				}
			}
		}
	}

	return 0;
}
