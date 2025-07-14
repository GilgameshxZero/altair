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

class Node {
	public:
	array<Node *, 26> next;
	array<LL, 26> size;
};

int main(int, char const *[]) {
#if !defined(ONLINEJUDGE) && (defined(__APPLE__) || defined(__MACH__))
	std::freopen("../build/i.default.txt", "r", stdin);
	std::freopen("../build/o.default.txt", "w", stdout);
#endif

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	Node root;
	root.size.fill(0);
	LL N;
	cin >> N;
	vector<string> S(N);
	RF(i, 0, N) {
		cin >> S[i];

		Node *cur{&root};
		RF(j, 0, S[i].size()) {
			if (cur->size[S[i][j] - 'a'] == 0) {
				cur->next[S[i][j] - 'a'] = new Node;
				cur->next[S[i][j] - 'a']->size.fill(0);
			}
			cur->size[S[i][j] - 'a']++;
			cur = cur->next[S[i][j] - 'a'];
		}
	}
	RF(i, 0, N) {
		LL ans{0};
		Node *cur{&root};
		for (; ans < S[i].size(); ans++) {
			if (cur->size[S[i][ans] - 'a'] < 2) {
				break;
			}
			cur = cur->next[S[i][ans] - 'a'];
		}
		cout << ans << '\n';
	}

	return 0;
}
