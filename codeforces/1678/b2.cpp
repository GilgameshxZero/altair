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
		string S;
		cin >> N >> S;
		string T(S);
		LL rl{1}, ch{0};
		char cp{S[0]};
		RF(i, 1, N) {
			if (S[i] != cp) {
				if (rl % 2 == 0) {
					rl = 0;
				} else {
					if (rl == 1) {
						S[i - 1] = S[i];
					} else {
						S[i] = S[i - 1];
					}
				}
			}

			rl++;
			cp = S[i];
		}

		cp = 0;
		LL tr{0};
		RF(i, 0, N) {
			ch += S[i] != T[i];
			tr += cp != S[i];
			cp = S[i];
		}

		S = T;
		rl = 3;
		cp = S[0];
		RF(i, 1, N) {
			if (S[i] != cp) {
				if (rl % 2 == 0) {
					rl = 0;
				} else {
					if (rl == 1) {
						S[i - 1] = S[i];
					} else {
						S[i] = S[i - 1];
					}
				}
			}

			rl++;
			cp = S[i];
		}
		LL tr2{0};
		cp = 0;
		RF(i, 0, N) {
			tr2 += cp != S[i];
			cp = S[i];
		}

		cout << ch << ' ' << min(tr, tr2) << '\n';
	}

	return 0;
}
