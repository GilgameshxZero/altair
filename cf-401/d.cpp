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

int main(int, char const *[]) {
#if !defined(ONLINEJUDGE) && (defined(__APPLE__) || defined(__MACH__))
	std::freopen("../build/i.default.txt", "r", stdin);
	std::freopen("../build/o.default.txt", "w", stdout);
#endif

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	LL N, M;
	cin >> N >> M;
	string sN{to_string(N)};

	vector<vector<LL>> dp(1LL << sN.size(), vector<LL>(M, 0));
	dp[0][0] = 1;
	set<LL> l1, l2;
	l1.insert(0);
	RF(i, 0, sN.size()) {
		for (auto &j : l1) {
			RF(k, 0, sN.size()) {
				if (j & (1LL << k)) {
					continue;
				}
				l2.insert(j | (1LL << k));
				RF(l, 0, M) {
					dp[j | (1LL << k)][(l * 10 + sN[k] - '0') % M] += dp[j][l];
				}
			}
		}
		RF(j, 0, sN.size()) {
			if (sN[j] == '0') {
				RF(k, 0, M) {
					dp[1LL << j][k] = 0;
				}
			}
		}
		l1 = l2;
		l2.clear();
	}

	vector<LL> cnt(10, 0);
	RF(i, 0, sN.size()) {
		cnt[sN[i] - '0']++;
	}
	LL ans{dp.back()[0]};
	RF(i, 0, 10) {
		while (cnt[i] > 1) {
			ans /= cnt[i]--;
		}
	}
	cout << ans;
	return 0;
}
