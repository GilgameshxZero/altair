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

// Fixed-size Fenwick/Binary-Indexed Tree implementation. O(ln N) point
// updates and range queries. Not thread-safe.
//
// Value must support commutative addition. In addition, default
// initialization should be equivalent to "empty".
template <typename Value = long long>
class FenwickTree {
	private:
	std::vector<Value> tree;

	public:
	// Creates a Fenwick tree, which may be resized by operations.
	FenwickTree(std::size_t const size = 100001) : tree(size) {}

	// Computes prefix sum up to and including idx.
	Value sum(std::size_t const idx) const {
		Value aggregate{};
		for (std::size_t i = idx; i != SIZE_MAX; i &= i + 1, i--) {
			aggregate += this->tree[i];
		}
		return aggregate;
	}

	// Modify index by a delta.
	void modify(std::size_t const idx, Value const &delta) {
		for (std::size_t i = idx; i < this->tree.size(); i |= i + 1) {
			this->tree[i] += delta;
		}
	}
};

/* ---------------------------- End of template. ---------------------------- */

array<array<array<FenwickTree<LL>, 10>, 10>, 4> prc;

int main(int, char const *[]) {
#if !defined(ONLINEJUDGE) && (defined(__APPLE__) || defined(__MACH__))
	std::freopen("../build/i.default.txt", "r", stdin);
	std::freopen("../build/o.default.txt", "w", stdout);
#endif

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	string S;
	cin >> S;
	LL Q;
	cin >> Q;

	char cm[]{'A', 'T', 'G', 'C'};
	LL cmr[128];
	RF(i, 0, 4) {
		cmr[cm[i]] = i;
	}
	RF(j, 0, 10) {
		RF(l, 0, S.length()) {
			prc[cmr[S[l]]][j][l % (j + 1)].modify(l + 1, 1);
		}
	}

	RF(i, 0, Q) {
		LL T;
		cin >> T;
		if (T == 1) {
			LL X;
			char C;
			cin >> X >> C;
			X--;
			RF(i, 0, 10) {
				prc[cmr[S[X]]][i][X % (i + 1)].modify(X + 1, -1);
			}
			S[X] = C;
			RF(i, 0, 10) {
				prc[cmr[S[X]]][i][X % (i + 1)].modify(X + 1, 1);
			}
		} else {
			LL L, R;
			string E;
			cin >> L >> R >> E;
			L--;
			R--;
			LL ans{0};
			RF(i, 0, E.length()) {
				ans += prc[cmr[E[i]]][E.length() - 1][(L + i) % E.length()].sum(R + 1) -
					prc[cmr[E[i]]][E.length() - 1][(L + i) % E.length()].sum(L);
			}
			cout << ans << '\n';
		}
	}
	return 0;
}
