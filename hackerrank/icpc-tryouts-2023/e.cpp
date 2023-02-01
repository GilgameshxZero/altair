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
#include <type_traits>
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

// LL const INF{1000000000};

// void dfs(
// 	vector<unordered_set<LL>> &E,
// 	vector<LL> &unlit,
// 	vector<LL> &lit,
// 	vector<LL> &underlit,
// 	LL cur,
// 	LL par) {
// 	LL sumUnlit{0};
// 	for (auto const &i : E[cur]) {
// 		if (i == par) {
// 			continue;
// 		}
// 		dfs(E, unlit, lit, underlit, i, cur);
// 		sumUnlit += unlit[i];
// 		lit[cur] += underlit[i];
// 	}

// 	for (auto const &i : E[cur]) {
// 		if (i == par) {
// 			continue;
// 		}
// 		unlit[cur] = min(unlit[cur], sumUnlit - unlit[i] + lit[i]);
// 	}
// 	lit[cur]++;
// 	underlit[cur] = sumUnlit;

// 	unlit[cur] = min(unlit[cur], lit[cur]);
// 	underlit[cur] = min(underlit[cur], unlit[cur]);
// }

LL dfs(vector<unordered_set<LL>> &E, vector<LL> &dist, LL cur, LL par) {
	if (E[cur].size() == 1 && par != -1) {
		dist[cur] = 2;
		return 0;
	}

	LL maxDist{0}, ret{0};
	for (auto const &i : E[cur]) {
		if (i == par) {
			continue;
		}
		ret += dfs(E, dist, i, cur);
		maxDist = max(maxDist, dist[i] + 1);
	}
	return ret + ((dist[cur] = (maxDist == 3 ? 0 : maxDist)) == 0);
}

int main(int, char const *[]) {
#if !defined(ONLINEJUDGE) && (defined(__APPLE__) || defined(__MACH__))
	std::freopen("../build/i.default.txt", "r", stdin);
	std::freopen("../build/o.default.txt", "w", stdout);
#endif

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	LL N, E;
	cin >> N >> E;

	vector<LL> scans;
	RF(i, 0, N) {
		LL R;
		cin >> R;
		vector<unordered_set<LL>> E(R);
		RF(i, 0, R - 1) {
			LL U, V;
			cin >> U >> V;
			E[U].insert(V);
			E[V].insert(U);
		}

		vector<LL> dist(R);
		scans.push_back(R == 1 ? 1 : dfs(E, dist, 0, -1));
		scans.back() += dist[0] == 2;

		// vector<LL> unlit(R, INF), lit(R, 0), underlit(R);
		// dfs(E, unlit, lit, underlit, 0, -1);
		// scans.push_back(unlit[0]);
	}

	sort(scans.begin(), scans.end());
	LL sum{0};
	RF(i, 0, N) {
		sum += scans[i];
		if (sum > E) {
			cout << i;
			return 0;
		}
	}
	cout << N;
	return 0;
}
