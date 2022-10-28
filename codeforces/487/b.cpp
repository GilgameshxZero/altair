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

	LL N, S, L;
	cin >> N >> S >> L;
	vector<LL> A(N);
	RF(i, 0, N) {
		cin >> A[i];
	}
	if (L > N) {
		cout << -1;
		return 0;
	}

	vector<LL> ans(N + 1, 1000000000);
	multiset<LL> As, as;
	ans[0] = 0;
	RF(i, 0, L - 1) {
		As.insert(A[i]);
	}
	LL lagger{0}, l2{0};
	RF(i, L, N + 1) {
		As.insert(A[i - 1]);
		while (!As.empty() && *As.rbegin() - *As.begin() > S) {
			As.erase(As.find(A[lagger++]));
		}
		as.insert(ans[i - L]);
		while (!as.empty() && l2 < lagger) {
			as.erase(as.find(ans[l2++]));
		}
		if (l2 == lagger && !as.empty() && As.size() >= L) {
			ans[i] = *as.begin() + 1;
		}
	}
	cout << (ans[N] >= 1000000000 ? -1 : ans[N]);
	return 0;
}
