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
		string A, B;
		cin >> N >> A >> B;
		bool xt((bool)(A[0] - '0') ^ (bool)(B[0] - '0')), possible{true};
		RF(i, 1, N) {
			possible &= xt == ((bool)(A[i] - '0') ^ (bool)(B[i] - '0'));
		}
		if (!possible) {
			cout << "NO\n";
			continue;
		}
		cout << "YES\n";
		vector<pair<LL, LL>> ans;
		RF(i, 1, N) {
			if (A[i] != A[0]) {
				ans.push_back({i + 1, i + 1});
			}
		}
		if (ans.size() % 2 == 1) {
			B[0] = (B[0] == '0' ? '1' : '0');
		}
		if (A[0] == '0' && B[0] == '1') {
			ans.push_back({1, N});
			ans.push_back({1, 1});
			ans.push_back({2, N});
		} else if (A[0] == '1' && B[0] == '0') {
			ans.push_back({1, N});
		} else if (A[0] == '1' && B[0] == '1') {
			ans.push_back({1, 1});
			ans.push_back({2, N});
		}
		cout << ans.size() << '\n';
		RF(i, 0, ans.size()) {
			cout << ans[i].first << ' ' << ans[i].second << '\n';
		}
	}

	return 0;
}
