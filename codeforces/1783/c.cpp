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
		LL N, M;
		cin >> N >> M;
		vector<pair<LL, LL>> A(N);
		RF(i, 0, N) {
			cin >> A[i].first;
			A[i].second = i;
		}
		A.push_back({1000000000, N});
		sort(A.begin(), A.end());
		vector<LL> ps(N + 2);
		ps[0] = 0;
		RF(i, 0, N + 1) {
			ps[i + 1] = ps[i] + A[i].first;
		}
		LL wins{0};
		while (ps[wins + 1] <= M) {
			wins++;
		}
		if (wins == 0) {
			cout << N + 1 << '\n';
		} else if (wins == N) {
			cout << "1\n";
		} else {
			bool beatable{false};
			RF(i, 0, wins) {
				if (A[i].second == wins) {
					beatable = true;
					break;
				}
			}
			if (!beatable) {
				RF(i, wins - 1, N) {
					if (A[i].second == wins && A[i].first + ps[wins - 1] <= M) {
						beatable = true;
						break;
					}
				}
			}
			cout << N - wins + 1 + (beatable ? -1 : 0) << '\n';
		}
	}

	return 0;
}
