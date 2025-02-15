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

// GCD using Euclidean algorithm.
template <typename Integer>
inline Integer greatestCommonDivisor(Integer x, Integer y) {
	if (x > y) {
		std::swap(x, y);
	}
	while (x != 0) {
		y %= x;
		std::swap(x, y);
	}
	return y;
}

// LCM. Integer type must be large enough to store product.
template <typename Integer>
inline Integer leastCommonMultiple(Integer const x, Integer const y) {
	return x * y / greatestCommonDivisor(x, y);
}


/* ---------------------------- End of template. ---------------------------- */

vector<LL> spf(10000001, -1);

int main(int, char const *[]) {
#if !defined(ONLINEJUDGE) && (defined(__APPLE__) || defined(__MACH__))
	std::freopen("../build/i.default.txt", "r", stdin);
	std::freopen("../build/o.default.txt", "w", stdout);
#endif

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	RF(i, 2, spf.size()) {
		if (spf[i] == -1) {
			for (LL j{i * i}; j < spf.size(); j += i) {
				if (spf[j] == -1) {
					spf[j] = i;
				}
			}
			spf[i] = i;
		}
	}

	LL T;
	cin >> T;
	while (T--) {
		LL X, Y;
		cin >> X >> Y;
		LL D{Y - X}, A{X % D};
		if (D == 1) {
			cout << "-1\n";
			continue;
		}
		if (greatestCommonDivisor(X, Y) != 1) {
			cout << "0\n";
			continue;
		}

		LL ans{D - A};
		while (D != 1) {
			ans = min(ans, spf[D] - A % spf[D]);
			D /= spf[D];
		}
		cout << ans << '\n';
	}

	return 0;
}
