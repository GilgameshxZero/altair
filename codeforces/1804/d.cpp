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

	LL N, M;
	cin >> N >> M;

	LL tmin{0}, tmax{0};
	RF(i, 0, N) {
		string S;
		cin >> S;

		vector<LL> runpar(1, 0);
		char prev{'0'};
		LL z{0}, o{0};
		RF(j, 0, M) {
			z += S[j] == '0';
			o += S[j] == '1';
			if (S[j] == prev) {
				runpar.back()++;
			} else {
				prev = S[j];
				runpar.push_back(1);
			}
		}

		tmin += o;
		LL relief{0};
		for (LL j{1}; j < runpar.size(); j += 2) {
			relief += runpar[j] / 2;
		}
		tmin -= min(relief, M / 4);

		tmax += o - M / 4;
		relief = 0;
		for (LL j{0}; j < runpar.size(); j += 2) {
			if (j + 2 >= runpar.size()) {
				if (j + 1 < runpar.size()) {
					runpar[j]++;
				}
				relief += runpar[j] / 2;
				continue;
			}
			if (runpar[j + 1] >= 2) {
				runpar[j + 2]++;
				runpar[j]++;
				relief += runpar[j] / 2;
			} else if (runpar[j + 1] == 1) {
				runpar[j + 2] += 1 + runpar[j];
			} else {
				runpar[j + 2] += runpar[j];
			}
		}
		tmax += min(relief, M / 4);
	}
	cout << tmin << ' ' << tmax;

	return 0;
}
