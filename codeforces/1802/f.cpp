#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC target("avx2", "bmi", "bmi2", "popcnt", "lzcnt")
#pragma GCC optimize("Ofast", "unroll-loops")
#endif

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <algorithm>
#include <array>
#include <atomic>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cinttypes>
#include <climits>
#include <cmath>
#include <condition_variable>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <mutex>
#include <numeric>
#include <queue>
#include <random>
#include <regex>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <system_error>
#include <thread>
#include <tuple>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using LL = long long;
using LD = long double;

#define RF(x, from, to)                                                      \
	for (long long x = from, _to = to, _delta{x < _to ? 1LL : -1LL}; x != _to; \
			 x += _delta)

using namespace std;

#pragma hdrstop

/* ------------------------ End of primary template. ------------------------ */

int main(int, char const *[]) {
#if !defined(ONLINEJUDGE) && (defined(__APPLE__) || defined(__MACH__))
	std::freopen("../build/i.default.txt", "r", stdin);
	std::freopen("../build/o.default.txt", "w", stdout);
#endif

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	LL T;
	cin >> T;
	while (T--) {
		LL N, M, P;
		cin >> N >> M >> P;

		vector<LL> profit(N);
		vector<pair<LL, LL>> pi(N);
		RF(i, 0, N) {
			cin >> profit[i];
			pi[i] = {profit[i], i};
		}
		sort(pi.begin(), pi.end());

		LL const INF{LLONG_MAX / 10};
		vector<vector<LL>> mincost(N, vector<LL>(N, INF));
		RF(i, 0, N) {
			mincost[i][i] = 0;
		}
		RF(i, 0, M) {
			LL U, V, C;
			cin >> U >> V >> C;
			mincost[U - 1][V - 1] = min(mincost[U - 1][V - 1], C);
		}
		RF(i, 0, N) {
			RF(j, 0, N) {
				RF(k, 0, N) {
					mincost[j][k] = min(mincost[j][k], mincost[j][i] + mincost[i][k]);
				}
			}
		}

		vector<LL> minperfs(N, INF), coins(N, -INF);
		minperfs[0] = 0;
		coins[0] = P;
		LL p2{0};
		for (LL cc{0}; cc < N; cc++) {
			LL cur{pi[cc].second};
			if (minperfs[cur] == INF) {
				continue;
			}
			if (cur == N - 1) {
				continue;
			}
			for (; p2 < N && pi[p2].first <= profit[cur]; p2++)
				;
			RF(i, p2, N) {
				if (mincost[cur][pi[i].second] == INF) {
					continue;
				}
				if (pi[i].second == N - 1) {
					continue;
				}
				LL lacking{mincost[cur][pi[i].second] - coins[cur]},
					candperfs{
						lacking > 0
							? minperfs[cur] + (lacking + profit[cur] - 1) / profit[cur]
							: minperfs[cur]},
					candcoins{
						lacking > 0
							? coins[cur] + (candperfs - minperfs[cur]) * profit[cur] -
								mincost[cur][pi[i].second]
							: coins[cur] - mincost[cur][pi[i].second]};
				if (
					candperfs < minperfs[pi[i].second] ||
					(candperfs == minperfs[pi[i].second] &&
					 candcoins > coins[pi[i].second])) {
					minperfs[pi[i].second] = candperfs;
					coins[pi[i].second] = candcoins;
				}
			}
			if (mincost[cur][N - 1] != INF) {
				LL lacking{mincost[cur][N - 1] - coins[cur]},
					candperfs{
						lacking > 0
							? minperfs[cur] + (lacking + profit[cur] - 1) / profit[cur]
							: minperfs[cur]},
					candcoins{
						lacking > 0 ? coins[cur] +
								(candperfs - minperfs[cur]) * profit[cur] - mincost[cur][N - 1]
												: coins[cur] = mincost[cur][N - 1]};
				if (
					candperfs < minperfs[N - 1] ||
					(candperfs == minperfs[N - 1] && candcoins > coins[N - 1])) {
					minperfs[N - 1] = candperfs;
					coins[N - 1] = candcoins;
				}
			}
		}
		cout << (minperfs[N - 1] == INF ? -1 : minperfs[N - 1]) << '\n';
	}

	return 0;
}
