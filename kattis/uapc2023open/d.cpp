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

	LL T, N;
	cin >> T >> N;

	LL tL{0}, tR{0};
	vector<LL> nL(T), nR(T);
	RF(i, 0, N) {
		LL t;
		char c;
		cin >> t >> c;
		if (c == 'L') {
			nL[t - 1]++;
			tL++;
		} else {
			nR[t - 1]++;
			tR++;
		}
	}

	LL flex{0}, cL{0}, cR{0};
	bool possible{true};
	RF(i, 0, T) {
		if (nL[i] == 0 && nR[i] == 0) {
			possible = false;
			break;
		} else if (nL[i] == 0 && nR[i] != 0) {
			cR++;
			tR--;
		} else if (nL[i] != 0 && nR[i] == 0) {
			cL++;
			tL--;
		} else {
			flex++;
		}
	}
	if (!possible) {
		cout << -1;
		return 0;
	}

	if (cL <= cR && cL + tL >= cR || cR < cL && cR + tR >= cL) {
		if (max(cL, cR) >= (T + 1) / 2) {
			cout << max(cL, cR) * 2;
		} else {
			cout << (T + 1) / 2 * 2;
		}
		return 0;
	}

	cout << -1;
	return 0;
}
