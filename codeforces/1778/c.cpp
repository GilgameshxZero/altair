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

LL choose(
	vector<LL> &choice,
	LL upto,
	LL big,
	string &A,
	string &B,
	vector<char> &choices) {
	if (choice.size() - 1 == upto) {
		unordered_set<char> chosen;
		RF(i, 1, choice.size()) {
			chosen.insert(choices[choice[i]]);
		}
		LL seq{0}, ans{0};
		RF(i, 0, A.size()) {
			if (chosen.count(A[i]) || A[i] == B[i]) {
				seq++;
			} else {
				seq = 0;
			}
			ans += seq;
		}
		return ans;
	}

	LL ans{0};
	RF(i, choice.back() + 1, big) {
		choice.push_back(i);
		ans = max(ans, choose(choice, upto, big, A, B, choices));
		choice.pop_back();
	}
	return ans;
}

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
		LL N, K;
		cin >> N >> K;
		string A, B;
		cin >> A >> B;

		set<char> aD;
		RF(i, 0, A.size()) {
			aD.insert(A[i]);
		}
		vector<char> distinct(aD.begin(), aD.end());
		vector<LL> choice{-1};
		cout
			<< choose(
					 choice, min(K, (LL)distinct.size()), distinct.size(), A, B, distinct)
			<< '\n';
	}

	return 0;
}
