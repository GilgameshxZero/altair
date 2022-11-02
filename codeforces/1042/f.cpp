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

LL N, K, carry;
vector<vector<LL>> E;
vector<LL> height;

multiset<LL> dfs(LL cur, LL par) {
	multiset<LL> ret;
	LL cch{0};
	RF(i, 0, E[cur].size()) {
		if (E[cur][i] == par) {
			continue;
		}
		height[E[cur][i]] = height[cur] + 1;
		cch++;
		auto res{dfs(E[cur][i], cur)};
		for (auto j : res) {
			ret.insert(j);
		}
		while (ret.size() >= 2) {
			auto k{ret.rbegin()}, l{k};
			k++;
			if (*k - height[cur] + *l - height[cur] > K) {
				ret.erase(ret.find(*l));
				carry++;
			} else {
				break;
			}
		}
		while (ret.size() >= 2) {
			auto k{ret.begin()}, l{k};
			k++;
			if (*k - height[cur] + *l - height[cur] <= K) {
				ret.erase(ret.find(*l));
			} else {
				break;
			}
		}
	}
	if (cch == 0) {
		ret.insert(height[cur]);
		return ret;
	}
	return ret;
}

int main(int, char const *[]) {
#if !defined(ONLINEJUDGE) && (defined(__APPLE__) || defined(__MACH__))
	std::freopen("../build/i.default.txt", "r", stdin);
	std::freopen("../build/o.default.txt", "w", stdout);
#endif

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	cin >> N >> K;
	height.resize(N, 0);
	E.resize(N);
	RF(i, 0, N - 1) {
		LL U, V;
		cin >> U >> V;
		E[U - 1].push_back(V - 1);
		E[V - 1].push_back(U - 1);
	}
	LL root{0};
	for (; root < N; root++) {
		if (E[root].size() > 1) {
			break;
		}
	}
	cout << dfs(root, -1).size() + carry;
	return 0;
}
