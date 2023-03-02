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
		string S;
		cin >> S;
		map<char, LL> cd;
		RF(i, 0, S.length()) {
			cd[S[i]]++;
		}
		string front, back;
		for (auto i{cd.begin()}; i != cd.end(); i++) {
			while (i->second >= 2) {
				i->second -= 2;
				front += i->first;
				back += i->first;
			}
			if (i->second == 1) {
				if (next(i) == cd.end()) {
					front += i->first;
					i->second--;
				} else if (next(next(i)) == cd.end()) {
					front += string((next(i)->second + 1) / 2, next(i)->first);
					back += string(next(i)->second / 2, next(i)->first);
					front += i->first;
					i->second--;
					next(i)->second = 0;
				} else {
					back += i->first;
					i->second--;
					i = next(i);
					while (i != cd.end()) {
						front += string(i->second, i->first);
						i = next(i);
					}
					break;
				}
			}
		}
		reverse(back.begin(), back.end());
		cout << front << back << '\n';
	}

	return 0;
}
