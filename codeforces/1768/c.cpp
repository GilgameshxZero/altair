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
		LL N;
		cin >> N;
		vector<LL> P(N, -1), Q(N, -1), A(N);
		RF(i, 0, N) {
			cin >> A[i];
		}
		set<LL> rp, rq;
		RF(i, 1, N + 1) {
			rp.insert(i);
			rq.insert(i);
		}
		bool fail{false};
		RF(i, 0, N) {
			if (rp.count(A[i])) {
				P[i] = A[i];
				rp.erase(A[i]);
			} else if (rq.count(A[i])) {
				Q[i] = A[i];
				rq.erase(A[i]);
			} else {
				fail = true;
				break;
			}
		}
		if (fail) {
			cout << "NO\n";
			continue;
		}
		RF(i, 0, N) {
			if (P[i] == -1) {
				auto it{rp.upper_bound(Q[i])};
				if (it == rp.begin()) {
					fail = true;
					break;
				} else {
					P[i] = *prev(it);
					rp.erase(prev(it));
				}
			}
			if (Q[i] == -1) {
				auto it{rq.upper_bound(P[i])};
				if (it == rq.begin()) {
					fail = true;
					break;
				} else {
					Q[i] = *prev(it);
					rq.erase(prev(it));
				}
			}
		}
		if (fail) {
			cout << "NO\n";
		} else {
			cout << "YES\n";
			RF(i, 0, N) {
				cout << P[i] << ' ';
			}
			cout << '\n';
			RF(i, 0, N) {
				cout << Q[i] << ' ';
			}
			cout << '\n';
		}
	}

	return 0;
}
