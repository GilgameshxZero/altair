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
		LL N;
		cin >> N;
		string S, T;
		cin >> S >> T;
		if (S[0] != T[0] || S.back() != T.back()) {
			cout << "-1\n";
			continue;
		}

		set<LL> flippable;
		RF(i, 1, N - 1) {
			if (S[i - 1] != S[i + 1]) {
				flippable.insert(i);
			}
		}

		vector<LL> rte(N + 1);
		LL ans{0}, toggles{0};
		bool possible{true};

		auto calc{[&](LL i) { return '0' + ((S[i] - '0' + toggles) % 2); }};
		auto tflip{[&](LL i) {
			if (i <= 0 || i >= N - 1) {
				return;
			}
			if (flippable.count(i)) {
				flippable.erase(i);
			} else {
				flippable.insert(i);
			}
		}};

		RF(i, 1, N - 1) {
			toggles -= rte[i];
			if (calc(i) == T[i]) {
				continue;
			}
			auto it{flippable.lower_bound(i)};
			if (it == flippable.end()) {
				possible = false;
				break;
			}
			auto j{*it};
			ans += j - i + 1;
			rte[j + 1]++;
			toggles++;
			tflip(i - 1);
			tflip(i);
			tflip(j);
			tflip(j + 1);
		}
		cout << (possible ? ans : -1) << '\n';
	}

	return 0;
}
