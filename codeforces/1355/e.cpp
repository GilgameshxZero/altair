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

/* ---------------------------- End of template. ---------------------------- */

LL cost(vector<LL> &presum, LL A, LL R, LL M, LL x) {
	LL N = presum.size() - 1;
	LL low{0}, high{N + 1}, mid;
	while (low + 1 < high) {
		mid = (low + high) / 2;
		if (presum[mid] - presum[mid - 1] >= x) {
			high = mid;
		} else {
			low = mid;
		}
	}
	LL ldelta{low * x - presum[low]},
		hdelta{presum[N] - presum[low] - (N - low) * x};

	if (A + R < M) {
		return ldelta * A + hdelta * R;
	} else {
		return min(ldelta, hdelta) * M +
			(ldelta < hdelta ? (hdelta - ldelta) * R : (ldelta - hdelta) * A);
	}
	return 0;
}

int main(int, char const *[]) {
#if !defined(ONLINEJUDGE) && (defined(__APPLE__) || defined(__MACH__))
	std::freopen("../build/i.default.txt", "r", stdin);
	std::freopen("../build/o.default.txt", "w", stdout);
#endif

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	LL N, A, R, M, sum{0};
	cin >> N >> A >> R >> M;
	vector<LL> H(N), presum(N + 1);
	RF(i, 0, N) {
		cin >> H[i];
		sum += H[i];
	}
	sort(H.begin(), H.end());
	presum[0] = 0;
	RF(i, 1, N + 1) {
		presum[i] = presum[i - 1] + H[i - 1];
	}

	LL low{0}, high{H.back() + 1}, mid1, mid2;
	while (low + 2 < high) {
		mid1 = low + (high - low) / 3;
		mid2 = low + 2 * (high - low) / 3;

		LL cost1{cost(presum, A, R, M, mid1)}, cost2{cost(presum, A, R, M, mid2)};
		if (cost1 < cost2) {
			high = mid2;
		} else {
			low = mid1;
		}
	}
	cout << min(cost(presum, A, R, M, low), cost(presum, A, R, M, low + 1));
	return 0;
}
