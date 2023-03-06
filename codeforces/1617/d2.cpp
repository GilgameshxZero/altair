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

/* ------------------------ End of primary template. ------------------------ */

LL query(LL X, LL Y, LL Z) {
	cout << "? " << X + 1 << ' ' << Y + 1 << ' ' << Z + 1 << '\n' << flush;
	LL ans;
	cin >> ans;
	return ans;
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
		vector<LL> status(N, -1);
		vector<LL> qr(N / 3);
		LL qr0, qr1;
		RF(i, 0, N / 3) {
			qr[i] = query(i * 3, i * 3 + 1, i * 3 + 2);
			if (qr[i] == 0) {
				qr0 = i;
			} else if (qr[i] == 1) {
				qr1 = i;
			}
		}
		LL a{query(qr0 * 3, qr0 * 3 + 1, qr1 * 3)},
			b{query(qr0 * 3, qr0 * 3 + 1, qr1 * 3 + 1)},
			c{query(qr0 * 3, qr0 * 3 + 1, qr1 * 3 + 2)},
			d{query(qr1 * 3, qr1 * 3 + 1, qr0 * 3)},
			e{query(qr1 * 3, qr1 * 3 + 1, qr0 * 3 + 1)},
			f{query(qr1 * 3, qr1 * 3 + 1, qr0 * 3 + 2)};
		LL i0, i1;
		if (a == 0 && b == 0 && c == 0) {
			i0 = qr0 * 3;
			status[qr0 * 3] = status[qr0 * 3 + 1] = 0;
		} else {
			i0 = qr0 * 3 + 2;
			status[qr0 * 3 + 2] = 0;
		}
		if (d == 1 && e == 1 && f == 1) {
			i1 = qr1 * 3;
			status[qr1 * 3] = status[qr1 * 3 + 1] = 1;
		} else {
			i1 = qr1 * 3 + 2;
			status[qr1 * 3 + 2] = 1;
		}

		if (i0 == qr0 * 3) {
			status[qr0 * 3 + 2] = query(i0, i1, qr0 * 3 + 2);
		} else {
			status[qr0 * 3] = query(i0, i1, qr0 * 3);
			status[qr0 * 3 + 1] = query(i0, i1, qr0 * 3 + 1);
		}
		if (i1 == qr1 * 3) {
			status[qr1 * 3 + 2] = query(i0, i1, qr1 * 3 + 2);
		} else {
			status[qr1 * 3] = query(i0, i1, qr1 * 3);
			status[qr1 * 3 + 1] = query(i0, i1, qr1 * 3 + 1);
		}

		RF(i, 0, N / 3) {
			if (i == qr0 || i == qr1) {
				continue;
			}
			if (qr[i] == 0) {
				LL X{query(i1, i * 3, i * 3 + 1)}, Y{query(i1, i * 3, i * 3 + 2)};
				if (X == 1 && Y == 1) {
					status[i * 3] = 1;
					status[i * 3 + 1] = status[i * 3 + 2] = 0;
				} else if (X == 0 && Y == 0) {
					status[i * 3] = status[i * 3 + 1] = status[i * 3 + 2] = 0;
				} else {
					status[i * 3] = 0;
					status[i * 3 + 1] = X;
					status[i * 3 + 2] = Y;
				}
			} else if (qr[i] == 1) {
				LL X{query(i0, i * 3, i * 3 + 1)}, Y{query(i0, i * 3, i * 3 + 2)};
				if (X == 0 && Y == 0) {
					status[i * 3] = 0;
					status[i * 3 + 1] = status[i * 3 + 2] = 1;
				} else if (X == 1 && Y == 1) {
					status[i * 3] = status[i * 3 + 1] = status[i * 3 + 2] = 1;
				} else {
					status[i * 3] = 1;
					status[i * 3 + 1] = X;
					status[i * 3 + 2] = Y;
				}
			}
		}

		// i0 = s0;
		// i1 = s1;
		// for (auto const &i : {qr0, qr1}) {
		// 	if (qr[i] == 0) {
		// 		LL X{query(i1, i * 3, i * 3 + 1)}, Y{query(i1, i * 3, i * 3 + 2)};
		// 		if (X == 1 && Y == 1) {
		// 			status[i * 3] = 1;
		// 			status[i * 3 + 1] = status[i * 3 + 2] = 0;
		// 		} else if (X == 0 && Y == 0) {
		// 			status[i * 3] = status[i * 3 + 1] = status[i * 3 + 2] = 0;
		// 		} else {
		// 			status[i * 3] = 0;
		// 			status[i * 3 + 1] = X;
		// 			status[i * 3 + 2] = Y;
		// 		}
		// 	} else if (qr[i] == 1) {
		// 		LL X{query(i0, i * 3, i * 3 + 1)}, Y{query(i0, i * 3, i * 3 + 2)};
		// 		if (X == 0 && Y == 0) {
		// 			status[i * 3] = 0;
		// 			status[i * 3 + 1] = status[i * 3 + 2] = 1;
		// 		} else if (X == 1 && Y == 1) {
		// 			status[i * 3] = status[i * 3 + 1] = status[i * 3 + 2] = 1;
		// 		} else {
		// 			status[i * 3] = 1;
		// 			status[i * 3 + 1] = X;
		// 			status[i * 3 + 2] = Y;
		// 		}
		// 	}
		// }

		LL imps{0};
		RF(i, 0, N) {
			imps += status[i] == 0;
		}
		cout << "! " << imps;
		RF(i, 0, N) {
			if (status[i] == 0) {
				cout << ' ' << i + 1;
			}
		}
		cout << '\n' << flush;
	}

	return 0;
}
