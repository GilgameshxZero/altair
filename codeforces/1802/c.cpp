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

	// cout << (548 ^ 549 ^ 550 ^ 551) << ' ' << (1064 ^ 1065 ^ 1066 ^ 1067) << '
	// '
	// 		 << (556 ^ 557 ^ 558 ^ 559);

	LL T;
	cin >> T;
	while (T--) {
		LL N, M;
		cin >> N >> M;
		cout << N * M << '\n';
		vector<vector<LL>> A(N + (N % 2), vector<LL>(M + (M % 2)));
		LL delta;
		RF(i, 0, A.size() / 2) {
			RF(j, 0, A[0].size() / 2) {
				delta = j * 4 + i * 512;
				A[i * 2][j * 2] = delta;
				A[i * 2][j * 2 + 1] = delta + 1;
				A[i * 2 + 1][j * 2] = delta + 2;
				A[i * 2 + 1][j * 2 + 1] = delta + 3;
			}
		}
		RF(i, 0, N) {
			RF(j, 0, M) {
				cout << A[i][j] << ' ';
			}
			cout << '\n';
		}
	}

	return 0;
}
