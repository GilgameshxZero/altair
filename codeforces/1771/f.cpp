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

struct custom_hash {
	static uint64_t splitmix64(uint64_t x) {
		// http://xorshift.di.unimi.it/splitmix64.c
		x += 0x9e3779b97f4a7c15;
		x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
		x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
		return x ^ (x >> 31);
	}

	size_t operator()(uint64_t x) const {
		static const uint64_t FIXED_RANDOM =
			chrono::steady_clock::now().time_since_epoch().count();
		return splitmix64(x + FIXED_RANDOM);
	}
};

// [L, R).
LL cnt2xBs(vector<LL> &pos2, LL L, LL R) {
	return lower_bound(pos2.begin(), pos2.end(), R) -
		lower_bound(pos2.begin(), pos2.end(), L);
}

int main(int, char const *[]) {
#if !defined(ONLINEJUDGE) && (defined(__APPLE__) || defined(__MACH__))
	std::freopen("../build/i.default.txt", "r", stdin);
	std::freopen("../build/o.default.txt", "w", stdout);
#endif

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	LL N;
	cin >> N;

	vector<LL> A(N);
	RF(i, 0, N) {
		cin >> A[i];
	}

	unordered_map<LL, vector<LL>, custom_hash> pos;
	RF(i, 0, N) {
		pos[A[i]].push_back(i);
	}
	for (auto &i : pos) {
		sort(i.second.begin(), i.second.end());
	}

	LL sqN{0};
	while (sqN * sqN < N) {
		++sqN;
	}
	LL cBuckets{(N + sqN - 1) / sqN};
	vector<LL> bBegin(cBuckets + 1);
	RF(i, 0, cBuckets) {
		bBegin[i] = i * sqN;
	}
	bBegin.back() = N;

	vector<set<LL>> preOdd(cBuckets);
	RF(i, 0, cBuckets) {
		set<LL> odd;
		RF(j, bBegin[i], bBegin[i + 1]) {
			auto it{odd.find(A[j])};
			if (it == odd.end()) {
				odd.insert(A[j]);
			} else {
				odd.erase(it);
			}
		}
		preOdd[i] = odd;
		while (preOdd[i].size() > sqN) {
			auto j{preOdd[i].end()};
			j--;
			preOdd[i].erase(j);
		}
	}

	LL Q, prevAns{0};
	cin >> Q;
	RF(i, 0, Q) {
		LL X, Y;
		cin >> X >> Y;
		LL L{(X ^ prevAns) - 1}, R{(Y ^ prevAns)};

		LL lBucket{L / sqN}, rBucket{R / sqN - 1};
		set<LL> xorOdd;
		if (rBucket >= 0 && lBucket < rBucket) {
			xorOdd = preOdd[rBucket];
			for (auto &j : preOdd[lBucket]) {
				auto it{xorOdd.find(j)};
				if (it == xorOdd.end()) {
					xorOdd.insert(j);
				} else {
					xorOdd.erase(it);
				}
			}
			RF(j, L, bBegin[lBucket + 1]) {
				auto it{xorOdd.find(A[j])};
				if (it == xorOdd.end()) {
					xorOdd.insert(A[j]);
				} else {
					xorOdd.erase(it);
				}
			}
			RF(j, bBegin[rBucket + 1], R) {
				auto it{xorOdd.find(A[j])};
				if (it == xorOdd.end()) {
					xorOdd.insert(A[j]);
				} else {
					xorOdd.erase(it);
				}
			}
		} else {
			RF(j, L, R) {
				auto it{xorOdd.find(A[j])};
				if (it == xorOdd.end()) {
					xorOdd.insert(A[j]);
				} else {
					xorOdd.erase(it);
				}
			}
		}

		prevAns = xorOdd.empty() ? 0 : *xorOdd.begin();
		cout << prevAns << '\n';
	}

	return 0;
}
