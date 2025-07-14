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

	LL N, M, K;
	cin >> N >> M >> K;
	vector<unordered_set<LL>> E(N * 2);
	RF(i, 0, M) {
		LL U, V, A;
		cin >> U >> V >> A;
		E[!A * N + U - 1].insert(!A * N + V - 1);
		E[!A * N + V - 1].insert(!A * N + U - 1);
	}
	RF(i, 0, K) {
		LL S;
		cin >> S;
		E[S - 1].insert(S - 1 + N);
		E[S - 1 + N].insert(S - 1);
	}

	queue<LL> q;
	vector<LL> cnt(N * 2, 1000000000);
	cnt[0] = 0;
	q.push(0);
	while (!q.empty()) {
		auto qt{q.front()};
		q.pop();
		for (auto &i : E[qt]) {
			if (cnt[i] == 1000000000) {
				q.push(i);
				cnt[i] = cnt[qt] + (i / N == qt / N);
			}
		}
	}
	if (cnt[N - 1] == 1000000000 && cnt[N * 2 - 1] == 1000000000) {
		cout << -1;
	} else {
		cout << min(cnt[N - 1], cnt[N * 2 - 1]);
	}
	return 0;
}
