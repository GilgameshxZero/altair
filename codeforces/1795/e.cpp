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

/* ---------------------------- End of template. ---------------------------- */

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
		vector<LL> H(N), R(N), L(N), A(N), B(N), presum(N), postsum(N), pr(N),
			pl(N);
		RF(i, 0, N) {
			cin >> H[i];
			R[i] = H[i] + i;
			L[i] = H[i] + N - 1 - i;
		}

		presum[0] = H[0];
		RF(i, 1, N) {
			presum[i] = presum[i - 1] + H[i];
		}
		postsum[N - 1] = H[N - 1];
		RF(i, N - 2, -1) {
			postsum[i] = postsum[i + 1] + H[i];
		}

		A[N - 1] = N;
		RF(i, N - 2, -1) {
			if (R[i + 1] <= R[i]) {
				A[i] = i + 1;
			} else {
				A[i] = A[i + 1];
				while (A[i] < N && R[A[i]] > R[i]) {
					A[i] = A[A[i]];
				}
			}
		}
		pr[N - 1] = 0;
		RF(i, N - 2, -1) {
			if (A[i] == N) {
				LL clamp{max(0LL, H[i] - (N - i))};
				pr[i] =
					postsum[i + 1] - (H[i] - 1) * H[i] / 2 + (clamp) * (clamp + 1) / 2;
			} else {
				LL clamp{max(0LL, H[i] - (A[i] - i))};
				pr[i] = pr[A[i]] + postsum[i + 1] - postsum[A[i]] -
					(H[i] - 1) * H[i] / 2 + (clamp) * (clamp + 1) / 2;
			}
		}

		B[0] = -1;
		RF(i, 1, N) {
			if (L[i - 1] <= L[i]) {
				B[i] = i - 1;
			} else {
				B[i] = B[i - 1];
				while (B[i] >= 0 && L[B[i]] > L[i]) {
					B[i] = B[B[i]];
				}
			}
		}
		pl[0] = 0;
		RF(i, 1, N) {
			if (B[i] == -1) {
				LL clamp{max(0LL, H[i] - 1 - i)};
				pl[i] =
					presum[i - 1] - (H[i] - 1) * H[i] / 2 + (clamp) * (clamp + 1) / 2;
			} else {
				LL clamp{max(0LL, H[i] - (i - B[i]))};
				pl[i] = pl[B[i]] + presum[i - 1] - presum[B[i]] -
					(H[i] - 1) * H[i] / 2 + (clamp) * (clamp + 1) / 2;
			}
		}

		LL ans{LLONG_MAX};
		RF(i, 0, N) {
			ans = min(ans, H[i] + pl[i] + pr[i]);
		}
		cout << ans << '\n';
	}

	return 0;
}
