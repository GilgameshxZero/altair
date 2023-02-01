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

	LL N, E, K;
	cin >> N >> E >> K;

	LL const MAXSE{100005}, INF{100000000000};
	vector<LL> SI(N), EI(N), PI(N), inNoteId(MAXSE + 3000, -1), sumNotePts{0},
		sumNoteTime{0};
	RF(i, 0, N) {
		cin >> SI[i] >> EI[i] >> PI[i];
		RF(j, SI[i] + 1, EI[i]) {
			inNoteId[j] = i;
		}
		sumNotePts.resize(EI[i], sumNotePts.back());
		sumNotePts.push_back(sumNotePts.back() + PI[i]);
		sumNoteTime.resize(EI[i], sumNoteTime.back());
		sumNoteTime.push_back(sumNoteTime.back() + EI[i] - SI[i]);
	}
	sumNotePts.resize(inNoteId.size(), sumNotePts.back());
	sumNoteTime.resize(inNoteId.size(), sumNoteTime.back());

	vector<array<LL, 11>> s(
		inNoteId.size(),
		{-INF, -INF, -INF, -INF, -INF, -INF, -INF, -INF, -INF, -INF, -INF});
	s[0][E] = 0;
	RF(i, 0, MAXSE + 1500) {
		RF(j, 0, s[i].size()) {
			s[i + 1][min(E, j + 1)] = max(s[i + 1][min(E, j + 1)], s[i][j]);
			RF(k, 1, j + 1) {
				LL deltaPlayTime{1LL << (k - 1)},
					deltaNoteTime{max(
						0LL,
						sumNoteTime[i + deltaPlayTime] - sumNoteTime[i] -
							(inNoteId[i] == -1 ? 0 : EI[inNoteId[i]] - SI[inNoteId[i]]))},
					deltaScore{
						max(
							0LL,
							sumNotePts[i + deltaPlayTime] - sumNotePts[i] -
								(inNoteId[i] == -1 ? 0 : PI[inNoteId[i]])) -
						K * (deltaPlayTime - deltaNoteTime)};
				s[i + deltaPlayTime + 1][j - k] =
					max(s[i + deltaPlayTime + 1][j - k], s[i][j] + deltaScore);
			}
		}
	}
	cout << s[MAXSE + 1499][E];

	return 0;
}
