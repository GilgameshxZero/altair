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
#include <regex>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <system_error>
#include <thread>
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

/* ---------------------------- End of template. ---------------------------- */

const int MAXN = 1000001;
const int MAXK = 21;
int dp[MAXN][MAXK];

int main(int, char const *[]) {
#if !defined(ONLINEJUDGE) && (defined(__APPLE__) || defined(__MACH__))
	std::freopen("../build/i.default.txt", "r", stdin);
	std::freopen("../build/o.default.txt", "w", stdout);
#endif

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	for (int i = 0; i < MAXN; i++) {
		for (int j = 0; j < MAXK; j++) {
			dp[i][j] = 0;
		}
	}

	int n, K;
	cin >> n >> K;
	// read graph
	vector<vector<int>> g(n + 1);
	RF(i, 0, n - 1) {
		int u, v;
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}

	if (K == 1) {
		if (n > 1) {
			cout << -1 << endl;
		} else {
			cout << 1 << endl;
		}
		return 0;
	}

	// dfs
	function<void(int, int)> dfs = [&](int x, int p) {
		for (int w : g[x])
			if (w != p) {
				dfs(w, x);
			}

		for (int k = 1; k <= K; k++) {
			dp[x][k] = k;
			for (int w : g[x])
				if (w != p) {
					int best = -1;
					for (int k2 = 1; k2 <= K; k2++) {
						if (k2 == k) continue;
						if (best == -1 || dp[w][k2] < best) {
							best = dp[w][k2];
						}
					}
					dp[x][k] += best;
				}
		}
	};

	dfs(1, -1);
	int ans = -1;
	for (int k = 1; k <= K; k++) {
		if (ans == -1 || dp[1][k] < ans) {
			ans = dp[1][k];
		}
	}
	cout << ans << endl;

	return 0;
}
