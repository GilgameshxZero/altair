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
		vector<pair<LL, vector<LL>>> A(N);
		RF(i, 0, N) {
			A[i].second.resize(1);
			LL K;
			cin >> K >> A[i].second[0];
			RF(j, 1, K) {
				LL X;
				cin >> X;
				if (X > A[i].second.back()) {
					A[i].second.push_back(X);
				}
			}
			A[i].first = A[i].second.back();
		}
		sort(A.begin(), A.end());
		map<LL, LL> best;
		best[0] = 0;
		RF(i, 0, N) {
			auto &target{best[A[i].first]};
			RF(j, 0, A[i].second.size()) {
				auto it{best.lower_bound(A[i].second[j])};
				target = max(target, (LL)A[i].second.size() - j + prev(it)->second);
			}
		}
		cout << best.rbegin()->second << '\n';
	}

	return 0;
}