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

#pragma hdrstop

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
		LL N, K, X;
		cin >> N >> K >> X;
		vector<LL> A(N);
		RF(i, 0, N) {
			cin >> A[i];
			A[i] -= X;
		}
		X *= 2;

		vector<array<LL, 21>> F(N + 1), G(N + 1);
		F[0][0] = G[0][0] = 0;
		F[0][1] = G[0][1] = -INT_MAX;
		RF(i, 0, N) {
			G[i + 1][0] = max(0LL, A[i] + G[i][0]);
			F[i + 1][0] = max(F[i][0], G[i + 1][0]);
			LL boundary{min(i + 2, K + 1)};
			if (boundary < 21) {
				F[i + 1][boundary] = G[i + 1][boundary] = -INT_MAX;
			}
			RF(j, 1, boundary) {
				G[i + 1][j] = max({0LL, A[i] + G[i][j], A[i] + X + G[i][j - 1]});
				F[i + 1][j] = max({F[i][j - 1], F[i][j], G[i + 1][j]});
			}
		}

		cout << F[N][K] << '\n';
	}

	return 0;
}
