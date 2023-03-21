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
#include <complex>
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

#if __has_include(<ext/pb_ds/assoc_container.hpp>)
#include <ext/pb_ds/assoc_container.hpp>
template <typename Key, typename Value, typename Hasher = std::hash<Key>>
using UnorderedMap = __gnu_pbds::gp_hash_table<Key, Value, Hasher>;
#else
template <typename Key, typename Value, typename Hasher = std::hash<Key>>
using UnorderedMap = std::unordered_map<Key, Value, Hasher>;
#endif

#define RF(x, from, to)                                                      \
	for (long long x = from, _to = to, _delta{x < _to ? 1LL : -1LL}; x != _to; \
			 x += _delta)

using LL = long long;
using LD = long double;
using namespace std;

#pragma hdrstop	 // ------------------------------------------------------------

array<LL, 100000> A;
array<LL, 100001> seen;

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
		RF(i, 0, N) {
			cin >> A[i];
		}
		LL lastDec{N - 2};
		fill(seen.begin(), seen.begin() + N + 1, -1);
		for (; lastDec >= 0; lastDec--) {
			if (seen[A[lastDec + 1]] == -1) {
				seen[A[lastDec + 1]] = lastDec + 1;
			}
			if (A[lastDec] > A[lastDec + 1]) {
				break;
			}
		}
		if (lastDec == -1) {
			cout << 0 << '\n';
			continue;
		}
		LL lastSeen{lastDec};
		for (LL i{0}; i < lastSeen + 1; i++) {
			lastSeen = max(lastSeen, seen[A[i]]);
		}

		fill(seen.begin(), seen.begin() + N + 1, 0);
		RF(i, 0, lastSeen + 1) {
			seen[A[i]]++;
		}
		LL unique{0};
		RF(i, 0, N + 1) {
			unique += seen[i] > 0;
		}
		cout << unique << '\n';
	}

	return 0;
}
