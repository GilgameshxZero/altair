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

	LL T;
	cin >> T;
	while (T--) {
		LL N, M;
		cin >> N >> M;
		vector<vector<LL>> A(N);
		vector<LL> rS(N);
		LL S{0};
		RF(i, 0, N) {
			A[i].resize(M);
			RF(j, 0, M) {
				cin >> A[i][j];
				S += A[i][j];
				rS[i] += A[i][j];
			}
		}
		if (S % N != 0) {
			cout << "-1\n";
			continue;
		}

		LL target{S / N}, df;
		for (df = 0; df < N && rS[df] >= target; df++)
			;

		vector<pair<LL, pair<LL, LL>>> ans;
		RF(sp, 0, N) {
			if (rS[sp] <= target) {
				continue;
			}

			while (true) {
				RF(i, 0, M) {
					if (A[sp][i] == 1 && A[df][i] == 0) {
						rS[sp]--;
						rS[df]++;
						swap(A[sp][i], A[df][i]);
						ans.push_back({i, {sp, df}});

						if (rS[df] == target) {
							for (; df < N && rS[df] >= target; df++)
								;
							break;
						}
						if (rS[sp] == target) {
							break;
						}
					}
				}
				if (rS[sp] == target) {
					break;
				}
			}
		}

		cout << ans.size() << '\n';
		RF(i, 0, ans.size()) {
			cout << ans[i].second.first + 1 << ' ' << ans[i].second.second + 1 << ' '
					 << ans[i].first + 1 << '\n';
		}
	}

	return 0;
}
