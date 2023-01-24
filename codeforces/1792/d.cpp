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

LL hAi(vector<LL> &Ai) {
	LL h{0};
	for (auto &i : Ai) {
		h = h * 11 + i;
	}
	return h;
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

		vector<vector<LL>> A(N);
		unordered_set<LL> S;
		RF(i, 0, N) {
			A[i].resize(M);
			RF(j, 0, M) {
				cin >> A[i][j];
			}
			S.insert(hAi(A[i]));

			auto Bi{A[i]};
			RF(j, M, 0) {
				RF(k, 0, M) {
					if (Bi[k] == j) {
						Bi[k] = 0;
						break;
					}
				}
				S.insert(hAi(Bi));
			}
		}

		RF(i, 0, N) {
			vector<LL> Bi(M);
			RF(k, 0, M) {
				Bi[A[i][k] - 1] = k + 1;
			}

			if (S.find(hAi(Bi)) != S.end()) {
				cout << M << ' ';
				continue;
			}

			RF(j, M, 0) {
				Bi[A[i][j - 1] - 1] = 0;
				if (S.find(hAi(Bi)) != S.end()) {
					cout << j - 1 << ' ';
					break;
				}
			}
		}
		cout << '\n';
	}

	return 0;
}
