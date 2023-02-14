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

/* ---------------------------- End of template. ---------------------------- */

int main(int, char const *[]) {
#if !defined(ONLINEJUDGE) && (defined(__APPLE__) || defined(__MACH__))
	std::freopen("../build/i.default.txt", "r", stdin);
	std::freopen("../build/o.default.txt", "w", stdout);
#endif

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	LL N;
	cin >> N;
	vector<LL> A(N);
	RF(i, 0, N) {
		cin >> A[i];
	}
	sort(A.begin(), A.end());

	vector<LL> _mg(N + 1), _mmg(N + 1);
	LL *mg{_mg.data() + 1}, *mmg{_mmg.data() + 1};
	mg[-1] = 0;
	mmg[-1] = 0;
	RF(i, 0, N) {
		if (A[i] > i + 1) {
			mg[i] = -1;
		} else {
			mg[i] = mmg[i - A[i]] + 1;
		}
		mmg[i] = max(mmg[i - 1], mg[i]);
	}

	vector<LL> d(N);
	d[N - 1] = mg[N - 1];
	RF(i, N - 2, -1) {
		d[i] = max(d[i + 1], mg[i] == -1 ? N - A[i] + 1 : mg[i] + N - 1 - i);
	}
	reverse(d.begin(), d.end());

	LL Q;
	cin >> Q;
	RF(i, 0, Q) {
		LL k;
		cin >> k;
		auto ans{lower_bound(d.begin(), d.end(), k) - d.begin()};
		cout << N - ans << '\n';
	}

	return 0;
}
