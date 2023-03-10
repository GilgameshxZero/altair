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
		LL N, M;
		cin >> N >> M;
		vector<vector<LL>> A(N);
		RF(i, 0, N) {
			A[i].resize(M + 3);
			RF(j, 0, M) {
				cin >> A[i][j];
			}
		}
		RF(i, 0, M) {
			LL minA{LLONG_MAX};
			RF(j, 0, N) {
				minA = min(minA, A[j][i]);
			}
			RF(j, 0, N) {
				LL delta{A[j][i] - minA};
				A[j][i] -= delta;
				A[j][i + 1] += 2 * delta;
				A[j][i + 2] -= delta;
			}
		}

		LL ans1;
		RF(i, 0, N) {
			if (A[i][M] == 0 && A[i][M + 1] == 0 && A[i][M + 2] == 0) {
				ans1 = i;
				break;
			}
		}

		LL a2t{ans1 == 0 ? 1 : 0};
		cout << ans1 + 1 << ' ' << abs(A[a2t][M]) + abs(A[a2t][M + 2]) << '\n';
	}

	return 0;
}
