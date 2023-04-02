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

	int n,m;
	cin>>n>>m;
	vector<LL> s(n);
	for(int i=0;i<n;i++){
		cin>>s[i];
	}
	vector<LL> b(m);
	for(int i=0;i<m;i++){
		cin>>b[i];
	}

	map<LL, vector<LL>> d;
	for(int s1 : s) {
		d[s1] = vector<LL>(s1, -1);

		d[s1][0] = 0;
		set<pair<LL,LL>> q;
		q.emplace(0, 0);
		while(!q.empty()) {
			auto [dc, c] = *q.begin();
			q.erase(q.begin());
			for(int s2: s) {
				int nxt = (c + s2)%s1;
				if(d[s1][nxt] == -1 || d[s1][nxt] > dc + s2) {
					q.erase({d[s1][nxt], nxt});
					d[s1][nxt] = dc + s2;
					q.emplace(d[s1][nxt], nxt);
				}
			}
		}
	}

	for(LL bi: b) {
		int possible = 0;
		for(int s1: s) {
			if(d[s1][bi%s1] != -1 && d[s1][bi%s1] <= bi) {
				possible = 1;
				break;
			}
		}
		cout<<possible<<" ";
	}
	cout<<endl;

	return 0;
}
