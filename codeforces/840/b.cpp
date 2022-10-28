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

#define RF(x, from, to) \
	for (long long x = from, rfDir = from < to ? 1 : -1; x != to; x += rfDir)

using namespace std;

/* ---------------------------- End of template. ---------------------------- */

bool dfs(
	vector<unordered_map<LL, LL>> &edges,
	vector<bool> &toggle,
	vector<bool> &visited,
	unordered_set<LL> &sinks,
	LL cur,
	LL par) {
	bool parity{sinks.find(cur) != sinks.end()};
	visited[cur] = true;
	for (auto const &edge : edges[cur]) {
		if (edge.first == par) {
			continue;
		}
		if (visited[edge.first]) {
			continue;
		}
		bool result{dfs(edges, toggle, visited, sinks, edge.first, cur)};
		toggle[edge.second] = toggle[edge.second] ^ result;
		parity ^= result;
	}
	return parity;
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
	vector<LL> D(N);
	LL wild{-1}, cOdd{0};
	RF(i, 0, N) {
		cin >> D[i];
		if (D[i] == -1) {
			wild = i;
		}
		cOdd += D[i] == 1;
	}
	if (wild == -1 && cOdd % 2 == 1) {
		cout << "-1";
		return 0;
	}
	if (cOdd == 0) {
		cout << "0";
		return 0;
	}

	vector<unordered_map<LL, LL>> edges(N);
	vector<bool> toggle(M, false), visited(N, false);
	RF(i, 0, M) {
		LL U, V;
		cin >> U >> V;
		edges[U - 1][V - 1] = i;
		edges[V - 1][U - 1] = i;
	}

	LL source;
	unordered_set<LL> sinks;
	if (wild == -1) {
		RF(i, 0, N) {
			if (D[i] == 1) {
				sinks.insert(i);
			}
		}
		source = *sinks.begin();
		sinks.erase(source);
	} else {
		source = wild;
		RF(i, 0, N) {
			if (D[i] == 1) {
				sinks.insert(i);
			}
		}
	}

	dfs(edges, toggle, visited, sinks, source, -1);
	LL cTog{0};
	RF(i, 0, M) {
		cTog += toggle[i];
	}
	cout << cTog << '\n';
	RF(i, 0, M) {
		if (toggle[i]) {
			cout << i + 1 << '\n';
		}
	}

	return 0;
}
