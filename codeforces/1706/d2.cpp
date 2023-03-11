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

	vector<vector<LL>> update(100001);
	vector<LL> cnt(100001);

	LL T;
	cin >> T;
	while (T--) {
		LL N, K;
		cin >> N >> K;
		vector<LL> A(N);
		LL minA{LLONG_MAX / 10};
		LL minS, maxS{0};
		RF(i, 0, N) {
			cin >> A[i];
			cnt[A[i]]++;
			minA = min(minA, A[i]);
			maxS = max(maxS, A[i]);
		}
		minS = minA;
		vector<LL> B{A}, C(N, 1);
		LL p2{0};
		RF(i, 0, N) {
			if (K >= 2) {
				update[A[i] / 2].push_back(i);
				p2 = max(p2, A[i] / 2);
			}
		}
		LL sweep{minA}, ans{LLONG_MAX / 10};
		for (; sweep >= 0; sweep--) {
			for (; p2 >= sweep; p2--) {
				while (!update[p2].empty()) {
					LL i{update[p2].back()};
					C[i] = A[i] / B[i] + 1;
					cnt[B[i]]--;
					while (cnt[maxS] == 0) {
						maxS--;
					}
					B[i] = A[i] / C[i];
					cnt[B[i]]++;
					minS = min(minS, B[i]);
					maxS = max(maxS, B[i]);
					update[p2].pop_back();
					if (B[i] == 0) {
						continue;
					}
					LL cand{A[i] / B[i] + 1};
					if (cand <= K) {
						update[A[i] / cand].push_back(i);
					}
				}
				update[p2].shrink_to_fit();
			}
			ans = min(ans, maxS - minS);
		}
		cout << ans << '\n';
		for (; p2 >= 0; p2--) {
			update[p2].clear();
			update[p2].shrink_to_fit();
		}
		for (; maxS >= minS; maxS--) {
			cnt[maxS] = 0;
		}
	}

	return 0;
}
