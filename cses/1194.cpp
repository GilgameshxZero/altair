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

	array<pair<LL, LL>, 4> const D{{{-1, 0}, {0, 1}, {0, -1}, {1, 0}}};
	array<char, 4> L{{'U', 'R', 'L', 'D'}};

	LL N, M;
	cin >> N >> M;
	vector<string> G(N);
	queue<pair<LL, LL>> W, X, Y;
	RF(i, 0, N) {
		cin >> G[i];
		RF(j, 0, M) {
			if (G[i][j] == 'M') {
				G[i][j] = '#';
				X.push({i, j});
			} else if (G[i][j] == 'A') {
				G[i][j] = '.';
				Y.push({i, j});
			}
		}
	}

	vector<vector<LL>> T(N, vector<LL>(M, -1));
	vector<vector<bool>> VX(N, vector<bool>(M, false)), VY{VX};
	pair<LL, LL> S;
	bool fail{true};
	while (fail && !Y.empty()) {
		while (!Y.empty()) {
			auto [i, j]{Y.front()};
			Y.pop();
			if (VY[i][j]) {
				continue;
			}
			if (G[i][j] == '#') {
				continue;
			}
			if (i == 0 || i == N - 1 || j == 0 || j == M - 1) {
				S = {i, j};
				fail = false;
				break;
			}
			VY[i][j] = true;
			RF(k, 0, 4) {
				LL I{i + D[k].first}, J{j + D[k].second};
				if (I < 0 || I >= N || J < 0 || J >= M || VY[I][J] || G[I][J] == '#') {
					continue;
				}
				T[I][J] = 3 - k;
				W.push({I, J});
			}
		}
		swap(W, Y);
		W = queue<pair<LL, LL>>();

		while (fail && !X.empty() && !Y.empty()) {
			auto [i, j]{X.front()};
			X.pop();
			if (VX[i][j]) {
				continue;
			}
			VX[i][j] = true;
			G[i][j] = '#';
			RF(k, 0, 4) {
				LL I{i + D[k].first}, J{j + D[k].second};
				if (I < 0 || I >= N || J < 0 || J >= M || VX[I][J] || G[I][J] == '#') {
					continue;
				}
				W.push({I, J});
				G[I][J] = '#';
			}
		}
		swap(W, X);
		W = queue<pair<LL, LL>>();
	}

	if (fail) {
		cout << "NO\n";
		return 0;
	}
	cout << "YES\n";
	string Z;
	while (T[S.first][S.second] != -1) {
		Z.push_back(L[3 - T[S.first][S.second]]);
		auto C{D[T[S.first][S.second]]};
		S.first += C.first;
		S.second += C.second;
	}
	reverse(Z.begin(), Z.end());
	cout << Z.size() << '\n' << Z;

	return 0;
}
