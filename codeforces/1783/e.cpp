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

	LL T;
	cin >> T;
	while (T--) {
		LL N;
		cin >> N;
		vector<LL> A(N), B(N);
		RF(i, 0, N) {
			cin >> A[i];
		}
		vector<pair<LL, LL>> C;
		RF(i, 0, N) {
			cin >> B[i];
			if (B[i] < A[i]) {
				C.emplace_back(B[i], A[i]);
			}
		}
		sort(C.begin(), C.end());
		vector<bool> exc(N + 1, false);
		LL active{0}, cj1{0}, cj2{0};
		RF(i, 1, N + 1) {
			while (cj1 < C.size() && C[cj1].first <= i) {
				active++;
				cj1++;
			}
			while (cj2 < C.size() && C[cj2].second <= i) {
				active--;
				cj2++;
			}
			exc[i] = active > 0;
		}
		vector<bool> okay(N + 1, true);
		RF(i, N, 0) {
			if (okay[i] && exc[i]) {
				for (LL j{1}; j * j <= i; j++) {
					if (i % j == 0) {
						okay[j] = false;
						okay[i / j] = false;
					}
				}
			}
		}
		LL ans{0};
		RF(i, 1, N + 1) {
			ans += okay[i];
		}
		cout << ans << '\n';
		RF(i, 1, N + 1) {
			if (okay[i]) {
				cout << i << ' ';
			}
		}
		cout << '\n';
	}

	return 0;
}
