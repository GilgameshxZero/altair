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
		LL N, K;
		cin >> N >> K;
		vector<LL> A(N);
		RF(i, 0, N) {
			cin >> A[i];
			A[i]--;
		}
		vector<LL> cold(K), hot(K);
		RF(i, 0, K) {
			cin >> cold[i];
		}
		RF(i, 0, K) {
			cin >> hot[i];
		}

		vector<LL> mcp(K + 1, LLONG_MAX / 10);
		LL mca{0};
		mcp[K] = cold[A[0]];
		LL mcpmin{cold[A[0]]};
		RF(i, 1, N) {
			if (A[i] == A[i - 1]) {
				mcp[A[i]] = min(mcpmin + cold[A[i]], mcp[A[i]] + hot[A[i]]);
			} else {
				mcp[A[i - 1]] = min(mcpmin + cold[A[i]], mcp[A[i]] + hot[A[i]]);
				mcp[A[i]] += cold[A[i]];
			}

			if (A[i] == A[i - 1]) {
				mca += hot[A[i]];
				mcp[A[i]] -= hot[A[i]];
			} else {
				mca += cold[A[i]];
				mcp[A[i]] -= cold[A[i]];
				mcp[A[i - 1]] -= cold[A[i]];
			}

			mcpmin = min(mcpmin, mcp[A[i]]);
			mcpmin = min(mcpmin, mcp[A[i - 1]]);
		}

		cout << mcpmin + mca << '\n';
	}

	return 0;
}
