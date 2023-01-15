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

class R {
	public:
	LL u, l, d, r, i;
};

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
		map<LL, unordered_map<LL, R>> Rs;
		LL N;
		cin >> N;
		RF(i, 0, N) {
			LL u, l, d, r;
			cin >> u >> l >> d >> r;
			Rs[l].insert({i, {u, l, d, r, i}});
		}
		vector<R *> carry;
		for (auto i{Rs.begin()}; i != Rs.end(); i++) {
			decltype(carry) c2;
			RF(j, 0, carry.size()) {
				if (carry[j]->r >= i->first) {
					c2.push_back(carry[j]);
				}
			}
			swap(c2, carry);
			if (carry.size() == 2 && carry[0]->u == 2) {
				swap(carry[0], carry[1]);
			}

			for (auto j{i->second.begin()}; j != i->second.end();) {
				R &s{j->second};
				if (s.l > s.r) {
					continue;
				}
				if (carry.empty()) {
					carry.push_back(&s);
				} else if (carry.size() == 1 && carry[0]->u != carry[0]->d) {
					if (s.r <= carry[0]->r) {
						s.u = s.d = s.l = s.r = 0;
						Rs[s.l].insert({s.i, s});
						j = i->second.erase(j);
						continue;
					} else {
						s.l = carry[0]->r + 1;
						Rs[s.l].insert({s.i, s});
						j = i->second.erase(j);
						continue;
					}
				} else if (carry.size() == 1) {
					if (s.u != s.d && s.r >= carry[0]->r) {
						carry[0]->r = s.l - 1;
						carry.pop_back();
						carry.push_back(&s);
					} else if (s.u != s.d && s.r < carry[0]->r) {
						s.u = s.d = 3 - carry[0]->u;
						carry.push_back(&s);
					} else if (s.u != carry[0]->u) {
						carry.push_back(&s);
					} else if (s.r > carry[0]->r) {
						s.l = carry[0]->r + 1;
						Rs[s.l].insert({s.i, s});
						j = i->second.erase(j);
						continue;
					} else {
						s.u = s.d = s.l = s.r = 0;
						Rs[s.l].insert({s.i, s});
						j = i->second.erase(j);
						continue;
					}
				} else if (carry.size() == 2) {
					if (s.u != s.d && s.r >= carry[0]->r && s.r >= carry[1]->r) {
						carry[0]->r = s.l - 1;
						carry[1]->r = s.l - 1;
						carry.clear();
						carry.push_back(&s);
					} else if (s.u != s.d && s.r <= carry[0]->r && s.r <= carry[1]->r) {
						s.u = s.d = s.l = s.r = 0;
						Rs[s.l].insert({s.i, s});
						j = i->second.erase(j);
						continue;
					} else if (s.u != s.d) {
						s.l = min(carry[0]->r, carry[1]->r) + 1;
						s.u = s.d = (carry[0]->r > carry[1]->r ? 2 : 1);
						Rs[s.l].insert({s.i, s});
						j = i->second.erase(j);
						continue;
					} else if (s.r > carry[s.u - 1]->r) {
						s.l = carry[s.u - 1]->r + 1;
						Rs[s.l].insert({s.i, s});
						j = i->second.erase(j);
						continue;
					} else {
						s.u = s.d = s.l = s.r = 0;
						Rs[s.l].insert({s.i, s});
						j = i->second.erase(j);
						continue;
					}
				}
				j++;
			}
		}

		LL ans{0};
		for (auto &i : Rs) {
			if (i.first == 0) {
				continue;
			}
			for (auto j{i.second.begin()}; j != i.second.end();) {
				R &s{j->second};
				if (s.l > s.r) {
					s.u = s.d = s.l = s.r = 0;
					Rs[s.l].insert({s.i, s});
					j = i.second.erase(j);
					continue;
				} else {
					ans += (s.r - s.l + 1) * (s.d - s.u + 1);
				}
				j++;
			}
		}
		cout << ans << '\n';

		vector<R> ansR(N);
		for (auto &i : Rs) {
			for (auto j{i.second.begin()}; j != i.second.end(); j++) {
				R &s{j->second};
				ansR[s.i] = s;
			}
		}
		RF(i, 0, N) {
			cout << ansR[i].u << ' ' << ansR[i].l << ' ' << ansR[i].d << ' '
					 << ansR[i].r << '\n';
		}
	}

	return 0;
}
