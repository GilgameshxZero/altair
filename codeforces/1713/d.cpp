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

LL query(LL X, LL Y) {
	cout << "? " << X << ' ' << Y << endl;
	LL result;
	cin >> result;
	return result;
}

int main(int, char const *[]) {
#if !defined(ONLINEJUDGE) && (defined(__APPLE__) || defined(__MACH__))
	std::freopen("../build/i.default.txt", "r", stdin);
	std::freopen("../build/o.default.txt", "w", stdout);
#endif

	std::ios_base::sync_with_stdio(false);
	// std::cin.tie(nullptr);

	LL T;
	cin >> T;
	while (T--) {
		LL N;
		cin >> N;

		vector<LL> A(1LL << N);
		RF(i, 0, 1LL << N) {
			A[i] = i + 1;
		}
		while (N >= 2) {
			vector<LL> B(1LL << (N - 2));
			RF(i, 0, B.size()) {
				LL result{query(A[i * 4], A[i * 4 + 2])};
				if (result == 0) {
					B[i] = query(A[i * 4 + 1], A[i * 4 + 3]) == 1 ? A[i * 4 + 1]
																												: A[i * 4 + 3];
				} else if (result == 1) {
					B[i] = query(A[i * 4], A[i * 4 + 3]) == 1 ? A[i * 4] : A[i * 4 + 3];
				} else if (result == 2) {
					B[i] = query(A[i * 4 + 1], A[i * 4 + 2]) == 1 ? A[i * 4 + 1]
																												: A[i * 4 + 2];
				}
			}
			swap(A, B);
			N -= 2;
		}
		if (N == 1) {
			LL tmp{query(A[0], A[1]) == 1 ? A[0] : A[1]};
			A.clear();
			A.push_back(tmp);
		}
		cout << "! " << A[0] << endl;
	}

	return 0;
}
