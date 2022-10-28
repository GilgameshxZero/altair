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

#define RF(x, from, to)                                                     \
	for (long long x = from, rfDir = x < static_cast<long long>(to) ? 1 : -1; \
			 x != static_cast<long long>(to);                                     \
			 x += rfDir)

using namespace std;

/* ---------------------------- End of template. ---------------------------- */

void dfs(
	vector<unordered_set<LL>> &e,
	bool &loopable,
	vector<LL> &parent,
	unordered_set<LL> &anc,
	LL cur) {
	anc.insert(cur);
	for (auto &i : e[cur]) {
		if (parent[i] == -1) {
			parent[i] = cur;
			dfs(e, loopable, parent, anc, i);
		} else if (anc.find(i) != anc.end()) {
			loopable = true;
		}
	}
	anc.erase(cur);
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

	vector<unordered_set<LL>> e(N * 2);
	RF(i, 0, N) {
		LL C;
		cin >> C;
		RF(j, 0, C) {
			LL x;
			cin >> x;
			x--;
			e[i * 2].insert(x * 2 + 1);
			e[i * 2 + 1].insert(x * 2);
		}
	}

	LL S;
	cin >> S;
	S--;

	vector<LL> parent(N * 2, -1);
	bool loopable{false};
	unordered_set<LL> anc;
	dfs(e, loopable, parent, anc, S * 2);

	RF(i, 0, N) {
		if (parent[i * 2 + 1] != -1 && e[i * 2 + 1].empty()) {
			cout << "Win\n";
			vector<LL> path;
			LL x{i * 2 + 1};
			while (x != S * 2) {
				path.push_back(x);
				x = parent[x];
			}
			path.push_back(S * 2);
			RF(j, path.size() - 1, -1) {
				cout << path[j] / 2 + 1 << ' ';
			}
			return 0;
		}
	}

	cout << (loopable ? "Draw" : "Lose");
	return 0;
}
