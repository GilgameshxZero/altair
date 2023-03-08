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

#pragma hdrstop

/* ------------------------ End of primary template. ------------------------ */

void ccdfs(vector<string> &G, LL cx, LL cy) {
	static vector<pair<LL, LL>> const dirs{{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
	for (auto const &i : dirs) {
		if (
			cx + i.first >= 0 && cx + i.first < G.size() && cy + i.second >= 0 &&
			cy + i.second < G[0].size()) {
			if (G[cx + i.first][cy + i.second] == '#') {
				G[cx + i.first][cy + i.second] = G[cx][cy];
				ccdfs(G, cx + i.first, cy + i.second);
			}
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

	LL T;
	cin >> T;
	while (T--) {
		LL N, M;
		cin >> N >> M;
		vector<string> G(N);
		RF(i, 0, N) {
			cin >> G[i];
		}

		RF(i, 0, N) {
			LL j(G[i].find_first_of('#')), k(G[i].find_last_of('#'));
			if (j >= M || j < 0) {
				continue;
			}
			RF(l, j, k + 1) {
				G[i][l] = '#';
			}
		}
		RF(i, 0, M) {
			LL j{-1}, k{-1};
			RF(l, 0, N) {
				if (G[l][i] == '#') {
					j = l;
					break;
				}
			}
			RF(l, N - 1, -1) {
				if (G[l][i] == '#') {
					k = l;
					break;
				}
			}
			if (j == -1) {
				continue;
			}
			RF(l, j, k + 1) {
				G[l][i] = '#';
			}
		}

		RF(i, 0, N) {
			LL j(G[i].find_first_of('#')), k(G[i].find_last_of('#'));
			if (j >= M || j < 0) {
				continue;
			}
			RF(l, j, k + 1) {
				G[i][l] = '#';
			}
		}
		RF(i, 0, M) {
			LL j{-1}, k{-1};
			RF(l, 0, N) {
				if (G[l][i] == '#') {
					j = l;
					break;
				}
			}
			RF(l, N - 1, -1) {
				if (G[l][i] == '#') {
					k = l;
					break;
				}
			}
			if (j == -1) {
				continue;
			}
			RF(l, j, k + 1) {
				G[l][i] = '#';
			}
		}

		LL ccc{0};
		RF(i, 0, N) {
			RF(j, 0, M) {
				if (G[i][j] == '#') {
					G[i][j] = '0' + ++ccc;
					ccdfs(G, i, j);
				}
			}
		}

		if (ccc == 1) {
			RF(i, 0, N) {
				RF(j, 0, M) {
					G[i][j] = G[i][j] == '.' ? '.' : '#';
				}
			}
			RF(i, 0, N) {
				cout << G[i] << '\n';
			}
			cout << '\n';
			continue;
		}

		LL l1(M), r1(0), l2(M), r2(0), b1(0), u2(N);
		RF(i, 0, N) {
			RF(j, 0, M) {
				if (G[i][j] == '1') {
					l1 = min(l1, j);
					r1 = max(r1, j);
					b1 = max(b1, i);
				} else if (G[i][j] == '2') {
					l2 = min(l2, j);
					r2 = max(r2, j);
					u2 = min(u2, i);
				}
			}
		}

		RF(i, 0, N) {
			RF(j, 0, M) {
				G[i][j] = G[i][j] == '.' ? '.' : '#';
			}
		}

		if (r1 < l2) {
			RF(i, r1 + 1, l2) {
				G[b1][i] = '#';
			}
			RF(i, b1, u2) {
				G[i][l2] = '#';
			}
			RF(i, b1, -1) {
				if (G[i][r1] == '#') {
					break;
				}
				RF(j, r1, l1 - 1) {
					if (G[i][j] == '#') {
						break;
					}
					G[i][j] = '#';
				}
			}
			RF(i, u2, N) {
				if (G[i][l2] == '#') {
					break;
				}
				RF(j, l2, r2 + 1) {
					if (G[i][j] == '#') {
						break;
					}
					G[i][j] = '#';
				}
			}
		} else {
			RF(i, r2 + 1, l1) {
				G[b1][i] = '#';
			}
			RF(i, b1, u2) {
				G[i][r2] = '#';
			}
			RF(i, b1, -1) {
				if (G[i][l1] == '#') {
					break;
				}
				RF(j, l1, r1 + 1) {
					if (G[i][j] == '#') {
						break;
					}
					G[i][j] = '#';
				}
			}
			RF(i, u2, N) {
				if (G[i][r2] == '#') {
					break;
				}
				RF(j, r2, l2 - 1) {
					if (G[i][j] == '#') {
						break;
					}
					G[i][j] = '#';
				}
			}
		}

		RF(i, 0, N) {
			RF(j, 0, M) {
				G[i][j] = G[i][j] == '.' ? '.' : '#';
			}
		}
		RF(i, 0, N) {
			cout << G[i] << '\n';
		}
		cout << '\n';
	}

	return 0;
}
