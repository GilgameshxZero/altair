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

void dfscolor(vector<vector<LL>> &E, vector<bool> &color, LL cur, LL par) {
	for (auto const &i : E[cur]) {
		if (i == par) {
			continue;
		}
		color[i] = !color[cur];
		dfscolor(E, color, i, cur);
	}
}

pair<LL, LL> dfsfar(vector<vector<LL>> &E, vector<LL> &pars, LL cur, LL par) {
	pair<LL, LL> far{0, cur};
	pars[cur] = par;
	for (auto const &i : E[cur]) {
		if (i == par) {
			continue;
		}
		auto ffar{dfsfar(E, pars, i, cur)};
		ffar.first++;
		far = max(far, ffar);
	}
	return far;
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
	vector<vector<LL>> E(N);
	RF(i, 0, N - 1) {
		LL U, V;
		cin >> U >> V;
		E[U - 1].push_back(V - 1);
		E[V - 1].push_back(U - 1);
	}

	if (N == 1) {
		cout << 1;
		return 0;
	}

	vector<bool> color(N);
	dfscolor(E, color, 0, -1);

	vector<LL> pars(N);
	auto dia1{dfsfar(E, pars, 0, -1).second};
	auto [dial, dia2]{dfsfar(E, pars, dia1, -1)};
	if (dial <= 2) {
		cout << -1;
		return 0;
	}

	LL d1{dia2}, d2{pars[pars[pars[d1]]]};

	vector<LL> cc[2];
	RF(i, 0, N) {
		cc[color[i]].push_back(i);
	}

	RF(i, 0, cc[color[d1]].size()) {
		if (cc[color[d1]][i] == d1) {
			continue;
		}
		cout << cc[color[d1]][i] + 1 << ' ';
	}
	cout << d1 + 1 << ' ' << d2 + 1 << ' ';
	RF(i, 0, cc[color[d2]].size()) {
		if (cc[color[d2]][i] == d2) {
			continue;
		}
		cout << cc[color[d2]][i] + 1 << ' ';
	}

	return 0;
}
