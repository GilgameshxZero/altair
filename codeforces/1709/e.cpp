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
using LD = long double;
using namespace std;

#pragma hdrstop	 // ------------------------------------------------------------

vector<LL> A, AR;
vector<vector<LL>> E;
vector<bool> R;
vector<unordered_set<LL>> S;

void dfsAR(LL cur, LL par) {
	if (par == -1) {
		AR[cur] = A[cur];
	} else {
		AR[cur] = A[cur] ^ AR[par];
	}
	for (auto const &i : E[cur]) {
		if (i == par) {
			continue;
		}
		dfsAR(i, cur);
	}
}

void dfs(LL cur, LL par) {
	LL maxi{-1};
	for (auto const &i : E[cur]) {
		if (i == par) {
			continue;
		}
		dfs(i, cur);
		if (R[i]) {
			continue;
		}
		if (maxi == -1 || S[i].size() > S[maxi].size()) {
			maxi = i;
		}
	}
	if (maxi == -1) {
		S[cur].insert(AR[cur]);
		return;
	}
	swap(S[cur], S[maxi]);
	if (S[cur].count(AR[cur] ^ A[cur])) {
		R[cur] = true;
		return;
	}
	S[cur].insert(AR[cur]);
	for (auto const &i : E[cur]) {
		if (i == par || i == maxi || R[i]) {
			continue;
		}
		for (auto const &j : S[i]) {
			if (S[cur].count(j ^ A[cur])) {
				R[cur] = true;
				return;
			}
		}
		for (auto const &j : S[i]) {
			S[cur].insert(j);
		}
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
	A.resize(N);
	RF(i, 0, N) {
		cin >> A[i];
	}
	AR.resize(N);
	E.resize(N);
	RF(i, 0, N - 1) {
		LL U, V;
		cin >> U >> V;
		E[U - 1].push_back(V - 1);
		E[V - 1].push_back(U - 1);
	}
	dfsAR(0, -1);
	R.resize(N, false);
	S.resize(N);
	dfs(0, -1);
	LL ans{0};
	RF(i, 0, N) {
		ans += R[i];
	}
	cout << ans;

	return 0;
}
