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

	LL N, L, D;
	cin >> N >> L >> D;

	vector<unordered_map<char, vector<LL>>> b0s(L);
	vector<string> S(N);
	RF(i, 0, N) {
		cin >> S[i];
		RF(j, 0, L) {
			b0s[j][S[i][j]].push_back(i);
		}
	}

	vector<LL> bi;
	RF(i, 0, L) {
		if (b0s[i].size() > 1) {
			bi.push_back(i);
		}
	}
	if (bi.size() > N * D) {
		cout << 0;
		return 0;
	}

	vector<string> cand(1);
	RF(i, 0, bi.size()) {
		cand[0].push_back(S[0][bi[i]]);
	}
	vector<array<LL, 50>> relief;
	vector<LL> bad, ch;
	vector<array<LL, 7>> ixs;
	while (!cand.empty()) {
		if (ch.size() < cand.size()) {
			relief.push_back({});
			relief.back().fill(0);
			RF(i, 0, bi.size()) {
				for (auto const &j : b0s[bi[i]]) {
					if (j.first == cand.back()[i]) {
						continue;
					}
					for (auto const &k : j.second) {
						relief.back()[k]++;
						if (relief.back()[k] > D) {
							bad.push_back(k);
							break;
						}
					}
					if (bad.size() == cand.size()) {
						break;
					}
				}
				if (bad.size() == cand.size()) {
					break;
				}
			}
			if (bad.size() < cand.size()) {
				RF(i, 0, bi.size()) {
					S[0][bi[i]] = cand.back()[i];
				}
				cout << S[0];
				return 0;
			}

			ixs.push_back({});
			LL ixss{0};
			RF(i, 0, bi.size()) {
				if (ixss > D) {
					break;
				}
				if (cand.back()[i] != S[bad.back()][bi[i]]) {
					ixs.back()[ixss++] = i;
				}
			}
			ch.push_back(-1);
		}

		if (cand.size() <= D) {
			ch.back()++;
			if (ch.back() < D + 1) {
				cand.push_back(cand.back());
				cand.back()[ixs.back()[ch.back()]] =
					S[bad.back()][bi[ixs.back()[ch.back()]]];
				continue;
			}
		}

		cand.pop_back();
		relief.pop_back();
		bad.pop_back();
		ixs.pop_back();
		ch.pop_back();
	}

	cout << 0;
	return 0;
}
