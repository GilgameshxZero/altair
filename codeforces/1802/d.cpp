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

	LL T;
	cin >> T;
	while (T--) {
		LL N;
		cin >> N;
		vector<pair<LL, LL>> A(N);
		multiset<LL> p2force, optional;
		RF(i, 0, N) {
			cin >> A[i].first >> A[i].second;
			p2force.insert(A[i].second);
		}
		LL ans{INT_MAX};
		sort(A.begin(), A.end());
		for (LL i{0}; i < N;) {
			auto j{i};
			for (; j < N && A[i].first == A[j].first; j++) {
				p2force.erase(p2force.find(A[j].second));
			}
			if (j != i + 1) {
				RF(k, i, j) {
					optional.insert(A[k].second);
				}
			}
			LL after{-1}, before{-1};
			auto it{optional.lower_bound(A[i].first)};
			if (it != optional.end()) {
				after = *it;
			}
			if (it != optional.begin()) {
				before = *prev(it);
			}
			LL forcebig{-INT_MAX};
			if (p2force.size() >= 1) {
				forcebig = *prev(p2force.end());
			}
			ans = min(ans, abs(forcebig - A[i].first));
			if (after != -1) {
				ans = min(ans, abs(max(after, forcebig) - A[i].first));
			}
			if (before != -1) {
				ans = min(ans, abs(max(before, forcebig) - A[i].first));
			}
			if (j == i + 1) {
				RF(k, i, j) {
					optional.insert(A[k].second);
				}
			}
			i = j;
		}
		cout << ans << '\n';
	}

	return 0;
}
