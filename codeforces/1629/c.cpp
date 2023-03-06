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
		cin >> N;
		vector<LL> A(N);
		RF(i, 0, N) {
			cin >> A[i];
		}
		vector<bool> seen(N + 1, false);
		LL curmex{0};
		vector<LL> postmex(N);
		RF(i, N - 1, -1) {
			seen[A[i]] = true;
			while (seen[curmex]) {
				curmex++;
			}
			postmex[i] = curmex;
		}
		fill(seen.begin(), seen.end(), false);

		vector<LL> ans;
		RF(i, 0, N) {
			curmex = 0;
			RF(j, i, N) {
				seen[A[j]] = true;
				while (seen[curmex]) {
					curmex++;
				}
				if (curmex == postmex[i]) {
					ans.push_back(curmex);
					RF(k, j, i - 1) {
						seen[A[k]] = false;
					}
					i = j;
					break;
				}
			}
		}

		cout << ans.size() << '\n';
		RF(i, 0, ans.size()) {
			cout << ans[i] << ' ';
		}
		cout << '\n';
	}

	return 0;
}
