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

namespace Rain::Algorithm {
	// Most significant 1-bit for unsigned integral types of at most long long in
	// size. Undefined result if x = 0.
	template <typename Integer>
	inline std::size_t mostSignificant1BitIdx(Integer const &x) {
#ifdef __has_builtin
#if __has_builtin(__builtin_clzll)
		return 8 * sizeof(unsigned long long) - __builtin_clzll(x) - 1;
#endif
#endif
		for (std::size_t bit{8 * sizeof(Integer) - 1};
				 bit != std::numeric_limits<std::size_t>::max();
				 bit--) {
			if (x & (static_cast<Integer>(1) << bit)) {
				return bit;
			}
		}
		return std::numeric_limits<std::size_t>::max();
	}

	// Least significant 1-bit for unsigned integral types of at most long long in
	// size. Undefined result if x = 0.
	template <typename Integer>
	inline std::size_t leastSignificant1BitIdx(Integer const &x) {
#ifdef __has_builtin
#if __has_builtin(__builtin_ctzll)
		return __builtin_ctzll(x);
#endif
#endif
		for (std::size_t bit{0}; bit != 8 * sizeof(Integer); bit++) {
			if (x & (static_cast<Integer>(1) << bit)) {
				return bit;
			}
		}
		return std::numeric_limits<std::size_t>::max();
	}

	// Count of 1-bits in unsigned integral types of at most long long in size.
	template <typename Integer>
	inline std::size_t bitPopcount(Integer const &x) {
#ifdef __has_builtin
#if __has_builtin(__builtin_popcountll)
		return __builtin_popcountll(x);
#endif
#endif
		std::size_t count{0};
		for (std::size_t bit{0}; bit != 8 * sizeof(Integer); bit++) {
			count += !!(x & (static_cast<Integer>(1) << bit));
		}
		return count;
	}
}

using namespace Rain::Algorithm;

/* ------------------------ End of primary template. ------------------------ */

struct Result {
	LL X, Y, longest = 0, D, deepest;
};

Result dfs(unordered_map<LL, unordered_set<LL>> &E, LL cur, LL par) {
	Result res;
	if (E[cur].size() == 1 && par != -1) {
		res.X = res.Y = -1;
		res.longest = 0;
		res.D = cur;
		res.deepest = 0;
		return res;
	}

	vector<pair<LL, LL>> d2;
	for (auto const &i : E[cur]) {
		if (i == par) {
			continue;
		}
		auto ires{dfs(E, i, cur)};
		if (ires.longest > res.longest) {
			res.X = ires.X;
			res.Y = ires.Y;
			res.longest = ires.longest;
		}
		if (d2.size() < 2) {
			d2.push_back({ires.D, ires.deepest});
			if (d2.size() == 2 && d2[1].second > d2[0].second) {
				swap(d2[0], d2[1]);
			}
		} else {
			if (ires.deepest > d2[1].second) {
				d2[1] = {ires.D, ires.deepest};
			}
			if (d2[1].second > d2[0].second) {
				swap(d2[0], d2[1]);
			}
		}
	}

	res.D = d2[0].first;
	res.deepest = d2[0].second + 1;
	if (d2.size() > 1 && res.longest < 2 + d2[0].second + d2[1].second) {
		res.longest = 2 + d2[0].second + d2[1].second;
		res.X = d2[0].first;
		res.Y = d2[1].first;
	}
	return res;
}

int main(int, char const *[]) {
#if !defined(ONLINEJUDGE) && (defined(__APPLE__) || defined(__MACH__))
	std::freopen("../build/i.default.txt", "r", stdin);
	std::freopen("../build/o.default.txt", "w", stdout);
#endif

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	LL N;
	cin >> N;
	unordered_map<LL, unordered_set<LL>> E;
	unordered_map<LL, LL> bref;
	RF(i, 0, N) {
		LL X;
		cin >> X;
		bref[X] = i + 1;
		while (X != 0) {
			auto msb{mostSignificant1BitIdx(X)};
			LL next{(1LL << (msb + 1)) - X};
			if (next == X) {
				next = 0;
			}
			E[next].insert(X);
			E[X].insert(next);
			X = next;
		}
	}
	auto ans{dfs(E, 0, -1)};
	if (ans.longest == 0) {
		LL prev{-1}, cur{0}, best{-1}, X;
		while (cur == 0 || E[cur].size() > 1) {
			if (best == -1 && bref.count(cur)) {
				best = 1;
				X = cur;
			} else if (best >= 0) {
				best++;
			}
			if (prev == *E[cur].begin()) {
				prev = cur;
				cur = *next(E[cur].begin());
			} else {
				prev = cur;
				cur = *E[cur].begin();
			}
		}
		cout << bref[X] << ' ' << bref[cur] << ' ' << best;
		return 0;
	}
	cout << bref[ans.X] << ' ' << bref[ans.Y] << ' ' << ans.longest;

	return 0;
}
