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

bool flood(
	vector<vector<pair<LL, LL>>> &E,
	vector<bool> &vis,
	unordered_set<LL> &costs,
	LL cur,
	LL par) {
	vis[cur] = true;
	bool res{false};
	for (auto const &i : E[cur]) {
		if (i.first == par) {
			continue;
		}
		costs.insert(i.second);
		if (!vis[i.first]) {
			res |= flood(E, vis, costs, i.first, cur);
		} else {
			res = true;
		}
	}
	return res;
}

int main(int, char const *[]) {
#if !defined(ONLINEJUDGE) && (defined(__APPLE__) || defined(__MACH__))
	std::freopen("../build/i.default.txt", "r", stdin);
	std::freopen("../build/o.default.txt", "w", stdout);
#endif

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	LL N, M;
	cin >> N >> M;
	vector<vector<pair<LL, LL>>> E(N);
	vector<LL> costs;
	RF(i, 0, M) {
		LL U, V, C;
		cin >> U >> V >> C;
		E[U - 1].push_back({V - 1, costs.size()});
		E[V - 1].push_back({U - 1, costs.size()});
		costs.push_back(C);
	}

	vector<bool> vis(N, false);
	vector<pair<LL, LL>> comps;
	RF(i, 0, N) {
		if (vis[i]) {
			continue;
		}
		LL sum{0}, smallest{LLONG_MAX / 10};
		unordered_set<LL> c;
		bool res{flood(E, vis, c, i, -1)};
		for (auto const &j : c) {
			sum += costs[j];
			smallest = min(smallest, costs[j]);
		}
		comps.push_back({sum, res ? smallest : 0});
	}

	if (comps.size() == 1) {
		cout << comps[0].first;
	} else {
		LL ans{0};
		RF(i, 0, comps.size()) {
			ans += comps[i].first - comps[i].second;
		}
		cout << ans;
	}

	return 0;
}
