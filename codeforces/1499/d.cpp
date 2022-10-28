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

array<int, 20000001> cpr;

int main(int, char const *[]) {
#if !defined(ONLINEJUDGE) && (defined(__APPLE__) || defined(__MACH__))
	std::freopen("../build/i.default.txt", "r", stdin);
	std::freopen("../build/o.default.txt", "w", stdout);
#endif

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	RF(i, 2, cpr.size()) {
		if (cpr[i] == 0) {
			for (LL j{i * 2}; j < cpr.size(); j += i) {
				cpr[j]++;
			}
			cpr[i]++;
		}
	}

	auto calc = [](LL C, LL D, LL X, LL G) {
		LL N{X / G + D};
		if (N % C != 0) {
			return 0LL;
		}
		LL R{N / C};
		if (R == 1) {
			return 1LL;
		}
		return 1LL << (cpr[R]);
	};

	LL T;
	cin >> T;
	while (T--) {
		LL C, D, X;
		cin >> C >> D >> X;

		LL ans{0};
		for (LL i{1}; i * i <= X; i++) {
			if (X % i == 0) {
				ans += calc(C, D, X, i);
				if (i * i != X) {
					ans += calc(C, D, X, X / i);
				}
			}
		}
		cout << ans << '\n';
	}

	return 0;
}
