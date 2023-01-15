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

	LL T;
	cin >> T;
	while (T--) {
		LL N;
		cin >> N;
		string S;
		cin >> S;
		array<LL, 26> frc;
		array<pair<LL, LL>, 26> freq;
		RF(i, 0, N) {
			freq[S[i] - 'a'].first++;
		}
		RF(i, 0, 26) {
			freq[i].second = i;
		}
		sort(freq.begin(), freq.end(), [](auto &a, auto &b) {
			return a.first > b.first;
		});
		RF(i, 0, 26) {
			frc[freq[i].second] = i;
		}
		LL best{N}, ans{0};
		RF(i, 1, 27) {
			if (N % i != 0) {
				continue;
			}
			LL cur{0};
			RF(j, 0, i) {
				cur += abs(freq[j].first - N / i);
			}
			RF(j, i, 26) {
				cur += freq[j].first;
			}
			cur /= 2;
			if (cur < best) {
				best = cur;
				ans = i;
			}
		}
		cout << best << '\n';

		unordered_set<LL> red;
		RF(i, 0, ans) {
			if (freq[i].first > N / ans) {
				red.insert(freq[i].second);
			}
		}
		RF(i, 0, N) {
			if (red.count(S[i] - 'a')) {
				freq[frc[S[i] - 'a']].first--;
				if (freq[frc[S[i] - 'a']].first == N / ans) {
					red.erase(S[i] - 'a');
				}
				S[i] = ' ';
			}
		}

		red.clear();
		RF(i, ans, 26) {
			if (freq[i].first > 0) {
				red.insert(freq[i].second);
			}
		}
		RF(i, 0, N) {
			if (red.count(S[i] - 'a')) {
				freq[frc[S[i] - 'a']].first--;
				if (freq[frc[S[i] - 'a']].first == 0) {
					red.erase(S[i] - 'a');
				}
				S[i] = ' ';
			}
		}

		vector<LL> add;
		RF(i, 0, ans) {
			if (freq[i].first < N / ans) {
				add.push_back(freq[i].second);
			}
		}
		RF(i, 0, N) {
			if (S[i] != ' ') {
				continue;
			}
			S[i] = add.back() + 'a';
			freq[frc[add.back()]].first++;
			if (freq[frc[add.back()]].first == N / ans) {
				add.pop_back();
			}
		}

		cout << S << '\n';
	}

	return 0;
}
