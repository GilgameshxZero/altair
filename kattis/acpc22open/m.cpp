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

	vector<LL> primes;
	vector<bool> isPrime(1000001, true);
	isPrime[0] = isPrime[1] = false;
	for (LL i = 2; i <= 1000000; ++i) {
		if (isPrime[i]) {
			primes.push_back(i);
			for (LL j = i * i; j <= 1000000; j += i) {
				isPrime[j] = false;
			}
		}
	}

	long long A_, C_;
	cin >> A_ >> C_;
	LL A{A_}, C{C_};
	unordered_map<LL, LL> fa, fc, famp, fcmp;
	LL a{A}, c{C};
	for (LL p : primes) {
		while (a % p == 0) {
			a /= p;
			fa[p]++;
			famp[p] = max(p, famp[p] * p);
		}
	}
	for (LL p : primes) {
		while (c % p == 0) {
			c /= p;
			fc[p]++;
			fcmp[p] = max(p, fcmp[p] * p);
		}
	}

	map<LL, LL> cfa, cfc;
	for (auto &i : fa) {
		cfa[i.first] = 0;
	}
	for (auto &i : fc) {
		cfc[i.first] = 0;
	}

	// List of highly composite numbers up to 10^16
	// https://oeis.org/A000041
	// vector<LL> hcn{
	// 		1, 2, 4, 6, 12, 24, 36, 48, 60, 120, 180, 240, 360, 720, 840, 1260,
	// 		1680, 2520, 5040, 7560, 10080, 15120, 20160, 25200, 27720, 45360,
	// 		50400, 55440, 83160, 110880, 166320, 221760, 277200, 332640, 498960,
	// 		554400, 665280, 720720, 1081080, 1441440, 2162160, 2882880, 3603600,
	// 		4324320, 6486480, 7207200, 8648640, 10810800, 14414400, 17297280,
	// 		21621600, 32432400, 36756720, 43243200, 61261200, 73513440, 110270160,
	// 		122522400, 147026880, 183783600, 245044800, 294053760, 367567200,
	// 		551350800, 698377680, 735134400, 1102701600, 1396755360, 2095133040,
	// 		2205403200, 2327925600, 2793510720, 3491888400, 4655851200, 5587021440,
	// 		6983776800, 10475665200, 13967553600, 20951330400, 27935107200,
	// 		34918884000, 48886437600, 55870214400, 69837768000, 111333477600,
	// 		139675536000, 167248483200, 223092870000, 334371868800, 446185740000,
	// 		557940830000, 669654740000, 2230928700000, 4461857400000,
	// 		6696547400000, 22309287000000, 44618574000000, 223092870000000,
	// 		446185740000000};

	using LLL = LL;
	unordered_set<LLL> ans;
	LLL cfam{1}, cfcm{1};
	while (true) {
		while (true) {
			LLL d{cfam}, f{A / d}, e{cfcm}, g{C / e}, b{e * f + d * g};
			ans.insert(b);

			if (C == 1) {
				break;
			}

			auto i{cfc.rbegin()};
			i->second++;
			cfcm *= i->first;
			while (i != cfc.rend() && i->second > fc[i->first]) {
				cfcm /= fcmp[i->first] * i->first;
				i->second = 0;
				i++;
				if (i != cfc.rend()) {
					i->second++;
					cfcm *= i->first;
				}
			}

			if (i == cfc.rend()) {
				break;
			}
		}

		if (A == 1) {
			break;
		}

		auto i{cfa.rbegin()};
		i->second++;
		cfam *= i->first;
		while (i != cfa.rend() && i->second > fa[i->first]) {
			cfam /= famp[i->first] * i->first;
			i->second = 0;
			i++;
			if (i != cfa.rend()) {
				i->second++;
				cfam *= i->first;
			}
		}

		if (i == cfa.rend()) {
			break;
		}
	}

	cout << ans.size() * 2 - ans.count(0);

	return 0;
}
