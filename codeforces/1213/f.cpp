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

int main(int, char const *[]) {
#if !defined(ONLINEJUDGE) && (defined(__APPLE__) || defined(__MACH__))
	std::freopen("../build/i.default.txt", "r", stdin);
	std::freopen("../build/o.default.txt", "w", stdout);
#endif

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	LL N, K;
	cin >> N >> K;
	vector<LL> P(N), br(N);
	RF(i, 0, N) {
		cin >> P[i];
		P[i]--;
		br[P[i]] = i;
	}
	LL Q;
	cin >> Q;
	Q--;
	vector<pair<LL, LL>> tt, ttr;
	RF(i, 1, N) {
		LL Qn;
		cin >> Qn;
		Qn--;
		if (br[Qn] < br[Q]) {
			tt.push_back({br[Qn], br[Q]});
			ttr.push_back({br[Q], br[Qn]});
		}
		Q = Qn;
	}
	sort(tt.begin(), tt.end());
	sort(ttr.begin(), ttr.end());
	vector<LL> sec(N, 0);
	LL cint{0}, ii{0}, li{0};
	while (ii < tt.size() && tt[ii].first <= 0) {
		cint++;
		ii++;
	}
	RF(i, 1, N) {
		while (li < ttr.size() && ttr[li].first < i) {
			cint--;
			li++;
		}
		if (cint == 0) {
			sec[i] = sec[i - 1] + 1;
		} else {
			sec[i] = sec[i - 1];
		}
		while (ii < tt.size() && tt[ii].first <= i) {
			cint++;
			ii++;
		}
	}
	if (sec.back() < K - 1) {
		cout << "NO";
		return 0;
	}
	string ans(N, ' ');
	RF(i, 0, N) {
		ans[P[i]] = 'a' + min(sec[i], K - 1);
	}
	cout << "YES\n" << ans;
	return 0;
}
