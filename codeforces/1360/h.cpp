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
	while (T--) {
		LL N, M;
		cin >> N >> M;

		LL med{(1LL << (M - 1)) - 1}, rbias{1};
		unordered_set<LL> rem;
		RF(i, 0, N) {
			string S;
			cin >> S;
			LL A{0};
			RF(j, 0, S.length()) {
				A = A * 2 + S[j] - '0';
			}
			rem.insert(A);
			if (A > med) {
				rbias--;
				if (rbias < 0) {
					rbias += 2;
					med--;
					while (rem.find(med) != rem.end()) {
						med--;
					}
				}
			} else if (A < med) {
				rbias++;
				if (rbias > 1) {
					rbias -= 2;
					med++;
					while (rem.find(med) != rem.end()) {
						med++;
					}
				}
			} else {
				rbias++;
				med--;
				while (rem.find(med) != rem.end()) {
					med--;
				}
				if (rbias > 1) {
					rbias -= 2;
					med++;
					while (rem.find(med) != rem.end()) {
						med++;
					}
				}
			}
		}

		RF(i, M, 0) {
			cout << (char)('0' + (((1LL << (i - 1)) & med) != 0));
		}
		cout << '\n';
	}

	return 0;
}
