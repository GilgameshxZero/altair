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

	LL N;
	cin >> N;
	vector<LL> P(N), Q(N);
	RF(i, 0, N) {
		cin >> P[i];
	}
	RF(i, 0, N) {
		cin >> Q[i];
	}

	vector<LL> psuf(N), ppre(N), qsuf(N), qpre(N);
	psuf[0] = qsuf[0] = N + 1;
	ppre.back() = qpre.back() = N + 1;
	RF(i, 1, N) {
		psuf[i] = min(psuf[i - 1], P[i - 1]);
		qsuf[i] = min(qsuf[i - 1], Q[i - 1]);
	}
	RF(i, N - 2, -1) {
		ppre[i] = min(ppre[i + 1], P[i + 1]);
		qpre[i] = min(qpre[i + 1], Q[i + 1]);
	}

	vector<LL> pep(N);
	pep[0] = ppre[0] == qpre[0];
	RF(i, 1, N) {
		pep[i] = pep[i - 1] + (ppre[i] == qpre[i]);
	}

	LL ans{0};
	RF(i, 0, N) {
		LL XX{lower_bound(ppre.begin() + i, ppre.end(), psuf[i]) - ppre.begin()},
			YY{lower_bound(qpre.begin() + i, qpre.end(), qsuf[i]) - qpre.begin()};

		ans += min(XX, YY) == 0 ? 0 : pep[min(XX, YY) - 1];
		ans -= i == 0 ? 0 : pep[i - 1];
		ans += psuf[i] == qsuf[i] ? N - max(XX, YY) : 0;

		if (XX < YY) {
			LL z1{
				lower_bound(qpre.begin() + XX, qpre.begin() + YY, psuf[i]) -
				qpre.begin()},
				z2{
					upper_bound(qpre.begin() + XX, qpre.begin() + YY, psuf[i]) -
					qpre.begin()};
			ans += z2 - z1;
		} else if (YY < XX) {
			LL z1{
				lower_bound(ppre.begin() + YY, ppre.begin() + XX, qsuf[i]) -
				ppre.begin()},
				z2{
					upper_bound(ppre.begin() + YY, ppre.begin() + XX, qsuf[i]) -
					ppre.begin()};
			ans += z2 - z1;
		}
	}
	cout << ans;
	return 0;
}