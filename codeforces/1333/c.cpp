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

	LL N;
	cin >> N;
	vector<LL> A(N);
	RF(i, 0, N) {
		cin >> A[i];
	}
	LL good{-1};
	RF(i, 0, N) {
		if (A[i] != 0) {
			good = i;
			break;
		}
	}
	if (good == -1) {
		cout << "0\n";
	}
	LL ans{0};
	unordered_set<LL> sums;
	LL shift{0}, msum{0};
	RF(i, good, N) {
		while (i < N && A[i] == 0) {
			i++;
			good = i;
			sums.clear();
			shift = 0;
			msum = 0;
		}
		if (i == N) {
			break;
		}

		while (sums.count(-shift - A[i])) {
			sums.erase(msum - shift);
			msum -= A[good];
			good++;
		}

		sums.insert(-shift);
		shift += A[i];
		msum += A[i];
		ans += i - good + 1;
	}
	cout << ans << '\n';

	return 0;
}
