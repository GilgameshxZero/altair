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

/* ---------------------------- End of template. ---------------------------- */

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
		LL N, S;
		cin >> N >> S;
		vector<LL> A(N);
		RF(i, 0, N) {
			cin >> A[i];
		}

		vector<LL> minX(N, -1), maxX(N, -1);
		minX[N - 1] = maxX[N - 1] = A[N - 1];
		minX[0] = maxX[0] = 0;
		RF(i, 1, N - 1) {
			if (A[i] <= S) {
				minX[i] = 0;
			} else {
				minX[i] = min(S, A[i] - S);
			}
			maxX[i] = A[i] - minX[i];
		}

		vector<LL> dp[2];
		dp[0].resize(N);
		dp[1].resize(N);
		RF(i, 1, N) {
			dp[0][i] = min(
				minX[i] * (A[i - 1] - minX[i - 1]) + dp[0][i - 1],
				minX[i] * (A[i - 1] - maxX[i - 1]) + dp[1][i - 1]);
			dp[1][i] = min(
				maxX[i] * (A[i - 1] - maxX[i - 1]) + dp[1][i - 1],
				maxX[i] * (A[i - 1] - minX[i - 1]) + dp[0][i - 1]);
		}
		cout << min(dp[0][N - 1], dp[1][N - 1]) << '\n';
	}

	return 0;
}
