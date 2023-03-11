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
		LL N, K;
		cin >> N >> K;
		vector<LL> A(N);
		RF(i, 0, N) {
			cin >> A[i];
		}
		vector<vector<LL>> pos(N);
		RF(i, 0, N) {
			RF(j, K, 0) {
				if (pos[i].empty() || pos[i].back() != A[i] / j) {
					pos[i].push_back(A[i] / j);
				}
			}
		}
		vector<LL> p2(N);
		LL ans{LLONG_MAX / 10};
		bool done{false};
		RF(i, 0, 3001) {
			LL pmin{LLONG_MAX / 10}, pmax{0};
			RF(j, 0, N) {
				while (p2[j] < pos[j].size() && pos[j][p2[j]] < i) {
					p2[j]++;
				}
				if (p2[j] == pos[j].size()) {
					done = true;
					break;
				}
				pmin = min(pmin, pos[j][p2[j]]);
				pmax = max(pmax, pos[j][p2[j]]);
			}
			if (done) {
				break;
			}
			ans = min(ans, pmax - pmin);
		}
		cout << ans << '\n';
	}

	return 0;
}
