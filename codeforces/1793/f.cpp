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

	LL N, Q;
	cin >> N;
	vector<LL> A(N);
	RF(i, 0, N) {
		cin >> A[i];
	}
	cin >> Q;

	LL sqn(sqrt(N)), cbc{(N + sqn - 1) / sqn};
	vector<vector<pair<pair<LL, LL>, LL>>> LR(cbc);
	RF(i, 0, Q) {
		LL L, R;
		cin >> L >> R;
		LR[L / sqn].push_back({{L - 1, R - 1}, i});
	}

	vector<LL> ans(Q);
	RF(i, 0, cbc) {
		if (LR[i].empty()) {
			continue;
		}
		sort(LR[i].begin(), LR[i].end(), [](auto const &X, auto const &Y) {
			return X.first.second < Y.first.second;
		});

		set<LL> s;
		priority_queue<LL, vector<LL>, greater<LL>> q;
		unordered_map<LL, LL> diffe;
		LL low{LR[i][0].first.first}, high{low - 1};
		RF(j, 0, LR[i].size()) {
			while (high < LR[i][j].first.second) {
				high++;
				auto k{s.insert(A[high]).first};
				if (k != s.begin()) {
					q.push(*k - *prev(k));
				}
				if (next(k) != s.end()) {
					q.push(*next(k) - *k);
				}
				if (k != s.begin() && next(k) != s.end()) {
					diffe[*next(k) - *prev(k)]++;
				}
			}
			while (low > LR[i][j].first.first) {
				low--;
				auto k{s.insert(A[low]).first};
				if (k != s.begin()) {
					q.push(*k - *prev(k));
				}
				if (next(k) != s.end()) {
					q.push(*next(k) - *k);
				}
				if (k != s.begin() && next(k) != s.end()) {
					diffe[*next(k) - *prev(k)]++;
				}
			}
			while (low < LR[i][j].first.first) {
				auto k{s.find(A[low])};
				if (k != s.begin()) {
					diffe[*k - *prev(k)]++;
				}
				if (next(k) != s.end()) {
					diffe[*next(k) - *k]++;
				}
				if (k != s.begin() && next(k) != s.end()) {
					q.push(*next(k) - *prev(k));
				}
				s.erase(k);
				low++;
			}

			LL top{q.top()};
			while (diffe[top] > 0) {
				diffe[top]--;
				q.pop();
				top = q.top();
			}
			ans[LR[i][j].second] = top;
		}
	}

	RF(i, 0, Q) {
		cout << ans[i] << '\n';
	}
	return 0;
}
