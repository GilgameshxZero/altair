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
		LL N;
		set<LL> A;
		cin >> N;
		bool ans{true};
		RF(i, 0, N) {
			LL X;
			cin >> X;
			if (A.count(X)) {
				ans = false;
			} else {
				A.insert(X);
			}
		}
		if (!ans) {
			cout << "NO" << '\n';
			continue;
		}
		map<LL, LL> dc;
		for (auto i{A.begin()}; i != A.end(); i++) {
			for (auto j{i}; j != A.end(); j++) {
				if (*i == *j) continue;
				if (abs(*i - *j) == 1) continue;
				LL k{abs(*i - *j)};
				if (dc[k] == 0) {
					dc[k] = k - (min(*i, *j) % k);
				} else if (dc[k] != k - min(*i, *j) % k) {
					ans = false;
					break;
				}
			}
		}
		if (!ans) {
			cout << "NO" << '\n';
			continue;
		}
		for (auto i{dc.begin()}; i != dc.end(); i++) {
			for (auto j{i}; j != dc.end(); j++) {
				if (i->first == j->first) continue;
				if (
					i->second % greatestCommonDivisor(i->first, j->first) !=
					j->second % greatestCommonDivisor(i->first, j->first)) {
					ans = false;
					break;
				}
			}
		}
		cout << (ans ? "YES" : "NO") << '\n';
	}

	return 0;
}