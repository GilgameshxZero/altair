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

pair<LL, LL> bpc(
	vector<unordered_set<LL>> &E,
	unordered_set<LL> &bpc1,
	vector<LL> &par,
	LL cur) {
	bool add{bpc1.find(cur) == bpc1.end()};
	for (auto const &i : E[cur]) {
		if (i == par[cur]) {
			continue;
		}
		if (par[i] != -1) {
			return {cur, i};
		}
		par[i] = cur;
		if (add) {
			bpc1.insert(i);
		}
		auto res = bpc(E, bpc1, par, i);
		if (res.first != -1) {
			return res;
		}
	}
	return {-1, -1};
}

int main(int, char const *[]) {
#if !defined(ONLINEJUDGE) && (defined(__APPLE__) || defined(__MACH__))
	std::freopen("../build/i.default.txt", "r", stdin);
	std::freopen("../build/o.default.txt", "w", stdout);
#endif

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	LL N, M, K;
	cin >> N >> M >> K;
	vector<unordered_set<LL>> E(N);
	RF(i, 0, M) {
		LL U, V;
		cin >> U >> V;
		E[U - 1].insert(V - 1);
		E[V - 1].insert(U - 1);
	}

	unordered_set<LL> bpc1;
	vector<LL> par(N, -1);
	par[0] = -2;
	auto res = bpc(E, bpc1, par, 0);
	if (res.first == -1) {
		cout << "1\n";
		if (bpc1.size() >= (K + 1) / 2) {
			auto it = bpc1.begin();
			RF(i, 0, (K + 1) / 2) {
				cout << *it + 1 << ' ';
				it++;
			}
		} else {
			LL j{0};
			RF(i, 0, (K + 1) / 2) {
				while (bpc1.find(j) != bpc1.end()) {
					j++;
				}
				cout << j++ + 1 << ' ';
			}
		}
	} else {
		vector<LL> cycle;
		unordered_set<LL> anc2;
		LL cur{res.second};
		while (cur != -2) {
			anc2.insert(cur);
			cur = par[cur];
		}
		cur = res.first;
		while (anc2.find(cur) == anc2.end()) {
			cycle.push_back(cur);
			cur = par[cur];
		}
		cycle.push_back(cur);
		LL share{cur};
		reverse(cycle.begin(), cycle.end());
		cur = res.second;
		while (cur != share) {
			cycle.push_back(cur);
			cur = par[cur];
		}

		if (cycle.size() <= K) {
			cout << "2\n" << cycle.size() << '\n';
			RF(i, 0, cycle.size()) {
				cout << cycle[i] + 1 << ' ';
			}
		} else {
			cout << "1\n";
			RF(i, 0, (K + 1) / 2) {
				cout << cycle[i * 2] + 1 << ' ';
			}
		}
	}

	return 0;
}
