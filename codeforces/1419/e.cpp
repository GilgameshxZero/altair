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

	LL T;
	cin >> T;
	while (T--) {
		LL N;
		cin >> N;

		// Why doesn’t unordered_map work on some compilers? e.g. C++17 on CF.
		map<LL, LL> factor;
		LL n{N};
		for (LL i{2}; i * i <= n; i++) {
			while (n % i == 0) {
				n /= i;
				factor[i]++;
			}
		}
		if (n != 1) {
			factor[n]++;
		}

		LL mp{0};
		for (auto const &i : factor) {
			if (i.second > factor[mp]) {
				mp = i.first;
			}
		}
		factor.erase(0);
		if (factor[mp] > 1) {
			n = N;
			RF(i, 0, factor[mp]) {
				n /= mp;
			}
			vector<LL> fs;
			if (n != 1) {
				fs.push_back(n);
			}
			for (LL i{2}; i * i <= n; i++) {
				if (n % i == 0) {
					fs.push_back(i);
					if (i * i != n) {
						fs.push_back(n / i);
					}
				}
			}
			LL cur{mp};
			RF(i, 0, factor[mp]) {
				cout << cur << ' ';
				cur *= mp;
			}
			RF(i, 0, fs.size()) {
				cout << fs[i] * mp << ' ' << fs[i] << ' ';
				cur = mp * mp;
				RF(j, 2, factor[mp] + 1) {
					cout << fs[i] * cur << ' ';
					cur *= mp;
				}
			}
			cout << "\n0\n";
			continue;
		}

		vector<LL> primes;
		for (auto const &i : factor) {
			primes.push_back(i.first);
		}
		if (primes.size() == 1) {
			cout << primes[0] << "\n0\n";
			continue;
		}
		vector<LL> ans;
		ans.push_back(primes[0]);
		ans.push_back(primes[0] * primes[1]);
		ans.push_back(primes[1]);
		RF(i, 2, primes.size()) {
			RF(j, ans.size() - 1, -1) {
				ans.push_back(ans[j] * primes[i]);
			}
			LL tmp{ans.back()};
			ans.pop_back();
			ans.push_back(primes[i]);
			ans.push_back(tmp);
		}
		RF(i, 0, ans.size()) {
			cout << ans[i] << ' ';
		}
		if (primes.size() > 2) {
			cout << "\n0\n";
		} else {
			cout << "\n1\n";
		}
	}

	return 0;
}
