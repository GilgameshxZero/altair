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

using LL = long long;
using LD = long double;

#define RF(x, from, to)                                                      \
	for (long long x = from, _to = to, _delta{x < _to ? 1LL : -1LL}; x != _to; \
			 x += _delta)

using namespace std;

/* ------------------------ End of primary template. ------------------------ */

void splay(vector<vector<bool>> &grid, LL X, LL Y) {
	grid[X - 1][Y] = !grid[X - 1][Y];
	grid[X + 1][Y] = !grid[X + 1][Y];
	grid[X][Y - 1] = !grid[X][Y - 1];
	grid[X][Y + 1] = !grid[X][Y + 1];
}

int main(int, char const *[]) {
#if !defined(ONLINEJUDGE) && (defined(__APPLE__) || defined(__MACH__))
	std::freopen("../build/i.default.txt", "r", stdin);
	std::freopen("../build/o.default.txt", "w", stdout);
#endif

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	// vector<vector<bool>> grid(10, vector<bool>(10, false));
	// RF(i, 2, 8) {
	// 	RF(j, 2, 8) {
	// 		splay(grid, i, j);
	// 	}
	// }
	// RF(i, 4, 6) {
	// 	RF(j, 4, 6) {
	// 		splay(grid, i, j);
	// 	}
	// }
	// for (auto i{1}; i < 9; i += 2) {
	// 	splay(grid, i + 1, i);
	// }
	// for (auto i{1}; i < 7; i += 2) {
	// 	splay(grid, i + 3, i);
	// }
	// for (auto i{1}; i < 5; i += 2) {
	// 	splay(grid, i + 5, i);
	// }
	// for (auto i{1}; i < 3; i += 2) {
	// 	splay(grid, i + 7, i);
	// }
	// // RF(i, 1, 9) {
	// // 	RF(j, 1, i + 1) {
	// // 		splay(grid, i, j);
	// // 	}
	// // }
	// // RF(i, 1, 9) {
	// // 	RF(j, 1, 10 - i) {
	// // 		splay(grid, i, j);
	// // 	}
	// // }
	// // RF(i, 1, 9) {
	// // 	RF(j, 1, min(i, 9 - i)) {
	// // 		splay(grid, i, j);
	// // 	}
	// // }
	// RF(i, 0, 10) {
	// 	RF(j, 0, 10) {
	// 		cout << grid[i][j];
	// 	}
	// 	cout << '\n';
	// }
	// return 0;

	LL T;
	cin >> T;
	while (T--) {
		LL N;
		cin >> N;
		vector<vector<int>> mut(N + 2, vector<int>(N + 2, 0)), ul(mut);
		RF(i, 1, N + 1) {
			RF(j, 1, N + 1) {
				cin >> mut[i][j];
				ul[i][j] = ul[i - 1][j - 1] ^ mut[i][j] ^ ul[i - 1][j] ^ ul[i][j - 1];
			}
		}

		int ans{0};
		for (auto i{2}; i <= N / 2; i += 2) {
			ans ^= ul[N - i + 1][N - i + 1] ^ ul[i - 1][i - 1] ^
				ul[i - 1][N - i + 1] ^ ul[N - i + 1][i - 1];
		}

		for (auto i{N}; i > 0; i -= 2) {
			for (auto j{1}; j <= i; j += 2) {
				ans ^= mut[i][j];
			}
		}

		for (auto i{N}; i > 0; i -= 2) {
			for (auto j{1}; j <= i; j += 2) {
				ans ^= mut[N + 1 - i][j];
			}
		}

		cout << ans << '\n';
	}

	return 0;
}
