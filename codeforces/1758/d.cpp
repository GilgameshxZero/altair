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
		if (N == 2) {
			cout << "1 3\n";
			continue;
		}
		bool done{false};
		LL ldiff{N - 1}, hdiff{99999999};
		while (!done) {
			LL mdiff{(ldiff + hdiff) / 2}, low{1}, high{1000000000 - mdiff + 1};

			{
				LL mid{low}, ab{mid}, ae{ab + mdiff},
					af{
						(ae - ab) * (ae - ab) - ab - ae - (ab + N - 3) * (ab + N - 2) / 2 +
						ab * (ab + 1) / 2};
				if (af <= ab + N - 3) {
					ldiff = mdiff;
					continue;
				}
			}

			{
				LL mid{high - 1}, ab{mid}, ae{ab + mdiff},
					af{
						(ae - ab) * (ae - ab) - ab - ae - (ab + N - 3) * (ab + N - 2) / 2 +
						ab * (ab + 1) / 2};
				if (af >= ae) {
					hdiff = mdiff;
					continue;
				}
			}

			while (low + 1 < high) {
				LL mid{(low + high) / 2}, ab{mid}, ae{ab + mdiff},
					af{
						(ae - ab) * (ae - ab) - ab - ae - (ab + N - 3) * (ab + N - 2) / 2 +
						ab * (ab + 1) / 2};
				if (af <= ab + N - 3) {
					high = mid;
				} else if (af >= ae) {
					low = mid;
				} else {
					cout << ab << ' ' << ae << ' ';
					RF(i, 1, N - 2) {
						cout << ab + i << ' ';
					}
					cout << af << '\n';
					done = true;
					break;
				}
			}
		}
	}

	return 0;
}
