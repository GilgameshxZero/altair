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

bool detect(
	vector<unordered_set<LL>> &E,
	unordered_set<LL> &vis,
	unordered_set<LL> &s,
	LL cur) {
	s.insert(cur);
	vis.insert(cur);
	for (auto &i : E[cur]) {
		if (s.count(i)) {
			return true;
		}
		if (!vis.count(i) && detect(E, vis, s, i)) {
			return true;
		}
	}
	s.erase(cur);
	return false;
}

int main(int, char const *[]) {
#if !defined(ONLINEJUDGE) && (defined(__APPLE__) || defined(__MACH__))
	std::freopen("../build/i.default.txt", "r", stdin);
	std::freopen("../build/o.default.txt", "w", stdout);
#endif

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	LL H, W;
	cin >> H >> W;
	vector<unordered_set<LL>> RE(W * (H + 1) + H), CE(H * (W + 1) + W);
	vector<vector<LL>> A(H, vector<LL>(W));
	RF(i, 0, H) {
		RF(j, 0, W) {
			cin >> A[i][j];
		}
	}
	RF(i, 0, H) {
		RF(j, 0, W) {
			CE[i * (W + 1) + j].insert(i * (W + 1) + j + 1);
		}
		vector<pair<LL, LL>> t;
		RF(j, 0, W) {
			if (A[i][j] == 0) {
				continue;
			}
			t.push_back({A[i][j], j});
		}
		sort(t.begin(), t.end());
		LL lag{0};
		RF(j, 0, t.size()) {
			if (j != 0 && t[j].first != t[j - 1].first) {
				lag = j;
			}
			CE[i * (W + 1) + lag].insert(H * (W + 1) + t[j].second);
			CE[H * (W + 1) + t[j].second].insert(i * (W + 1) + lag + 1);
		}
	}
	unordered_set<LL> vis, s;
	if (detect(CE, vis, s, 0)) {
		cout << "No";
		return 0;
	}
	vis.clear();
	s.clear();
	RF(i, 0, W) {
		RF(j, 0, H) {
			RE[i * (H + 1) + j].insert(i * (H + 1) + j + 1);
		}
		vector<pair<LL, LL>> t;
		RF(j, 0, H) {
			if (A[j][i] == 0) {
				continue;
			}
			t.push_back({A[j][i], j});
		}
		sort(t.begin(), t.end());
		LL lag{0};
		RF(j, 0, t.size()) {
			if (j != 0 && t[j].first != t[j - 1].first) {
				lag = j;
			}
			RE[i * (H + 1) + lag].insert(W * (H + 1) + t[j].second);
			RE[W * (H + 1) + t[j].second].insert(i * (H + 1) + lag + 1);
		}
	}
	if (detect(RE, vis, s, 0)) {
		cout << "No";
		return 0;
	}
	cout << "Yes";
	return 0;
}
