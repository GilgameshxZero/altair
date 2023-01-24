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
		LL N;
		cin >> N;
		vector<LL> A(N + 2);
		A[0] = 0;
		RF(i, 1, N + 1) {
			cin >> A[i];
		}
		A[N + 1] = N + 1;
		vector<pair<LL, LL>> B(N + 2);
		LL rev{0};
		RF(i, 1, N + 1) {
			B[A[i]] = {A[i - 1], A[i + 1]};
			if (A[i] > A[i + 1]) {
				++rev;
			}
		}
		LL ans{0};
		while (rev > 0) {
			LL i{1 + ans};
			B[B[i].first].second = B[i].second;
			B[B[i].second].first = B[i].first;
			rev -= (B[i].first > i);
			rev -= (i > B[i].second);
			rev += (B[i].first > B[i].second);

			if (1 + ans != N - ans) {
				i = N - ans;
				B[B[i].first].second = B[i].second;
				B[B[i].second].first = B[i].first;
				rev -= (B[i].first > i);
				rev -= (i > B[i].second);
				rev += (B[i].first > B[i].second);
			}

			ans++;
		}

		cout << ans << '\n';
	}

	return 0;
}
