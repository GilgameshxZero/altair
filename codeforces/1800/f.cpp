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

#pragma hdrstop

/* ------------------------ End of primary template. ------------------------ */

int main(int, char const *[]) {
#if !defined(ONLINEJUDGE) && (defined(__APPLE__) || defined(__MACH__))
	std::freopen("../build/i.default.txt", "r", stdin);
	std::freopen("../build/o.default.txt", "w", stdout);
#endif

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	LL N;
	cin >> N;
	vector<string> S(N);
	vector<LL> exc[26];
	vector<array<LL, 26>> cnt(N);
	RF(i, 0, N) {
		cnt[i].fill(false);
		cin >> S[i];
		for (auto const &j : S[i]) {
			cnt[i][j - 'a']++;
		}
		RF(j, 0, 26) {
			if (cnt[i][j] == 0) {
				exc[j].push_back(i);
			}
		}
	}

	LL ans{0};
	RF(i, 0, 26) {
		unordered_map<LL, LL> hashes;
		RF(j, 0, exc[i].size()) {
			LL hash{0};
			RF(k, 0, 26) {
				hash += (cnt[exc[i][j]][k] & 1) << k;
			}
			LL target{0};
			RF(k, 0, 26) {
				target += (!(cnt[exc[i][j]][k] & 1)) << k;
			}
			target &= ~(1LL << i);

			ans += hashes[target];
			hashes[hash]++;
		}
	}
	cout << ans;

	return 0;
}
