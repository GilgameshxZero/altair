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

	LL N, Q;
	cin >> N >> Q;
	vector<LL> S(N);
	deque<LL> A;
	RF(i, 0, N) {
		cin >> S[i];
		A.push_back(S[i]);
	}

	vector<set<pair<LL, LL>>> wins(N);
	LL eqn{0};
	for (; A.front() != N; eqn++) {
		LL first{A.front()};
		A.pop_front();
		LL second{A.front()};
		A.pop_front();
		A.push_front(max(first, second));
		A.push_back(min(first, second));
		wins[A.front() - 1].insert({eqn, wins[A.front() - 1].size()});
	}

	RF(i, 0, Q) {
		LL I, K;
		cin >> I >> K;
		auto j{wins[S[I - 1] - 1].upper_bound({K, -1})};
		cout << (j == wins[S[I - 1] - 1].end() ? wins[S[I - 1] - 1].size()
																					 : j->second) +
				(S[I - 1] == N ? max(0LL, K - eqn) : 0)
				 << '\n';
	}
	return 0;
}
