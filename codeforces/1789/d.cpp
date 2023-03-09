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

using LL = long long;
using LD = long double;

#define RF(x, from, to)                                                      \
	for (long long x = from, _to = to, _delta{x < _to ? 1LL : -1LL}; x != _to; \
			 x += _delta)

using namespace std;

#pragma hdrstop

/* ------------------------ End of primary template. ------------------------ */

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
		string _A, _B;
		cin >> _A >> _B;

		vector<bool> A(N), B(N);
		RF(i, 0, N) {
			A[i] = _A[i] == '1';
			B[i] = _B[i] == '1';
		}
		vector<LL> ans;

		auto splay{[&](LL shift) {
			ans.push_back(shift);
			if (shift > 0) {
				RF(i, 0, N - shift) {
					A[i] = A[i] ^ A[i + shift];
				}
			} else {
				RF(i, N - 1, -shift - 1) {
					A[i] = A[i] ^ A[i + shift];
				}
			}
		}};

		LL lA(_A.find_first_of('1')), rB(_B.find_last_of('1'));
		if (lA == string::npos && rB == string::npos) {
			cout << "0\n";
			continue;
		} else if ((lA == string::npos) ^ (rB == string::npos)) {
			cout << "-1\n";
			continue;
		}
		if (lA > rB) {
			splay(lA - rB);
			lA = rB;
		}
		RF(i, rB, N) {
			if (A[i] != B[i]) {
				splay(lA - i);
			}
		}
		RF(i, rB, -1) {
			if (A[i] != B[i]) {
				splay(rB - i);
			}
		}
		cout << ans.size() << '\n';
		RF(i, 0, ans.size()) {
			cout << ans[i] << ' ';
		}
		cout << '\n';
	}

	return 0;
}
