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
		LL N, M;
		cin >> N >> M;
		string S;
		cin >> S;
		vector<LL> ngr(S.length(), 0);
		vector<LL> presum(S.length());
		ngr[0] = presum[0] = S[0] == '1';
		RF(i, 1, S.length()) {
			presum[i] = presum[i - 1] + (S[i] == '1');
		}
		RF(i, 1, M) {
			ngr[i] = (S[i] == '1' ? 1 : ngr[i - 1]);
		}
		RF(i, M, S.length()) {
			ngr[i] = ngr[i - M] + (presum[i] - presum[i - M] > 0);
		}
		vector<bool> col(M, false);
		LL colans{0};
		RF(i, 0, S.length()) {
			if (!col[i % M] && S[i] == '1') {
				col[i % M] = true;
				colans++;
			}
			cout << colans + ngr[i] << ' ';
		}
		cout << '\n';
	}

	return 0;
}
