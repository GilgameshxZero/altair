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

#define RF(x, from, to) \
	for (long long x = from, rfDir = from < to ? 1 : -1; x != to; x += rfDir)

using namespace std;

/* ---------------------------- End of template. ---------------------------- */

int main(int, char const *[]) {
#if !defined(ONLINEJUDGE) && (defined(__APPLE__) || defined(__MACH__))
	std::freopen("../build/i.default.txt", "r", stdin);
	std::freopen("../build/o.default.txt", "w", stdout);
#endif

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	LL N, K;
	string S, T;
	cin >> N >> K >> S >> T;

	if (T[0] == T[1]) {
		LL cnt{0};
		RF(i, 0, N) {
			cnt += S[i] == T[0];
		}
		cnt = min(cnt + K, N);
		cout << cnt * (cnt - 1) / 2;
		return 0;
	}

	vector<vector<vector<LL>>> s(
		N, vector<vector<LL>>(K + 1, vector<LL>(N + 1, numeric_limits<LL>::min())));
	if (T[0] == S[0]) {
		s[0][0][1] = 0;
	} else {
		s[0][0][0] = 0;
		if (K > 0) {
			s[0][1][1] = 0;
		}
	}
	RF(i, 1, N) {
		RF(j, 0, K + 1) {
			RF(k, 0, N + 1) {
				if (S[i] == T[0]) {
					if (k > 0) {
						s[i][j][k] = s[i - 1][j][k - 1];
					}
				} else {
					s[i][j][k] = s[i - 1][j][k] + (S[i] == T[1]) * k;
				}
				if (j > 0 && k > 0) {
					s[i][j][k] = max(s[i][j][k], s[i - 1][j - 1][k - 1]);
				}
				if (j > 0) {
					s[i][j][k] = max(s[i][j][k], s[i - 1][j - 1][k] + k);
				}
			}
		}
	}

	LL ans{0};
	RF(j, 0, K + 1) {
		RF(k, 0, N + 1) {
			ans = max(ans, s[N - 1][j][k]);
		}
	}
	cout << ans;

	return 0;
}
