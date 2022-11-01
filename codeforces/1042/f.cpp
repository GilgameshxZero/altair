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

LL N, K;
vector<vector<LL>> E;
vector<bool> cut;

LL dfs(LL cur, LL par) {
	vector<pair<LL, LL>> subhs;
	RF(i, 0, E[cur].size()) {
		if (E[cur][i] == par) {
			continue;
		}
		LL subh{dfs(E[cur][i], cur)};
		if (!cut[E[cur][i]]) {
			subhs.push_back({subh, E[cur][i]});
		}
	}
	if (subhs.size() == 0) {
		return 0;
	} else {
		sort(subhs.begin(), subhs.end());
		while (true) {
			if (subhs.size() == 1) {
				if (subhs[0].first + 1 > K) {
					cut[subhs[0].second] = true;
					return 0;
				} else {
					return subhs[0].first + 1;
				}
			} else {
				if (subhs.back().first + subhs[subhs.size() - 2].first + 2 > K) {
					cut[subhs.back().second] = true;
					subhs.pop_back();
				} else {
					return subhs.back().first + 1;
				}
			}
		}
	}
}

int main(int, char const *[]) {
#if !defined(ONLINEJUDGE) && (defined(__APPLE__) || defined(__MACH__))
	std::freopen("../build/i.default.txt", "r", stdin);
	std::freopen("../build/o.default.txt", "w", stdout);
#endif

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	cin >> N >> K;
	cut.resize(N, false);
	E.resize(N);
	RF(i, 0, N - 1) {
		LL U, V;
		cin >> U >> V;
		E[U - 1].push_back(V - 1);
		E[V - 1].push_back(U - 1);
	}
	dfs(0, -1);
	cut[0] = true;
	LL ans{0};
	RF(i, 0, N) {
		ans += cut[i];
	}
	cout << ans;
	return 0;
}
