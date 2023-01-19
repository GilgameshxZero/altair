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
		LL N, X;
		cin >> N >> X;

		string nB, xB;
		RF(i, 0, 63) {
			nB += (N & (1LL << i)) ? '1' : '0';
			xB += (X & (1LL << i)) ? '1' : '0';
		}

		bool okay{true}, preserve{false};
		LL first{-1};
		RF(i, 0, nB.size()) {
			if (nB[i] == '0' && xB[i] == '1') {
				okay = false;
				break;
			} else if (nB[i] == '1' && xB[i] == '0' && !preserve) {
				first = i;
			} else if (nB[i] == '1' && xB[i] == '0' && preserve) {
				okay = false;
				break;
			} else if (nB[i] == '1' && xB[i] == '1') {
				preserve = true;
			}
		}

		if (!okay) {
			cout << "-1\n";
			continue;
		} else if (first == -1) {
			cout << N << '\n';
			continue;
		}
		LL M{N + (1LL << (first + 1)) - N % (1LL << (first + 1))};
		if ((N & M) != X) {
			cout << "-1\n";
			continue;
		}
		cout << M << '\n';
	}

	return 0;
}
