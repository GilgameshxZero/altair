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

	LL H, W, N, h, w;
	cin >> H >> W >> N >> h >> w;

	vector<LL> cnt(N + 1);
	vector<vector<LL>> A(H, vector<LL>(W));
	RF(i, 0, H) {
		RF(j, 0, W) {
			cin >> A[i][j];
			cnt[A[i][j]]++;
		}
	}
	LL total{0};
	RF(k, 0, N + 1) {
		total += cnt[k] != 0;
	}

	RF(i, 0, H - h + 1) {
		vector<LL> c2(N + 1);
		RF(ii, 0, h) {
			RF(jj, 0, w) {
				c2[A[i + ii][jj]]++;
			}
		}
		RF(j, 0, W - w + 1) {
			LL cans{0};
			RF(k, 0, N + 1) {
				cans += cnt[k] != 0 && cnt[k] == c2[k];
			}
			cout << total - cans << ' ';
			if (j + w < W) {
				RF(ii, 0, h) {
					c2[A[i + ii][j]]--;
					c2[A[i + ii][j + w]]++;
				}
			}
		}
		cout << '\n';
	}

	return 0;
}
