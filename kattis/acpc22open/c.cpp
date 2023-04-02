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

const LL maxn = 107;
LL C[maxn+1][maxn+1];
LL F[maxn+1];

int main(int, char const *[]) {
#if !defined(ONLINEJUDGE) && (defined(__APPLE__) || defined(__MACH__))
	std::freopen("../build/i.default.txt", "r", stdin);
	std::freopen("../build/o.default.txt", "w", stdout);
#endif

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);


	int n;
	cin>>n;

	if (n >= 12) {
		cout<<"JUST RUN!!"<<endl;
		return 0;
	}

	C[0][0] = 1;
	for(int n=1; n<=maxn; n++) {
		C[n][0] = C[n][n] = 1;
		for(int k=1; k<n; k++) {
			C[n][k] = C[n-1][k-1] + C[n-1][k];
		}
	}
	
	F[0] = 1;
	for(int i=1; i<=maxn; i++) {
		F[i] = F[i-1] * i;
	}


	
	LL ans = 0;
	for(int i=1;i<=n;i++) {
		ans += C[n][i] * F[i];
	}
	cout<<ans<<endl;

	return 0;
}
