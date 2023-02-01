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
	vector<string> G(N);
	priority_queue<pair<LL, pair<LL, LL>>> q;
	pair<LL, LL> finish;
	RF(i, 0, N) {
		cin >> G[i];
		RF(j, 0, M) {
			if (G[i][j] == 'S') {
				G[i][j] = '.';
				q.push({-1, {i, j}});
			} else if (G[i][j] == 'F') {
				G[i][j] = '#';
				finish = {i, j};
			}
		}
	}

	LL const INF{1000000000};
	vector<vector<LL>> up(N, vector<LL>(M)), right(up), down(up), left(up);
	RF(j, 0, M) {
		up[0][j] = G[0][j] == '#' ? 0 : INF;
	}
	RF(i, 1, N) {
		RF(j, 0, M) {
			up[i][j] = G[i][j] == '#' ? 0 : up[i - 1][j] + 1;
		}
	}
	RF(i, 0, N) {
		right[i][M - 1] = G[i][M - 1] == '#' ? 0 : INF;
	}
	RF(i, 0, N) {
		RF(j, M - 2, -1) {
			right[i][j] = G[i][j] == '#' ? 0 : right[i][j + 1] + 1;
		}
	}
	RF(j, 0, M) {
		down[N - 1][j] = G[N - 1][j] == '#' ? 0 : INF;
	}
	RF(i, N - 2, -1) {
		RF(j, 0, M) {
			down[i][j] = G[i][j] == '#' ? 0 : down[i + 1][j] + 1;
		}
	}
	RF(i, 0, N) {
		left[i][0] = G[i][0] == '#' ? 0 : INF;
	}
	RF(i, 0, N) {
		RF(j, 1, M) {
			left[i][j] = G[i][j] == '#' ? 0 : left[i][j - 1] + 1;
		}
	}

	auto Hash{[](pair<LL, LL> const &X) { return X.first * 1000000 + X.second; }};
	unordered_map<pair<LL, LL>, LL, decltype(Hash)> dist(0, Hash);
	dist[q.top().second] = -q.top().first;
	while (!q.empty()) {
		auto [cd, front]{q.top()};
		q.pop();
		cd = -cd;
		if (cd != dist[front]) {
			continue;
		}
		if (
			front == make_pair(finish.first - 1, finish.second) ||
			front == make_pair(finish.first, finish.second + 1) ||
			front == make_pair(finish.first + 1, finish.second) ||
			front == make_pair(finish.first, finish.second - 1)) {
			cout << cd + 1;
			return 0;
		}

		vector<pair<LL, LL>> cand;
		if (up[front.first][front.second] < INF) {
			cand.push_back(
				{front.first - (up[front.first][front.second] - 1), front.second});
		}
		if (right[front.first][front.second] < INF) {
			cand.push_back(
				{front.first, front.second + (right[front.first][front.second] - 1)});
		}
		if (down[front.first][front.second] < INF) {
			cand.push_back(
				{front.first + (down[front.first][front.second] - 1), front.second});
		}
		if (left[front.first][front.second] < INF) {
			cand.push_back(
				{front.first, front.second - (left[front.first][front.second] - 1)});
		}
		for (auto const &i : cand) {
			if (i == front) {
				continue;
			}
			LL j{cd + abs(i.first - front.first) + abs(i.second - front.second)};
			if (dist.count(i) == 0 || j < dist[i]) {
				dist[i] = j;
				q.push({-j, i});
			}
		}
	}
	return 0;
}
