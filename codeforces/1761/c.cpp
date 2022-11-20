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

	LL T;
	cin >> T;
	while (T--) {
		LL N;
		cin >> N;
		vector<string> A(N);
		vector<set<LL>> E(N), B(N);
		RF(i, 0, N) {
			cin >> A[i];
			RF(j, 0, N) {
				if (A[i][j] == '1') {
					E[j].insert(i);
					B[i].insert(j);
				}
			}
		}

		vector<set<LL>> cE(E);
		queue<LL> q;
		RF(i, 0, N) {
			if (E[i].empty()) {
				q.push(i);
			}
		}
		vector<LL> order;
		while (!q.empty()) {
			LL front{q.front()};
			q.pop();
			order.push_back(front);
			for (auto &i : B[front]) {
				E[i].erase(front);
				if (E[i].empty()) {
					q.push(i);
				}
			}
		}

		vector<set<LL>> ans(N);
		for (auto &i : order) {
			ans[i].insert(i + 1);
			for (auto &j : cE[i]) {
				set<LL> tmp;
				set_union(
					ans[i].begin(),
					ans[i].end(),
					ans[j].begin(),
					ans[j].end(),
					inserter(tmp, tmp.begin()));
				ans[i].swap(tmp);
			}
		}

		RF(i, 0, N) {
			cout << ans[i].size() << ' ';
			for (auto &j : ans[i]) {
				cout << j << ' ';
			}
			cout << '\n';
		}
	}

	return 0;
}
