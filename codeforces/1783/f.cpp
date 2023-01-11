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
	cin >> N;
	vector<LL> A(N), B(N);
	RF(i, 0, N) {
		cin >> A[i];
	}
	RF(i, 0, N) {
		cin >> B[i];
	}

	vector<unordered_set<LL>> groups;
	vector<bool> visA(N), visB(N);
	unordered_map<LL, unordered_set<LL>> rm;
	RF(i, 0, N) {
		if (A[i] == i + 1) {
			visA[i] = true;
		}
		if (visA[i]) {
			continue;
		}
		groups.push_back({i});
		rm[i].insert(groups.size() - 1);
		LL j{i};
		while (A[j] - 1 != i) {
			j = A[j] - 1;
			visA[j] = true;
			groups.back().insert(j);
			rm[j].insert(groups.size() - 1);
		}
	}
	RF(i, 0, N) {
		if (B[i] == i + 1) {
			visB[i] = true;
		}
		if (visB[i]) {
			continue;
		}
		groups.push_back({i});
		rm[i].insert(groups.size() - 1);
		LL j{i};
		while (B[j] - 1 != i) {
			j = B[j] - 1;
			visB[j] = true;
			groups.back().insert(j);
			rm[j].insert(groups.size() - 1);
		}
	}

	vector<LL> ans;
	for (auto &i : rm) {
		if (i.second.size() == 0) {
			continue;
		}
		if (i.second.size() == 1) {
			continue;
		}
		ans.push_back(i.first + 1);
		LL first{*i.second.begin()}, second{*next(i.second.begin())};
		groups[first].erase(i.first);
		if (groups[first].size() == 1) {
			rm[*groups[first].begin()].erase(first);
		}
		groups[second].erase(i.first);
		if (groups[second].size() == 1) {
			rm[*groups[second].begin()].erase(second);
		}
		i.second.clear();
	}
	for (auto &i : rm) {
		if (i.second.size() == 0) {
			continue;
		}
		ans.push_back(i.first + 1);
		LL first{*i.second.begin()};
		groups[first].erase(i.first);
		if (groups[first].size() == 1) {
			rm[*groups[first].begin()].erase(first);
		}
	}

	cout << ans.size() << '\n';
	RF(i, 0, ans.size()) {
		cout << ans[i] << ' ';
	}

	return 0;
}
