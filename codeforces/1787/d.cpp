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
		vector<LL> A(N);
		vector<unordered_set<LL>> B(N);
		RF(i, 0, N) {
			cin >> A[i];
			if (i + A[i] >= 0 && i + A[i] < N) {
				B[i + A[i]].insert(i);
			}
		}

		queue<LL> Q;
		vector<LL> Bm(N);
		RF(i, 0, N) {
			Bm[i] = B[i].size();
			if (Bm[i] == 0) {
				Q.push(i);
			}
		}

		vector<LL> iU(N, 0);
		LL chainTotal{0};
		while (!Q.empty()) {
			auto top{Q.front()};
			Q.pop();
			iU[top] = 1;
			for (auto const &i : B[top]) {
				iU[top] += iU[i];
			}
			if (top + A[top] >= 0 && top + A[top] < N) {
				Bm[top + A[top]]--;
				if (Bm[top + A[top]] == 0) {
					Q.push(top + A[top]);
				}
			} else {
				chainTotal += iU[top];
			}
		}

		vector<LL> cI(N, -1), ccc;
		LL cc{0};
		RF(i, 0, N) {
			if (iU[i] != 0) {
				continue;
			}
			LL cur{i}, cnt{0};
			do {
				cI[cur] = ccc.size();
				cur = cur + A[cur];
				cnt++;
			} while (cur >= 0 && cur < N && cur != i);
			ccc.push_back(cnt);
		}

		RF(i, 0, N) {
			if (iU[i] == 0) {
				continue;
			}
			stack<LL> S;
			S.push(i);
			S.push(i + A[i]);
			while (S.top() >= 0 && S.top() < N && iU[S.top()] != 0) {
				S.push(S.top() + A[S.top()]);
			}
			if (S.top() >= 0 && S.top() < N) {
				S.pop();
				while (!S.empty()) {
					iU[S.top()] = 0;
					S.pop();
				}
			}
		}

		vector<bool> iD(N, false);
		bool isLoop{false};
		LL cur{0};
		do {
			iD[cur] = true;
			cur = cur + A[cur];
		} while (cur >= 0 && cur < N && cI[cur] == -1);
		if (cur < 0 || cur >= N) {
			isLoop = false;
		} else {
			isLoop = true;
			RF(i, 0, N) {
				if (cI[i] != cI[cur]) {
					continue;
				}
				iD[i] = true;
			}
		}

		LL ans{0};
		RF(i, 0, N) {
			if (iD[i]) {
				ans += N + 1 + (chainTotal - iU[i]);
			} else {
				ans += isLoop ? 0 : (N * 2 + 1);
			}
		}
		cout << ans << '\n';
	}

	return 0;
}
