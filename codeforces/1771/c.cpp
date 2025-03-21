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

array<bool, 5000> ps;

int main(int, char const *[]) {
#if !defined(ONLINEJUDGE) && (defined(__APPLE__) || defined(__MACH__))
	std::freopen("../build/i.default.txt", "r", stdin);
	std::freopen("../build/o.default.txt", "w", stdout);
#endif

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	vector<bool> isPrime(31525, true);
	vector<LL> primes;
	isPrime[0] = isPrime[1] = false;
	RF(i, 2, 31525) {
		if (isPrime[i]) {
			primes.push_back(i);
			for (LL j = i * i; j < 31525; j += i) {
				isPrime[j] = false;
			}
		}
	}

	LL T;
	cin >> T;
	while (T--) {
		LL N;
		cin >> N;

		unordered_set<LL> seen;
		bool done{false};
		ps.fill(false);
		RF(i, 0, N) {
			LL X;
			cin >> X;
			if (done) {
				continue;
			}

			RF(j, 0, primes.size()) {
				if (primes[j] * primes[j] > X) {
					break;
				}
				if (X % primes[j] == 0) {
					if (ps[j]) {
						cout << "YES" << '\n';
						done = true;
						break;
					}
					ps[j] = true;
					while (X % primes[j] == 0) {
						X /= primes[j];
					}
				}
			}

			if (done) {
				continue;
			}

			if (X > 1) {
				if (seen.count(X)) {
					cout << "YES" << '\n';
					done = true;
				} else {
					seen.insert(X);
				}
			}
		}

		if (!done) {
			cout << "NO" << '\n';
		}
	}

	return 0;
}
