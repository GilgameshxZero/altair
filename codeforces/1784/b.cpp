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
		LL M;
		cin >> M;

		// w for i, i for n, n for w, i for w, n for i, w for n.
		vector<LL> ids[6];
		string S;
		LL ow, oi, on;
		RF(i, 0, M) {
			cin >> S;
			ow = oi = on = 0;
			RF(j, 0, 3) {
				ow += S[j] == 'w';
				oi += S[j] == 'i';
				on += S[j] == 'n';
			}
			if (ow == 3) {
				ids[0].push_back(i);
				ids[5].push_back(i);
			} else if (oi == 3) {
				ids[1].push_back(i);
				ids[3].push_back(i);
			} else if (on == 3) {
				ids[2].push_back(i);
				ids[4].push_back(i);
			} else if (ow == 2 && oi == 0) {
				ids[0].push_back(i);
			} else if (oi == 2 && on == 0) {
				ids[1].push_back(i);
			} else if (on == 2 && ow == 0) {
				ids[2].push_back(i);
			} else if (oi == 2 && ow == 0) {
				ids[3].push_back(i);
			} else if (on == 2 && oi == 0) {
				ids[4].push_back(i);
			} else if (ow == 2 && on == 0) {
				ids[5].push_back(i);
			}
		}

		vector<pair<LL, LL>> As;
		vector<pair<char, char>> Cs;
		while (ids[0].size() > 0 && ids[3].size() > 0) {
			As.push_back({ids[0].back(), ids[3].back()});
			Cs.push_back({'w', 'i'});
			ids[0].pop_back();
			ids[3].pop_back();
		}
		while (ids[1].size() > 0 && ids[4].size() > 0) {
			As.push_back({ids[1].back(), ids[4].back()});
			Cs.push_back({'i', 'n'});
			ids[1].pop_back();
			ids[4].pop_back();
		}
		while (ids[2].size() > 0 && ids[5].size() > 0) {
			As.push_back({ids[2].back(), ids[5].back()});
			Cs.push_back({'n', 'w'});
			ids[2].pop_back();
			ids[5].pop_back();
		}
		while (ids[0].size() > 0 && ids[1].size() > 0 && ids[2].size() > 0) {
			As.push_back({ids[0].back(), ids[1].back()});
			Cs.push_back({'w', 'i'});
			As.push_back({ids[1].back(), ids[2].back()});
			Cs.push_back({'w', 'n'});
			ids[0].pop_back();
			ids[1].pop_back();
			ids[2].pop_back();
		}
		while (ids[3].size() > 0 && ids[4].size() > 0 && ids[5].size() > 0) {
			As.push_back({ids[3].back(), ids[5].back()});
			Cs.push_back({'i', 'w'});
			As.push_back({ids[4].back(), ids[5].back()});
			Cs.push_back({'n', 'i'});
			ids[3].pop_back();
			ids[4].pop_back();
			ids[5].pop_back();
		}

		cout << As.size() << '\n';
		RF(i, 0, As.size()) {
			cout << As[i].first + 1 << ' ' << Cs[i].first << ' ' << As[i].second + 1
					 << ' ' << Cs[i].second << '\n';
		}
	}

	return 0;
}
