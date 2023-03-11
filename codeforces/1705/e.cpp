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

#define RF(x, from, to)                                                      \
	for (long long x = from, _to = to, _delta{x < _to ? 1LL : -1LL}; x != _to; \
			 x += _delta)

using LL = long long;
using namespace std;

#pragma hdrstop	 // ------------------------------------------------------------

set<LL> zeros, ones;

void add(LL X) {
	auto p0{zeros.upper_bound(X)}, p1{ones.upper_bound(X)};
	auto prev0{*prev(p0)}, prev1{*prev(p1)};
	if (prev0 > prev1) {
		auto next1{*p1};
		if (next1 - prev0 == 1) {
			zeros.erase(X);
			ones.erase(next1);
		} else if (X == prev0) {
			zeros.erase(X);
			zeros.insert(X + 1);
		} else if (X == next1 - 1) {
			ones.erase(next1);
			ones.insert(next1 - 1);
		} else {
			ones.insert(X);
			zeros.insert(X + 1);
		}
	} else {
		auto next0{*p0};
		if (next0 - prev1 == 1) {
			ones.erase(X);
			zeros.erase(next0);
		} else if (X == prev1) {
			ones.erase(X);
			zeros.erase(next0);
		} else if (X == next0 - 1) {
			zeros.erase(next0);
			zeros.insert(next0 - 1);
		} else {
			zeros.erase(next0);
			zeros.insert(X);
		}
		add(next0);
	}
}

void subtract(LL X) {
	auto p0{zeros.upper_bound(X)}, p1{ones.upper_bound(X)};
	auto prev0{*prev(p0)}, prev1{*prev(p1)};
	if (prev0 > prev1) {
		auto next1{*p1};
		if (next1 - prev0 == 1) {
			zeros.erase(X);
			ones.erase(next1);
		} else if (X == prev0) {
			zeros.erase(X);
			ones.erase(next1);
		} else if (X == next1 - 1) {
			ones.erase(next1);
			ones.insert(next1 - 1);
		} else {
			ones.insert(X);
			ones.erase(next1);
		}
		subtract(next1);
	} else {
		auto next0{*p0};
		if (next0 - prev1 == 1) {
			ones.erase(X);
			zeros.erase(next0);
		} else if (X == prev1) {
			ones.erase(X);
			ones.insert(X + 1);
		} else if (X == next0 - 1) {
			zeros.erase(next0);
			zeros.insert(next0 - 1);
		} else {
			zeros.insert(X);
			ones.insert(X + 1);
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

	zeros.insert(-2);
	zeros.insert(0);
	ones.insert(-1);
	ones.insert(LLONG_MAX / 10);

	LL N, Q;
	cin >> N >> Q;
	vector<LL> A(N);
	RF(i, 0, N) {
		cin >> A[i];
		add(A[i]);
	}
	RF(i, 0, Q) {
		LL K, L;
		cin >> K >> L;
		subtract(A[K - 1]);
		add(L);
		A[K - 1] = L;
		cout << (*prev(zeros.end())) - 1 << '\n';
	}

	return 0;
}
