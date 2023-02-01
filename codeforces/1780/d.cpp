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

	LL T;
	cin >> T;
	while (T--) {
		LL N;
		cin >> N;

		LL i{0}, prev{0}, n{0}, ans{0};
		while (n < N) {
			cout << "- " << (1LL << i) - prev << endl;
			cout.flush();
			prev = (1LL << i);
			LL cnt;
			cin >> cnt;
			if (cnt == N - 1) {
				ans += prev;
				n++;
			}
			i++;
		}
		cout << "! " << ans << endl;
		cout.flush();

		// LL ans{0};
		// while (true) {
		// 	LL N;
		// 	cin >> N;
		// 	if (N == 0) {
		// 		break;
		// 	}
		// 	if (N == 1) {
		// 		ans++;
		// 		break;
		// 	}
		// 	cout << "- " << (1LL << (N - 1)) << endl;
		// 	ans += (1LL << (N - 1));
		// }
		// cout << "! " << ans << endl;
	}

	return 0;
}
