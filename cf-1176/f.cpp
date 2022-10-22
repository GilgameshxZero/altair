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

	LL N;
	cin >> N;
	vector<LL> K(N);
	vector<array<vector<LL>, 3>> CD(N);
	RF(i, 0, N) {
		cin >> K[i];
		RF(j, 0, K[i]) {
			LL C, D;
			cin >> C >> D;
			CD[i][C - 1].push_back(D);
		}
		RF(j, 0, 3) {
			sort(CD[i][j].begin(), CD[i][j].end(), greater<LL>());
			while (CD[i][j].size() > 3) {
				CD[i][j].pop_back();
			}
		}
	}

	// 1 1 1, 1 2, 2 1, 3.
	// 1 1, 2.
	// 1.
	// .
	vector<array<LL, 10>> state(N + 1);
	RF(i, N - 1, -1) {
		RF(j, 0, 10) {
			if (CD[i][0].size() >= 3) {
				if (j >= 7) {
					state[i][j] = max(
						state[i][j],
						state[i + 1][(j + 3) % 10] + CD[i][0][0] * 2 + CD[i][0][1] +
							CD[i][0][2]);
				} else {
					state[i][j] = max(
						state[i][j],
						state[i + 1][j + 3] + CD[i][0][0] + CD[i][0][1] + CD[i][0][2]);
				}
			}
			if (CD[i][0].size() >= 1 && CD[i][1].size() >= 1) {
				if (j >= 8) {
					state[i][j] = max(
						state[i][j],
						state[i + 1][(j + 2) % 10] + 2 * max(CD[i][0][0], CD[i][1][0]) +
							min(CD[i][0][0], CD[i][1][0]));
				} else {
					state[i][j] =
						max(state[i][j], state[i + 1][j + 2] + CD[i][0][0] + CD[i][1][0]);
				}
			}
			if (CD[i][2].size() >= 1) {
				if (j >= 9) {
					state[i][j] =
						max(state[i][j], state[i + 1][(j + 1) % 10] + 2 * CD[i][2][0]);
				} else {
					state[i][j] = max(state[i][j], state[i + 1][j + 1] + CD[i][2][0]);
				}
			}
			if (CD[i][0].size() >= 2) {
				if (j >= 8) {
					state[i][j] = max(
						state[i][j],
						state[i + 1][(j + 2) % 10] + CD[i][0][0] * 2 + CD[i][0][1]);
				} else {
					state[i][j] =
						max(state[i][j], state[i + 1][j + 2] + CD[i][0][0] + CD[i][0][1]);
				}
			}
			if (CD[i][1].size() >= 1) {
				if (j >= 9) {
					state[i][j] =
						max(state[i][j], state[i + 1][(j + 1) % 10] + 2 * CD[i][1][0]);
				} else {
					state[i][j] = max(state[i][j], state[i + 1][j + 1] + CD[i][1][0]);
				}
			}
			if (CD[i][0].size() >= 1) {
				if (j >= 9) {
					state[i][j] =
						max(state[i][j], state[i + 1][(j + 1) % 10] + CD[i][0][0] * 2);
				} else {
					state[i][j] = max(state[i][j], state[i + 1][j + 1] + CD[i][0][0]);
				}
			}
			state[i][j] = max(state[i][j], state[i + 1][j]);
		}
	}
	cout << state[0][0];

	return 0;
}
