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
	// std::cin.tie(nullptr);

	LL T, jury;
	cin >> T;
	while (T--) {
		LL N;
		cin >> N;

		if (N == 2) {
			cout << "! 1 2" << endl;
			cin >> jury;
			if (jury == -1) {
				return 0;
			}
			continue;
		}

		LL pivot;
		vector<pair<LL, LL>> possible;
		vector<LL> tc;
		RF(i, 2, N) {
			cout << "? 1 " << i + 1 << endl;
			cin >> jury;
			if (jury != 1) {
				pivot = 0;
				possible.emplace_back(i, jury);
				tc.push_back(1);
				break;
			}
			cout << "? 2 " << i + 1 << endl;
			cin >> jury;
			if (jury != 1) {
				pivot = 1;
				possible.emplace_back(i, jury);
				break;
			}
		}
		if (possible.empty()) {
			cout << "! 1 2" << endl;
			cin >> jury;
			if (jury == -1) {
				return 0;
			}
			continue;
		}
		RF(i, possible.back().first + 1, N) {
			tc.push_back(i);
		}

		while (true) {
			RF(i, 0, tc.size()) {
				cout << "? " << pivot + 1 << ' ' << tc[i] + 1 << endl;
				cin >> jury;
				if (jury > possible.back().second) {
					possible.clear();
					possible.emplace_back(tc[i], jury);
				} else if (jury == possible.back().second) {
					possible.emplace_back(tc[i], jury);
				}
			}
			if (possible.size() == 1) {
				cout << "! " << pivot + 1 << ' ' << possible[0].first + 1 << endl;
				cin >> jury;
				if (jury == -1) {
					return 0;
				}
				break;
			}

			tc.clear();
			pivot = possible[0].first;
			LL tmp{possible[1].first};
			cout << "? " << pivot + 1 << ' ' << tmp + 1 << endl;
			cin >> jury;
			RF(i, 2, possible.size()) {
				tc.push_back(possible[i].first);
			}
			possible.clear();
			possible.emplace_back(tmp, jury);
		}
	}

	return 0;
}
