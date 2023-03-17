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
using LD = long double;
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
		string S;
		cin >> S;
		LL cL{0}, cR{0};
		RF(i, 0, S.length()) {
			cL += S[i] == '(';
			cR += S[i] == ')';
		}
		LL rL{(LL)S.length() / 2 - cL}, rR{(LL)S.length() / 2 - cR};
		if (rL == 0 || rR == 0) {
			cout << "YES\n";
			continue;
		}
		rL--;
		rR--;
		LL ll{1}, rr{1};
		RF(i, 0, S.length()) {
			if (S[i] != '?') {
				continue;
			}
			if (rL > 0) {
				S[i] = '(';
				rL--;
			} else if (rr > 0) {
				S[i] = ')';
				rr--;
			} else if (ll > 0) {
				S[i] = '(';
				ll--;
			} else {
				S[i] = ')';
				rR--;
			}
		}
		bool ans{true};
		LL height{0};
		RF(i, 0, S.length()) {
			height += 2 * (S[i] == '(') - 1;
			ans &= height >= 0;
		}
		cout << (ans ? "NO" : "YES") << '\n';
	}

	return 0;
}
