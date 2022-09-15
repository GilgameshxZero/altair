#pragma GCC target("avx2", "bmi", "bmi2", "popcnt", "lzcnt")
#pragma GCC optimize("Ofast", "unroll-loops")

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
	LL T;
	cin >> T;
	while (T--) {
		string S[2], P[2];
		cin >> S[0] >> S[1];
		reverse(S[0].begin(), S[0].end());
		reverse(S[1].begin(), S[1].end());

		bool done{false};
		RF(i, 0, 1000) {
			RF(j, 0, 2) {
				if (S[j].empty()) {
					if (P[j].empty()) {
						cout << (j == 0 ? "John" : "Jane") << " wins.\n";
						done = true;
						break;
					} else {
						S[j] = P[j];
						P[j].clear();
						reverse(S[j].begin(), S[j].end());
					}
				}
			}
			if (done) {
				break;
			}

			P[0] += S[0].back();
			P[1] += S[1].back();
			S[0].pop_back();
			S[1].pop_back();

			if (P[0].back() == P[1].back()) {
				LL caller{rand() / 141 % 2};
				P[caller] += P[1 - caller];
				P[1 - caller].clear();
				string rev{P[caller]};
				reverse(rev.begin(), rev.end());
				cout << "Snap! for " << (caller == 0 ? "Jane" : "John") << ": " << rev
						 << '\n';
			}
		}

		if (!done) {
			cout << "Keeps going and going...\n";
		}
		if (T != 0) {
			cout << '\n';
		}
	}

	return 0;
}

/* ---------------------------- End of solution. ---------------------------- */

class IO {
	public:
	IO() {
#ifndef ONLINEJUDGE
#if defined(__APPLE__) || defined(__MACH__)
		std::freopen("../build/i.default.txt", "r", stdin);
		std::freopen("../build/o.default.txt", "w", stdout);
#endif
#endif

		std::ios_base::sync_with_stdio(false);
		std::cin.tie(nullptr);
	}
} io;
