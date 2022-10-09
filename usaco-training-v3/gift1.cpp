/*
TASK: gift1
LANG: C++
*/
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

#define RF(x, from, to) \
	for (long long x = from, rfDir = from < to ? 1 : -1; x != to; x += rfDir)

using namespace std;

/* ---------------------------- End of template. ---------------------------- */

int main(int, char const *[]) {
#if !defined(ONLINEJUDGE) && (defined(__APPLE__) || defined(__MACH__))
	std::freopen("../build/i.default.txt", "r", stdin);
	std::freopen("../build/o.default.txt", "w", stdout);
#endif
	std::freopen("gift1.in", "r", stdin);
	std::freopen("gift1.out", "w", stdout);

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	LL N;
	cin >> N;
	map<string, LL> bal;
	string S;
	vector<string> P;
	RF(i, 0, N) {
		cin >> S;
		P.push_back(S);
	}
	RF(i, 0, N) {
		cin >> S;
		LL X, Y;
		cin >> X >> Y;
		bal[S] -= X;
		if (Y == 0) {
			bal[S] += X;
			continue;
		}
		bal[S] += X % Y;
		RF(j, 0, Y) {
			cin >> S;
			bal[S] += X / Y;
		}
	}
	RF(i, 0, P.size()) {
		cout << P[i] << ' ' << bal[P[i]] << '\n';
	}

	return 0;
}
