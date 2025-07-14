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

	LL N, M;
	cin >> N >> M;
	vector<LL> A(N);
	RF(i, 0, N) {
		cin >> A[i];
	}

	vector<vector<LL>> md(N, vector<LL>(M + 1, 1000000000));
	vector<LL> gd(M + 1, 1000000000);
	if (A[0] <= M) {
		md[0][A[0]] = 0;
	}
	RF(i, 1, N) {
		if (A[i] <= M) {
			md[i][A[i]] = 1;
		}
		for (LL j{A[i] + 1}; j < M + 1; j++) {
			LL target{j - A[i]};
			md[i][j] = min(md[i - 1][target], 1 + gd[target]);
		}
		RF(j, 0, M + 1) {
			gd[j] = min(gd[j], md[i - 1][j]);
		}
	}
	RF(i, 1, M + 1) {
		LL t{min(1 + gd[i], md[N - 1][i])};
		cout << (t == 1000000000 ? -1 : t) << '\n';
	}
	return 0;
}
