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

int main(int, char const *[]) {
#if !defined(ONLINEJUDGE) && (defined(__APPLE__) || defined(__MACH__))
	std::freopen("../build/i.default.txt", "r", stdin);
	std::freopen("../build/o.default.txt", "w", stdout);
#endif

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	LL B;
	cin >> B;

	vector<array<LL, 27>> trie(1);
	trie[0].fill(-LLONG_MAX);
	RF(i, 0, B) {
		string S;
		cin >> S;
		LL cur{0};
		RF(j, 0, S.length()) {
			if (trie[cur][S[j] - 'a'] == -LLONG_MAX) {
				trie[cur][S[j] - 'a'] = trie.size();
				trie.push_back({});
				trie.back().fill(-LLONG_MAX);
			}
			cur = trie[cur][S[j] - 'a'];
		}
		trie[cur].back() = i;
	}

	string S;
	cin >> S;
	LL cur{0}, ans{0};
	RF(i, 0, S.length()) {
		cur = trie[cur][S[i] - 'a'];
		if (trie[cur].back() != -LLONG_MAX) {
			ans = ans * B + trie[cur].back();
			cur = 0;
		}
	}
	cout << ans;

	return 0;
}
