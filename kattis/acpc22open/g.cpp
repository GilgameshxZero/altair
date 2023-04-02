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

	int n, m;
	cin >> n >> m;

	vector<LL> a(m);
	for (auto &x : a) {
		cin >> x;
	}

	LL mask = (1LL << n) - 1;

	// Computes position of least significant bit.
	auto lsb = [] (LL x) -> int {
		int ret = 0;
		while ((x & 1) == 0) {
			x >>= 1;
			++ret;
		}
		return ret;
	};

	auto get_crosses = [&](LL a, LL b) -> int {
		if (a == 0 && b == 0) return 0;
		if (a == 0) return n - lsb(b);
		if (b == 0) return n - lsb(a);

		for (int k = n - max(lsb(a), lsb(b)); k >= 0; --k) {
			assert(k != 0);

			LL sa = (a << (n - lsb(a) - k)) & mask;
			LL sb = (b << (n - lsb(b) - k)) & mask;

			if (sa == sb) {
				return (n - lsb(a) - k) + (n - lsb(b) - k);
			}
		}
	};

	int res = 0;
	for (int i = 0; i < m - 1; ++i) {
		res += get_crosses(a[i], a[i + 1]);
	}

	cout << res << endl;

	return 0;
}
