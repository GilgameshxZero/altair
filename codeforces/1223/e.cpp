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

pair<LL, LL> dfs(vector<unordered_map<LL, LL>> &E, LL K, LL cur, LL par) {
	vector<pair<LL, pair<LL, LL>>> delta;
	LL ssum{0};
	for (auto const &i : E[cur]) {
		if (i.first == par) {
			continue;
		}
		auto res = dfs(E, K, i.first, cur);
		delta.push_back({res.second - res.first + i.second, res});
		ssum += res.first;
	}
	sort(delta.begin(), delta.end(), greater<pair<LL, pair<LL, LL>>>());
	LL a2{ssum};
	RF(i, 0, min((LL)delta.size(), K - 1)) {
		if (delta[i].first < 0) {
			break;
		}
		a2 += delta[i].first;
	}
	LL a1{a2};
	if (delta.size() >= K && delta[K - 1].first > 0) {
		a1 += delta[K - 1].first;
	}
	return {a1, a2};
}

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
		LL N, K;
		cin >> N >> K;
		vector<unordered_map<LL, LL>> E(N);
		RF(i, 0, N - 1) {
			LL U, V, W;
			cin >> U >> V >> W;
			E[U - 1][V - 1] = W;
			E[V - 1][U - 1] = W;
		}
		cout << dfs(E, K, 0, -1).first << '\n';
	}

	return 0;
}
