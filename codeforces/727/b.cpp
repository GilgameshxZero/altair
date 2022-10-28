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

	string S;
	cin >> S;
	vector<string> prices;
	prices.push_back("");
	RF(i, 0, S.size()) {
		if (S[i] == '.' || (S[i] >= '0' && S[i] <= '9')) {
			prices.back().push_back(S[i]);
		} else if (!prices.back().empty()) {
			prices.push_back("");
		}
	}

	LL cents{0};
	RF(i, 0, prices.size()) {
		LL cc{0};
		auto x = prices[i].find_last_of('.');
		if (prices[i].find_last_of('.') == string::npos) {
			RF(j, 0, prices[i].size()) {
				cc = cc * 10 + prices[i][j] - '0';
			}
			cc *= 100;
		} else if (prices[i].find_last_of('.') == prices[i].size() - 3) {
			RF(j, 0, prices[i].size()) {
				if (prices[i][j] == '.') {
					continue;
				}
				cc = cc * 10 + prices[i][j] - '0';
			}
		} else {
			RF(j, 0, prices[i].size()) {
				if (prices[i][j] == '.') {
					continue;
				}
				cc = cc * 10 + prices[i][j] - '0';
			}
			cc *= 100;
		}
		cents += cc;
	}

	if (cents < 10) {
		cout << "0.0" << cents;
	} else if (cents < 100) {
		cout << "0." << cents;
	} else if (cents % 100 == 0) {
		LL dollars{cents / 100};
		string sd{to_string(dollars)};
		reverse(sd.begin(), sd.end());
		for (LL i{3}; i < sd.size(); i += 3) {
			sd.insert(sd.begin() + i++, '.');
		}
		reverse(sd.begin(), sd.end());
		cout << sd;
	} else {
		string sd{to_string(cents)};
		reverse(sd.begin(), sd.end());
		for (LL i{2}; i < sd.size(); i += 3) {
			sd.insert(sd.begin() + i++, '.');
		}
		reverse(sd.begin(), sd.end());
		cout << sd;
	}
	return 0;
}
