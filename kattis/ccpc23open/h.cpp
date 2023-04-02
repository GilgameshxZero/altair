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

	LL N, F;
	cin >> N >> F;

	vector<vector<vector<LL>>> best(
		F + 1, vector<vector<LL>>(N, vector<LL>(N, -LONG_MAX / 2)));
	RF(i, 0, N) {
		RF(j, 0, N) {
			cin >> best[0][i][j];
		}
	}

	vector<pair<LL, LL>> const dirs{{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
	RF(i, 1, F + 1) {
		RF(j, 0, N) {
			RF(k, 0, N) {
				RF(l, 0, dirs.size()) {
					pair<LL, LL> cand{j + dirs[l].first, k + dirs[l].second};
					if (
						cand.first < 0 || cand.first >= N || cand.second < 0 ||
						cand.second >= N) {
						continue;
					}
					if (best[0][cand.first][cand.second] <= best[0][j][k]) {
						continue;
					}
					best[i][j][k] = max(
						best[i][j][k],
						best[i - 1][cand.first][cand.second] + best[0][j][k]);
				}
			}
		}
	}

	LL ans{0};
	RF(i, 0, N) {
		RF(j, 0, F + 1) {
			ans = max(
				{ans,
				 best[j][0][i],
				 best[j][i][N - 1],
				 best[j][N - 1][i],
				 best[j][i][0]});
		}
	}
	cout << ans;

	// auto best{[&](LL I, LL J) {
	// 	static vector<pair<LL, LL>> const dirs{{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

	// 	vector<vector<bool>> vis(N, vector<bool>(N, false));
	// 	vector<vector<LL>> reward(N, vector<LL>(N, -1)), rem(N, vector<LL>(N,
	// -1)); 	queue<pair<LL, LL>> Q; 	LL ans{0}; 	reward[I][J] = G[I][J];
	// rem[I][J] = F; 	Q.push({I, J}); 	while (!Q.empty()) { 		auto
	// cur{Q.front()}; 		Q.pop(); 		vis[cur.first][cur.second] = true; 		ans =
	// max(ans, reward[cur.first][cur.second]); 		if (rem[cur.first][cur.second]
	// == 0) { 			continue;
	// 		}
	// 		RF(i, 0, dirs.size()) {
	// 			pair<LL, LL> cand{
	// 				cur.first + dirs[i].first, cur.second + dirs[i].second};
	// 			if (
	// 				cand.first < 0 || cand.first >= N || cand.second < 0 ||
	// 				cand.second >= N) {
	// 				continue;
	// 			}
	// 			if (G[cand.first][cand.second] <= G[cur.first][cur.second]) {
	// 				continue;
	// 			}
	// 			if (reward[cand.first][cand.second] != -1) {
	// 				continue;
	// 			}
	// 			reward[cand.first][cand.second] =
	// 				reward[cur.first][cur.second] + G[cand.first][cand.second];
	// 			rem[cand.first][cand.second] = rem[cur.first][cur.second] - 1;
	// 			Q.push(cand);
	// 		}
	// 	}
	// 	return ans;
	// }};

	// LL ans{0};
	// RF(i, 0, N) {
	// 	ans = max(ans, best(0, i));
	// }
	// cout << ans;

	return 0;
}
