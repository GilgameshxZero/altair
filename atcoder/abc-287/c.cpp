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

int main(int, char const *[]) {
#if !defined(ONLINEJUDGE) && (defined(__APPLE__) || defined(__MACH__))
	std::freopen("../build/i.default.txt", "r", stdin);
	std::freopen("../build/o.default.txt", "w", stdout);
#endif

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	LL N, M;
	cin >> N >> M;
	vector<unordered_set<LL>> E(N);
	RF(i, 0, M) {
		LL U, V;
		cin >> U >> V;
		E[U - 1].insert(V - 1);
		E[V - 1].insert(U - 1);
	}

	if (N - 1 != M) {
		cout << "No";
		return 0;
	}

	LL cur{-1};
	RF(i, 0, N) {
		if (E[i].size() == 1) {
			cur = i;
			break;
		}
	}

	if (cur == -1) {
		cout << "No";
		return 0;
	}

	LL prev{cur};
	vector<bool> vis(N, false);
	vis[cur] = true;
	cur = *E[cur].begin();
	while (true) {
		if (vis[cur]) {
			cout << "No";
			return 0;
		}
		vis[cur] = true;
		if (E[cur].size() == 1) {
			break;
		}
		if (E[cur].size() != 2) {
			cout << "No";
			return 0;
		}
		if (*E[cur].begin() == prev) {
			prev = cur;
			cur = *next(E[cur].begin());
		} else {
			prev = cur;
			cur = *E[cur].begin();
		}
	}

	LL cv{0};
	RF(i, 0, N) {
		cv += vis[i];
	}
	if (cv != N) {
		cout << "No";
		return 0;
	}

	cout << "Yes";
	return 0;
}
