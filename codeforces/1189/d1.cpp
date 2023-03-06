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

using LL = long long;
using LD = long double;

#define RF(x, from, to)                                                      \
	for (long long x = from, _to = to, _delta{x < _to ? 1LL : -1LL}; x != _to; \
			 x += _delta)

using namespace std;

/* ------------------------ End of primary template. ------------------------ */

void findLeaves(
	bool &possible,
	vector<vector<LL>> &E,
	vector<bool> &isLeaf,
	vector<LL> &cLeaves,
	vector<LL> &cSize,
	LL cur,
	LL par) {
	if (E[cur].size() <= 1) {
		isLeaf[cur] = true;
	}
	RF(i, 0, E[cur].size()) {
		if (par == E[cur][i]) {
			continue;
		}
		findLeaves(possible, E, isLeaf, cLeaves, cSize, E[cur][i], cur);
		cLeaves[cur] += cLeaves[E[cur][i]];
		cSize[cur] += cSize[E[cur][i]];
	}
	cLeaves[cur] += isLeaf[cur];
	cSize[cur]++;

	if (E[cur].size() == 2) {
		possible = false;
	}
}

int main(int, char const *[]) {
#if !defined(ONLINEJUDGE) && (defined(__APPLE__) || defined(__MACH__))
	std::freopen("../build/i.default.txt", "r", stdin);
	std::freopen("../build/o.default.txt", "w", stdout);
#endif

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	LL N;
	cin >> N;
	if (N == 2) {
		cout << "YES";
		return 0;
	}
	vector<vector<LL>> E(N);
	RF(i, 0, N - 1) {
		LL U, V;
		cin >> U >> V;
		E[U - 1].push_back(V - 1);
		E[V - 1].push_back(U - 1);
	}
	vector<bool> isLeaf(N, false);
	vector<LL> cLeaves(N, 0), cSize(N, 0);
	bool possible{true};
	findLeaves(possible, E, isLeaf, cLeaves, cSize, 0, -1);
	cout << (possible ? "YES" : "NO");

	return 0;
}
