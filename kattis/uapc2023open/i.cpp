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

	LL N, M, P;
	cin >> N >> M >> P;
	vector<multiset<LL>> cards(N);
	vector<pair<string, LL>> names(N);
	vector<LL> order(N);
	RF(i, 0, N) {
		cin >> names[i].first;
		names[i].second = i;
		RF(j, 0, M) {
			LL X;
			cin >> X;
			cards[i].insert(X);
		}
	}
	sort(names.begin(), names.end());
	RF(i, 0, N) {
		order[names[i].second] = i;
	}
	vector<string> ans;
	RF(i, 0, N * M) {
		pair<LL, LL> smallest{LLONG_MAX, 0};
		RF(j, 0, N) {
			if (cards[j].empty()) {
				continue;
			}
			smallest = min(smallest, {*cards[j].begin(), order[j]});
		}
		LL spec{names[smallest.second].second};
		cards[spec].erase(cards[spec].begin());
		if (cards[spec].empty()) {
			ans.push_back(names[smallest.second].first);
		}
		RF(j, 0, N) {
			if (cards[j].empty() || j == spec) {
				continue;
			}
			LL topen{*cards[j].begin()};
			cards[j].erase(cards[j].begin());
			cards[j].insert(topen + P);
		}
	}

	RF(i, 0, ans.size()) {
		cout << ans[i] << ' ';
	}

	return 0;
}
