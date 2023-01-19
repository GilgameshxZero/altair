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
		string S;
		cin >> S;
		LL ct{0};
		RF(i, 0, S.size() - 1) {
			ct += S[i] != S[i + 1];
		}
		if (ct == 0) {
			cout << S[0] << ' ' << S[0] << ' ' << S.substr(2, S.size() - 2) << '\n';
		} else if (ct == 1) {
			LL chi;
			RF(i, 0, S.size() - 1) {
				if (S[i] != S[i + 1]) {
					chi = i;
					break;
				}
			}
			if (chi == 0) {
				cout << S[0] << ' ';
				if (S[0] == 'a') {
					cout << string(S.size() - 2, 'b') << ' ' << 'b' << '\n';
				} else {
					cout << 'a' << ' ' << string(S.size() - 2, 'a') << '\n';
				}
			} else {
				if (S[0] == 'a') {
					cout << string(chi, 'a') << ' ' << 'a' << ' '
							 << string(S.size() - chi - 1, 'b') << '\n';
				} else {
					cout << 'b' << ' ' << string(chi, 'b') << ' '
							 << string(S.size() - chi - 1, 'a') << '\n';
				}
			}
		} else {
			LL c1, c2;
			RF(i, 0, S.size() - 1) {
				if (S[i] != S[i + 1]) {
					c1 = i;
					break;
				}
			}
			RF(i, c1 + 1, S.size() - 1) {
				if (S[i] != S[i + 1]) {
					c2 = i;
					break;
				}
			}
			cout << S.substr(0, c1 + 1) << ' ' << S.substr(c1 + 1, c2 - c1) << ' '
					 << S.substr(c2 + 1, S.size() - c2 - 1) << '\n';
		}
	}

	return 0;
}
