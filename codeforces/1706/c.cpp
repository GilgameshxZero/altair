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
		LL N;
		cin >> N;
		vector<LL> A(N);
		RF(i, 0, N) {
			cin >> A[i];
		}
		vector<LL> prefix(N);
		prefix[0] = 0;
		for (LL i{1}; i < N - 1; i += 2) {
			LL mnh{max(A[i - 1], A[i + 1])};
			prefix[i] = prefix[i + 1] = prefix[i - 1] + max(0LL, mnh + 1 - A[i]);
		}
		LL ans{prefix[N - 2]};
		if (N % 2 == 0) {
			vector<LL> postfix(N);
			postfix[N - 1] = 0;
			for (LL i{N - 2}; i >= 1; i -= 2) {
				LL mnh{max(A[i - 1], A[i + 1])};
				postfix[i] = postfix[i - 1] = postfix[i + 1] + max(0LL, mnh + 1 - A[i]);
			}
			for (LL i{0}; i < N; i += 2) {
				ans = min(ans, prefix[i] + postfix[i + 1]);
			}
		}
		cout << ans << '\n';
	}

	return 0;
}
