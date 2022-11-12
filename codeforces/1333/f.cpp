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

	LL N;
	cin >> N;

	vector<LL> primes;
	vector<unordered_map<LL, LL>> fz(N + 1);
	RF(i, 2, N) {
		if (fz[i].empty()) {
			for (LL j{i * 2}; j <= N; j += i) {
				fz[j][primes.size()] = 0;
			}
			fz[i][primes.size()] = 1;
			primes.push_back(i);
		} else {
			LL k{i};
			for (auto &j : fz[i]) {
				while (k % primes[j.first] == 0) {
					j.second++;
					k /= primes[j.first];
				}
			}
		}
	}

	unordered_set<LL> in;
	LL thresh{1};
	RF(i, 1, N + 1) {
		in.insert(i);
	}
	while (!in.empty()) {
		RF(i, 1, N + 1) {
			fz[i][thresh]
		}
	}
	return 0;
}
