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

	LL N;
	string S;
	cin >> N >> S;

	LL ld{0}, gd{0};
	RF(i, N - 1, -1) {
		if (S[i] == '0') {
			gd = gd * 2 + 1;
		} else {
			ld = ld * 2 + 1;
		}
	}

	RF(i, ld + 1, (1LL << N) - gd + 1) {
		cout << i << ' ';
	}
	return 0;

	// vector<LL> A(1LL << N);
	// RF(i, 0, A.size()) {
	// 	A[i] = i;
	// }

	// set<LL> ans;
	// do {
	// 	vector<LL> B(A);
	// 	RF(i, 0, N) {
	// 		RF(j, 0, (1LL << (N - i - 1))) {
	// 			if (
	// 				S[i] == '0' && B[j * 2 * (1LL << i)] > B[(j * 2 + 1) * (1LL << i)]
	// || 				S[i] == '1' && B[j * 2 * (1LL << i)] < B[(j * 2 + 1) * (1LL << i)]) {
	// 				swap(B[j * 2 * (1LL << i)], B[(j * 2 + 1) * (1LL << i)]);
	// 			}
	// 		}
	// 	}
	// 	ans.insert(B[0]);
	// } while (next_permutation(A.begin(), A.end()));

	// for (auto &i : ans) {
	// 	cout << i + 1 << ' ';
	// }

	return 0;
}
