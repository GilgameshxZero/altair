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
		LL M;
		cin >> M;

		vector<LL> ud(M * 2);
		RF(i, 0, M * 2) {
			cin >> ud[i];
		}
		reverse(ud.begin() + M, ud.end());
		vector<LL> pc;
		LL pcl{M}, pch{M - 1}, mud{-1}, mdu{-1};
		RF(i, M - 1, -1) {
			if (i == M - 1) {
				if (M % 2 == 0) {
					pcl--;
					mud = max(mud, ud[pcl] + M * 2 - 1 - pcl);
					mdu = max(mdu, ud[pcl] + pcl);
				} else {
					pch++;
					mud = max(mud, ud[pch] + M * 2 - 1 - pch);
					mdu = max(mdu, ud[pch] + pch);
				}
			} else if (i % 2 == 0) {
				pch++;
				mud = max(mud, ud[pch] + M * 2 - 1 - pch);
				mdu = max(mdu, ud[pch] + pch);
				pch++;
				mud = max(mud, ud[pch] + M * 2 - 1 - pch);
				mdu = max(mdu, ud[pch] + pch);
			} else {
				pcl--;
				mud = max(mud, ud[pcl] + M * 2 - 1 - pcl);
				mdu = max(mdu, ud[pcl] + pcl);
				pcl--;
				mud = max(mud, ud[pcl] + M * 2 - 1 - pcl);
				mdu = max(mdu, ud[pcl] + pcl);
			}
			if (i % 2 == 0) {
				pc.push_back(mud);
			} else {
				pc.push_back(mdu);
			}
		}
		LL prev{0}, ans{LLONG_MAX / 2};
		RF(i, 0, M) {
			if (i == 0) {
				prev = -1;
			} else if (i % 2 == 0) {
				prev = max({prev + 2, ud[i - 1] + 1, ud[i]});
			} else {
				prev = max({prev + 2, ud[M * 2 - i] + 1, ud[M * 2 - i - 1]});
			}
			ans = min(
				ans, max(prev + 1 + M * 2 - i * 2 - 1, pc[pc.size() - 1 - i] - i + 1));
		}
		cout << ans << '\n';
	}

	return 0;
}
