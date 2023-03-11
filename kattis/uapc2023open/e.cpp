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

bool close(long double X, long double Y) {
	return abs(X - Y) < 1e-9;
}

long double
cross(long double x1, long double y1, long double x2, long double y2) {
	return x1 * y2 - y1 * x2;
}

bool side(
	long double x1,
	long double y1,
	long double x2,
	long double y2,
	long double x3,
	long double y3) {
	// return cross(x2 - x1, y2 - y1, x3 - x2, y3 - y2) >= 0;
	return (x3 - x1) * (y2 - y1) - (y3 - y1) * (x2 - x1) >= 0;
}

int main(int, char const *[]) {
#if !defined(ONLINEJUDGE) && (defined(__APPLE__) || defined(__MACH__))
	std::freopen("../build/i.default.txt", "r", stdin);
	std::freopen("../build/o.default.txt", "w", stdout);
#endif

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	LL N;
	long double delta;
	cin >> N >> delta;

	vector<pair<long double, long double>> pos1(N), pos2(N);
	vector<long double> T(N);
	RF(i, 0, N) {
		cin >> pos1[i].first >> pos1[i].second >> pos2[i].first >> pos2[i].second >>
			T[i];
	}

	long double low{0}, high{1}, mid;
	while (low + 1e-9 < high) {
		mid = (low + high) / 2;
		bool possible{true};
		RF(i, 0, N) {
			if (
				close(pos1[i].first, pos2[i].first) &&
				(close(pos1[i].first, 0) || close(pos1[i].first, 1))) {
				continue;
			} else if (
				close(pos1[i].second, pos2[i].second) &&
				(close(pos1[i].second, 0) || close(pos1[i].second, 1))) {
				continue;
			}
			bool sides[]{
				side(
					pos1[i].first,
					pos1[i].second,
					pos2[i].first,
					pos2[i].second,
					(1 - mid) / 2,
					1 - (1 - mid) / 2),
				side(
					pos1[i].first,
					pos1[i].second,
					pos2[i].first,
					pos2[i].second,
					1 - (1 - mid) / 2,
					1 - (1 - mid) / 2),
				side(
					pos1[i].first,
					pos1[i].second,
					pos2[i].first,
					pos2[i].second,
					(1 - mid) / 2,
					(1 - mid) / 2),
				side(
					pos1[i].first,
					pos1[i].second,
					pos2[i].first,
					pos2[i].second,
					1 - (1 - mid) / 2,
					(1 - mid) / 2)};

			auto ratiotest{[&]() {
				long double sl1{abs(pos1[i].first - pos2[i].first)},
					sl2{abs(pos1[i].second - pos2[i].second)},
					hypo{sqrt(sl1 * sl1 + sl2 * sl2)}, rat{mid / 1}, slow{rat * hypo},
					fast{hypo - slow}, tt{fast / 0.1 + slow / (0.1 * delta)};
				return tt;
			}};
			auto tritest{[&](long double sl1, long double sl2) {
				// long double sl1{abs(pos1[i].first - pos2[i].first)},
				// 	sl2{abs(pos1[i].second - pos2[i].second)},
				long double hypo{sqrt(sl1 * sl1 + sl2 * sl2)}, push{(1 - mid) / 2},
					rat1{(sl1 - push) / sl1}, rat2{(sl2 * rat1 - push) / (sl2 * rat1)},
					slow{hypo * rat1 * rat2}, fast{hypo - slow};
				// tt{fast / 0.1 + slow / (0.1 * delta)};
				return make_pair(fast, slow);
			}};

			if (
				close(1, pos1[i].first) && close(0, pos2[i].first) ||
				close(0, pos1[i].first) && close(1, pos2[i].first)) {
				if (sides[0] == sides[1] && sides[2] == sides[3]) {
					if (sides[0] == sides[2]) {
						continue;
					} else {
						possible &= ratiotest() <= T[i];
					}
				} else {
					long double far, near;
					if (sides[0] != sides[1]) {
						far = 1 - pos1[i].second;
						near = 1 - pos2[i].second;
					} else {
						far = pos1[i].second;
						near = pos2[i].second;
					}
					if (far < near) {
						swap(far, near);
					}
					long double extra{near * (1 / (far - near))},
						hypo{sqrt((far - near) * (far - near) + 1)};
					auto tt{tritest(far, extra + 1)};
					possible &=
						(hypo - tt.second) / 0.1 + tt.second / (0.1 * delta) <= T[i];
				}
			} else if (
				close(1, pos1[i].second) && close(0, pos2[i].second) ||
				close(0, pos1[i].second) && close(1, pos2[i].second)) {
				if (sides[0] == sides[2] && sides[1] == sides[3]) {
					if (sides[0] == sides[1]) {
						continue;
					} else {
						possible &= ratiotest() <= T[i];
					}
				} else {
					long double far, near;
					if (sides[0] != sides[2]) {
						far = pos1[i].first;
						near = pos2[i].first;
					} else {
						far = 1 - pos1[i].first;
						near = 1 - pos2[i].first;
					}
					if (far < near) {
						swap(far, near);
					}
					long double extra{near * (1 / (far - near))},
						hypo{sqrt((far - near) * (far - near) + 1)};
					auto tt{tritest(far, extra + 1)};
					possible &=
						(hypo - tt.second) / 0.1 + tt.second / (0.1 * delta) <= T[i];
				}
			} else {
				if (
					sides[0] == sides[1] && sides[1] == sides[2] &&
					sides[2] == sides[3]) {
					continue;
				}
				long double sl1{abs(pos1[i].first - pos2[i].first)},
					sl2{abs(pos1[i].second - pos2[i].second)};
				auto tt{tritest(sl1, sl2)};
				possible &= tt.first / 0.1 + tt.second / (0.1 * delta) <= T[i];
			}
		}
		if (possible) {
			low = mid;
		} else {
			high = mid;
		}
	}
	cout << setprecision(12) << low;

	return 0;
}
