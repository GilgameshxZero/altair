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

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	LL T;
	cin >> T;
	RF(t, 0, T) {
		string S;
		cin >> S;
		LL Q, N = S.length(), ss{0};
		cin >> Q;
		for (; ss * ss < N; ss++)
			;
		LL sss{N / ss + 1};
		vector<vector<pair<LL, LL>>> q(ss);
		RF(i, 0, Q) {
			LL X, Y;
			cin >> X >> Y;
			q[X / sss].push_back({Y - 1, X - 1});
		}
		LL ans{0};
		RF(i, 0, ss) {
			if (q[i].empty()) {
				continue;
			}
			sort(q[i].begin(), q[i].end());
			vector<LL> parl(26, false), parr{parl};
			LL mid{-1}, cl{q[i].front().second}, cr{cl}, diffc, dm;
			RF(j, 0, q[i].size()) {
				for (; cl < q[i][j].second; cl++) {
					if (mid == -1) {
						mid = S[(cl + cr) / 2] - 'a';
						parr[mid]--;
					} else {
						parl[mid]++;
						mid = -1;
					}
					parl[S[cl] - 'a']--;
				}
				for (; cl > q[i][j].second; cl--) {
					if (mid == -1) {
						mid = S[(cl + cr) / 2 - 1] - 'a';
						parl[mid]--;
					} else {
						parr[mid]++;
						mid = -1;
					}
					parl[S[cl - 1] - 'a']++;
				}
				for (; cr <= q[i][j].first; cr++) {
					if (mid == -1) {
						mid = S[(cl + cr) / 2] - 'a';
						parr[mid]--;
					} else {
						parl[mid]++;
						mid = -1;
					}
					parr[S[cr] - 'a']++;
				}
				if (mid == -1) {
					continue;
				}
				diffc = 0;
				dm = 0;
				RF(k, 0, 26) {
					if (parl[k] != parr[k]) {
						if (k == mid) {
							dm = abs(parl[k] - parr[k]);
						}
						diffc += abs(parl[k] - parr[k]);
					}
				}
				if (diffc == 0 || (diffc == 2 && dm >= 1)) {
					ans++;
				}
			}
		}
		cout << "Case #" << t + 1 << ": " << ans << '\n';
	}

	return 0;
}
