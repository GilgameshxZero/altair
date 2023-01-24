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

int main(int, char const *[]) {
#if !defined(ONLINEJUDGE) && (defined(__APPLE__) || defined(__MACH__))
	std::freopen("../build/i.default.txt", "r", stdin);
	std::freopen("../build/o.default.txt", "w", stdout);
#endif

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	vector<LL> primes, minFac(32000);
	minFac[1] = 1;
	RF(i, 2, minFac.size()) {
		if (minFac[i] == 0) {
			minFac[i] = i;
			primes.push_back(i);
			for (LL j{i * i}; j < minFac.size(); j += i) {
				minFac[j] = i;
			}
		}
	}

	LL T;
	cin >> T;
	while (T--) {
		LL N, M1, M2;
		cin >> N >> M1 >> M2;

		unordered_map<LL, LL> cFac;
		LL cur{M1};
		RF(i, 0, primes.size()) {
			while (cur % primes[i] == 0) {
				cur /= primes[i];
				cFac[primes[i]]++;
			}
		}
		if (cur != 1) {
			cFac[cur]++;
		}
		cur = M2;
		RF(i, 0, primes.size()) {
			while (cur % primes[i] == 0) {
				cur /= primes[i];
				cFac[primes[i]]++;
			}
		}
		if (cur != 1) {
			cFac[cur]++;
		}

		vector<unordered_map<LL, LL>> divisors;
		divisors.push_back({});
		for (auto const &p : cFac) {
			LL p1{p.first}, p2{p.second};
			LL k = divisors.size();
			RF(i, 1, p2 + 1) {
				RF(j, 0, k) {
					unordered_map<LL, LL> d2(divisors[j]);
					d2[p1] = i;
					divisors.push_back(d2);
				}
			}
		}

		LL ans{0}, count{0};
		for (auto const &divisor : divisors) {
			vector<LL> dd;
			dd.push_back(1);
			LL d{1};
			for (auto const &p : divisor) {
				LL p1{p.first}, p2{p.second};
				LL k = dd.size(), cur{p1};
				RF(i, 1, p2 + 1) {
					RF(j, 0, k) {
						dd.push_back(dd[j] * cur);
						d = max(d, dd.back());
					}
					cur *= p1;
				}
			}

			sort(dd.begin(), dd.end());
			RF(i, 0, dd.size()) {
				if (dd[i] <= N && d / dd[i] <= N) {
					count++;
					ans ^= dd[i];
					break;
				}
			}
		}

		cout << count << ' ' << ans << '\n';
	}

	return 0;
}
