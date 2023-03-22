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

void split(vector<pair<LL, LL>> &R, vector<LL> &A, LL rem) {
	if (rem == 0) {
		vector<LL> B(A);
		return;
	}

	array<LL, 18> count;
	count.fill(0);
	RF(i, 0, R.size()) {
		count[R[i].first]++;
	}
	LL common{0};
	RF(i, 0, count.size()) {
		if (count[i] > count[common]) {
			common = i;
		}
	}

	vector<pair<LL, LL>> s[2];
	bool flip{false};
	RF(i, 0, R.size()) {
		if (R[i].first == common) {
			flip = !flip;
		} else {
			s[flip].push_back(R[i]);
		}
	}

	split(s[0], A, rem - 1);
	RF(i, 0, A.size() / (1LL << (common + 1))) {
		RF(
			j,
			i * (1LL << (common + 1)),
			i * (1LL << (common + 1)) + (1LL << common)) {
			swap(A[j], A[j + (1LL << common)]);
		}
	}
	split(s[1], A, rem - 1);
	RF(i, 0, A.size() / (1LL << (common + 1))) {
		RF(
			j,
			i * (1LL << (common + 1)),
			i * (1LL << (common + 1)) + (1LL << common)) {
			swap(A[j], A[j + (1LL << common)]);
		}
	}
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
		LL N, Q;
		cin >> N;
		vector<LL> A(N);
		RF(i, 0, N) {
			cin >> A[i];
		}
		cin >> Q;
		vector<LL> R(Q);
		RF(i, 0, Q) {
			cin >> R[i];
		}

		split(R, A, 9);
	}

	return 0;
}
