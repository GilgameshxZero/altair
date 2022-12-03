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

class StringReduction {
	public:
	static int reduce(string start, vector<int> X, string Y) {
		map<int, int> cnt;
		for (auto &i : start) {
			cnt[i]++;
		}
		map<int, vector<int>> avail;
		for (int i = 0; i < Y.size(); i++) {
			avail[Y[i]].push_back(X[i] - 1);
		}
		map<int, vector<bool>> possible;
		for (auto &i : avail) {
			possible[i.first].resize(2501);
			for (int j = 0; j <= 2500; j++) {
				for (auto &k : i.second) {
					if (j - k < 0) continue;
					if (j - k == 0) {
						possible[i.first][j] = true;
						continue;
					}
					possible[i.first][j] =
						possible[i.first][j] || possible[i.first][j - k];
				}
			}
		}
		int ans = start.size();
		for (auto &i : cnt) {
			for (int j = i.second - 1; j > 0; j--) {
				if (possible[i.first].size() > j && possible[i.first][j]) {
					ans -= j;
					break;
				}
			}
		}
		return ans;
	}
};

int main(int, char const *[]) {
#if !defined(ONLINEJUDGE) && (defined(__APPLE__) || defined(__MACH__))
	std::freopen("../build/i.default.txt", "r", stdin);
	std::freopen("../build/o.default.txt", "w", stdout);
#endif

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	cout << StringReduction::reduce("abba", {2}, "a") << endl;
	cout << StringReduction::reduce("bbbxbbbx", {3, 2, 1}, "bxx") << endl;

	return 0;
}
