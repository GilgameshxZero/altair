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

	vector<LL> primes;
	unordered_map<LL, LL> primeIdx;
	vector<LL> minFac(300001);
	minFac[0] = minFac[1] = 1;
	RF(i, 2, minFac.size()) {
		if (minFac[i] == 0) {
			minFac[i] = i;
			primes.push_back(i);
			primeIdx[i] = primes.size() - 1;
			for (LL j = i * i; j < minFac.size(); j += i) {
				if (minFac[j] == 0) {
					minFac[j] = i;
				}
			}
		}
	}

	vector<vector<pair<LL, LL>>> edges(primes.size());
	LL N;
	cin >> N;
	vector<LL> A(N);
	RF(i, 0, N) {
		cin >> A[i];
		LL cur{A[i]};
		vector<LL> group;
		while (cur > 1) {
			if (group.empty() || group.back() != minFac[cur]) {
				group.push_back(minFac[cur]);
			}
			cur /= minFac[cur];
		}

		RF(j, 0, group.size()) {
			RF(k, j + 1, group.size()) {
				edges[primeIdx[group[j]]].push_back({primeIdx[group[k]], i});
				edges[primeIdx[group[k]]].push_back({primeIdx[group[j]], i});
			}
		}
	}

	LL S, T;
	cin >> S >> T;
	if (S == T) {
		cout << "1\n" << S << '\n';
		return 0;
	}

	edges.push_back({});
	LL cur{A[S - 1]};
	while (cur > 1) {
		if (
			edges.back().empty() ||
			primes[edges.back().back().first] != minFac[cur]) {
			edges.back().push_back({primeIdx[minFac[cur]], S - 1});
			edges[primeIdx[minFac[cur]]].push_back({edges.size() - 1, S - 1});
		}
		cur /= minFac[cur];
	}
	edges.push_back({});
	cur = A[T - 1];
	while (cur > 1) {
		if (
			edges.back().empty() ||
			primes[edges.back().back().first] != minFac[cur]) {
			edges.back().push_back({primeIdx[minFac[cur]], T - 1});
			edges[primeIdx[minFac[cur]]].push_back({edges.size() - 1, T - 1});
		}
		cur /= minFac[cur];
	}

	vector<LL> par(edges.size(), -1), num(edges.size());
	vector<bool> vis(edges.size());
	queue<LL> q;
	q.push(edges.size() - 2);
	while (!q.empty()) {
		LL top{q.front()};
		q.pop();
		if (top == edges.size() - 1) {
			break;
		}
		if (vis[top]) {
			continue;
		}
		vis[top] = true;

		for (auto &e : edges[top]) {
			if (par[e.first] == -1 && !vis[e.first]) {
				par[e.first] = top;
				num[e.first] = e.second;
				q.push(e.first);
			}
		}
	}

	if (par[edges.size() - 1] == -1) {
		cout << "-1\n";
		return 0;
	}

	vector<LL> ans;
	cur = edges.size() - 1;
	while (cur != edges.size() - 2) {
		ans.push_back(num[cur] + 1);
		cur = par[cur];
	}
	reverse(ans.begin(), ans.end());
	cout << ans.size() << '\n';
	RF(i, 0, ans.size()) {
		cout << ans[i] << ' ';
	}
	return 0;
}
