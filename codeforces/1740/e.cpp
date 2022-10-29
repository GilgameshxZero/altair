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

void dfs(vector<vector<LL>> &E, vector<pair<LL, LL>> &dp, LL cur, LL par) {
	if (E[cur].size() == 1 && par != -1) {
		dp[cur] = {1, 1};
		return;
	}

	for (auto &i : E[cur]) {
		if (i == par) {
			continue;
		}
		dfs(E, dp, i, cur);
		dp[cur].first = max(dp[cur].first, dp[i].first + 1);
		dp[cur].second += max(dp[i].first, dp[i].second);
	}
}

int main(int, char const *[]) {
#if !defined(ONLINEJUDGE) && (defined(__APPLE__) || defined(__MACH__))
	std::freopen("../build/i.default.txt", "r", stdin);
	std::freopen("../build/o.default.txt", "w", stdout);
#endif

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	LL N;
	cin >> N;
	vector<vector<LL>> E(N);
	RF(i, 1, N) {
		LL P;
		cin >> P;
		P--;
		E[i].push_back(P);
		E[P].push_back(i);
	}

	vector<pair<LL, LL>> dp(N);
	dfs(E, dp, 0, -1);
	cout << max(dp[0].first, dp[0].second);
	return 0;
}
