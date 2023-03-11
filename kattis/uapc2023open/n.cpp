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
#include <complex>
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

#define RF(x, from, to)                                                      \
	for (long long x = from, _to = to, _delta{x < _to ? 1LL : -1LL}; x != _to; \
			 x += _delta)

using LL = long long;
using namespace std;

#pragma hdrstop	 // ------------------------------------------------------------

int main(int, char const *[]) {
#if !defined(ONLINEJUDGE) && (defined(__APPLE__) || defined(__MACH__))
	std::freopen("../build/i.default.txt", "r", stdin);
	std::freopen("../build/o.default.txt", "w", stdout);
#endif

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	LL T, N1, N2, S1, S2;
	cin >> T >> N1 >> N2 >> S1 >> S2;
	vector<vector<LL>> dp(N1 + 1, vector<LL>(N2 + 1, LLONG_MAX / 10));
	dp[0][0] = 0;
	RF(i, 0, N1 + 1) {
		RF(j, 0, N2 + 1) {
			vector<pair<LL, LL>> ops;
			RF(k, 0, 5) {
				if (T - S2 * k >= 0) {
					ops.push_back({(T - S2 * k) / S1, k});
				}
			}
			for (auto const &k : ops) {
				LL ii{min(i + k.first, N1)}, jj{min(j + k.second, N2)};
				dp[ii][jj] = min(dp[ii][jj], dp[i][j] + 1);
			}
		}
	}
	cout << dp[N1][N2];

	return 0;
}
