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
#include <complex>
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

#define RF(x, from, to)                                                      \
	for (long long x = from, _to = to, _delta{x < _to ? 1LL : -1LL}; x != _to; \
			 x += _delta)

using LL = long long;
using namespace std;

#pragma hdrstop	 // ------------------------------------------------------------

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
		LL N, M;
		cin >> N >> M;
		vector<LL> A(M);
		RF(i, 0, M) {
			cin >> A[i];
		}
		sort(A.begin(), A.end());
		vector<LL> gaps;
		RF(i, 0, M - 1) {
			gaps.push_back(A[i + 1] - A[i] - 1);
		}
		gaps.push_back(N + A[0] - A.back() - 1);
		sort(gaps.begin(), gaps.end());
		LL turns{0}, saved{0};
		RF(i, gaps.size() - 1, -1) {
			gaps[i] = max(0LL, gaps[i] - turns * 2);
			if (gaps[i] == 0) {
				continue;
			} else if (gaps[i] == 1) {
				saved += 1;
				turns += 1;
			} else if (gaps[i] == 2) {
				saved += 1;
				turns += 1;
			} else {
				saved += gaps[i] - 1;
				turns += 2;
			}
		}
		cout << N - saved << '\n';
	}

	return 0;
}
