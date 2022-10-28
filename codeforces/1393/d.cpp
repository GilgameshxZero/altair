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

	LL N, M;
	cin >> N >> M;
	vector<string> S;
	S.push_back(string(M + 2, ' '));
	RF(i, 0, N) {
		string t;
		cin >> t;
		S.push_back(" " + t + " ");
	}
	S.push_back(S[0]);

	vector<vector<LL>> qa(N + 2, vector<LL>(M + 2, 0));
	RF(i, 1, N + 1) {
		RF(j, M, 0) {
			if (S[i][j] != S[i - 1][j] || S[i][j] != S[i][j + 1]) {
				qa[i][j] = 1;
				continue;
			}
			if (S[i][j] != S[i - 1][j + 1]) {
				qa[i][j] = 2;
				continue;
			}
			qa[i][j] = min(2 + qa[i - 1][j + 1], 1 + min(qa[i - 1][j], qa[i][j + 1]));
		}
	}

	decltype(qa) a{qa};
	RF(i, 1, N + 1) {
		RF(j, 1, M + 1) {
			if (S[i][j] != S[i - 1][j] || S[i][j] != S[i][j - 1]) {
				qa[i][j] = 1;
				continue;
			}
			if (S[i][j] != S[i - 1][j - 1]) {
				qa[i][j] = 2;
				continue;
			}
			qa[i][j] = min(2 + qa[i - 1][j - 1], 1 + min(qa[i - 1][j], qa[i][j - 1]));
		}
	}
	RF(i, 0, N + 2) {
		RF(j, 0, M + 2) {
			a[i][j] = min(a[i][j], qa[i][j]);
		}
	}

	RF(i, N, 0) {
		RF(j, 1, M + 1) {
			if (S[i][j] != S[i + 1][j] || S[i][j] != S[i][j - 1]) {
				qa[i][j] = 1;
				continue;
			}
			if (S[i][j] != S[i + 1][j - 1]) {
				qa[i][j] = 2;
				continue;
			}
			qa[i][j] = min(2 + qa[i + 1][j - 1], 1 + min(qa[i + 1][j], qa[i][j - 1]));
		}
	}
	RF(i, 0, N + 2) {
		RF(j, 0, M + 2) {
			a[i][j] = min(a[i][j], qa[i][j]);
		}
	}

	RF(i, N, 0) {
		RF(j, M, 0) {
			if (S[i][j] != S[i + 1][j] || S[i][j] != S[i][j + 1]) {
				qa[i][j] = 1;
				continue;
			}
			if (S[i][j] != S[i + 1][j + 1]) {
				qa[i][j] = 2;
				continue;
			}
			qa[i][j] = min(2 + qa[i + 1][j + 1], 1 + min(qa[i + 1][j], qa[i][j + 1]));
		}
	}
	RF(i, 0, N + 2) {
		RF(j, 0, M + 2) {
			a[i][j] = min(a[i][j], qa[i][j]);
		}
	}

	LL ans{0};
	RF(i, 1, N + 1) {
		RF(j, 1, M + 1) {
			ans += a[i][j];
		}
	}
	cout << ans;

	return 0;
}
